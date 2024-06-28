add_library(model src/model.cpp src/command_executor.cpp)
target_include_directories(model PRIVATE src ${DEPS_DIR}/logging/h ${DEPS_DIR}/lib/h)
target_include_directories(model PUBLIC ../model/h)

# Unit test
add_executable(model_ut ut/model_ut.cpp ut/command_executor_ut.cpp)
target_include_directories(model_ut PRIVATE src ${DEPS_DIR}/logging/h ${DEPS_DIR}/lib/h)
target_link_libraries(model_ut model gtest gtest_main)
add_test(NAME ModelTest COMMAND model_ut)
