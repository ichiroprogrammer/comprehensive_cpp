cmake_minimum_required(VERSION 3.10)
project(architecture)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(GTEST_DIR "../../googletest")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories("${GTEST_DIR}/googletest/include")
add_subdirectory(${GTEST_DIR} ${CMAKE_BINARY_DIR}/googletest EXCLUDE_FROM_ALL)

# Add subdirectories
add_subdirectory(controller)
add_subdirectory(model)
add_subdirectory(view)

# Include directories
include_directories(controller/h model/h view/h)

# Create the executable
add_executable(app app/main.cpp)

# Link the libraries
target_link_libraries(app controller model view)

# Clang-Format
file(GLOB_RECURSE ALL_CXX_SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/app/*/*.[ch]*"
    "${PROJECT_SOURCE_DIR}/controller/*/*.[ch]*"
    "${PROJECT_SOURCE_DIR}/model/*.h"
    "${PROJECT_SOURCE_DIR}/view/*/*.[ch]*"
)

add_custom_target(
    clang-format
    COMMAND clang-format
    -i
    -style=file
    ${ALL_CXX_SOURCE_FILES}
)

add_dependencies(app clang-format)
