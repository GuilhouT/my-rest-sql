#include "webservice.h"

WebService::WebService()
{

}

void WebService::get(QTcpSocket * socket)
{
    QTextStream os(socket);
    // Build your JSON string as usual
    QByteArray jsonString = "{\"method\":\"AuthenticatePlain\",\"loginName\":\"username@domain.com\",\"password\":\"mypass\"}";

    // For your "Content-Length" header
//    QByteArray postDataSize = QByteArray::number(jsonString.size());

//    // Time for building your request
//    QUrl serviceURL("https://www.superService.com/api/1.7/ssapi.asmx");
//    QNetworkRequest request(serviceURL);

    // Add the headers specifying their names and their values with the following method : void QNetworkRequest::setRawHeader(const QByteArray & headerName, const QByteArray & headerValue);
//    request.setRawHeader("User-Agent", "My app name v0.1");
//    request.setRawHeader("X-Custom-User-Agent", "My app name v0.1");
//    request.setRawHeader("Content-Type", "application/json");
//    request.setRawHeader("Content-Length", postDataSize);
    os.setAutoDetectUnicode(true);

    os << "HTTP/1.0 200 Ok\r\n"
          "Content-Type: application/json; charset=\"utf-8\"\r\n"
          "\r\n"
       <<  jsonString << "\n";
}

void WebService::create()
{

}

void WebService::update(int id)
{

}

void WebService::destroy(int id)
{

}

WebService::~WebService()
{

}

