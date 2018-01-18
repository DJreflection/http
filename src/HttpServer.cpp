//
// Created by zy on 11/19/17.
//

#include "HttpServer.h"

HttpServer::HttpServer(const uint16_t& Port) : tcp_server_(Port)
{
    tcp_server_.setOnMessageCallBack(std::bind(&HttpServer::OnMessage, this, std::placeholders::_1, std::placeholders::_2));
}

void HttpServer::OnMessage(TcpConnection &conn, Buffer& buffer)
{
    if(conn.ptr == nullptr)
    {
        conn.ptr =
    }
    const char* crlf = buffer.findCRLF();
    if(crlf == nullptr && buffer.readableBytes() > 10240)
    {
        return;
    }

    if(crlfcrlf == nullptr)
        return;

    LOG_DEBUG(std::string(buffer.beginRead(), buffer.readableBytes()));

    std::string tmp(const_cast<const char*>(buffer.beginRead()), buffer.findCRLF());
    std::stringstream string_buffer(tmp);
    buffer.retrieve(tmp.size()+2);

    std::string way, uri, version;
    string_buffer >> way >> uri >> version;
    if(way.empty() || uri.empty() || version.empty())
    {
        LOG_ERROR(conn.getSrcAddr(), "http requests header error");
        conn.setBekill();
        return;
    }

    if(way != "GET")
    {
        conn.setBekill();
        return;
    }

    HTTP_HEADER recv_header;
    recv_header["way"] = way;
    recv_header["uri"] = uri;
    recv_header["version"] = version;

    while(true)
    {
        std::string res(const_cast<const char*>(buffer.beginRead()), buffer.findCRLF());
        if(res.empty())
            break;

        size_t n;
        if((n = res.find(':')) == std::string::npos)
        {
            LOG_ERROR(conn.getSrcAddr(), "http requests header error");
            conn.setBekill();
            break;
        }

        recv_header[res.substr(0, n)] = res.substr(n+1, res.size());
        buffer.retrieve(res.size()+2);
    }

    if(!conn.isValid())
    {
        return;
    }

}

void HttpServer::start()
{
    tcp_server_.start();
}

std::string HttpServer::keep_alive_{
        "HTTP/1.1 %d %s\r\n\
        Connection: Keep-Alive\r\n\
        Keep-Alive: timeout=20\r\n\
        Content-Type: text/html\r\n\
        Content-Length: %d\r\n\
        \r\n"
};

std::string HttpServer::close_alive_{
        "HTTP/1.1 %d %s\r\n\
        Connection: close\r\n\
        Content-Type: text/html\r\n\
        Content-Length: %d\r\n\
        \r\n"
};

std::string HttpServer::pages_404_{
        "<!DOCTYPE html>\n\
        <html>\n<head>\n\
        \t<title>404</title>\n\
        </head>\n\
        <body>\n\
        <H1>NOT FOUND!</H1>\n\
        </body>\n\
        </html>"
};


std::string HttpServer::pages_400_{
        "<!DOCTYPE html>\n\
        <html>\n<head>\n\
        \t<title>400</title>\n\
        </head>\n\
        <body>\n\
        <H1>Bad Requests</H1>\n\
        </body>\n\
        </html>"
};

