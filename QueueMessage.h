//
// Created by zy on 7/27/17.
//

#ifndef HTT4_QUEUEMESSAGE_H
#define HTT4_QUEUEMESSAGE_H
#include <string>
#include <queue>
#include <thread>
#include <mutex>

using namespace std;
#include "Configure.h"

class MessageQueue
{
public:
    void push(struct Message* msg)
    {
        m_mutex.lock();
        que.push(msg);
        m_mutex.unlock();
    }

    struct Message* front()
    {
        struct Message* msg;
        m_mutex.lock();
        msg = que.front();
        que.pop();
        m_mutex.unlock();
        return msg;
    }

    bool empty(){
        return que.size() == 0;
    }

private:
    queue<struct Message*> que;
    mutex m_mutex;
};

void PushMessage(struct Message *msg);
#endif //HTT4_QUEUEMESSAGE_H
