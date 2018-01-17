//
// Created by zy on 17-12-12.
//

#include "TcpServer.h"

TcpServer::TcpServer(const uint16_t& port) : thread_number_(4), port_(port) {
    tcp_sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp_sockfd_ == -1)
    {
        LOG_ERROR("Create socket failed!");
        exit(EXIT_FAILURE);
    }

    int flags = 1;
    if(setsockopt(tcp_sockfd_, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &flags, sizeof(flags)) != 0)
    {
        LOG_ERROR("setsockopt error!");
    }

    struct  sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(port_);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(tcp_sockfd_, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        LOG_ERROR("bind failed");
        exit(EXIT_FAILURE);
    }

    if(listen(tcp_sockfd_, 1024) != 0)
    {
        LOG_ERROR("listen failed");
        exit(EXIT_FAILURE);
    }
}


void TcpServer::setThreadNum(const uint16_t& number)
{
    thread_number_ = number;
}


void TcpServer::setOnMessageCallBack(const MessageCallBack_& messageCallBack) {
    messageCallBack_ = messageCallBack;
}

void TcpServer::start() {

    for(int i=0; i<thread_number_; ++ i)
    {
        std::shared_ptr<EventLoop> tmp = std::make_shared<EventLoop>();
        thread_pool_.emplace_back(tmp);
    }

    for(int i=0; i<thread_number_; ++ i)
        thread_pool_[i]->startLoop();

    struct sockaddr_in client;
    socklen_t clientlen = sizeof(client);

    int take_turn = 0;
    while(true)
    {
        int socketConnect = accept(tcp_sockfd_, (struct sockaddr *)&client, &clientlen);

        TcpConnection *connect_info = new TcpConnection(socketConnect, client);
        if(!thread_pool_[take_turn]->addListenReadableEvent(socketConnect, connect_info))
        {
            delete(connect_info);
            continue;
        }

        if(++ take_turn == thread_pool_.size())
            take_turn = 0;
    }
}