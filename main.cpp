#include <iostream>

#include "./src/HttpServer.h"
#include "./src/Configure.h"

using namespace std;

int main() {
    Configure::getInstance().setUri("../Config");
    Configure::getInstance().init();

    std::cout << Configure::getInstance().getPort() << std::endl;

    Log::getInstance().setLogRoot(Configure::getInstance().getRoot());
    Log::getInstance().setLogLevel(Configure::getInstance().getLogLevel());
    Log::getInstance().start();

    HttpServer httpServer(Configure::getInstance().getPort());
    httpServer.setRoot(Configure::getInstance().getRoot());
    httpServer.start();
}