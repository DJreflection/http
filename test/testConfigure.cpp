//
// Created by zy on 17-11-17.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <jsoncpp/json/json.h>
#include "../Configure.h"

using namespace Json;

int main()
{
    Json::Value val;
    val["port"] = 12345;
    val["root"] = "~/Workspace/http/www";
    val["log_level"] = "debug";
    val["thread_number"] = 4;

    std::ofstream writer("../test/tt");
    writer << val.toStyledString();
    writer.close();

    Configure::readConfigure("../test/tt");

    std::cout << "thread_number :" << Configure::thread_number << std::endl;
    std::cout << "port :" << Configure::port << std::endl;
    std::cout << "root :" << Configure::root << std::endl;
    std::cout << "log_level :" << Configure::log_level << std::endl;
    return 0;
}