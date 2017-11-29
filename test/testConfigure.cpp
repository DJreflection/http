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

    //std::cout << val.toStyledString() << std::endl;
    // /home/zy/Documents/http/test/tt

    std::ofstream writer("/home/zy/Documents/github/http/test/tt");
    writer << val.toStyledString();
    writer.close();

    Configure::readConfigure("/home/zy/Documents/github/http/test/tt");
    Configure::printConfigure();
    return 0;
}