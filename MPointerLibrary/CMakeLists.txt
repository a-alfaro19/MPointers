cmake_minimum_required(VERSION 3.29)
project(MPointerLibrary)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    src/MPointerGC.cpp
)

add_library(MPointerLibrary STATIC ${SOURCES})

# Add Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add test files
set(TEST_SOURCES
        tests/DoublyLinkedListTest.cpp
        tests/MPointerTest.cpp
        tests/MPointerGCTest.cpp
)

# 'Google_Tests_run' is the target name
add_executable(Google_Tests_run ${TEST_SOURCES} ${SOURCES})
target_link_libraries(Google_Tests_run gtest gtest_main)
add_test(NAME Google_Tests_run COMMAND Google_Tests_run)