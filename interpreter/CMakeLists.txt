cmake_minimum_required(VERSION 3.10)
project(SOS_Project)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(sos
    sos.cc
    interpret.cc
    stack_class.cc
    bitwise_io.cc
)

# Include directories
target_include_directories(sos PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
