add_library(view STATIC src/view.cpp)
target_include_directories(view PRIVATE src ../view/h ${CMAKE_SOURCE_DIR}/logging/h ${CMAKE_SOURCE_DIR}/lib/h)
target_include_directories(view PUBLIC ../view/h ../model/h)

# Unit test
add_executable(view_ut ut/view_ut.cpp)

target_link_libraries(view_ut view gtest gtest_main logging)
add_test(NAME ViewTest COMMAND view_ut)
