cmake_minimum_required(VERSION 3.29)
project(OOP_vector)

set(CMAKE_CXX_STANDARD 17)

# Add executable
add_executable(program main.cpp)

# Set Release build type with optimizations
set(CMAKE_BUILD_TYPE Release)

# Add compiler-specific optimization flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
elseif(MSVC)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
endif()

# Add test file location
set(TEST_FILE_LOCATION "${CMAKE_SOURCE_DIR}/../../test_files/")
target_compile_definitions(program PRIVATE TEST_FILE_LOCATION="${TEST_FILE_LOCATION}")

#-----------------------------------------------------------------

# Include FetchContent module
include(FetchContent)

# Fetch GoogleTest
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add test executable
add_executable(Studentai_tests
	Studentai_tests.cpp
        program.cpp
        template.h
)

# Link against Google Test
target_link_libraries(Studentai_tests PRIVATE
        gtest
        gtest_main
)

set(TEST_FILE_LOCATION "${CMAKE_SOURCE_DIR}/../../test_files/")
target_compile_definitions(Studentai_tests PRIVATE TEST_FILE_LOCATION="${TEST_FILE_LOCATION}")

enable_testing()
add_test(NAME StudentaiTests COMMAND studentai_tests)