cmake_minimum_required(VERSION 3.10)

project(lib VERSION 1.0)

# C++の標準を設定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(lib_ut_exe ut/nstd_ut.cpp)

if(NOT TARGET gtest)
    message(FATAL_ERROR "gtest target not found. Make sure googletest is added at the top level CMakeLists.txt")
endif()

target_include_directories(lib_ut_exe PRIVATE h ../../h/ ../../../deep/h)
target_link_libraries(lib_ut_exe gtest gtest_main)

enable_testing()
add_test(NAME lib_ut COMMAND lib_ut_exe)

add_custom_target(lib_ut
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS lib_ut_exe
)

