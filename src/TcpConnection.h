//
// Created by zy on 17-12-9.
//

#ifndef HTTP_TCPCONNECTION_H
#define HTTP_TCPCONNECTION_H

#include <cstdint>
#include <cassert>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <rpc/types.h>
#include <arpa/inet.h>
#include <functional>

#include "EventLoop.h"
#include "Buffer.h"
#include "Log.h"

class TcpConnection
{
public:

    typedef std::function<void (const TcpConnection& conn, const Buffer& buffer)> OnMessageCallBack;

    TcpConnection(int32_t connectfd, struct sockaddr_in client, const std::shared_ptr<EventLoop>& loop);

    void readMessage()
    {
        char buffer[1024];
        ssize_t read_bytes = ::read(connectfd_, buffer, 1024);
        if(read_bytes < 0)
        {
            LOG_ERROR("read_bytes < 0");
            return;
        }
        if(read_bytes == 0)
            valid_ = false;

        read_buffer_.append(buffer, read_bytes);
        on_message_call_back_(*this, read_buffer_);
    }

    void writMessage()
    {
        ssize_t writ_bytes = ::write(connectfd_, write_buffer_.beginRead(), write_buffer_.readableBytes());
        if(writ_bytes < 0)
        {
            LOG_ERROR("writ_bytes < 0");
            return;
        }
        write_buffer_.retrieve(writ_bytes);

        if(getWriteBufferSize() == 0 && keep_alive_ == false)
        {
            valid_ = false;
        }
    }

    void setOnMessageCallBack(const OnMessageCallBack& onMessageCallBack){
        on_message_call_back_ = onMessageCallBack;
    }
    
    void write(const std::string& message){
        write_buffer_.append(message);
        event_loop_weak_ptr_->modListenEventWriteableEvent(connectfd_);
    }
    
    int32_t getConnectFd(){
        return connectfd_;
    }

    size_t getReadBufferSize()
    {
        return read_buffer_.readableBytes();
    }

    size_t getWriteBufferSize()
    {
        return write_buffer_.readableBytes();
    }
    
    std::string getSrcAddr(){
        return std::string{inet_ntoa(client_.sin_addr)};
    }

    void setBekill()
    {
        valid_ = false;
    }

    void setKeepAlive()
    {
        keep_alive_ = true;
    }

    bool isValid()
    {
        return valid_;
    }

private:

    Buffer read_buffer_;
    Buffer write_buffer_;

    int32_t connectfd_;
    struct sockaddr_in client_;

    bool keep_alive_;
    bool valid_;
    OnMessageCallBack on_message_call_back_;
    std::shared_ptr<EventLoop> event_loop_weak_ptr_;

    static const size_t buffer_max_;
};

#endif //HTTP_TCPCONNECTION_H
