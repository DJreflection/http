//
// Created by zy on 11/18/17.
//

#include <unistd.h>
#include <memory>
#include "../src/log.h"

int main()
{


    HTTP::log::getInstance().setLogRoot("/home/zy/Http/");
    HTTP::log::getInstance().setLogLevel("debug");
    HTTP::log::getInstance().start();

    LOG_DEBUG("fdskfd", 1234, "sdfks", "23424", "sdf", 1234);
    LOG_WARN("sdjskf", 1432.2342, "sfdfksl", "1432", "1324.23");
    LOG_NORMAL("sdjskf", 143892, "sdjkf", "1432", 234.23);
    LOG_ERROR("sdjskf", 1432.2342, "sfdfksl", "1432", "1324.23");

    sleep(2);
    HTTP::log::getInstance().stop();
    return 0;
}