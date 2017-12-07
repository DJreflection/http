//
// Created by zy on 11/19/17.
//

#ifndef HTTP_EPOLLTHREAD_H
#define HTTP_EPOLLTHREAD_H
#include <sys/epoll.h>
#include <assert.h>
#include <cstring>
#include <thread>
#include <unistd.h>
#include <fcntl.h>
#include <functional>

class EpollThread
{
public:
    typedef std::function<void (const std::string &message)> OnMessage;
    EpollThread();

    void epollAddSocket(int socketfd, uint32_t status);
    void epollModSocket(int socketfd, uint32_t new_status);
    void startListenSocket();
private:
    void setNoBlock(int socketfd);
    void listenSocket();

    int epollfd_;
    std::shared_ptr<std::thread> thread_id_;
    //OnMessage _onMessage;

    static const uint32_t EVENTSIZE;
    static const uint32_t BUFFERSIZE;
};
#endif //HTTP_EPOLLTHREAD_H
