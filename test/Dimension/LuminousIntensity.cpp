// Copyright 2020-2023 Alexandre Coderre-Chabot
//
// This file is part of Physical Quantities (PhQ), a C++ library of physical
// quantities, physical models, and units of measure for scientific computation.
//
// Physical Quantities is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at your
// option) any later version. Physical Quantities is distributed in the hope
// that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details. You should have received a
// copy of the GNU Lesser General Public License along with Physical Quantities.
// If not, see <https://www.gnu.org/licenses/>.

#include "../../include/PhQ/Dimension/LuminousIntensity.hpp"

#include <gtest/gtest.h>

namespace PhQ::Dimension {

namespace {

TEST(DimensionLuminousIntensity, Abbreviation) {
  EXPECT_EQ(LuminousIntensity::Abbreviation(), "J");
}

TEST(DimensionLuminousIntensity, Comparisons) {
  constexpr LuminousIntensity first{-1};
  constexpr LuminousIntensity second{2};
  EXPECT_EQ(first, first);
  EXPECT_NE(first, second);
  EXPECT_LT(first, second);
  EXPECT_LE(first, first);
  EXPECT_LE(first, second);
  EXPECT_GT(second, first);
  EXPECT_GE(second, first);
  EXPECT_GE(first, first);
}

TEST(DimensionLuminousIntensity, CopyAssignment) {
  constexpr LuminousIntensity first{3};
  LuminousIntensity second{0};
  second = first;
  EXPECT_EQ(second, first);
}

TEST(DimensionLuminousIntensity, CopyConstructor) {
  constexpr LuminousIntensity first{3};
  constexpr LuminousIntensity second{first};
  EXPECT_EQ(second, first);
}

TEST(DimensionLuminousIntensity, DefaultConstructor) {
  EXPECT_NO_THROW(LuminousIntensity{});
}

TEST(DimensionLuminousIntensity, Hash) {
  constexpr LuminousIntensity first{0};
  constexpr LuminousIntensity second{2};
  constexpr LuminousIntensity third{-1};
  constexpr std::hash<LuminousIntensity> hash;
  EXPECT_NE(hash(first), hash(second));
  EXPECT_NE(hash(first), hash(third));
  EXPECT_NE(hash(second), hash(third));
}

TEST(DimensionLuminousIntensity, Label) {
  EXPECT_EQ(LuminousIntensity::Label(), "Luminous Intensity");
}

TEST(DimensionLuminousIntensity, MoveAssignment) {
  constexpr LuminousIntensity first{3};
  LuminousIntensity second{3};
  LuminousIntensity third{-1};
  third = std::move(second);
  EXPECT_EQ(third, first);
}

TEST(DimensionLuminousIntensity, MoveConstructor) {
  constexpr LuminousIntensity first{3};
  LuminousIntensity second{3};
  LuminousIntensity third{std::move(second)};
  EXPECT_EQ(third, first);
}

TEST(DimensionLuminousIntensity, Print) {
  EXPECT_EQ(LuminousIntensity().Print(), "");
  EXPECT_EQ(LuminousIntensity(-1).Print(), "J^(-1)");
  EXPECT_EQ(LuminousIntensity(0).Print(), "");
  EXPECT_EQ(LuminousIntensity(1).Print(), "J");
  EXPECT_EQ(LuminousIntensity(2).Print(), "J^2");
}

TEST(DimensionLuminousIntensity, SizeOf) {
  EXPECT_EQ(sizeof(LuminousIntensity{}), sizeof(int8_t));
}

TEST(DimensionLuminousIntensity, Stream) {
  constexpr LuminousIntensity dimension{3};
  std::ostringstream stream;
  stream << dimension;
  EXPECT_EQ(stream.str(), dimension.Print());
}

TEST(DimensionLuminousIntensity, Value) {
  EXPECT_EQ(LuminousIntensity().Value(), 0);
  EXPECT_EQ(LuminousIntensity(-1).Value(), -1);
  EXPECT_EQ(LuminousIntensity(0).Value(), 0);
  EXPECT_EQ(LuminousIntensity(1).Value(), 1);
  EXPECT_EQ(LuminousIntensity(2).Value(), 2);
}

}  // namespace

}  // namespace PhQ::Dimension
