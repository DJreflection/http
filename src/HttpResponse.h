//
// Created by zy on 18-1-18.
//

#ifndef HTTP_HTTPRESPONSE_H
#define HTTP_HTTPRESPONSE_H
#include <iostream>
#include <map>

class HttpResponse
{
public:
    enum HttpStatus{
        status_unknow,
        status_200 = 200,
        status_400 = 400,
        status_404 = 404,
    };

    HttpResponse() : http_version_("HTTP/1.1"), status_code_(status_unknow), status_message_(), header_(){};

    HttpResponse(const std::string& http_version, const HttpStatus& status_code, const std::string& status_message):
            http_version_(http_version),
            status_code_(status_code),
            status_message_(status_message),
            header_()
            {};

    void setStatusCode(const HttpStatus& status_code)
    {
        status_code_ = status_code;
    }

    void setStatusMessage(const std::string& status_message)
    {
        status_message_ = status_message;
    }

    void addHeader(const std::string& key, const std::string& value)
    {
        header_[key] = value;
    }

    void setContent(const std::string& body)
    {
        body_ = body;
    }

    std::string toString()
    {
        std::string res;
        res += http_version_ + ' ';
        if(status_code_ == status_200)
            res += "200 ";
        else if(status_code_ == status_400)
            res += "400 ";
        else
            res += "404　";

        res += status_message_ + "\r\n";
        for(auto& i: header_)
        {
            res += i.first + ':';
            res += i.second + "\r\n";
        }
        res += "\r\n";
        res += body_;
        return res;
    }

    static const std::string pages_400_;
    static const std::string pages_404_;

private:
    std::map<std::string, std::string> header_;
    std::string http_version_;
    HttpStatus status_code_;
    std::string status_message_;
    std::string body_;
};

std::string HttpResponse::pages_400_{
        "<!DOCTYPE html>\n\
        <html>\n<head>\n\
        \t<title>400</title>\n\
        </head>\n\
        <body>\n\
        <H1>Bad Requests</H1>\n\
        </body>\n\
        </html>"
};


std::string HttpResponse::pages_404_{
        "<!DOCTYPE html>\n\
        <html>\n<head>\n\
        \t<title>404</title>\n\
        </head>\n\
        <body>\n\
        <H1>NOT FOUND!</H1>\n\
        </body>\n\
        </html>"
};
#endif //HTTP_HTTPRESPONSE_H
