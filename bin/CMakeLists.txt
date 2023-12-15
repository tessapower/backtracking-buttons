add_executable(main main.cpp)

target_compile_definitions(main PRIVATE "-DPPM_FILES=\"${PROJECT_SOURCE_DIR}//ppm//\"")

# Match the default stack size on macOS/Linux (8 MB) for the recursive flood-fill
if(MSVC)
    target_link_options(main PRIVATE /STACK:8388608)
endif()

target_link_libraries(main PRIVATE alg)
target_link_libraries(main PRIVATE geom)
target_link_libraries(main PRIVATE img)