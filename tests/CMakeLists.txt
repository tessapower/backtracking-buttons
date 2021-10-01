FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

add_executable(button_utils_tests button_utils_tests.cpp)
add_executable(pixel_tests pixel_class_tests.cpp)

target_link_libraries(button_utils_tests PRIVATE button_utils gtest gtest_main)
target_link_libraries(pixel_tests PRIVATE pixel gtest gtest_main)

add_test(NAME button_utils_tests COMMAND button_utils_tests)
add_test(NAME pixel_tests COMMAND pixel_tests)
