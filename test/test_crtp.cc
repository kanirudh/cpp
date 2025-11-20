//
// Created by Anirudh Agrawal on 11/20/25.
//

#include "design_patterns/crtp.h"
#include "design_patterns/crtp.h"
#include "gtest/gtest.h"

TEST(Crtp, Basic) {
  Derived *derived = new Derived();
  derived->Name();
}
