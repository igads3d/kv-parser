cmake_minimum_required(VERSION 3.10)
project(KVparser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(SOURCES_DIR src)
include_directories(${SOURCES_DIR})

add_library(KVparser src/KVparser.cpp)
