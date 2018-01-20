//
// Created by zy on 17-12-12.
//

#ifndef HTTP_TCPSERVER_H
#define HTTP_TCPSERVER_H

#include <cstdint>
#include <cassert>
#include <cstring>
#include <thread>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "EventLoop.h"
#include "Time.h"
#include "TcpConnection.h"
#include "Log.h"

class TcpServer
{
public:
    typedef std::function<void (TcpConnection& Conn, Buffer &buffer)> MessageCallBack_;

    TcpServer(const uint16_t& Port);
    ~TcpServer(){
        for(auto& i: thread_pool_)
        {
            i->stopLoop();
        }
    }

    void setThreadNum(const uint16_t& number);
    void setOnMessageCallBack(const MessageCallBack_& messageCallBack);
    void start();

private:

    // thread number
    uint16_t thread_number_;

    // Tcp socket
    int32_t tcp_sockfd_;
    uint16_t port_;

    // OnMessage Call back
    MessageCallBack_ message_call_back_;
    std::vector<std::shared_ptr<EventLoop>> thread_pool_;
};

#endif //HTTP_TCPSERVER_H
