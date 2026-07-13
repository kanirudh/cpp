# EXCLUDE_FROM_ALL: this currently fails to link on AppleClang 21 (Xcode 26
# beta). The compiler mis-resolves the unqualified `Benchmark` name inside
# benchmark.h's `internal` namespace to a nonexistent benchmark::internal::
# Benchmark type when the TU also uses std::string, producing undefined
# symbols at link time. Reproduces the same way regardless of how gtest/
# benchmark are obtained (FetchContent, Homebrew, vcpkg) -- it's a compiler
# bug, not a dependency/build-system issue. Build explicitly with
# `cmake --build . --target perf_data_structures` once fixed/upstream'd.
add_executable(perf_data_structures EXCLUDE_FROM_ALL perf_circular_array.cc)
target_link_libraries(perf_data_structures benchmark::benchmark)