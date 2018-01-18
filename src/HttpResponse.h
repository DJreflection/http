//
// Created by zy on 18-1-18.
//

#ifndef HTTP_HTTPRESPONSE_H
#define HTTP_HTTPRESPONSE_H
#include <iostream>

class HttpResponse
{
public:
    enum HttpStatus{
        status_unknow,
        status_200 = 200,
        status_400 = 400,
        status_404 = 404,
    };

    HttpResponse(){};



private:
    std::string http_version_;
    HttpStatus status_code_;
    std::string status_message_;
};
#endif //HTTP_HTTPRESPONSE_H
