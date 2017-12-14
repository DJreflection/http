//
// Created by zy on 17-12-12.
//

#include "TcpServer.h"

TcpServer::EpollThread::EpollThread()
{
    epollfd_ = epoll_create1(EPOLL_CLOEXEC);
}

const uint32_t TcpServer::EpollThread::BUFFERSIZE = 10240;
const uint32_t TcpServer::EpollThread::EVENTSIZE = 1024;


void TcpServer::EpollThread::epollAddSocket(const int& socketfd, void* const message, const uint32_t& status)
{
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = status;
    ev.data.ptr = message;

    int tmp = epoll_ctl(socketfd, EPOLL_CTL_ADD, socketfd, &ev);
    assert(tmp != -1);
}

void TcpServer::EpollThread::epollModSocket(const int& socketfd, const uint32_t& new_status)
{
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = new_status;

    int tmp = epoll_ctl(socketfd, EPOLL_CTL_MOD, socketfd, &ev);
    assert(tmp != -1);
}


void TcpServer::EpollThread::setOnMessageCallBack(MessageCallBack_ messageCallBack) {
    messageCallBack_ = messageCallBack;
}

void TcpServer::EpollThread::startListenSocket()
{
    thread_id_ = std::make_shared<std::thread>(std::bind(&EpollThread::listenSocket, this));
}


void TcpServer::EpollThread::setNoBlock(int socketfd)
{
    int status_old;
    status_old = fcntl(socketfd, F_GETFL, 0);
    assert(status_old >= 0);

    int tmp = fcntl(socketfd, F_SETFL, status_old | O_NONBLOCK);
    assert(tmp >= 0);
}

void TcpServer::EpollThread::listenSocket()
{
    struct epoll_event event[EVENTSIZE];
    char buffer[BUFFERSIZE];

    while(true)
    {
        int size = epoll_wait(epollfd_, event, EVENTSIZE, -1);
        for(int i=0; i<size; ++ i)
        {
            TcpConnection *connect_info = (TcpConnection *)event[i].data.ptr;
            int read_bytes = read(connect_info->getConnectFd(), buffer, BUFFERSIZE);
            if(read_bytes <= 0)
            {
                continue;
            }

            messageCallBack_((*connect_info), std::string{buffer, read_bytes});
        }
    }
}


TcpServer::TcpServer(const uint16_t& Port) {
    tcp_sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    assert(tcp_sockfd_ != -1);

    int flags = 1;
    setsockopt(tcp_sockfd_, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &flags, sizeof(flags));
    //setsockopt(tcp_sockfd, IPPROTO_TCP, TCP_NODELAY, &flags, sizeof(flags));

    struct  sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(Port);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    int tmp = 0;
    tmp = bind(tcp_sockfd_, (struct sockaddr *)&server, sizeof(server));
    assert(tmp != -1);

    tmp = listen(tcp_sockfd_, 1024);
    assert(tmp != -1);
}


void TcpServer::setThreadNum(const int& number)
{
    thread_number = number;
}

void TcpServer::start() {
    for(int i=0; i<thread_number; ++ i)
    {
        std::shared_ptr<EpollThread> tmp = std::make_shared<>();
        thread_pool.emplace_back(tmp);
    }

    for(int i=0; i<thread_number; ++ i)
        thread_pool[i]->startListenSocket();

    struct sockaddr_in client;
    socklen_t clientlen = sizeof(client);

    int take_turn = 0;
    while(true)
    {
        int socketConnect = accept(tcp_sockfd_, (struct sockaddr *)&client, &clientlen);

        TcpConnection *connect_info = new TcpConnection(socketConnect, client);
        thread_pool[take_turn ++ ]->epollAddSocket(socketConnect, connect_info, EPOLLIN);

        if(take_turn == thread_pool.size())
            take_turn = 0;
    }
}

uint32_t TcpServer::thread_number = 4;