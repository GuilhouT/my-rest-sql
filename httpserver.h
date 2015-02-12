#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
#include <QTcpServer>

class HttpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit HttpServer(quint16 port = 8000, QObject *parent = 0);
    void incomingConnection(int socket);
    ~HttpServer();

signals:

public slots:
};

#endif // HTTPSERVER_H
