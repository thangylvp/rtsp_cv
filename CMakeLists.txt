cmake_minimum_required(VERSION 2.8)
project(rtsp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


find_package(OpenCV 4.0 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(GetStream src/1.GetStream/main.cpp)
target_link_libraries(GetStream ${OpenCV_LIBS})

add_executable(Test src/0.Test/main.cpp)
target_link_libraries(Test ${OpenCV_LIBS})
