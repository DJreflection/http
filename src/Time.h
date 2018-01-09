//
// Created by zy on 11/18/17.
//

#ifndef HTTP_TIME_H
#define HTTP_TIME_H

#include <ctime>
#include <iostream>

class Time
{
public:
    static const time_t getTimet();
    static const std::string getNowTime();
    static const std::string timetToString(const time_t &time);

private:
    static char buffer[64];
};

#endif //HTTP_TIME_H
