cmake_minimum_required(VERSION 3.10)

project(main_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(GTEST_DIR "../../googletest")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(${GTEST_DIR} ${CMAKE_BINARY_DIR}/googletest)

add_subdirectory(lib)
add_subdirectory(logging)
add_subdirectory(file_utils)
add_subdirectory(dependency)
add_subdirectory(app)


# カスタムターゲットを追加して、すべてのテストを実行
add_custom_target(tests
    DEPENDS app_ut dependency_ut file_utils_ut lib_ut logging_ut deps_it
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

