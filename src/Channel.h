//
// Created by zy on 18-1-10.
//

#ifndef HTTP_CHANNEL_H
#define HTTP_CHANNEL_H

#include <sys/epoll.h>
#include <functional>
#include "Time.h"

class Channel
{
public:
    typedef std::function<void()> EventCallBack;

    Channel(int32_t sockfd):sockfd_(sockfd), event_status_(0){
    }

    void setReadCallBack(const EventCallBack& eventCallBack)
    {
        onReadCallBack_ = eventCallBack;
    }

    void setWriteCallBack(const EventCallBack& eventCallBack)
    {
        onWriteCallBack_ = eventCallBack;
    }


    void enableReading()
    {
        event_status_ |= EPOLLIN;
        event_status_ |= EPOLLPRI;
    }

    void enableWriting()
    {
        event_status_ |= EPOLLOUT;
    }

    void handleEvent()
    {

    }

private:
    int32_t sockfd_;
    int32_t event_status_;
    EventCallBack onReadCallBack_;
    EventCallBack onWriteCallBack_;
};


#endif //HTTP_CHANNEL_H
