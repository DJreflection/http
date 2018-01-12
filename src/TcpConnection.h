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
#include "Buffer.h"
#include "Log.h"

class TcpConnection
{
public:
    TcpConnection(int32_t connectfd, struct sockaddr_in client);

    Buffer read_buffer_;
    Buffer writ_buffer_;

    void readMessage()
    {
        char buffer[1024];
        ssize_t read_bytes = ::read(connectfd_, buffer, 1024);
        if(read_bytes < 0)
        {
            LOG_ERROR("read_bytes < 0");
            return;
        }
        if(read_bytes == 0)
            valid_ = false;

        read_buffer_.append(buffer, read_bytes);
    }

    void writMessage()
    {
        ssize_t writ_bytes = ::write(connectfd_, writ_buffer_.beginRead(), writ_buffer_.readableBytes());
        if(writ_bytes < 0)
        {
            LOG_ERROR("writ_bytes < 0");
            return;
        }
        writ_buffer_.retrieve(writ_bytes);
    }

    std::string read()
    {
        if(read_buffer_.findCRLF() != nullptr)
            return std::string(read_buffer_.beginRead(), read_buffer_.readableBytes());
    }

    void setEvents(int status)
    {
        events = status;
    }

    int32_t getConnectFd(){
        return connectfd_;
    }

    std::string getSrcAddr(){
        return std::string{inet_ntoa(client_.sin_addr)};
    }

    void setBekill()
    {
        valid_ = false;
    }

    bool isValid()
    {
        valid_ = true;
    }

private:
    int32_t connectfd_;
    struct sockaddr_in client_;
    int events;
    bool valid_;
};

#endif //HTTP_TCPCONNECTION_H
