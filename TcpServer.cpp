//
// Created by zy on 17-12-12.
//

#include "TcpServer.h"


TcpServer::TcpServer(const uint16_t& Port) {
    tcp_sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    assert(tcp_sockfd_ != -1);

    int flags = 1;
    setsockopt(tcp_sockfd_, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &flags, sizeof(flags));
    //setsockopt(tcp_sockfd, IPPROTO_TCP, TCP_NODELAY, &flags, sizeof(flags));

    struct  sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(Port);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    int tmp = 0;
    tmp = bind(tcp_sockfd_, (struct sockaddr *)&server, sizeof(server));
    assert(tmp != -1);

    tmp = listen(tcp_sockfd_, 1024);
    assert(tmp != -1);
}

void TcpServer::start() {

}