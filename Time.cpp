//
// Created by zy on 11/18/17.
//

#include "Time.h"


const time_t Time::getTimet() {
    return time(nullptr);
}

const std::string Time::getNowTime() {
    time_t time_timet = time(nullptr);

    struct tm *time_local;
    time_local = localtime(&time_timet);

    sprintf(buffer, "%04d年%02d月%02d日%02d:%02d:%02d",
            time_local->tm_year+1900,
            time_local->tm_mon+1,
            time_local->tm_mday,
            time_local->tm_hour,
            time_local->tm_min,
            time_local->tm_sec
    );

    return std::string(buffer, 26);
}

const std::string Time::timetToString(const time_t &time)
{
    struct tm *local_time;
    local_time = localtime(&time);

    sprintf(buffer, "%04d年%02d月%02d日%02d:%02d:%02d",
            local_time->tm_year+1900,
            local_time->tm_mon+1,
            local_time->tm_mday,
            local_time->tm_hour,
            local_time->tm_min,
            local_time->tm_sec
    );

    return std::string(buffer, 25);
}

char Time::buffer[64] = {};