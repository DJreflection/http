#include <vector>
#include <thread>
#include <string.h>
#include <sys/epoll.h>

using namespace std;

#include "Conf.h"
#include "OpSocket.h"
#include "ThreadWork.h"
#include "QueueMessage.h"

struct Conf conf;
MessageQueue que;

void _GetNowTime(char *tm){
    time_t second = time(0);
    char *str = asctime(localtime(&second));
    int i;
    for(i=4; i<24; ++ i){
        tm[i-4] = str[i];
    }
    tm[i-4] = '\0';
}

int main() {
    ReadConf(conf);
    vector<pair<int, thread> >ThreadPool(conf.THREAD_SIZE);
    ThreadInit(ThreadPool);

    thread writelog;
    if(conf.flag_log){
        writelog = thread(WriteLog);
        printf("thread writelog create success!\n");
    }

    int sockfd = InitTcpSocket(conf.PORT);
    struct sockaddr_in client;
    socklen_t clientlen = sizeof(client);
    uint32_t tmp = 0;

    printf("Init Successed! server is running...\n");

    while(1){
        int n = accept(sockfd, (struct sockaddr *)&client, &clientlen);

        struct Message *msg = (struct Message *)malloc(sizeof(struct Message));

        _GetNowTime(msg->time);

        memset(msg->way, '\0', sizeof(msg->way));
        memset(msg->request_uri, '\0', sizeof(msg->request_uri));
        msg->connectfd = n, msg->port = client.sin_port, msg->sin_addr = client.sin_addr;
        if((msg->err = SetSocketNoBlock(n)) != 0){
            PushMessage(msg);
            continue;
        }

        if((msg->err = EpollOpSocket(ThreadPool[tmp].first, n, EPOLL_CTL_ADD, (void *)msg, EPOLLIN)) != 0){
            PushMessage(msg);
            continue;
        }

        if((++tmp) >= conf.THREAD_SIZE){
            tmp -= conf.THREAD_SIZE;
        }
    }
}