cmake_minimum_required(VERSION 3.29)
project(MPointerLibrary)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    include/DoublyLinkedList.h
    src/MPointerGC.cpp
)

add_library(MPointerLibrary STATIC ${SOURCES})