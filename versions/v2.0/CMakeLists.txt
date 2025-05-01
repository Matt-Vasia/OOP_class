cmake_minimum_required(VERSION 3.10)
project(OOP_vector)

# Add C++17 support
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set Release build type with optimizations
set(CMAKE_BUILD_TYPE Release)

# Add compiler-specific optimization flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
endif()

# Add executable
add_executable(program main.cpp)

# Add test file location
set(TEST_FILE_LOCATION "${CMAKE_SOURCE_DIR}/../../test_files/")
target_compile_definitions(program PRIVATE TEST_FILE_LOCATION="${TEST_FILE_LOCATION}")