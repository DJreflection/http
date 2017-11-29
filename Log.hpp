//
// Created by zy on 11/18/17.
//

#ifndef HTTP_LOG_H
#define HTTP_LOG_H

#include <iostream>
#include <queue>
#include <cstring>
#include <thread>
#include "Queue.hpp"
#include "Configure.h"
#include "Time.h"


class Log {

public:
    static void setLogLevel(int log_level)
    {
        log_level_ = log_level;
    }

    static void setLogRoot(const std::string& root)
    {
        root_ = root;
    }

    template <typename... Args>
    static void print(int log_level, const std::string &pattern, Args... args)
    {
        if(log_level_ > log_level)
            return;

        memset(buffer, 0, sizeof(buffer));
        try {
            sprintf(buffer, pattern.data(), args...);
        }
        catch (...){
            std::cout << "invalid pattern" << std::endl;
            return;
        }

        std::string log{Time::getNowTime() + " "};

        log += std::string{buffer};
        //std::cout << log << std::endl;
        queue_.push(log);
    }

    static void start()
    {
        *thread_id_ = std::thread(consumer);
    }

private:

    static void consumer()
    {
        int len = 0;
        while(true)
        {
            if(len == 0)
            {

            }
        }
    }

    static char buffer[4096];
    static int log_level_;
    static std::string root_;
    static std::thread* thread_id_;
    static QueueThread<std::string> queue_;
};

int Log::log_level_ = 0;
char Log::buffer[4096] = {};
std::string Log::root_ = {};
std::thread* Log::thread_id_ = nullptr;
QueueThread<std::string> Log::queue_{};

#endif //HTTP_LOG_H
