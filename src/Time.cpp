//
// Created by zy on 11/18/17.
//


#include "Time.h"

const std::string Time::getNowTime() {

    struct timeval tm;
    gettimeofday(&tm, nullptr);
    struct tm *time_local;
    time_local = localtime(&tm.tv_sec);

    sprintf(buffer_, "%04d年%02d月%02d日%02d时%02d分%02d.%06ld秒",
            time_local->tm_year+1900,
            time_local->tm_mon+1,
            time_local->tm_mday,
            time_local->tm_hour,
            time_local->tm_min,
            time_local->tm_sec,
            tm.tv_usec
    );
    return std::string(buffer_);
}