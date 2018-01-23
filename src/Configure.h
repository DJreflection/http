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
    explicit Configure() :
            uri_(),
            thread_number_(4),
            port_(80),
            root_("~/www/log/"),
            log_level_("debug")
    {}

    static Configure& getInstance()
    {
        static Configure tmp;
        return tmp;
    }

    void init()
    {
        std::ifstream file_reader(uri_);
        if(!file_reader.is_open())
        {
            std::cerr << "Path should set be first or File is not exit" << std::endl;
            exit(EXIT_FAILURE);
        }

        std::stringstream buffer;
        buffer << file_reader.rdbuf();
        file_reader.close();

        Json::Reader json_reader;
        Json::Value json_data;
        if(!json_reader.parse(buffer.str(), json_data))
        {
            std::cerr << "Config is unvalid" << std::endl;
            exit(EXIT_FAILURE);
        }

        if(json_data.isMember("thread_number") && json_data["thread_number"].isUInt())
            thread_number_ = static_cast<uint16_t >(json_data["thread_number"].asUInt());

        if(json_data.isMember("port") && json_data["port"].isUInt())
            port_ = static_cast<uint16_t >(json_data["port"].asUInt());

        if(json_data.isMember("root") && json_data["root"].isString())
            root_ = json_data["root"].asString();

        if(json_data.isMember("log_level") && json_data["log_level"].isString())
            log_level_ = json_data["log_level"].asString();
    }

    void setUri(const std::string& uri)
    {
        uri_ = uri;
    }

    uint16_t getThreadNum()
    {
        return thread_number_;
    }

    uint16_t getPort()
    {
        return port_;
    }

    std::string getRoot()
    {
        return root_;
    }
    std::string getLogLevel()
    {
        return log_level_;
    }

private:
    uint16_t thread_number_;
    uint16_t port_;
    std::string root_;
    std::string uri_;
    std::string log_level_;
};
#endif //HTTP_CONFIGURE_H
