add_library(controller src/controller.cpp)
target_include_directories(controller PUBLIC ../controller/h ../model/h ../view/h)

# Unit test
add_executable(controller_ut ut/controller_ut.cpp)
target_link_libraries(controller_ut controller model view gtest gtest_main)
add_test(NAME ControllerTest COMMAND controller_ut)
