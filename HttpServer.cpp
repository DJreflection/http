//
// Created by zy on 11/19/17.
//

#include "HttpServer.h"


HttpServer::HttpServer()
{
    tcp_sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    assert(tcp_sockfd_ != -1);

    int flags = 1;
    setsockopt(tcp_sockfd_, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &flags, sizeof(flags));
    //setsockopt(tcp_sockfd, IPPROTO_TCP, TCP_NODELAY, &flags, sizeof(flags));

    struct  sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(Configure::port);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    int tmp = 0;
    tmp = bind(tcp_sockfd_, (struct sockaddr *)&server, sizeof(server));
    assert(tmp != -1);

    tmp = listen(tcp_sockfd_, 1024);
    assert(tmp != -1);
}

void HttpServer::waitConnected()
{
    struct sockaddr_in client;
    socklen_t clientlen = sizeof(client);

    int take_turn = 0;
    while(true)
    {
        int socketConnect = accept(tcp_sockfd_, (struct sockaddr *)&client, &clientlen);

        // std::pair<uint32_t, sockfd>, 在epoll中

        using msg = std::pair<uint32_t , int32_t >;
        std::shared_ptr<msg> tmp{std::make_shared<msg>(std::make_pair(client.sin_addr.s_addr, socketConnect))};

        thread_pool_[take_turn].epollAddSocket()
    }
}

void HttpServer::start()
{
    thread_id = std::thread(std::bind(&HttpServer::waitConnected, this));

    for(int i=0; i<Configure::thread_number; ++ i)
    {
        thread_pool_[i].startListenSocket();
    }
}