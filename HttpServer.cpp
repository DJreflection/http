//
// Created by zy on 11/19/17.
//

#include "HttpServer.h"


HttpServer::HttpServer(const uint16_t& Port) : tcpServer(Port)
{

}

void HttpServer::start()
{
    thread_id = std::thread(std::bind(&HttpServer::waitConnected, this));

    for(int i=0; i<Configure::thread_number; ++ i)
    {
        thread_pool_[i].startListenSocket();
    }
}