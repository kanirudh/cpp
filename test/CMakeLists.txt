add_executable(test_concurrent_stack test_concurrent_stack.cc)
target_include_directories(test_concurrent_stack PRIVATE ${CMAKE_SOURCE_DIR}/)
target_link_libraries(test_concurrent_stack PRIVATE GTest::gtest_main)


add_executable(test_data_structures test_circular_array.cc test_optional.cc)
target_include_directories(test_data_structures PRIVATE ${CMAKE_SOURCE_DIR}/)
target_link_libraries(test_data_structures PRIVATE GTest::gtest_main)

add_executable(test_metaprogramming test_crtp.cc)
target_include_directories(test_metaprogramming PRIVATE ${CMAKE_SOURCE_DIR}/)
target_link_libraries(test_metaprogramming PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_concurrent_stack)
gtest_discover_tests(test_data_structures)

add_subdirectory(perf)