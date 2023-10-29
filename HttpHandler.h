#pragma once

#include "HttpClient.h"

#include <QObject>

class HttpHandler : public QObject
{
    Q_OBJECT
public:
    HttpHandler(QObject *parent = nullptr);

public:
    void makeRequest();

private slots:
    void onProcessResponse(const QByteArray &response);
    void onHandleError(const QString& error);

private:
    HttpClient* m_http_client;
    QByteArray m_data;
};

