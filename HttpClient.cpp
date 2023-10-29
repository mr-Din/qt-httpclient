#include "HttpClient.h"

HttpClient::HttpClient(QString ip, QObject *parent)
    : QObject{parent}
    , m_ip(ip)
    , m_network_manager(new QNetworkAccessManager(this))
    , m_current_reply(nullptr)
{
    connect(m_network_manager, &QNetworkAccessManager::finished, this, &HttpClient::onReplyFinished);
}

void HttpClient::sendGetRequest(const QString &endpoint)
{
    QNetworkRequest request;
    request.setUrl(QUrl("https://" + m_ip + "/" + endpoint));

    QNetworkReply* reply = m_network_manager->get(request);
    connect(reply, &QNetworkReply::errorOccurred, this, &HttpClient::onReplyError);

    m_current_reply = reply;
}

void HttpClient::sendPostRequest(const QString &endpoint, const QByteArray &data)
{
    QNetworkRequest request;
    request.setUrl(QUrl("https://" + m_ip + "/" + endpoint));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");

    QNetworkReply* reply = m_network_manager->post(request, data);
    connect(reply, &QNetworkReply::errorOccurred, this, &HttpClient::onReplyError);

    m_current_reply = reply;
}

void HttpClient::onReplyFinished(QNetworkReply *reply)
{
    int status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (status_code == 200)
    {
        QByteArray response = reply->readAll();
        emit sigRequestFinished(response);
    }
    else if (status_code == 404)
    {
        emit sigRequestFinished("Endpoint not found");
    }
    else if (status_code == 500)
    {
        emit sigRequestFinished("Internal server error");
    }

    reply->deleteLater();
}

void HttpClient::onReplyError(QNetworkReply::NetworkError error)
{
    QString error_str;

    switch (error)
    {
    case QNetworkReply::ConnectionRefusedError:
        error_str = "Connection refused";
        break;
    case QNetworkReply::RemoteHostClosedError:
        error_str = "Remote host closed";
        break;
    case QNetworkReply::HostNotFoundError:
        error_str = "Host not found";
        break;
    case QNetworkReply::TimeoutError:
        error_str = "Request timed out";
        break;
    default:
        error_str = "Unknown error";
        break;
    }

    emit sigRequestError(error_str);

    if (m_current_reply)
        m_current_reply->deleteLater();
}
