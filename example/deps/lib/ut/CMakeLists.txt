cmake_minimum_required(VERSION 3.10)

project(lib_ut VERSION 1.0)

# C++の標準を設定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# GoogleTestディレクトリを指定
# 必要に応じて自分の環境に合わせてパスを変更してください
set(GTEST_DIR "../../../../googletest")

# GoogleTestをビルド
add_subdirectory(${GTEST_DIR} ${CMAKE_BINARY_DIR}/googletest)

# テスト用のソースファイルを追加
add_executable(nstd_ut nstd_ut.cpp)

# ライブラリのインクルードディレクトリを指定
target_include_directories(nstd_ut PRIVATE ../../h/ ../h ../../../../deep/h)

# GoogleTestのリンク
target_link_libraries(nstd_ut gtest gtest_main)

# テストを追加
enable_testing()
add_test(NAME nstd_ut_test COMMAND nstd_ut)

# カスタムターゲットを追加して、ビルド後にテストを実行
add_custom_target(ut
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS nstd_ut
)

