//
// Created by zy on 11/19/17.
//

#ifndef HTTP_EPOLLTHREAD_H
#define HTTP_EPOLLTHREAD_H
#include <sys/epoll.h>
#include <assert.h>
#include <cstring>
#include <thread>
#include <fcntl.h>
#include <functional>

class EpollThread
{
public:
    typedef std::function<void (const std::string &message)> OnMessage;
    EpollThread();

    void epollAddSocket(int socketfd);
    void epollModSocket(int socketfd, uint32_t new_status);
    void setOnMessage(OnMessage &onMessage);
    void startListenSocket();
private:
    void setNoBlock(int socketfd);
    void listenSocket();

    int epollfd;
    std::thread thread_id;
    OnMessage _onMessage;
};
#endif //HTTP_EPOLLTHREAD_H
