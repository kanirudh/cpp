//
// Created by Anirudh Agrawal on 11/28/25.
//

#include "data_structures/optional.h"
#include "gtest/gtest.h"

namespace {
enum class Modes : uint8_t {
  kNetwork = 0,
  kDisk = 1,
  kRam = 2,
  kInvalid = 3
};

enum class Airlines : uint8_t {
  kIndia = 0,
  kSingapore = 1,
  kAustralia = 2,
  kHongKong = 3,
  kNetherlands = 4,
  kInvalid = 5
};

}
TEST(Optional, basic) {

  Optional<Modes, Modes::kInvalid> mode;
  static_assert(sizeof(mode) == sizeof(Modes), "");
  static_assert(sizeof(mode) == sizeof(uint8_t), "");
  EXPECT_FALSE(mode.has_value());

  mode = Modes::kNetwork;
  EXPECT_TRUE(mode.has_value());
}

TEST(Optional, bit_packing) {
  struct PackedStruct {
    Modes mode : 3;
    Airlines airlines : 3;
  };
  static_assert(sizeof(PackedStruct) == sizeof(uint8_t), "");
}