add_executable(test_concurrency test_concurrent_stack.cc test_concurrent_rate_limiter.cc)
target_include_directories(test_concurrency PRIVATE ${CMAKE_SOURCE_DIR}/)
target_link_libraries(test_concurrency PRIVATE GTest::gtest_main concurrency)


add_executable(test_data_structures test_circular_array.cc test_optional.cc)
target_include_directories(test_data_structures PRIVATE ${CMAKE_SOURCE_DIR}/)
target_link_libraries(test_data_structures PRIVATE GTest::gtest_main)

add_executable(test_metaprogramming test_crtp.cc test_typelist.cpp)
target_include_directories(test_metaprogramming PRIVATE ${CMAKE_SOURCE_DIR}/)
target_link_libraries(test_metaprogramming PRIVATE GTest::gtest_main)

add_executable(test_design_patterns test_decorator_static.cc test_mixin.cc)
target_include_directories(test_design_patterns PRIVATE ${CMAKE_SOURCE_DIR}/)
target_link_libraries(test_design_patterns PRIVATE GTest::gtest_main)

add_executable(test_allocators test_pool_allocator.cpp)
target_include_directories(test_allocators PRIVATE ${CMAKE_SOURCE_DIR}/)
target_link_libraries(test_allocators PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_concurrency)
gtest_discover_tests(test_metaprogramming)
gtest_discover_tests(test_design_patterns)
gtest_discover_tests(test_data_structures)

add_subdirectory(perf)