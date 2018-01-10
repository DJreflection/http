//
// Created by zy on 18-1-10.
//

#ifndef HTTP_EVENTLOOP_H
#define HTTP_EVENTLOOP_H

#include <sys/epoll.h>
#include <fcntl.h>
#include <vector>

class Eventloop
{
public:
    Eventloop();

private:
    void epollAddSocket();
    void epollModSocket();

private:
    int epollfd_;
    std::vector<epoll_event> event_{epoll_event_size_};

    static const int32_t epoll_event_size_;
};


#endif //HTTP_EVENTLOOP_H
