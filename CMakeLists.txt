cmake_minimum_required(VERSION 3.20)
project(String_proj)
set(CMAKE_CXX_STANDARD 20)

add_executable(String_proj String.cpp)
add_subdirectory(GTests)