cmake_minimum_required(VERSION 3.10)

project(app VERSION 1.0)

# C++の標準を設定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# アプリケーションのメインソースファイルを追加
add_executable(deps src/main.cpp src/deps_opts.cpp)

target_link_libraries(deps dependency file_utils logging)
target_include_directories(deps PRIVATE ../dependency/h ../file_utils/h ../lib/h)


# テスト用のソースファイルを追加
add_executable(app_ut_exe src/deps_opts.cpp ut/deps_opts_ut.cpp)

target_include_directories(app_ut_exe PRIVATE ../../../deep/h
    ../dependency/h ../file_utils/h ../lib/h src)
target_link_libraries(app_ut_exe file_utils logging gtest gtest_main)

enable_testing()
add_test(NAME app_ut COMMAND app_ut_exe)

# カスタムターゲットを追加して、ビルド後にテストを実行
add_custom_target(app_ut
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS app_ut_exe
)

enable_testing()
add_test(NAME deps_it COMMAND ../../it.sh deps)

add_custom_target(deps_it
    COMMAND ../../it.sh deps
    DEPENDS deps
)

