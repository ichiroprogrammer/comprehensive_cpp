# deps/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(main_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(GTEST_DIR "../../googletest")

add_subdirectory(${GTEST_DIR} ${CMAKE_BINARY_DIR}/googletest)

add_subdirectory(lib)
add_subdirectory(logging)
add_subdirectory(file_utils)

