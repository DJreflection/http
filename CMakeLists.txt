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

set(testLogSourceFile test/testLog.cpp Log.cpp Log.h)
add_executable(testLog ${testLogSourceFile})
target_link_libraries(testLog jsoncpp)