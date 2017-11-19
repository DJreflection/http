//
// Created by zy on 11/18/17.
//

#include "Log.h"

//void print()
//{
//    std::cout << std::endl;
//}
//
//template <class T, class... Args>
//void print(T head, Args... args)
//{
//    std::cout << head;
//    print(args...);
//};
//
//
//template <class... Args>
//void printDebug(Args... args)
//{
//    if(Configure::log_level > Configure::debug)
//        return;
//
//    std::cout << Time::getNowTime() << " debug ";
//    print(args...);
//}
//
//template <class... Args>
//void printNormal(Args... args)
//{
//    if(Configure::log_level > Configure::normal)
//        return ;
//    std::cout << Time::getNowTime() << " normal ";
//    print(args...);
//}
//
//template <class... Args>
//void printWarn(Args... args)
//{
//    std::cout << Time::getNowTime() << " warn ";
//    print(args...);
//}


int main()
{
//    printDebug("nihao", 1, " ", 23, " ", "hello");
//    printNormal("aa", " ", 1 , 2, "hell");
//    printWarn("sdfd", " sf", "sf ", 1 , 2, "hell");

    Log::printDebug("nihao", 1, " ", 23, " ", "hello");
    Log::printNormal("aa", " ", 1 , 2, "hell");
    Log::printWarn("sdfd", " sf", "sf ", 1 , 2, "hell");
    return 0;
}