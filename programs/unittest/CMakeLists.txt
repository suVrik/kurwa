cmake_minimum_required(VERSION 3.8.2)
project(unittest)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(unittest main.cpp)
