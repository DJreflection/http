//
// Created by zy on 18-1-18.
//

#ifndef HTTP_HTTPREQUEST_H
#define HTTP_HTTPREQUEST_H
#include <iostream>
#include <map>
#include "Buffer.h"
#include "Log.h"

class HttpRequest
{
public:

    enum HttpMethod{
        Method_unknow,
        Method_get,
        Method_post,
        Method_head,
        Method_put,
        Method_delete,
    };

    HttpRequest() : http_method_(Method_unknow),
                     http_header_(),
                     http_uri_(),
                     http_version_(),
                     status_(0)
    {};

    void setHttpMethod(const std::string& http_method)
    {
        if(http_method == "GET")
            http_method_ = Method_get;
        else if(http_method == "POST")
            http_method_ = Method_post;
        else if(http_method == "HEAD")
            http_method_ = Method_head;
        else if(http_method == "PUT")
            http_method_ = Method_put;
        else if(http_method == "DELETE")
            http_method_ = Method_delete;
        else
            http_method_ = Method_unknow;
    }

    HttpMethod getHttpMethod() {
        return http_method_;
    }

    void setHttpUri(const std::string& http_uri) {
        http_uri_ = http_uri;
    }

    const std::string& getHttpUri(){
        return http_uri_;
    }

    void setHttpVersion(const std::string& http_version)
    {
        http_version_ = http_version;
    }

    const std::string& getHttpVersion(){
        return http_version_;
    }

    bool isComplete() {
        return (status_ == 4);
    }

    bool parseMessage(Buffer& message);

    void reset()
    {
        http_header_.clear();
        http_method_ = Method_unknow;
        http_uri_.clear();
        http_version_.clear();
        status_  = 0;
    }

    bool keepAlive()
    {
        if(http_header_.count("connection") > 0 && http_header_["connection"] == "keep-alive")
            return true;
        return false;
    }

private:
    std::map<std::string, std::string> http_header_;
    HttpMethod http_method_;
    std::string http_uri_;
    std::string http_version_;

    // 标记消息到达过程
    // 0 : Nothing
    // 2 : get request line and waiting header
    // 3 : body
    // 4 : complete
    uint8_t status_;
};

//　Content-Length

#endif //HTTP_HTTPREQUEST_H
