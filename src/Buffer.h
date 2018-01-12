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
    static const size_t reserve_bytes;
    static const size_t buffer_size;
    explicit Buffer(size_t init_size=buffer_size) :
            buffer_(init_size + reserve_bytes),
            reader_index_(reserve_bytes),
            writer_index_(reader_index_)
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

    char *beginWrite()
    {
        return begin() + writer_index_;
    }

    const char* beginWrite() const
    {
        return begin() + writer_index_;
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

    void makeSpace(const size_t& len)
    {
        if(writableBytes() + reader_index_ - reserve_bytes < len)
        {
            buffer_.resize(writer_index_ + len);
        }
        else
        {
            for(size_t j = reserve_bytes, i=reader_index_; i<writer_index_; ++ i, ++ j)
                buffer_[j]= buffer_[i];

            reader_index_ = reserve_bytes;
            writer_index_ = reserve_bytes + readableBytes();
        }
    }
    std::vector<char> buffer_;
    size_t reader_index_;
    size_t writer_index_;
};


#endif //HTTP_BUFFER_H
