//
// Created by zy on 17-12-9.
//

#include "TcpConnection.h"

TcpConnection::TcpConnection(int connectfd, struct sockaddr_in client, const std::shared_ptr<EventLoop>& loop) :
    connectfd_(connectfd),
    client_(client),
    read_buffer_(),
    write_buffer_(),
    valid_(true),
    keep_alive_(false),
    event_loop_weak_ptr_(loop)
{};

size_t TcpConnection::buffer_max_ = 10240;