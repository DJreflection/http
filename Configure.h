//
// Created by zy on 7/27/17.
//

#ifndef HTTP_CONFIGURE_H
#define HTTP_CONFIGURE_H

#include <stdint.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>

#define BUF_SIZE 10240
#define EVENT_SIZE 10240


#include <fstream>
#include <sstream>
#include <jsoncpp/json/json.h>

class Configure
{
private:
    const static std::string debug_("debug");
    const static std::string normal_("normal");
    const static std::string warn_("warn");

public:
    static uint32_t buffer_size;
    static uint16_t event_size;
    static uint16_t port;
    static std::string root;
    static enum logLevel;

    static logLevel log_level;
    static void readConfigure(std::string &&url);
    static void printConfigure();
};


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
#endif //HTTP_CONFIGURE_H
