//
// Created by zy on 18-1-10.
//

#include "Buffer.h"

const size_t Buffer::buffer_size_ = 1024;

void Buffer::makeSpace(const size_t& len)
{
    if(writableBytes() + reader_index_  < len)
    {
        buffer_.resize(writer_index_ + len);
    }
    else
    {
        for(size_t j = 0, i=reader_index_; i<writer_index_; ++ i, ++ j)
            buffer_[j]= buffer_[i];

        writer_index_ = readableBytes();
        reader_index_ = 0;
    }
}