cmake_minimum_required(VERSION 3.31)

project(cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Show compile commands" FORCE)

add_subdirectory(metaprogramming)
add_subdirectory(design_patterns)

add_custom_target(create_symlink ALL
    COMMAND ${CMAKE_COMMAND} -E create_symlink 
        ${CMAKE_BINARY_DIR}/compile_commands.json 
        ${CMAKE_SOURCE_DIR}/compile_commands.json
    COMMENT "Creating symbolic link for compile_commands.json in the source directory"
)
