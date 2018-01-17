//
// Created by zy on 18-1-10.
//

#ifndef HTTP_BUFFER_H
#define HTTP_BUFFER_H


#include <vector>
#include <cstdint>
#include <cstdio>
#include <cassert>
#include <string>
#include <algorithm>

class Buffer
{
public:
    explicit Buffer(size_t init_size=buffer_size) :
            buffer_(init_size),
            reader_index_(0),
            writer_index_(0)
    {}

    size_t readableBytes()
    {
        return writer_index_ - reader_index_;
    }

    size_t writableBytes()
    {
        return buffer_.size() - writer_index_;
    }

    void retrieve(size_t len)
    {
        assert(len <= readableBytes());

        if(len <= readableBytes())
            reader_index_ += len;
        else
            reader_index_ += readableBytes();
    }

    char* beginRead()
    {
        return begin() + reader_index_;
    }

    const char* beginRead() const
    {
        return begin() + reader_index_;
    }

    void append(const std::string& str)
    {
        append(str.data(), str.size());
    }

    void append(const char* str, size_t len)
    {
        if(writableBytes() < len)
            makeSpace(len);

        for(size_t  i = 0; i < len;  ++ i, ++ writer_index_)
            buffer_[writer_index_] = str[i];
    }

    const char *findCRLF() const
    {
        char CRLF[] = "\r\n";
        const char* crlf = std::search(beginRead(), beginWrite(), CRLF, CRLF+2);
        return crlf == beginWrite() ? nullptr : crlf;
    }

    const char *findCRLFCRLF() const
    {
        char CRLFCRLF[] = "\r\n\r\n";
        const char* crlfcrlf = std::search(beginRead(), beginWrite(), CRLFCRLF, CRLFCRLF+2);
        return crlfcrlf == beginWrite() ? nullptr : crlfcrlf;
    }

    char *beginWrite()
    {
        return begin() + writer_index_;
    }

    const char* beginWrite() const
    {
        return begin() + writer_index_;
    }

    size_t size()
    {
        return buffer_.size();
    }


private:
    char* begin()
    {
        return &*buffer_.begin();
    }
    const char* begin() const
    {
        return &*buffer_.begin();
    }

    void makeSpace(const size_t& len);

    std::vector<char> buffer_;
    size_t reader_index_;
    size_t writer_index_;
    static const size_t buffer_size;
};


#endif //HTTP_BUFFER_H
