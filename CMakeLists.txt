cmake_minimum_required(VERSION 3.31.6)

project(cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Show compile commands" FORCE)

find_package(GTest CONFIG REQUIRED)
find_package(benchmark CONFIG REQUIRED)

# Workaround: on this toolchain (AppleClang 21 / Xcode 26 beta), declarations
# built with BENCHMARK_STATIC_DEFINE (no explicit visibility attribute) fail
# to resolve against libbenchmark.a at link time, even though the symbols are
# exported with default visibility in the archive. Dropping the define makes
# benchmark.h apply an explicit visibility("default") attribute instead,
# which links correctly.
get_target_property(_benchmark_defs benchmark::benchmark INTERFACE_COMPILE_DEFINITIONS)
if(_benchmark_defs)
    list(REMOVE_ITEM _benchmark_defs "BENCHMARK_STATIC_DEFINE")
    set_target_properties(benchmark::benchmark PROPERTIES INTERFACE_COMPILE_DEFINITIONS "${_benchmark_defs}")
endif()
unset(_benchmark_defs)

# Must precede add_subdirectory() below: gtest_discover_tests()/add_test()
# calls in subdirectories only register with CTest if testing is already
# enabled when those subdirectories are processed.
enable_testing()

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