#file_utils/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(file_utils VERSION 1.0)

# C++の標準を設定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(file_utils STATIC
    src/load_store_row.cpp
    src/path_utils.cpp
)

target_include_directories(file_utils PUBLIC h)

add_executable(file_utils_ut_exe ut/load_store_row_ut.cpp ut/path_utils_ut.cpp)

target_link_libraries(file_utils_ut_exe file_utils logging gtest gtest_main)

target_include_directories(file_utils_ut_exe PRIVATE h ../../../deep/h ../logging/h ../lib/h)

enable_testing()
add_test(NAME file_utils_ut_test COMMAND file_utils_ut_exe)

# カスタムターゲットを追加して、ビルド後にテストを実行
add_custom_target(file_utils_ut_run
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS file_utils_ut_exe
)
