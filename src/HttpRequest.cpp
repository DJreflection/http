//
// Created by zy on 18-1-19.
//

#include "HttpRequest.h"

bool HttpRequest::parseMessage(Buffer& message)
{
    LOG_DEBUG();
    while(true)
    {
        if(status_ == 3)
        {
            const std::string& body_length_string = http_header_["content-length"];
            int body_length_int = 0;
            for(int i=0; i<body_length_string.size(); ++i)
                body_length_int = body_length_int * 10 + body_length_string[i] - '0';

            std::string& body = http_header_["body"];

            size_t read_int_ = 0;
            if(message.readableBytes() < body_length_int)
            {
                read_int_ = message.readableBytes();
            }
            else
            {
                read_int_ = body_length_int - body.size();
            }

            std::string str(message.beginRead(),read_int_);
            body.append(str);
            message.retrieve(read_int_);

            if(body.size() == body_length_int)
                status_ = 4;
        }



        // all lower
        auto toStandardString = [](const std::string& str)->std::string{
            std::string res;
            size_t i = 0, j = str.size()-1;
            while(i <= j && str[i] == ' ')
                i ++;

            while(j >= i && str[j] == ' ')
                j --;

            for(; i<= j; ++ i)
            {
                if(str[i] >= 'A' && str[i] <= 'Z')
                    res += str[i] - 'A' + 'a';
                else
                    res += str[i];
            }
            return res;
        };

        const char* str = message.findCRLF();

        if(str)
        {
            if(status_ == 0)
            {
                std::string res(reinterpret_cast<const char*>(message.beginRead()), str);
                message.retrieve(res.size()+2);

                size_t x1 = res.find(' '), x2 = res.rfind(' ');
                std::string way(res.begin(), res.begin()+x1);
                std::string uri(res.begin()+x1+1, res.begin()+x2);
                std::string version(res.begin()+x2+1, res.end());

                //LOG_DEBUG(way, uri, version);

                if(way.empty() || uri.empty() || version.empty())
                    return false;

                http_header_["way"] = toStandardString(way);
                http_header_["uri"] = toStandardString(uri);
                http_header_["version"] = toStandardString(version);

                //LOG_DEBUG(http_header_["way"], http_header_["uri"], http_header_["version"]);
                status_ = 2;
            }
            else if(status_ == 2)
            {
                std::string res(reinterpret_cast<const char*>(message.beginRead()), str);

                std::cerr << "len :" << res.size() + 2 << "readableBytes: " << message.readableBytes() << std::endl;
                message.retrieve(res.size()+2);
                //LOG_DEBUG("res.size() == ", res.size());

                if(res.empty())
                {
                    if(http_header_["way"] !=  "get" && http_header_.count("content-length") > 0)
                        status_ = 3;
                    else
                        status_ = 4;

                    LOG_DEBUG("status: ", (int)status_);
                    LOG_DEBUG("Readable: ", message.readableBytes());
                    break;
                }

                size_t x1 = res.find(':');
                std::string key(res.begin(), res.begin()+x1);
                std::string value(res.begin()+x1+1, res.end());
                http_header_[toStandardString(key)] = toStandardString(value);
            }
        } else
        {
            //break;
        }
        if(status_ == 4 || status_ == 3)
            break;
    }
    return true;
}