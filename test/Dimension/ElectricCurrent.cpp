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

#include "../../include/PhQ/Dimension/ElectricCurrent.hpp"

#include <gtest/gtest.h>

namespace PhQ::Dimension {

namespace {

TEST(DimensionElectricCurrent, Abbreviation) {
  EXPECT_EQ(ElectricCurrent::Abbreviation(), "I");
}

TEST(DimensionElectricCurrent, Comparisons) {
  constexpr ElectricCurrent first{-1};
  constexpr ElectricCurrent second{2};
  EXPECT_EQ(first, first);
  EXPECT_NE(first, second);
  EXPECT_LT(first, second);
  EXPECT_LE(first, first);
  EXPECT_LE(first, second);
  EXPECT_GT(second, first);
  EXPECT_GE(second, first);
  EXPECT_GE(first, first);
}

TEST(DimensionElectricCurrent, CopyAssignment) {
  constexpr ElectricCurrent first{3};
  ElectricCurrent second{0};
  second = first;
  EXPECT_EQ(second, first);
}

TEST(DimensionElectricCurrent, CopyConstructor) {
  constexpr ElectricCurrent first{3};
  constexpr ElectricCurrent second{first};
  EXPECT_EQ(second, first);
}

TEST(DimensionElectricCurrent, DefaultConstructor) {
  EXPECT_NO_THROW(ElectricCurrent{});
}

TEST(DimensionElectricCurrent, Hash) {
  constexpr ElectricCurrent first{0};
  constexpr ElectricCurrent second{2};
  constexpr ElectricCurrent third{-1};
  constexpr std::hash<ElectricCurrent> hash;
  EXPECT_NE(hash(first), hash(second));
  EXPECT_NE(hash(first), hash(third));
  EXPECT_NE(hash(second), hash(third));
}

TEST(DimensionElectricCurrent, Label) {
  EXPECT_EQ(ElectricCurrent::Label(), "Electric Current");
}

TEST(DimensionElectricCurrent, MoveAssignment) {
  constexpr ElectricCurrent first{3};
  ElectricCurrent second{3};
  ElectricCurrent third{-1};
  third = std::move(second);
  EXPECT_EQ(third, first);
}

TEST(DimensionElectricCurrent, MoveConstructor) {
  constexpr ElectricCurrent first{3};
  ElectricCurrent second{3};
  ElectricCurrent third{std::move(second)};
  EXPECT_EQ(third, first);
}

TEST(DimensionElectricCurrent, Print) {
  EXPECT_EQ(ElectricCurrent().Print(), "");
  EXPECT_EQ(ElectricCurrent(-1).Print(), "I^(-1)");
  EXPECT_EQ(ElectricCurrent(0).Print(), "");
  EXPECT_EQ(ElectricCurrent(1).Print(), "I");
  EXPECT_EQ(ElectricCurrent(2).Print(), "I^2");
}

TEST(DimensionElectricCurrent, SizeOf) {
  EXPECT_EQ(sizeof(ElectricCurrent{}), sizeof(int8_t));
}

TEST(DimensionElectricCurrent, Stream) {
  constexpr ElectricCurrent dimension{3};
  std::ostringstream stream;
  stream << dimension;
  EXPECT_EQ(stream.str(), dimension.Print());
}

TEST(DimensionElectricCurrent, Value) {
  EXPECT_EQ(ElectricCurrent().Value(), 0);
  EXPECT_EQ(ElectricCurrent(-1).Value(), -1);
  EXPECT_EQ(ElectricCurrent(0).Value(), 0);
  EXPECT_EQ(ElectricCurrent(1).Value(), 1);
  EXPECT_EQ(ElectricCurrent(2).Value(), 2);
}

}  // namespace

}  // namespace PhQ::Dimension
