# Project Description

This project consists of two main components: `MPointerLibrary` and `MainApp`.
`MPointerLibrary` is a library that implements a garbage collector for pointers in C++.
`MainApp` is an application that uses `MPointerLibrary` to manage the memory of its pointers.
Additionally, the project includes unit tests for both components using Google Test.

## Instructions to Build and Run the Project

### Prerequisites

- CMake 3.29 or higher
- A compiler compatible with C++20
- Git

### Clone the Repository

```sh
git clone https://github.com/a-alfaro19/MPointers.git
cd MPointers
```

### Build the MPointerLibrary

1. Create a build directory for and navigate to it:

    ```sh
    mkdir -p build/MPointerLibrary
    cd build/MPointerLibrary
    ```

2. Configure the project with CMake:

    ```sh
   cmake ../../MPointerLibrary
    ```
   
3. Build the library:

    ```sh
   cmake --build .
    ```
   
### Run the MainApp

#### Set Paths in CMake to Include `MPointerLibrary`

To include `MPointerLibrary` in your CMake project, you need to set the appropriate paths in your CMakeLists.txt file. Here is an example of how to do it:  
Add the following lines to your `CMakeLists.txt` file in the MainApp directory:

```sh
    # Set the path to the MPointerLibrary
    set(MPOINTERLIBRARY_PATH "${CMAKE_SOURCE_DIR}/../MPointerLibrary")
    
    # Include the MPointerLibrary directory
    include_directories(${MPOINTERLIBRARY_PATH}/include)
    
    # Link the MPointerLibrary
    add_subdirectory(${MPOINTERLIBRARY_PATH} ${CMAKE_BINARY_DIR}/MPointerLibrary)
    target_link_libraries(MainApp MPointerLibrary)
```

1. Create a build directory for and navigate to it:

    ```sh
    mkdir -p build/MainApp
    cd build/MainApp
    ```
   
2. Configure the project with CMake:

    ```sh
    cmake ../../MainApp
    ```
   
3. Build the application:

    ```sh
    cmake --build .
    ```
   
4. Run the application:

    ```sh
    ./MainApp
    ```
   
### Run the Unit Tests

Tests for `MPointerLibrary`:

1. Create a build directory for and navigate to it (if you haven't already):

    ```sh
    mkdir -p build/MPointerLibraryTests
    cd build/MPointerLibraryTests
    ```
   
2. Configure the project with CMake (if you haven't already): 

    ```sh
    cmake ../../MPointerLibraryTests
    ```
   
3. Build the tests:

    ```sh
    cmake --build . --target MPointerLib_GTests_run
    ```

4. Run the tests:

    ```sh
    ./MPointerLib_GTests_run
    ```
   
Tests for `MainApp`:

1. Create a build directory for and navigate to it (if you haven't already):

    ```sh
    mkdir -p build/MainAppTests
    cd build/MainAppTests
    ```
   
2. Configure the project with CMake (if you haven't already):

    ```sh
    cmake ../../MainAppTests
    ```
   
3. Build the tests:

    ```sh
    cmake --build . --target MainApp_GTests_run
    ```
   
4. Run the tests:

    ```sh
    ./MainApp_GTests_run
    ```
   