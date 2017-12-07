//
// Created by zy on 11/19/17.
//

#include "EpollThread.h"
#include "Configure.h"

EpollThread::EpollThread()
{
    epollfd_ = epoll_create1(EPOLL_CLOEXEC);
}

const uint32_t EpollThread::BUFFERSIZE = 10240;
const uint32_t EpollThread::EVENTSIZE = 1024;

void EpollThread::epollAddSocket(int socketfd, uint32_t status)
{
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = status;
    ev.data.fd = socketfd;

    int tmp = epoll_ctl(epollfd_, EPOLL_CTL_ADD, socketfd, &ev);
    assert(tmp != -1);
}

void EpollThread::epollModSocket(int socketfd, uint32_t new_status)
{
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = new_status;
    ev.data.fd = socketfd;

    int tmp = epoll_ctl(epollfd_, EPOLL_CTL_MOD, socketfd, &ev);
    assert(tmp != -1);
}

void EpollThread::startListenSocket()
{
    std::thread thread_id = std::thread(std::bind(&EpollThread::listenSocket, this));
    thread_id_ = std::make_shared<std::thread>(std::move(thread_id));
}


void EpollThread::setNoBlock(int socketfd)
{
    int status_old;
    status_old = fcntl(socketfd, F_GETFL, 0);
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
        int size = epoll_wait(epollfd_, event, EVENTSIZE, -1);
        for(int i=0; i<size; ++ i)
        {
            std::shared_ptr<std::pair<uint32_t ,int32_t>> source_data = event[i].data.ptr;

            int read_bytes = read(sockfd, buffer, BUFFERSIZE);

        }
    }
}