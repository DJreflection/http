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
public:
    static const uint32_t buffer_size;
    static const uint32_t event_size;
    static uint32_t thread_number;
    static uint16_t port;
    static std::string root;
    enum logLevel{
        debug,
        normal,
        warn,
    };

    static logLevel log_level;
    static void readConfigure(std::string &&url);
    static void printConfigure();
};
void ReadConf(struct Conf &conf);
#endif //HTTP_CONFIGURE_H
