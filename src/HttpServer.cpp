//
// Created by zy on 11/19/17.
//

#include "HttpServer.h"


HttpServer::HttpServer(const uint16_t& Port) : tcpServer(Port)
{
    tcpServer.setOnMessageCallBack(std::bind(&HttpServer::OnMessage, this, std::placeholders::_1, std::placeholders::_2));
}

void HttpServer::OnMessage(const TcpConnection &conn, const std::string& message)
{
    std::cout << message << std::endl;

    RecvHeader recvHeader = parseHeader(message);
}

void HttpServer::start()
{
    tcpServer.start();
}

HttpServer::RecvHeader HttpServer::parseHeader(const std::string& message)
{
    return RecvHeader{};
}