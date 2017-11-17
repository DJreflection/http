cmake_minimum_required(VERSION 3.7)
project(http)

set(CMAKE_CXX_STANDARD 11)

set(readSourceFile read.cpp)
add_executable(readSourceFile ${readSourceFile})
target_link_libraries(readSourceFile jsoncpp)