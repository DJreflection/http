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