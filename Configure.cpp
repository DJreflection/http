//
// Created by zy on 7/27/17.
//
#include "Configure.h"

uint16_t Configure::port = 8080;
uint32_t Configure::thread_number = 4;

std::string Configure::root = "~/Workspace/http/www/";

std::string Configure::log_level = "debug";

void Configure::readConfigure(const std::string &url)
{
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
        log_level = val["log_level"].asString();
    }
    catch (...){
        std::cout << "error" << std::endl;
    }
}
