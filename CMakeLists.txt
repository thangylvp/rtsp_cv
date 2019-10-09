cmake_minimum_required(VERSION 2.8)
project(rtsp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


find_package(OpenCV  REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Threads REQUIRED)

add_executable(GetStream src/1.GetStream/main.cpp)
target_link_libraries(GetStream ${OpenCV_LIBS} Threads::Threads)

add_executable(GetStream1 src/1.GetStream/stdthread.cpp)
target_link_libraries(GetStream1 ${OpenCV_LIBS} Threads::Threads)

# add_executable(Test src/0.Test/main.cpp)
# target_link_libraries(Test ${OpenCV_LIBS} )
