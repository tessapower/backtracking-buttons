add_executable(main main.cpp)

target_compile_definitions(main PRIVATE "-DPPM_FILES=\"${PROJECT_SOURCE_DIR}//ppm//\"")

target_link_libraries(main PRIVATE alg)
target_link_libraries(main PRIVATE geom)
target_link_libraries(main PRIVATE img)