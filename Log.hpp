//
// Created by zy on 11/18/17.
//

#ifndef HTTP_LOG_H
#define HTTP_LOG_H

#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>
#include <thread>
#include "Queue.hpp"
#include "Time.h"


class Log {

private:

    template <typename T>
    static void print(std::stringstream& buffer, T t)
    {
        buffer << t;
    }

    template <typename T, typename... Args>
    static void print(std::stringstream& buffer, T t, Args... args)
    {
        buffer << t;
        print(buffer, args...);
    }

public:
    static void setLogLevel(const std::string& log_level)
    {
        if(log_level == "debug")
            log_level_ = debug;
        else if(log_level == "normal")
            log_level_ = normal;
        else
            log_level_ = warn;
    }

    static void setLogRoot(const std::string& root)
    {
        root_ = root;
    }

    template <typename... Args>
    static void logDebug(Args... args)
    {
        if(log_level_ > debug)
            return;

        std::stringstream buffer;
        print(buffer, args...);

        std::string log_(buffer.str());

        queue_.push(log_);

        //std::cout << log_ << std::endl;
    }


    template <typename... Args>
    static void logNormal(Args... args)
    {
        if(log_level_ > normal)
            return;

        std::stringstream buffer;
        print(buffer, args...);

        std::string log_(buffer.str());

        queue_.push(log_);

        //std::cout << log_ << std::endl;
    }


    template <typename... Args>
    static void logWarn(Args... args)
    {
        std::stringstream buffer;
        print(buffer, args...);

        std::string log_(buffer.str());

        queue_.push(log_);

        //std::cout << log_ << std::endl;
    }


    static void start()
    {

        std::cout << __FILE__ << " " << __LINE__ << std::endl;
        *thread_id_ = std::thread(consumer);
        std::cout << __FILE__ << " " << __LINE__ << std::endl;
    }

private:

    enum logLevel{
        debug,
        normal,
        warn,
    };

    static void consumer()
    {
        std::cout << __FILE__ << " " << __LINE__ << std::endl;
        int len = 0; // max : 67108864
        std::ofstream file;
        while(true)
        {
            if(len == 0)
            {
                std::string file_name = root_ + Time::getNowTime();
                std::cout << __FILE__ << " " << __LINE__ << std::endl;
                file.open(file_name, std::ofstream::app);
                std::cout << __FILE__ << " " << __LINE__ << std::endl;
            }

            std::string log;
            queue_.wait_and_pop(log);

            file << log;
            len += log.size();

            if(len >= 67108864)
            {
                len = 0;
                file.close();
            }
        }
    }

    static logLevel log_level_;
    static std::string root_;
    static std::thread* thread_id_;
    static QueueThread<std::string> queue_;
};

Log::logLevel Log::log_level_ = debug;
std::string Log::root_ = {};
std::thread* Log::thread_id_ = nullptr;
QueueThread<std::string> Log::queue_{};

#endif //HTTP_LOG_H
