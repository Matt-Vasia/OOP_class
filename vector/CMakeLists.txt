cmake_minimum_required(VERSION 3.10)
project(OOP_vector)

# Add C++11 support
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add optimization flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_executable(program uzd.cpp)