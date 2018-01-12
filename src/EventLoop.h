//
// Created by zy on 18-1-12.
//

#ifndef HTTP_EVENTLOOP_H
#define HTTP_EVENTLOOP_H

#include <cstdint>
#include <thread>
#include "TcpConnection.h"

class EventLoop
{
public:
    typedef std::function<void (const TcpConnection& Conn, const std::string &message)> MessageCallBack_;

    EventLoop();

    void addListenEvent(const int& socketfd, void*const message, const uint32_t& status);
    void modListenEvent(const int& socketfd, const uint32_t& new_status);
    void deleteListenEvent(const int& socketfd);


    void setOnMessageCallBack(const MessageCallBack_& messageCallBack);
    void startListenSocket();

private:

    void listenSocket();

    int epollfd_;

    // thread ID
    std::shared_ptr<std::thread> thread_id_;

    // OnMessage Call Back
    MessageCallBack_ messageCallBack_;

    // event_size and buffer_size
    static const uint32_t EVENTSIZE;
    static const uint32_t BUFFERSIZE;
};


#endif //HTTP_EVENTLOOP_H
