//
// Created by zy on 17-11-17.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <jsoncpp/json/json.h>
#include "../src/Configure.h"

using namespace Json;

int main()
{
    Json::Value val;
    val["port"] = 8080;
    val["root"] = "~/Workspace/http/www";
    val["log_level"] = "debug";
    val["thread_number"] = 4;

    std::ofstream writer("../Config");
    writer << val.toStyledString();
    writer.close();

    Configure::getInstance().setUri("../Config");
    Configure::getInstance().init();

    std::cout << "thread_number :" << Configure::getInstance().getThreadNum() << std::endl;
    std::cout << "port :" << Configure::getInstance().getPort() << std::endl;
    std::cout << "root :" << Configure::getInstance().getRoot() << std::endl;
    std::cout << "log_level :" << Configure::getInstance().getLogLevel() << std::endl;
    return 0;
}