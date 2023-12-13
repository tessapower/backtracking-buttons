cmake_minimum_required(VERSION 3.25)

project(backtracking_buttons)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    include(CTest)
endif()

add_subdirectory(bin)
add_subdirectory(src)
