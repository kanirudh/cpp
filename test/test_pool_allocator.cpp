//
// Created by Anirudh Agrawal on 2/14/26.
//

#include "allocators/PoolAllocator.h"
#include <vector>
#include <list>
#include "gtest/gtest.h"

/*
TEST(Allocator, PoolAllocatorWithVector) {
  std::vector<int, allocator::PoolAllocator<int>> vec;
  for (int i = 0; i < 10; i++) {
    vec.push_back(i);
  }
  for (int i = 0; i < 10; i++) {
    ASSERT_EQ(vec[i], i);
  }
}
*/

// TODO(anirudh): PoolAllocator deletes its copy/move constructors, but
// std::list requires its allocator to be copy-constructible (libc++ copies
// the allocator when creating nodes). Re-enable once PoolAllocator supports
// sharing its pool across copies.
/*
TEST(Allocator, PoolAllocatorWithList) {
  std::list<int, allocator::PoolAllocator<int>> l;
  for (int i =0; i < 64; ++i) {
    l.push_back(i);
  }
  auto itr = l.cbegin();
  for (int i =0; i < 64; ++i, ++itr) {
    ASSERT_EQ(*itr, i);
  }
}
*/