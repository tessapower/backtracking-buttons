cmake_minimum_required(VERSION 3.20)
project(a3)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
set(SOURCES
        src/algorithms.cpp
        src/coord.cpp
        src/statics.cpp
        src/pixel_class.cpp
        src/io.cpp
        src/bounds.cpp
        )
set(HEADERS
        include/algorithms.h
        include/coord.h
        include/statics.h
        include/pixel_class.h
        include/io.h
        include/bounds.h
        )

add_executable(main ${SOURCES} ${HEADERS} bin/main.cpp)

