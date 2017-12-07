//
// Created by zy on 11/19/17.
//

#include "HttpServer.h"


HttpServer::HttpServer()
{
    tcp_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(tcp_sockfd != -1);

    int flags = 1;
    setsockopt(tcp_sockfd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &flags, sizeof(flags));
    //setsockopt(tcp_sockfd, IPPROTO_TCP, TCP_NODELAY, &flags, sizeof(flags));

    struct  sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(Configure::port);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    int tmp = 0;
    tmp = bind(tcp_sockfd, (struct sockaddr *)&server, sizeof(server));
    assert(tmp != -1);

    tmp = listen(tcp_sockfd, 1024);
    assert(tmp != -1);
}

void HttpServer::waitConnected()
{
    struct sockaddr_in client;
    socklen_t clientlen = sizeof(client);

    while(true)
    {
        int socketConnect = accept(tcp_sockfd, (struct sockaddr *)&client, &clientlen);

        // std::pair<uint32_t, sockfd>, 在epoll中
    }
}

void HttpServer::start()
{
    thread_id = std::thread(std::bind(&HttpServer::waitConnected, this));
}