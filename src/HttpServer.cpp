//
// Created by zy on 11/19/17.
//

#include "HttpServer.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

HttpServer::HttpServer(const uint16_t& Port) : tcp_server_(Port)
{
    tcp_server_.setOnMessageCallBack(std::bind(&HttpServer::OnMessage, this, std::placeholders::_1, std::placeholders::_2));
}

void HttpServer::OnMessage(TcpConnection &conn, Buffer& buffer)
{
    if(conn.ptr == nullptr)
        conn.ptr = new HttpRequest();

    HttpRequest* http_request_ptr = static_cast<HttpRequest*>(conn.ptr);
    if(!http_request_ptr->parseMessage(buffer))
    {
        HttpResponse http_response("HTTP/1.1", HttpResponse::status_400, "Bad Request");
        http_response.addHeader("Content-Length", std::to_string(HttpResponse::pages_400_.size()));
        http_response.addHeader("Content-Type", "text/html");
        http_response.addHeader("Keep-Alive", "close");
        http_response.setContent(HttpResponse::pages_400_);
        conn.write(http_response.toString());
        delete(http_request_ptr);
        conn.setBekill();
        return ;
    }

    if(!http_request_ptr->isComplete())
        return ;

    if(http_request_ptr->getHttpMethod() != HttpRequest::Method_get)
    {
        HttpResponse http_response("HTTP/1.1", HttpResponse::status_400, "Bad Request");
        http_response.addHeader("Content-Length", std::to_string(HttpResponse::pages_400_.size()));
        http_response.addHeader("Content-Type", "text/html");
        http_response.addHeader("Keep-Alive", "close");
        http_response.setContent(HttpResponse::pages_400_);
        conn.write(http_response.toString());
        delete(http_request_ptr);
        conn.setBekill();
        return;
    }

    std::string uri = root_ + http_request_ptr->getHttpUri();
    std::fstream file(uri);
    if(!file.is_open())
    {
        HttpResponse http_response("HTTP/1.1", HttpResponse::status_404, "File don't exit!");
        http_response.addHeader("Content-Length", std::to_string(HttpResponse::pages_404_.size()));
        http_response.addHeader("Content-Type", "text/html");
        http_response.addHeader("Keep-Alive", "close");
        http_response.setContent(HttpResponse::pages_404_);
        conn.write(http_response.toString());
        delete(http_request_ptr);
        conn.setBekill();
        return;
    }
    std::stringstream body_sstring;
    body_sstring << file.rdbuf();
    file.close();

    std::string body_string(body_sstring.str());

    HttpResponse http_response("HTTP/1.1", HttpResponse::status_200, "OK");
    http_response.addHeader("Content-Length", std::to_string(body_string.size()));
    http_response.addHeader("Content-Type", "text/html");
    if(http_request_ptr->keepAlive())
    {
        http_response.addHeader("Connection", "keep-alive");
        http_response.addHeader("Keep-Alive", "timeout=10");
    }
    else
    {
        http_response.addHeader("Keep-Alive", "close");
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


