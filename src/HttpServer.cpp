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
        LOG_DEBUG("parseMessage");
        conn.write(HttpResponse400.toString());
        delete(http_request_ptr);
        conn.setKeepAlive(false);
        return ;
    }

    LOG_DEBUG(http_request_ptr->isComplete());

    if(!http_request_ptr->isComplete())
        return ;

    if(http_request_ptr->getHttpMethod() != HttpRequest::Method_get)
    {
        conn.write(HttpResponse400.toString());
        delete(http_request_ptr);
        conn.setKeepAlive(false);
        return;
    }

    std::string uri = root_ + http_request_ptr->getHttpUri();

    LOG_NORMAL(conn.getSrcAddr(), "get", uri);

    std::fstream file(uri);
    if(!file.is_open())
    {
        conn.write(HttpResponse404.toString());
        delete(http_request_ptr);
        conn.setKeepAlive(false);
        return;
    }

    std::stringstream body_sstring;
    body_sstring << file.rdbuf();
    file.close();

    HttpResponse http_response(HttpResponse::status_200, "OK", body_sstring.str());

    if(http_request_ptr->keepAlive())
    {
        http_response.setKeepAlive();
        conn.write(http_response.toString());
        conn.setKeepAlive(true);
        http_request_ptr->reset();
    }
    else
    {
        conn.write(http_response.toString());
        delete(http_request_ptr);
        conn.setKeepAlive(false);
        return;
    }
}

void HttpServer::start()
{
    tcp_server_.start();
}


