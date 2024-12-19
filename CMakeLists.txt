cmake_minimum_required(VERSION 3.23)
set(CMAKE_C_COMPILER /opt/gcc132/bin/gcc)
set(CMAKE_CXX_COMPILER /opt/gcc132/bin/g++)

project(cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Show compile commands" FORCE)

add_subdirectory(metaprogramming)
add_subdirectory(design_patterns)
