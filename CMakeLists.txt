cmake_minimum_required(VERSION 3.7)
project(http)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp OpSocket.h OpSocket.cpp Configure.cpp Configure.h ThreadWork.cpp ThreadWork.h QueueMessage.cpp QueueMessage.h)
add_executable(http ${SOURCE_FILES})
target_link_libraries(http pthread)
