
cmake_minimum_required(VERSION 3.8.0)
if(WIN32)
    set(CMAKE_C_COMPILER  "C:/msys64/ucrt64/bin/gcc.exe")
    set(CMAKE_CXX_COMPILER  "C:/msys64/ucrt64/bin/g++.exe")
endif()

project(tower-defense-cli VERSION 0.1.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for source code
include_directories(src)

# Add source files for the main executable
file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h)
add_executable(tower-defense-cli ${SOURCE_FILES})

# Platform-specific configurations
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Configuring for macOS")
    if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
        message(STATUS "Building for Apple Silicon (arm64)")
        set(CMAKE_OSX_ARCHITECTURES "arm64")
    elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
        message(STATUS "Building for Intel (x86_64)")
        set(CMAKE_OSX_ARCHITECTURES "x86_64")
    endif()
endif()
