//
// Created by zy on 11/19/17.
//

#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "TcpServer.h"
#include "Configure.h"
#include "Log.h"

class HttpServer
{
private:
    class RecvHeader{
    public:
        std::string way_;
        std::string url_;
        std::string http_version_;
        std::string host_;
        std::string user_agent_;
        std::string connection_;
    };

    class SendHeader{
    public:
        std::string http_version_;
        std::string status_;
    };

public:
    HttpServer(const uint16_t& Port);

    void OnMessage(const TcpConnection& conn,const std::string& message);
    void start();

private:
    RecvHeader parseHeader(const std::string& message);
    TcpServer tcp_server_;

    std::string root_;
};

#endif //HTTP_SERVER_H
