#include "Conf.h"
#include "QueueMessage.h"

//
// Created by zy on 7/27/17.
//
extern struct Conf conf;
extern MessageQueue que;
void PushMessage(struct Message *msg){
    if(conf.flag_log){
        que.push(msg);
    }
    else{
        free(msg);
    }
}