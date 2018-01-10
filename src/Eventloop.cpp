//
// Created by zy on 18-1-10.
//

#include "Eventloop.h"

int32_t Eventloop::epoll_event_size_ = 1024;
Eventloop::Eventloop() {
    epollfd_ = epoll_create1(FD_CLOEXEC);
}