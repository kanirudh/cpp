cmake_minimum_required(VERSION 3.18)
project(design_patterns)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(TMP)

add_executable(Adaptor Adaptor.cpp)
add_executable(Fluent Fluent.cpp)
