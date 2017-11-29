//
// Created by zy on 11/18/17.
//

#include "../Log.hpp"



int main()
{
    Log::setLogLevel(Configure::debug);
    Log::print(Configure::debug, "%s %d %d %s", "nihao", 1, 23, "hello");
    Log::print(Configure::normal, "%s %d %d %s", "aa", 1 , 2, "hell");
    Log::print(Configure::warn, "%s %s %s %d %d %s", "sdfd", " sf", "sf ", 1 , 2, "hell");
    return 0;
}