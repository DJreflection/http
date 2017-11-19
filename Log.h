//
// Created by zy on 11/18/17.
//

#ifndef HTTP_LOG_H
#define HTTP_LOG_H

#include <iostream>
#include <queue>
#include "Configure.h"
#include "Time.h"

class Log
{

private:
    static void print();
    template <class T, class... Args>
    static void print(T head, Args... args);

public:
    template <class... Args>
    static void printDebug(Args... args);

    template <class... Args>
    static void printNormal(Args... args);

    template <class... Args>
    static void printWarn(Args... args);

private:
    static void push();
    static void size();
    static void front();
    static void pop();

    static std::queue<std::string> log_queue;
};
#endif //HTTP_LOG_H
