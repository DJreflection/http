#include <iostream>

#include "./src/HttpServer.h"
using namespace std;

int main() {
    HttpServer httpServer(2048);
    httpServer.start();
}