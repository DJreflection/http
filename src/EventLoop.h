//
// Created by zy on 18-1-12.
//

#ifndef HTTP_EVENTLOOP_H
#define HTTP_EVENTLOOP_H

#include <cstdint>
#include <thread>
#include <map>
#include <sys/epoll.h>

class EventLoop
{
public:
    EventLoop();

    ~EventLoop(){
        if(is_valid_)
        {
            is_valid_ = false;
            stopLoop();
        }
    }

    bool addListenReadableEvent(const int& sockfd, void* const tcpConnection) {
        return addListenEvent(sockfd, tcpConnection, EPOLLIN);
    }

    bool addListenWriteableEvent(const int& sockfd, void* const tcpConnection) {
        return addListenEvent(sockfd, tcpConnection, EPOLLOUT);
    }

    bool modListenEventReadableEvent(const int& sockfd) {
        void* message = sockfd_to_message_[sockfd];
        return modListenEvent(sockfd, message, EPOLLIN);
    }

    bool modListenEventWriteableEvent(const int& sockfd) {
        void* message = sockfd_to_message_[sockfd];
        return modListenEvent(sockfd, message, EPOLLOUT);
    }

    bool deleteListenEvent(const int& socketfd);

    void startLoop() {
        is_valid_ = true;
        thread_id_ = std::make_shared<std::thread>(std::bind(&EventLoop::startListenEvent, this));
    }

    void stopLoop() {
        is_valid_ = false;
        if(thread_id_.get()->joinable())
        {
            thread_id_.get()->join();
        }
    }

    bool isRunning()
    {
        return (is_valid_ && thread_id_.get());
    }

private:
    void startListenEvent();
    bool addListenEvent(const int& socketfd, void* const message, const uint32_t& status);
    bool modListenEvent(const int& socketfd, void* const message, const uint32_t& new_status);


    int epollfd_;
    std::shared_ptr<std::thread> thread_id_;
    bool is_valid_;

    std::map<int, void*> sockfd_to_message_;
    static const uint32_t EVENTSIZE;
};


#endif //HTTP_EVENTLOOP_H
