cmake_minimum_required(VERSION 3.10)

project(main_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# CMakeオプションを定義
option(USE_SANITIZERS "Enable sanitizers" OFF)

# USE_SANITIZERS オプションをチェック
if(USE_SANITIZERS)
    message(STATUS "Sanitizers are enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,leak,undefined,float-divide-by-zero,float-cast-overflow")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address,leak,undefined,float-divide-by-zero,float-cast-overflow")
else()
    message(STATUS "Sanitizers are disabled")
endif()


set(GTEST_DIR "../../googletest")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("${GTEST_DIR}/googletest/include")

# googletestサブディレクトリを追加
add_subdirectory(${GTEST_DIR} ${CMAKE_BINARY_DIR}/googletest EXCLUDE_FROM_ALL)

add_subdirectory(lib)
add_subdirectory(logging)
add_subdirectory(file_utils)
add_subdirectory(dependency)
add_subdirectory(app)

# すべてのテストを実行するカスタムターゲットを追加
add_custom_target(tests
    DEPENDS app_ut dependency_ut file_utils_ut lib_ut logging_ut deps_it
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

