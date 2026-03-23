cmake_minimum_required(VERSION 3.31.6)

project(cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Show compile commands" FORCE)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(BENCHMARK_ENABLE_TESTING off)
FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG        v1.9.4  # use desired release tag or commit hash
)

FetchContent_MakeAvailable(googletest benchmark)

add_subdirectory(concurrency)
add_subdirectory(data_structures)
add_subdirectory(design_patterns)
add_subdirectory(metaprogramming)
add_subdirectory(test)

if(WIN32)
    # On Windows, symlinking compile_commands.json might fail without admin/developer mode
    # We can use a copy instead for better reliability
    add_custom_target(create_symlink ALL
        COMMAND ${CMAKE_COMMAND} -E copy 
            ${CMAKE_BINARY_DIR}/compile_commands.json 
            ${CMAKE_SOURCE_DIR}/compile_commands.json
        COMMENT "Copying compile_commands.json to the source directory"
    )
else()
    add_custom_target(create_symlink ALL
        COMMAND ${CMAKE_COMMAND} -E create_symlink 
            ${CMAKE_BINARY_DIR}/compile_commands.json 
            ${CMAKE_SOURCE_DIR}/compile_commands.json
        COMMENT "Creating symbolic link for compile_commands.json in the source directory"
    )
endif()

enable_testing()