cmake_minimum_required(VERSION 3.10)
project(architecture)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable testing
enable_testing()

# Google Test
set(GTEST_DIR "../../googletest")
include_directories("${GTEST_DIR}/googletest/include")
add_subdirectory(${GTEST_DIR} ${CMAKE_BINARY_DIR}/googletest EXCLUDE_FROM_ALL)
set(DEPS_DIR ../)

# Add subdirectories
add_subdirectory(controller)
add_subdirectory(model)
add_subdirectory(view)

# Add deps subdirectories
add_subdirectory(${CMAKE_SOURCE_DIR}/lib ${CMAKE_BINARY_DIR}/deps_lib)
add_subdirectory(${CMAKE_SOURCE_DIR}/logging ${CMAKE_BINARY_DIR}/deps_logging)

# Create the executable
add_executable(app app/main.cpp)

# Link the libraries
target_link_libraries(app controller model view logging)

# Clang-Format
file(GLOB_RECURSE ALL_CXX_SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/app/*/*.[ch]*"
    "${PROJECT_SOURCE_DIR}/controller/*/*.[ch]*"
    "${PROJECT_SOURCE_DIR}/model/*.[ch]*"
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

add_custom_target(ut
    DEPENDS controller_ut view_ut model_ut
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

