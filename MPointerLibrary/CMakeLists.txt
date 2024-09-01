cmake_minimum_required(VERSION 3.29)
project(MPointerLibrary)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    include/DoublyLinkedList.h
    include/MPointerGC.h
    src/MPointerGC.cpp
    include/MPointer.h
)

add_library(MPointerLibrary STATIC ${SOURCES})