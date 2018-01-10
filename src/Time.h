//
// Created by zy on 11/18/17.
//

#ifndef HTTP_TIME_H
#define HTTP_TIME_H

#include <ctime>
#include <iostream>
#include <sys/time.h>

class Time
{
public:
    Time(): buffer_{"\0"}{};
    static Time& getInstance()
    {
        static Time tmp;
        return tmp;
    }
    const std::string getNowTime();

    const int32_t getNowYear()
    {
        time_t time_now = time(nullptr);
        struct tm *time_local;
        time_local = localtime(&time_now);
        return time_local->tm_year+1900;
    }

    const int32_t getNowMonth()
    {
        time_t time_now = time(nullptr);
        struct tm *time_local;
        time_local = localtime(&time_now);
        return time_local->tm_mon + 1;
    }
    const int32_t getNowMday()
    {
        time_t time_now = time(nullptr);
        struct tm *time_local;
        time_local = localtime(&time_now);
        return time_local->tm_mday;
    }

    const int32_t getNowYday()
    {
        time_t time_now = time(nullptr);
        struct tm *time_local;
        time_local = localtime(&time_now);
        return time_local->tm_yday;
    }

    const int32_t getNowHour()
    {
        time_t time_now = time(nullptr);
        struct tm *time_local;
        time_local = localtime(&time_now);
        return time_local->tm_hour;
    }

    const int32_t getNowMin()
    {
        time_t time_now = time(nullptr);
        struct tm *time_local;
        time_local = localtime(&time_now);
        return time_local->tm_min;
    }

    const int32_t getNowSec()
    {
        time_t time_now = time(nullptr);
        struct tm *time_local;
        time_local = localtime(&time_now);
        return time_local->tm_sec;
    }
private:
    char buffer_[64];
};

#endif //HTTP_TIME_H
