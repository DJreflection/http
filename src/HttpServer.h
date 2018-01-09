//
// Created by zy on 11/19/17.
//

#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "TcpServer.h"
#include "Configure.h"
#include "log.h"

class HttpServer
{
private:
    class RecvHeader{
    public:
        std::string way;
        std::string url;
        std::string http_version;
        std::string host;
        std::string user_agent;
        std::string connection;
    };

    class SendHeader{
    public:
        std::string http_version;
        std::string status;
    };

public:
    HttpServer(const uint16_t& Port);

    void OnMessage(const TcpConnection& conn,const std::string& message);
    void start();

private:
    RecvHeader parseHeader(const std::string& message);
    TcpServer tcpServer;
};

#endif //HTTP_SERVER_H
