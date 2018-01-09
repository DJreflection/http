#include <iostream>

#include "./src/HttpServer.h"
#include "./src/Configure.h"

using namespace std;

int main() {
    Configure::getInstance().setUri("../Config");
    Configure::getInstance().init();

    HTTP::Log::getInstance().setLogRoot(Configure::getInstance().getRoot());
    HTTP::Log::getInstance().setLogLevel(Configure::getInstance().getLogLevel());
    HTTP::Log::getInstance().start();

    HttpServer httpServer(8080);
    httpServer.start();
}