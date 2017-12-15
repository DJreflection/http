cmake_minimum_required(VERSION 3.7)
project(HTTP)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(./src Srcs)
set(httpConfigureSourceFile main.cpp ${Srcs})
add_executable(Http ${httpConfigureSourceFile})
target_link_libraries(Http jsoncpp pthread)

set(testConfigureSourceFile test/testConfigure.cpp src/Configure.cpp src/Configure.h)
add_executable(testConfigure ${testConfigureSourceFile})
target_link_libraries(testConfigure jsoncpp)

set(testTimeSourceFile test/testTime.cpp src/Time.cpp src/Time.h)
add_executable(testTime ${testTimeSourceFile})
target_link_libraries(testTime jsoncpp)

set(testLogSourceFile test/testLog.cpp src/Log.hpp src/Configure.cpp src/Configure.h src/Time.cpp src/Time.h src/Queue.hpp)
add_executable(testLog ${testLogSourceFile})
target_link_libraries(testLog jsoncpp pthread)

set(testHttpServerSourceFile test/testHttpServer.cpp src/HttpServer.cpp src/HttpServer.h src/Log.hpp src/TcpServer.cpp src/TcpServer.h src/TcpConnection.cpp src/TcpConnection.h src/Configure.cpp src/Configure.h src/Time.cpp src/Time.h)
add_executable(testHttpServer ${testHttpServerSourceFile})
target_link_libraries(testHttpServer jsoncpp)


set(testSourceFile test/testtest.cpp)
add_executable(testSb ${testSourceFile})
target_link_libraries(testSb)