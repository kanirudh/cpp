cmake_minimum_required(VERSION 3.23)
project(design_patterns)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(metaprogramming)

add_executable(Adaptor Adaptor.cpp)
add_executable(Fluent Fluent.cpp)
add_executable(Decorator Decorator.cpp)
add_executable(Visitor Visitor.cpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Show compile commands" FORCE)
