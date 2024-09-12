cmake_minimum_required(VERSION 3.29)
project(MPointerLibrary)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

set(SOURCES
    src/MPointerList.cpp
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
        tests/MPointerTest.cpp
        tests/MPointerGCTest.cpp
)

# 'MPointerLib_GTests_run' is the target name
add_executable(MPointerLib_GTests_run ${TEST_SOURCES} ${SOURCES})
target_link_libraries(MPointerLib_GTests_run gtest gtest_main)
add_test(NAME MPointerLib_GTests_run COMMAND MPointerLib_GTests_run)