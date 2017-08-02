//
// Created by zy on 7/27/17.
//
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include "Conf.h"


int InitTcpSocket(const uint16_t port){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        perror("TcpSocket created failed\n");
        exit(0);
    }
    int flags = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &flags, sizeof(flags));
    setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &flags, sizeof(flags));

    struct  sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(port);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0){
        perror("Bind failed\n");
        close(sockfd);
        exit(0);
    }

    if(listen(sockfd, 10240) < 0){
        perror("Listen failed\n");
        close(sockfd);
        exit(0);
    }
    return sockfd;
}

int SetSocketNoBlock(int sockfd){
    int status_old;
    if((status_old = fcntl(sockfd, F_GETFL, 0)) < 0){
        return errno;
    }
    if(fcntl(sockfd, F_SETFL, status_old | O_NONBLOCK) < 0){
        return errno;
    }
    return 0;
}

int EpollOpSocket(int epfd, int sockfd, int op, void *msg, uint32_t status){
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = status;
    ev.data.ptr = msg;
    if(epoll_ctl(epfd, op, sockfd, &ev) == -1){
        return errno;
    }
    return 0;
}
