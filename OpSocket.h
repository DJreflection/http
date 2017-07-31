//
// Created by zy on 7/27/17.
//

#ifndef HTT4_OPSOCKET_H
#define HTT4_OPSOCKET_H

#include <stdint.h>

int InitTcpSocket(uint16_t port);
int SetSocketNoBlock(int sockfd);
int EpollOpSocket(int epfd, int sockfd, int op, void *message, uint32_t status);
#endif //HTT4_OPSOCKET_H
