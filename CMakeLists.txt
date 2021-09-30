cmake_minimum_required(VERSION 3.20)
project(a3)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(a3 bin/main.cpp include/pixel.h src/pixel.cpp)
