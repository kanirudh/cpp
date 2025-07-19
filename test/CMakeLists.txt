add_executable(test test_concurrent_stack.cc)
target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR}/)
target_link_libraries(test PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(hello_test)