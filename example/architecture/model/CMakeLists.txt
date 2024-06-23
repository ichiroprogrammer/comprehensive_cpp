add_library(model src/model.cpp)
target_include_directories(model PUBLIC ../model/h)

# Unit test
add_executable(model_ut ut/model_ut.cpp)
target_link_libraries(model_ut model gtest gtest_main)
add_test(NAME ModelTest COMMAND model_ut)
