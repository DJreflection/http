//
// Created by zy on 11/19/17.
//

#include "HttpServer.h"


HttpServer::HttpServer(const uint16_t& Port) : tcp_server_(Port)
{
    tcp_server_.setOnMessageCallBack(std::bind(&HttpServer::OnMessage, this, std::placeholders::_1, std::placeholders::_2));
}

void HttpServer::OnMessage(const TcpConnection &conn, const std::string& message)
{
    std::cout << message << std::endl;
    RecvHeader recvHeader = parseHeader(message);
}

void HttpServer::start()
{
    tcp_server_.start();
}

HttpServer::RecvHeader HttpServer::parseHeader(const std::string& message)
{
    std::stringstream message_buffer(message);
    std::string line;
    getline(message_buffer, line);


    std::map<std::string, std::string> mp;
    while(getline(message_buffer, line))
    {

    }

}