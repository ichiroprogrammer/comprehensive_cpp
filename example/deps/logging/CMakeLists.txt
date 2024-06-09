#logging/CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

project(logging VERSION 1.0)

# C++の標準を設定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(logging STATIC src/logger.cpp)

target_include_directories(logging PUBLIC h ../lib/h)

add_executable(logging_ut_exe ut/logger_ut.cpp)

# GoogleTestのターゲットをチェック
if(NOT TARGET gtest)
    message(FATAL_ERROR "gtest target not found. Make sure googletest is added at the top level CMakeLists.txt")
endif()

target_include_directories(logging_ut_exe PRIVATE ../../../deep/h ../lib/h)
target_link_libraries(logging_ut_exe logging gtest gtest_main)

enable_testing()
add_test(NAME logger_ut COMMAND logging_ut_exe)

add_custom_target(logging_ut_run
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS logging_ut_exe
)

