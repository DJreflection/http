//
// Created by zy on 17-11-17.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <jsoncpp/json/json.h>
#include <zconf.h>

using namespace Json;


class Configure
{
public:
    static uint32_t buffer_size;
    static uint16_t event_size;
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

uint32_t Configure::buffer_size = 10240;
uint16_t Configure::event_size = 1024;
uint16_t Configure::port = 8080;
std::string Configure::root = "~/Workspace/http/www/";

Configure::logLevel Configure::log_level = debug;

void Configure::readConfigure(std::string &&url)
{
    try{
        std::ifstream reader(url);
        std::stringstream json_value;
        json_value << reader.rdbuf();

        Json::Reader json_read;
        Json::Value val;
        if(!json_read.parse(json_value.str(), val))
            return ;

        buffer_size = val["buffer_size"].asUInt();
        event_size = val["event_size"].asUInt();
        port = val["port"].asInt();
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
    std::cout << "buffer_size :" << buffer_size << std::endl;
    std::cout << "event_size :" << event_size << std::endl;
    std::cout << "port :" << port << std::endl;
    std::cout << "root :" << root << std::endl;
}



int main()
{
    Json::Value val;
    val["buffer_size"] = 88888;
    val["event_size"] = 888;
    val["port"] = 12345;
    val["root"] = "~/Workspace/http/www";
    val["log_level"] = "normal";

    std::ofstream writer("/home/zy/Documents/github/http/test/tt");
    writer << val.toStyledString();
    writer.close();

    Configure::readConfigure("/home/zy/Documents/github/http/test/tt");

    Configure::printConfigure();
    return 0;
}