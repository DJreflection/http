//
// Created by zy on 11/18/17.
//

#include <iostream>
#include "../src/Time.h"

using namespace std;

int main()
{
    time_t time_timet = Time::getTimet();
    std::cout << time_timet << std::endl;

    std::cout << Time::timetToString(time_timet) << std::endl;

    string time_string = Time::getNowTime();
    std::cout << time_string << std::endl;
}