//
// Created by zy on 7/27/17.
//

#ifndef HTTP_CONFIGURE_H
#define HTTP_CONFIGURE_H

#include <stdint.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <jsoncpp/json/json.h>

class Configure
{
public:
    static uint32_t thread_number;
    static uint16_t port;
    static std::string root;
    static std::string log_level;
    static void readConfigure(const std::string &url);
};
#endif //HTTP_CONFIGURE_H
