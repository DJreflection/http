//
// Created by zy on 17-12-9.
//

#ifndef HTTP_TCPCONNECTION_H
#define HTTP_TCPCONNECTION_H

class TcpConnection
{
public:
    TcpConnection(int32_t connectfd, struct sockaddr_in client);

    int32_t readMessage(char *buffer, int32_t buffer_len);
    int32_t sendMessage(char *buffer, int32_t buffer_len);

    std::string getSrcAddr();
private:
    int connectfd_;
    struct sockaddr_in client_;
};

#endif //HTTP_TCPCONNECTION_H
