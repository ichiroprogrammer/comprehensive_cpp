cmake_minimum_required(VERSION 3.10)
project(MVCExample)

set(CMAKE_CXX_STANDARD 14)

# Add subdirectories
add_subdirectory(controller)
add_subdirectory(model)
add_subdirectory(view)
add_subdirectory(ut)

# Include directories
include_directories(controller/h model/h view/h)

# Create the executable
add_executable(app app/main.cpp)

# Link the libraries
target_link_libraries(app controller model view)
