//
// Created by zy on 17-12-9.
//

#ifndef HTTP_TCPCONNECTION_H
#define HTTP_TCPCONNECTION_H

#include <cstdint>
#include <cassert>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <rpc/types.h>
#include <arpa/inet.h>

class TcpConnection
{
public:
    TcpConnection(int32_t connectfd, struct sockaddr_in client);

    ssize_t readMessage(char* const buffer, const int32_t& buffer_len);
    ssize_t sendMessage(char* const buffer, const int32_t& message_len);

    int32_t getConnectFd();
    std::string getSrcAddr();

private:
    int32_t connectfd_;
    struct sockaddr_in client_;
    void* ptr;
};

#endif //HTTP_TCPCONNECTION_H
