//
// Created by zy on 11/19/17.
//

#ifndef HTTP_TCPSERVER_H
#define HTTP_TCPSERVER_H

#include <sys/socket.h>
#include <thread>
#include <cstring>
#include <assert.h>
#include <arpa/inet.h>
#include "EpollThread.h"
#include "Configure.h"
#include "Log.hpp"

class HttpServer
{
public:
    HttpServer();
    void start();

private:
    void waitConnected();
    int tcp_sockfd_;
    std::thread thread_id;
    std::vector<EpollThread> thread_pool_{Configure::thread_number};
};
#endif //HTTP_TCPSERVER_H
