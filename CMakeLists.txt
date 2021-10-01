cmake_minimum_required(VERSION 3.20)
project(a3)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
set(SOURCES
        src/button_utils.cpp
        src/Coord.cpp
        src/statics.cpp
        src/pixel_class.cpp
        )
set(HEADERS
        include/button_utils.h
        include/Coord.h
        include/statics.h
        include/pixel_class.h
        )

add_executable(main ${SOURCES} ${HEADERS} bin/main.cpp)

