//
// Created by zy on 7/27/17.
//

#ifndef HTT4_CONF_H
#define HTT4_CONF_H
#include <stdint.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 10240
#define EVENT_SIZE 10240

struct Conf{
    uint32_t PORT = 8080;
    uint32_t THREAD_SIZE = 3;
    char WWW[800];
    uint32_t _WWW_len = 0;
    uint32_t flag_log = 1;
};

struct Message{
    int connectfd;
    uint8_t flag = 0;
    char way[5];
    char request_uri[87];
    char time[26];
    uint16_t port;
    struct in_addr sin_addr;
    int err = 0;
};

void ReadConf(struct Conf &conf);
#endif //HTT4_CONF_H
