//
// Created by zy on 11/18/17.
//

#include <unistd.h>
#include <memory>
#include "../src/Log.h"

int main()
{
    Log::getInstance().setLogRoot("/home/zy/Http/");
    Log::getInstance().setLogLevel("debug");

    Log::getInstance().start();
    Log::getInstance().logDebug("fdskfd",1234, "sdfks", "23424", "sdf ", 1234);
    Log::getInstance().logNormal("sdjskf", 143892, "sdjkf", "1432", 234.23);
    Log::getInstance().logWarn("sdjskf", 1432.2342, "sfdfksl", "1432", "1324.23");
    sleep(10);
    return 0;
}