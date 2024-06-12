#logging/CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

project(logging VERSION 1.0)

# C++の標準を設定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(logging STATIC src/logger.cpp)

target_include_directories(logging PUBLIC h ../lib/h)

add_executable(logging_ut_exe ut/logger_ut.cpp)

target_include_directories(logging_ut_exe PRIVATE ../../../deep/h ../lib/h)
target_link_libraries(logging_ut_exe logging gtest gtest_main)

enable_testing()
add_test(NAME logging_ut COMMAND logging_ut_exe)

add_custom_target(logging_ut
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS logging_ut_exe
)

