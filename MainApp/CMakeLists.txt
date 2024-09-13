cmake_minimum_required(VERSION 3.29)
project(MainApp)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(../MPointerLibrary ../../MPointerLibrary/build/)

include_directories(include)

SET(SOURCES
    src/DoublyLinkedList.cpp
    src/SortAlgorithms.cpp
)

add_executable(MainApp main.cpp ${SOURCES})

target_include_directories(MainApp PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../MPointerLibrary/include")
target_link_libraries(MainApp PRIVATE MPointerLibrary)

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
        tests/SortAlgorithmsTest.cpp
        tests/DoublyLinkedListTest.cpp
)

add_executable(MainApp_GTests_run ${TEST_SOURCES} ${SOURCES})
target_include_directories(MainApp_GTests_run PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../MPointerLibrary/include")
target_link_libraries(MainApp_GTests_run gtest gtest_main MPointerLibrary)
add_test(NAME MainApp_GTests_run COMMAND MainApp_GTests_run )