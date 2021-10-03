cmake_minimum_required(VERSION 3.20)
project(a3)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
set(SOURCES
        src/algorithms.cpp
        src/circle.cpp
        src/point.cpp
        src/io.cpp
        src/pixel_class.cpp
        src/rect.cpp
        src/statics.cpp
        )
set(HEADERS
        include/algorithms.h
        include/button.h
        include/circle.h
        include/color.h
        include/point.h
        include/io.h
        include/pixel_class.h
        include/rect.h
        include/statics.h
        )

add_executable(main ${SOURCES} ${HEADERS} bin/main.cpp)

