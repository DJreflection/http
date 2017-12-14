cmake_minimum_required(VERSION 3.7)
project(http)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Configure.cpp Configure.h Time.cpp Time.h)
add_executable(http ${SOURCE_FILES})
target_link_libraries(http pthread)


set(testConfigureSourceFile test/testConfigure.cpp Configure.cpp Configure.h)
add_executable(testConfigure ${testConfigureSourceFile})
target_link_libraries(testConfigure jsoncpp)

set(testTimeSourceFile test/testTime.cpp Time.cpp Time.h)
add_executable(testTime ${testTimeSourceFile})
target_link_libraries(testTime jsoncpp)

set(testLogSourceFile test/testLog.cpp Log.hpp Configure.cpp Configure.h Time.cpp Time.h Queue.hpp)
add_executable(testLog ${testLogSourceFile})
target_link_libraries(testLog jsoncpp pthread)

set(testHttpServerSourceFile test/testHttpServer.cpp HttpServer.cpp HttpServer.h Log.hpp TcpServer.cpp TcpServer.h TcpConnection.cpp TcpConnection.h Configure.cpp Configure.h Time.cpp Time.h)
add_executable(testHttpServer ${testHttpServerSourceFile})
target_link_libraries(testHttpServer jsoncpp)


set(safdsf test/safdsf.cpp)
add_executable(safdsf ${safdsf})
target_link_libraries(safdsf)