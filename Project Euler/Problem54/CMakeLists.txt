cmake_minimum_required(VERSION 3.10)

# Set project name
project(MyProject)

# Enable testing with CTest
enable_testing()

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)

# Add Google Test - Using the FetchContent module (you could also use ExternalProject or submodule)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1  # You can choose a specific version
)
# Fetch and make available gtest
FetchContent_MakeAvailable(googletest)

# Add the main project sources (adjust this part to your actual project)
add_executable(Problem54 problem54.cpp poker.cpp)

# Add the tests executable
add_executable(test_suite test_example.cpp)

# Link the test executable with Google Test
target_link_libraries(test_suite gtest gtest_main)

# Register the test executable with CTest
add_test(NAME example_test COMMAND test_suite)