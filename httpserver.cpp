#include "httpserver.h"
#include "webservice.h"

HttpServer::HttpServer(quint16 port, QObject *parent) : QTcpServer(parent)
{
    QTcpServer *server = new QTcpServer(this);
    WebService *webservice1 = new WebService();

    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
    connect(server, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(server, SIGNAL(disconnected()), this, SLOT(discardClient()));

    if(!listen(QHostAddress::LocalHost, port))
    {
        qDebug() << "Server could not start!";
    }
    else
    {
        qDebug() << "Server listenning...";
    }
}

void HttpServer::incomingConnection(int socket)
{
    if (disabled)
        return;
    // When a new client connects, the server constructs a QTcpSocket and all
    // communication with the client is done over this QTcpSocket. QTcpSocket
    // works asynchronously, this means that all the communication is done
    // in the two slots readClient() and discardClient().
    QTcpSocket* s = new QTcpSocket(this);
    connect(s, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(s, SIGNAL(disconnected()), this, SLOT(discardClient()));
    s->setSocketDescriptor(socket);
    //QtServiceBase::instance()->logMessage("New Connection");
}

void HttpServer::pause()
{
    disabled = true;
}

void HttpServer::resume()
{
    disabled = false;
}

void HttpServer::readClient()
{
    if (disabled)
        return;
    // This slot is called when the client sent data to the server. The
    // server looks if it was a get request and sends a very simple HTML
    // document back.
    QTcpSocket* socket = (QTcpSocket*)sender();
    if (socket->canReadLine()) {
        QStringList tokens = QString(socket->readLine()).split(QRegExp("[ \r\n][ \r\n]*"));
        if (tokens[0] == "GET")
        {

            webservice1->get(socket);
            socket->close();
            //QtServiceBase::instance()->logMessage("Wrote to client");
            if (socket->state() == QTcpSocket::UnconnectedState)
            {
                delete socket;
                //QtServiceBase::instance()->logMessage("Connection closed");
            }
        }
        if (tokens[0] == "POST")
        {
            webservice1->create();
        }
        if (tokens[0] == "DELETE")
        {
            //webservice1->destroy(id);
        }
        if (tokens[0] == "PUT" || tokens[0] == "PATCH")
        {
            //webservice1->update(id);
        }
    }
}

void HttpServer::discardClient()
{
    qDebug() << "discardClient";
    QTcpSocket* socket = (QTcpSocket*)sender();
    socket->deleteLater();

    //QtServiceBase::instance()->logMessage("Connection closed");
}

HttpServer::~HttpServer()
{

}

