cmake_minimum_required(VERSION 3.10)
project(OOP_deque)

# Add C++11 support
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(program uzd.cpp)

# Add test file location
set(TEST_FILE_LOCATION "${CMAKE_SOURCE_DIR}/../../test_files/")
target_compile_definitions(program PRIVATE TEST_FILE_LOCATION="${TEST_FILE_LOCATION}")

# Release
set(CMAKE_BUILD_TYPE Release)
