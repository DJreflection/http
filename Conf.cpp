//
// Created by zy on 7/27/17.
//

#include <cstdio>
#include <string.h>
#include "Conf.h"

void ReadConf(struct Conf &conf){
    FILE *file = fopen(".conf", "rw");
    char buf[BUF_SIZE];
    while(fgets(buf, BUF_SIZE, file) != NULL){
        if(buf[0] != '#'){
            char *s;
            if((s = strstr(buf, "PORT:")) != NULL){
                sscanf(s, "PORT:%d", &conf.PORT);
            }
            else if((s = strstr(buf, "THREAD_SIZE:")) != NULL){
                sscanf(s, "THREAD_SIZE:%d", &conf.THREAD_SIZE);
            }
            else if((s = strstr(buf, "WWW:")) != NULL){
                sscanf(s, "WWW:%s", conf.WWW);
            }
            else if((s = strstr(buf, "LOG:")) != NULL){
                sscanf(s, "LOG:%d", &conf.flag_log);
            }
        }
    }
    conf._WWW_len = strlen(conf.WWW);
    fclose(file);

    printf("PORT: %d\nTHREAD_SIZE: %d\nWWW: %s\nLOG: %d\n", conf.PORT,
           conf.THREAD_SIZE, conf.WWW, conf.flag_log);
}
