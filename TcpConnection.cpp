//
// Created by zy on 17-12-9.
//

#include "TcpConnection.h"

//class TcpConnection
//{
//public:
//    TcpConnection(int connectfd, struct sockaddr_in client);
//};


TcpConnection::TcpConnection(int connectfd, struct sockaddr_in client) :
    connectfd_(connectfd),
    client_(client)
{

};


int32_t TcpConnection::readMessage(char *buffer, int32_t buffer_len)
{
    assert(buffer_len > 0);
    return read(connectfd_, buffer, buffer_len);
}

int32_t TcpConnection::sendMessage(char *buffer, int32_t message_len)
{
    assert(message_len >= 0);
    return write(connectfd_, buffer, message_len);
}