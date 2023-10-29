#include "HttpHandler.h"

HttpHandler::HttpHandler(QObject *parent)
    : QObject{parent}
    , m_http_client(new HttpClient("", this))
    , m_data(QByteArray())
{
    // Где-то происходит парсинг данных и получение m_data
}

void HttpHandler::makeRequest()
{
    connect(m_http_client, &HttpClient::sigRequestFinished, this, &HttpHandler::onProcessResponse);
    connect(m_http_client, &HttpClient::sigRequestError, this, &HttpHandler::onHandleError);

    // Пример GET
    m_http_client->sendGetRequest("/endpoint");
    // Пример POST
    m_http_client->sendPostRequest("/endpoint", m_data);
}

void HttpHandler::onProcessResponse(const QByteArray &response)
{
    // Обработка ответа
}

void HttpHandler::onHandleError(const QString &error)
{
    // Обработка ошибки
}
