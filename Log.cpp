//
// Created by zy on 11/18/17.
//

#include "Log.h"


////递归终止函数
//void print()
//{
//    cout << "empty" << endl;
//}
////展开函数
//template <class T, class ...Args>
//void print(T head, Args... rest)
//{
//    cout << "parameter " << head << endl;
//    print(rest...);
//}

template <class T>
void Log::print(T head)
{
    std::cout << head << std::endl;
}

template <class T, class... Args>
void Log::print(T head, Args... args)
{
    std::cout << head;
    print(args...);
};


template <class... Args>
void Log::printDebug(Args... args)
{
    if(Configure::log_level > Configure::debug)
        return;

    std::cout << Time::getNowTime() << " debug ";
    print(args...);
}

template <class... Args>
void Log::printNormal(Args... args)
{
    if(Configure::log_level > Configure::normal)
        return ;
    std::cout << Time::getNowTime() << " normal ";
    print(args...);
}

template <class... Args>
void Log::printWarn(Args... args)
{
    std::cout << Time::getNowTime() << " warn ";
    print(args...);
}

void Log::push()
{

}


void Log::size()
{

}

void Log::front()
{

}

void Log::pop()
{

}
