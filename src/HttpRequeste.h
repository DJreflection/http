//
// Created by zy on 18-1-18.
//

#ifndef HTTP_HTTPREQUEST_H
#define HTTP_HTTPREQUEST_H
#include <iostream>
#include <map>

class HttpRequeste
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

    HttpRequeste() : http_method_(Method_unknow), http_header_(){};

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



private:
    std::map<std::string, std::string> http_header_;
    HttpMethod http_method_;
    std::string http_uri_;
    std::string http_version_;
};


#endif //HTTP_HTTPREQUEST_H
