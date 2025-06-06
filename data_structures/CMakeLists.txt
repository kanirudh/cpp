add_executable(data_structures_test
    test_circular_array.cc)
target_link_libraries(data_structures_test
    GTest::gtest_main
)

include(GoogleTest)
# gtest_discover_tests(data_structures_test)

