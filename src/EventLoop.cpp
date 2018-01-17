//
// Created by zy on 18-1-12.
//

#include "EventLoop.h"
#include "TcpConnection.h"

EventLoop::EventLoop():
        epollfd_(epoll_create1(EPOLL_CLOEXEC)),
        thread_id_(nullptr),
        is_valid_(true),
        sockfd_to_message_()
{

}


uint32_t EventLoop::EVENTSIZE = 1024;


void EventLoop::startListenEvent() {
    struct epoll_event event[EVENTSIZE];

    while(is_valid_)
    {
        int size = epoll_wait(epollfd_, event, EVENTSIZE, 1000);
        for(int i=0; i<size; ++ i)
        {
            TcpConnection *connect_info = static_cast<TcpConnection *> (event[i].data.ptr);
            if(event[i].events & EPOLLIN)
            {
                connect_info->readMessage();
            } else
            {
                connect_info->writMessage();
            }

            if(connect_info->isValid() == false)
            {
                LOG_NORMAL(connect_info->getSrcAddr(), "disConnection");
                deleteListenEvent(connect_info->getConnectFd());
                delete(connect_info);
            }
        }
    }
}

bool EventLoop::addListenEvent(const int& socketfd, void* const message, const uint32_t& status) {
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = status;
    ev.data.ptr = message;

    if(epoll_ctl(epollfd_, EPOLL_CTL_ADD, socketfd, &ev) == 0)
    {
        sockfd_to_message_[socketfd] = message;
        return true;
    } else
    {
        return false;
    }
}

bool EventLoop::modListenEvent(const int &socketfd, void* const message, const uint32_t &new_status) {
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = new_status;
    ev.data.ptr = message;
    return (epoll_ctl(epollfd_, EPOLL_CTL_MOD, socketfd, &ev) == 0);
}

bool EventLoop::deleteListenEvent(const int &socketfd) {

    if(sockfd_to_message_.count(socketfd) > 0)
        sockfd_to_message_.erase(socketfd);

    struct epoll_event ev;
    return (epoll_ctl(socketfd, EPOLL_CTL_DEL, socketfd, &ev) == 0);
}