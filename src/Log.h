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
#include <memory>
#include <atomic>
#include <sstream>

#include "Queue.h"
#include "Time.h"

class Log {
public:
    enum LogLevel{
        debug,
        normal,
        warn,
        error,
    };

    Log(): log_level_(debug),
           root_{},
           thread_id_(nullptr),
           queue_{},
           running_(false)
    {};

    ~Log(){
        if(running_)
        {
            stop();
        }
    }

    void setLogLevel(const std::string& log_level)
    {
        if(log_level == "debug")
            log_level_ = debug;
        else if(log_level == "normal")
            log_level_ = normal;
        else if(log_level == "warn")
            log_level_ = warn;
        else
            log_level_ = error;
    }

    void setLogRoot(const std::string& root)
    {
        root_ = root;
    }

    template <typename... Args>
    void doLog(const LogLevel& log_level, Args... args)
    {
        if(log_level < log_level_)
            return;

        std::stringstream buffer;
        print(buffer, args...);
        std::string log_(buffer.str());
        queue_.push(log_);
    }

    static Log& getInstance()
    {
        static Log tmp;
        return tmp;
    }

    void start()
    {
        running_ = true;
        thread_id_ = std::make_shared<std::thread>(std::bind(&Log::consumer, this));
    }

    void stop()
    {
        running_ = false;
        if(thread_id_.get()->joinable())
        {
            thread_id_.get()->join();
        }
    }

private:
    template <typename T>
    void print(std::stringstream& buffer, T t)
    {
        buffer << t << std::endl;
    }

    template <typename T, typename... Args>
    void print(std::stringstream& buffer, T t, Args... args)
    {
        buffer << t << " ";
        print(buffer, args...);
    }

    void consumer()
    {
        int len = 0; // max : 67108864
        std::ofstream file;
        while(running_)
        {
            if(len == 0)
            {
                std::string file_name = root_ + Time::getInstance().getNowTime() + ".log";
                file.open(file_name, std::ofstream::app);
            }

            std::string log;
            queue_.wait_seconds_to_pop(log);
            if(log.empty())
            {
                continue;
            }

            file << log;
            len += log.size();

            if(len >= 67108864)
            {
                len = 0;
                file.close();
            }
        }
        file.flush();
        file.close();
    }

    LogLevel log_level_;
    std::string root_;
    std::shared_ptr<std::thread> thread_id_;
    QueueThread<std::string> queue_;
    std::atomic_bool running_;
};

#define LOG_DEBUG(args...) Log::getInstance().doLog(Log::debug, __FILE__, __LINE__, Time::getInstance().getNowTime(), "debug", args)
#define LOG_NORMAL(args...)  Log::getInstance().doLog(Log::normal, __FILE__, __LINE__, Time::getInstance().getNowTime(), "normal", args)
#define LOG_WARN(args...) Log::getInstance().doLog(Log::warn, __FILE__, __LINE__, Time::getInstance().getNowTime(), "warn", args)
#define LOG_ERROR(args...) Log::getInstance().doLog(Log::error, __FILE__, __LINE__, Time::getInstance().getNowTime(), "error", args)

#endif //HTTP_LOG_H
