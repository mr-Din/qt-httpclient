#pragma once

#include <QObject>

#include <QtNetwork/QtNetwork>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

class HttpClient : public QObject
{
    Q_OBJECT
public:
    explicit HttpClient(QString ip = "192.168.0.1", QObject *parent = nullptr);

public:
    void sendGetRequest(const QString& endpoint);
    void sendPostRequest(const QString& endpoint, const QByteArray& data);

private slots:
    void onReplyFinished(QNetworkReply* reply);
    void onReplyError(QNetworkReply::NetworkError error);

signals:
    void sigRequestFinished(const QByteArray &response);
    void sigRequestError(const QString &error);

private:
    QString m_ip;
    QNetworkAccessManager* m_network_manager;
    QNetworkReply* m_current_reply;
};

