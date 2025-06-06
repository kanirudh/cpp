# Actually use bazel maybe and see if that works.
add_executable(test test_concurrent_stack.cc)
# TODO(anirudh): Improve this once we create specific targets for each libraries.
target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR}/)
target_link_libraries(test PRIVATE GTest::gtest_main)
