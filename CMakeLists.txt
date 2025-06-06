cmake_minimum_required(VERSION 3.23)
set(CMAKE_C_COMPILER /opt/gcc132/bin/gcc)
set(CMAKE_CXX_COMPILER /opt/gcc132/bin/g++)
set(CMAKE_BUILD_RPATH /opt/gcc132/lib64)

project(cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Show compile commands" FORCE)

add_subdirectory(concurrency)
add_subdirectory(design_patterns)
add_subdirectory(metaprogramming)
add_subdirectory(test)

add_custom_target(create_symlink ALL
    COMMAND ${CMAKE_COMMAND} -E create_symlink 
        ${CMAKE_BINARY_DIR}/compile_commands.json 
        ${CMAKE_SOURCE_DIR}/compile_commands.json
    COMMENT "Creating symbolic link for compile_commands.json in the source directory"
)
