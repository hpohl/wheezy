# Minimum is 2.8
cmake_minimum_required(VERSION 2.8)

# Set module path
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/mod)

# Set bin
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# Set lib
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

# Project is wheezy
project(wheezy)

# Use C++ 11
add_definitions(-std=c++11 -Wall)

# Use GCC 4.8
set(CMAKE_CXX_COMPILER g++-4.8)

# Use FreeImage
find_package(FreeImage REQUIRED)
include_directories(${FREEIMAGE_INCLUDE_PATH})

# Use GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})

# Use GLUT
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

# Include source
include_directories(${CMAKE_SOURCE_DIR}/src)

# Add source
add_subdirectory(src)
