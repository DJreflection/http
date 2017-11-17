//
// Created by zy on 7/27/17.
//
#include "Configure.h"

uint32_t Configure::buffer_size = 10240;
uint16_t Configure::event_size = 1024;
uint16_t Configure::port = 8080;
std::string Configure::root = "~/Workspace/http/www/";
enum Configure::logLevel{
    debug,
    normal,
    warn,
};

logLevel Configure::log_level = debug;

void Configure::readConfigure(std::string &&url)
{
    try{
        std::ifstream reader(url);
        std::stringstream json_value;
        json_value << reader.rdbuf();
        Json::Value val(json_value.str());
        buffer_size = val["buffer_size"].asUInt();
        event_size = val["event_size"].asUInt();
        port = val["port"].asUInt();
        root = val["root"].asString();

        std::string log_level_tmp = val["log_level"].asString();
        switch (log_level_tmp)
        {
            case debug_:
                log_level = debug;
                break;
            case normal_:
                log_level = normal;
                break;
            case warn_:
                log_level = warn;
                break;
            default:
                log_level = normal;
                break;
        }
    }
    catch (...){

    }
}

void Configure::printConfigure()
{
    if(log_level != debug)
        return ;
    std::cout << "buffer_size :" << buffer_size << std::endl;
    std::cout << "event_size :" << event_size << std::endl;
    std::cout << "port :" << port << std::endl;
    std::cout << "root :" << root << std::endl;

}

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
