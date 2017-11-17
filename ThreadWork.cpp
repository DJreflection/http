//
// Created by zy on 7/27/17.
//

#include <thread>
#include <vector>
#include <sys/epoll.h>
#include <ctime>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/sendfile.h>

using namespace std;

#include "Configure.h"
#include "ThreadWork.h"
#include "OpSocket.h"
#include "QueueMessage.h"

#define HEADER_CLOSE "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %ld\r\n\r\n"


#define HEADER_KEEP_ALIVE "HTTP/1.1 200 OK\r\nConnection: Keep-Alive\r\n\
    Keep-Alive: timeout=20\r\nContent-Type: text/html\r\nContent-Length: %ld\r\n\r\n"

extern struct Conf conf;
extern MessageQueue que;

void _Analysis(char *buf, char *way, char *uri){
    size_t e = 0, x = 0;
    while(buf[e] != ' '){
        way[x ++] = buf[e ++];
    }
    way[x] = '\0';

    e ++, x = 0;
    while(buf[e] != ' '){
        uri[x ++] = buf[e ++];
    }
    uri[x] = '\0';
}

int Response(int connectfd, char *buf, char *uri, uint8_t &flag){
    struct stat f;
    int file;

    if(strstr(uri, "/../") != NULL || (file = open(uri, O_RDONLY)) == -1){
        file = open("./www/404.html", O_RDONLY);
        stat("./www/404.html", &f);
        flag |= (1 << 4);
    }
    else{
        stat(uri, &f);
    }

    if(flag & 1){
        sprintf(buf, HEADER_KEEP_ALIVE, f.st_size);
    }
    else{
        sprintf(buf, HEADER_CLOSE, f.st_size);
    }
    if(write(connectfd, buf, strlen(buf)) == -1){
        close(file);
        return errno;
    }
    sendfile(connectfd, file, 0l, f.st_size);
    close(file);
    return 0;
}

void _ThreadBranch(int argc){

    struct epoll_event event[EVENT_SIZE];
    char buf[BUF_SIZE], uri[1024];
    strcpy(uri, conf.WWW);
    int size;

    while(1){
        size = epoll_wait(argc, event, EVENT_SIZE-1, -1);

        for(int i=0; i<size; ++ i){
            struct Message *msg = (struct Message *)(event[i].data.ptr);
            if(event[i].events & EPOLLIN){
                ssize_t n;
                if((n = read(msg->connectfd, buf, BUF_SIZE)) <= 0){
                    if(n < 0){
                        msg->err = errno;
                    }
                    close(msg->connectfd);
                    PushMessage(msg);
                    continue;
                }
                msg->flag = strstr(buf, "Keep-Alive") ? 1 : 0;

                _Analysis(buf, msg->way, msg->request_uri);

                if((msg->err = EpollOpSocket(argc, msg->connectfd, EPOLL_CTL_MOD, msg, EPOLLOUT)) != 0){
                    close(msg->connectfd);
                    PushMessage(msg);
                    continue;
                }
            }
            else{
                for(int j=conf._WWW_len, k = 0; ; ++ j, ++ k){
                    if(!(msg->request_uri[k])){
                        uri[j] = '\0';
                        break;
                    }
                    uri[j] = msg->request_uri[k];
                }
                if((msg->err = Response(msg->connectfd, buf, uri, msg->flag)) != 0){
                    close(msg->connectfd);
                    PushMessage(msg);
                    continue;
                }

                if(!((msg->flag)&1)){
                    close(msg->connectfd);
                    PushMessage(msg);
                }
                else{
                    if(conf.flag_log){
                        struct Message *msgcp = (struct Message *)malloc(sizeof(struct Message));
                        memcpy(msgcp, msg, sizeof(struct Message));
                        que.push(msgcp);
                    }
                    EpollOpSocket(argc, msg->connectfd, EPOLL_CTL_MOD, msg, EPOLLIN);
                }
            }
        }
    }
}

void ThreadInit(vector<pair<int ,thread> >&ThreadPool){
    for(int i=0; i<ThreadPool.size(); ++ i){
        ThreadPool[i].first = epoll_create1(0);
        ThreadPool[i].second = thread(_ThreadBranch, ThreadPool[i].first);
        printf("Thread %d Create Success!\n", i+1);
    }
}

void WriteLog(){
    FILE *file;
    struct Message *msg;
    size_t len = 0;
    char uri[1024];
    uint32_t b = 0, e = 0;
    while(1){
        while(!que.empty()){

            msg = que.front();

            if(len >= 52428800 || b != e){
                fclose(file);
                len = 0;
            }

            if(len == 0){
                int i;
                strcpy(uri, "./log/");
                for(i=0; msg->time[i]; ++ i){
                    uri[i+6] = msg->time[i];
                    if(uri[i+6] == ' ')
                        uri[i+6] = '_';
                }
                uri[i+6] = '\0';
                file = fopen(uri, "a");
            }
            int grade = 0;
            if(msg->err)
                grade = 2;
            else if(msg->flag >> 4)
                grade = 1;

            // grade time ip:port way uri status
            len += fprintf(file, "%d %s %d.%d.%d.%d:%d %s %s %s\n", grade, msg->time,
                           (msg->sin_addr.s_addr)>>24, (msg->sin_addr.s_addr>>12)&(0xff),
                           (msg->sin_addr.s_addr>>8) &(0xff), (msg->sin_addr.s_addr) & (0xff),
                            msg->port, msg->way, msg->request_uri, strerror(msg->err));

            b = e;
            sscanf(msg->time, "%*4s%2d%*s", &e);
            free(msg);
        }
        //fflush(file);
    }
}
