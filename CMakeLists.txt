cmake_minimum_required(VERSION 3.7)
project(http)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp OpSocket.h OpSocket.cpp Configure.cpp Configure.h ThreadWork.cpp ThreadWork.h QueueMessage.cpp QueueMessage.h Time.cpp Time.h)
add_executable(http ${SOURCE_FILES})
target_link_libraries(http pthread)


set(testConfigureSourceFile test/testConfigure.cpp Configure.cpp Configure.h)
add_executable(testConfigure ${testConfigureSourceFile})
target_link_libraries(testConfigure jsoncpp)

set(testTimeSourceFile test/testTime.cpp Time.cpp Time.h)
add_executable(testTime ${testTimeSourceFile})
target_link_libraries(testTime jsoncpp)

set(testLogSourceFile test/testLog.cpp Log.cpp Log.h Configure.cpp Configure.h Time.cpp Time.h)
add_executable(testLog ${testLogSourceFile})
target_link_libraries(testLog jsoncpp)

set(testLogSourceFile2 fff.cpp Log.cpp Log.h Configure.cpp Configure.h Time.cpp Time.h)
add_executable(fff ${testLogSourceFile2})
target_link_libraries(fff jsoncpp)


set(testHttpServerSourceFile test/testHttpServer.cpp HttpServer.cpp HttpServer.h EpollThread.cpp EpollThread.h Log.cpp Log.h Configure.cpp Configure.h Time.cpp Time.h)
add_executable(testHttpServer ${testHttpServerSourceFile})
target_link_libraries(testHttpServer jsoncpp)