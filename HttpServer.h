//
// Created by zy on 11/19/17.
//

#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "TcpServer.h"
#include "Configure.h"
#include "Log.hpp"

class HttpServer
{
public:
    HttpServer(const uint16_t& Port);
    void start();

private:
    TcpServer tcpServer;
};

#endif //HTTP_SERVER_H
