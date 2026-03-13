cmake_minimum_required(VERSION 3.14)
project(Library)
set(CMAKE_CXX_STANDARD 17)

add_executable(Library
src/main.cpp
)

target_include_directories(Library PRIVATE include)
