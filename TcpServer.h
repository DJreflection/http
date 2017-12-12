//
// Created by zy on 17-12-12.
//

#ifndef HTTP_TCPSERVER_H
#define HTTP_TCPSERVER_H

#include <cstdint>
#include <cassert>
#include <cstring>
#include <thread>
#include <netinet/in.h>
#include <sys/socket.h>


class TcpServer
{
public:
    TcpServer(const uint16_t& Port);


    void start();
private:
    int32_t tcp_sockfd_;
    std::shared_ptr<std::thread> thread_id;
};
#endif //HTTP_TCPSERVER_H
