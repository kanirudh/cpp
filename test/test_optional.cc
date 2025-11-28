//
// Created by Anirudh Agrawal on 11/28/25.
//

#include "data_structures/optional.h"
#include "gtest/gtest.h"

TEST(Optional, basic) {
  enum Modes : uint8_t {
    kNetwork = 0,
    kDisk = 1,
    kRam = 2,
    kInvalid = 3
  };

  Optional<Modes, Modes::kInvalid> mode;
  EXPECT_FALSE(mode.has_value());

  mode = Modes::kNetwork;
  EXPECT_TRUE(mode.has_value());
}