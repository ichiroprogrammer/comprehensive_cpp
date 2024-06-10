cmake_minimum_required(VERSION 3.10)

project(dependency VERSION 1.0)

# C++の標準を設定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ライブラリのソースファイルを追加
add_library(dependency STATIC
    src/arch_pkg.cpp
    src/cpp_deps.cpp
    src/cpp_dir.cpp
    src/cpp_src.cpp
    src/deps_scenario.cpp
    src/load_store_format.cpp
)

target_include_directories(dependency PUBLIC ../dependency/h ../file_utils/h ../lib/h)

# テスト用のソースファイルを追加して単一の実行ファイルを生成
add_executable(dependency_ut_exe
    ut/arch_pkg_ut.cpp
    ut/cpp_deps_ut.cpp
    ut/cpp_dir_ut.cpp
    ut/cpp_src_ut.cpp
    ut/deps_scenario_ut.cpp
    ut/load_store_format_ut.cpp
)

# テスト対象のライブラリとGoogleTestのリンク
target_link_libraries(dependency_ut_exe dependency file_utils logging gtest gtest_main)

# インクルードディレクトリの設定
target_include_directories(dependency_ut_exe PRIVATE ../../../deep/h src)

# テストを追加
enable_testing()
add_test(NAME dependency_ut COMMAND dependency_ut_exe)

add_custom_target(dependency_ut_copy_test_data
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_SOURCE_DIR}/ut_data $<TARGET_FILE_DIR:dependency_ut_exe>/ut_data
)

# カスタムターゲットを追加して、ビルド後にテストを実行
add_custom_target(dependency_ut
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS dependency_ut_exe dependency_ut_copy_test_data
)

