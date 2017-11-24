//
// Created by zy on 11/19/17.
//

#include "EpollThread.h"
#include "Configure.h"

EpollThread::EpollThread()
{
    epollfd = epoll_create1(EPOLL_CLOEXEC);
}

const uint32_t EpollThread::BUFFERSIZE = 10240;
const uint32_t EpollThread::EVENTSIZE = 1024;

void EpollThread::epollAddSocket(int socketfd, uint32_t status)
{
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = status;
    ev.data.fd = socketfd;

    int tmp = epoll_ctl(epollfd, EPOLL_CTL_ADD, socketfd, &ev);
    assert(tmp != -1);
}

void EpollThread::epollModSocket(int socketfd, uint32_t new_status)
{
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = new_status;
    ev.data.fd = socketfd;

    int tmp = epoll_ctl(epollfd, EPOLL_CTL_MOD, socketfd, &ev);
    assert(tmp != -1);
}

void EpollThread::setOnMessage(OnMessage &on_message)
{
    _onMessage = std::move(on_message);
}


void EpollThread::startListenSocket()
{
    thread_id = std::thread(std::bind(&EpollThread::listenSocket, this));
}


void EpollThread::setNoBlock(int socketfd)
{
    int status_old;
    status_old = fcntl(socketfd, F_GETFL, 0))
    assert(status_old >= 0);

    int tmp = fcntl(socketfd, F_SETFL, status_old | O_NONBLOCK);
    assert(tmp >= 0);
}

void EpollThread::listenSocket()
{
    struct epoll_event event[EVENTSIZE];
    char buffer[BUFFERSIZE];

    while(true)
    {
        int size = epoll_wait(epollfd, event, EVENTSIZE, -1);
        for(int i=0; i<size; ++ i)
        {

        }
    }
}