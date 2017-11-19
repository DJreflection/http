//
// Created by zy on 7/27/17.
//
#include "Configure.h"

const uint32_t Configure::buffer_size = 10240;
const uint32_t Configure::event_size = 1024;
uint16_t Configure::port = 8080;
uint32_t Configure::thread_number = 4;

std::string Configure::root = "~/Workspace/http/www/";

Configure::logLevel Configure::log_level = debug;

void Configure::readConfigure(std::string &&url)
{
    std::cout << url << std::endl;

    try{
        std::stringstream json_value;
        std::ifstream reader(url);
        json_value << reader.rdbuf();
        reader.close();

        Json::Reader reader_json;
        Json::Value val;

        if(!reader_json.parse(json_value.str(), val))
        {
            std::cout << "url unvalid" << std::endl;
            return ;
        }

        thread_number = val["thread_number"].asUInt();
        port = val["port"].asUInt();
        root = val["root"].asString();

        std::string &&log_level_tmp = val["log_level"].asString();
        if(log_level_tmp == "warn")
            log_level = warn;
        else if(log_level_tmp == "normal")
            log_level = normal;
        else
            log_level = debug;
    }
    catch (...){
        std::cout << "error" << std::endl;
    }
}

void Configure::printConfigure()
{
    if(log_level != debug)
        return ;
    std::cout << "buffer_size :" << buffer_size << std::endl;
    std::cout << "event_size :" << event_size << std::endl;
    std::cout << "thread_number :" << thread_number << std::endl;
    std::cout << "port :" << port << std::endl;
    std::cout << "root :" << root << std::endl;
    std::cout << "log_level :" << log_level << std::endl;
}