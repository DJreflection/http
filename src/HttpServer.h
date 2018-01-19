//
// Created by zy on 11/19/17.
//

#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <fstream>
#include "Buffer.h"
#include "TcpServer.h"
#include "Configure.h"
#include "Log.h"

class HttpServer
{
public:
    typedef std::map<std::string, std::string> HTTP_HEADER;

    HttpServer(const uint16_t& Port);

    void OnMessage(TcpConnection& conn, Buffer& buffer);
    void setRoot(const std::string& root)
    {
        root_ = root;
    }

    void start();

private:
    TcpServer tcp_server_;

    std::string root_;

    static const std::string keep_alive_;
    static const std::string close_alive_;
};

#endif //HTTP_SERVER_H
