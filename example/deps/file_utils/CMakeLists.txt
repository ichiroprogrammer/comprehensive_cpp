cmake_minimum_required(VERSION 3.10)

project(file_utils VERSION 1.0)

# C++の標準を設定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(file_utils STATIC
    src/load_store_row.cpp
    src/path_utils.cpp
)

target_include_directories(file_utils PUBLIC ../file_utils/h)

add_executable(file_utils_ut_exe ut/load_store_row_ut.cpp ut/path_utils_ut.cpp)

target_link_libraries(file_utils_ut_exe file_utils logging gtest gtest_main)

target_include_directories(file_utils_ut_exe PRIVATE h ../../../deep/h ../logging/h ../lib/h)

add_custom_command(TARGET file_utils_ut_exe POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/ut_data $<TARGET_FILE_DIR:file_utils_ut_exe>/ut_data
)

enable_testing()
add_test(NAME file_utils_ut COMMAND file_utils_ut_exe)

add_custom_target(file_utils_ut_copy_test_data
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_SOURCE_DIR}/ut_data $<TARGET_FILE_DIR:file_utils_ut_exe>/ut_data
)

# カスタムターゲットを追加して、ビルド後にテストを実行
add_custom_target(file_utils_ut
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS file_utils_ut_exe file_utils_ut_copy_test_data
)

