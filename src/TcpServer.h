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

#include "TcpConnection.h"
#include "Log.h"

class TcpServer
{
public:
    typedef std::function<void (const TcpConnection& Conn, const std::string &message)> MessageCallBack_;

    TcpServer(const uint16_t& Port);
    void setThreadNum(const uint16_t& number);
    void setOnMessageCallBack(const MessageCallBack_& messageCallBack);
    void start();

private:

    class EpollThread
    {
    public:
        EpollThread();

        void epollAddSocket(const int& socketfd, void* const message, const uint32_t& status);
        void epollModSocket(const int& socketfd, const uint32_t& new_status);
        void setOnMessageCallBack(const MessageCallBack_& messageCallBack);
        void startListenSocket();

    private:
        void setNoBlock(int socketfd);
        void listenSocket();

        // epoll descriptor
        int epollfd_;

        // thread ID
        std::shared_ptr<std::thread> thread_id_;

        // OnMessage Call Back
        MessageCallBack_ messageCallBack_;

        // event_size and buffer_size
        static const uint32_t EVENTSIZE;
        static const uint32_t BUFFERSIZE;
    };

    // thread number
    uint16_t thread_number;

    // Tcp socket
    int32_t tcp_sockfd_;

    // OnMessage Call back
    MessageCallBack_ messageCallBack_;
    std::vector<std::shared_ptr<EpollThread>> thread_pool;
};

#endif //HTTP_TCPSERVER_H
