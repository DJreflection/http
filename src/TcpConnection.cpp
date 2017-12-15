//
// Created by zy on 17-12-9.
//

#include "TcpConnection.h"

TcpConnection::TcpConnection(int connectfd, struct sockaddr_in client) :
    connectfd_(connectfd),
    client_(client)
{
};


ssize_t TcpConnection::readMessage(char* const buffer, const int32_t& buffer_len)
{
    assert(buffer_len > 0);
    return read(connectfd_, buffer, buffer_len);
}

ssize_t TcpConnection::sendMessage(char* const buffer, const int32_t& message_len)
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