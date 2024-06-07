cmake_minimum_required(VERSION 3.10)

project(logging VERSION 1.0)

# C++の標準を設定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# GoogleTestディレクトリを指定
# 必要に応じて自分の環境に合わせてパスを変更してください
set(GTEST_DIR "../../../googletest")

# GoogleTestをビルド
add_subdirectory(${GTEST_DIR} ${CMAKE_BINARY_DIR}/googletest)

# ライブラリのソースファイルを追加
add_library(logging STATIC src/logger.cpp)

# ライブラリのインクルードディレクトリを指定
target_include_directories(logging PUBLIC h ../lib/h)

# テスト用のソースファイルを追加
add_executable(logger_ut ut/logger_ut.cpp)

# テスト対象のライブラリとGoogleTestのインクルードディレクトリを指定
target_include_directories(logger_ut PRIVATE ../../../deep/h ../lib/h)
target_link_libraries(logger_ut logging gtest gtest_main)


# テストを追加
enable_testing()
add_test(NAME logger_ut_test COMMAND logger_ut)

# カスタムターゲットを追加して、ビルド後にテストを実行
add_custom_target(ut
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS logger_ut
)

