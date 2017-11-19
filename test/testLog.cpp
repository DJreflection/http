//
// Created by zy on 11/18/17.
//

#include <iostream>
#include "../Log.h"

int main()
{
    Log::printDebug("nihao", 1, " ", 23, " ", "hello");
    Log::printNormal("aa", " ", 1 , 2, "hell");
    Log::printWarn("sdfd", " sf", "sf ", 1 , 2, "hell");
    return 0;
}