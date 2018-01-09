cmake_minimum_required(VERSION 3.7)
project(HTTP)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(./src Srcs)
set(httpConfigureSourceFile main.cpp ${Srcs})
add_executable(Http ${httpConfigureSourceFile})
target_link_libraries(Http jsoncpp pthread)

set(testConfigureSourceFile test/testConfigure.cpp src/Configure.h)
add_executable(testConfigure ${testConfigureSourceFile})
target_link_libraries(testConfigure jsoncpp)

set(testTimeSourceFile test/testTime.cpp src/Time.cpp src/Time.h)
add_executable(testTime ${testTimeSourceFile})
target_link_libraries(testTime jsoncpp)

set(testLogSourceFile test/testLog.cpp src/Log.h src/Configure.h src/Time.cpp src/Queue.h)
add_executable(testLog ${testLogSourceFile})
target_link_libraries(testLog jsoncpp pthread)

