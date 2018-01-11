//
// Created by zy on 17-12-9.
//

#include "TcpConnection.h"

TcpConnection::TcpConnection(int connectfd, struct sockaddr_in client) :
    connectfd_(connectfd),
    client_(client),
    read_buffer_(),
    writ_buffer_(),
    events(0),
    valid_(true)
{
};


void TcpConnection::writMessage()
{
    assert(message_len >= 0);
    return write(connectfd_, buffer, message_len);
}

int32_t TcpConnection::getConnectFd() {
    return connectfd_;
}

std::string TcpConnection::getSrcAddr() {
    return std::string{inet_ntoa(client_.sin_addr)};
}

bool TcpConnection::isValid()
{
    return valid_;
}