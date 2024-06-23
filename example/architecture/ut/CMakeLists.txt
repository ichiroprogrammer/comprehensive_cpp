enable_testing()

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
