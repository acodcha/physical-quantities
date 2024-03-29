// Copyright 2020-2023 Alexandre Coderre-Chabot
//
// Physical Quantities (PhQ): A C++ library of physical quantities, physical models, and units of
// measure for scientific computation. https://github.com/acodcha/physical-quantities
//
// Physical Quantities (PhQ) is free software: you can redistribute it and/or modify it under the
// terms of the GNU Lesser General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version. Physical Quantities (PhQ)
// is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
// General Public License for more details. You should have received a copy of the GNU Lesser
// General Public License along with Physical Quantities (PhQ). https://www.gnu.org/licenses

#include "../../include/PhQ/Dimension/Time.hpp"

#include <cstdint>
#include <functional>
#include <gtest/gtest.h>
#include <sstream>
#include <utility>

namespace PhQ::Dimension {

namespace {

TEST(DimensionTime, Abbreviation) {
  EXPECT_EQ(Time::Abbreviation(), "T");
}

TEST(DimensionTime, ComparisonOperators) {
  constexpr Time first{-1};
  constexpr Time second{2};
  EXPECT_EQ(first, first);
  EXPECT_NE(first, second);
  EXPECT_LT(first, second);
  EXPECT_LE(first, first);
  EXPECT_LE(first, second);
  EXPECT_GT(second, first);
  EXPECT_GE(second, first);
  EXPECT_GE(first, first);
}

TEST(DimensionTime, CopyAssignmentOperator) {
  constexpr Time first{3};
  Time second{0};
  second = first;
  EXPECT_EQ(second, first);
}

TEST(DimensionTime, CopyConstructor) {
  constexpr Time first{3};
  constexpr Time second{first};
  EXPECT_EQ(second, first);
}

TEST(DimensionTime, DefaultConstructor) {
  EXPECT_NO_THROW(Time{});
}

TEST(DimensionTime, Hash) {
  constexpr Time first{0};
  constexpr Time second{2};
  constexpr Time third{-1};
  constexpr std::hash<Time> hash;
  EXPECT_NE(hash(first), hash(second));
  EXPECT_NE(hash(first), hash(third));
  EXPECT_NE(hash(second), hash(third));
}

TEST(DimensionTime, Label) {
  EXPECT_EQ(Time::Label(), "Time");
}

TEST(DimensionTime, MoveAssignmentOperator) {
  Time first{3};
  Time second{-1};
  second = std::move(first);
  EXPECT_EQ(second, Time(3));
}

TEST(DimensionTime, MoveConstructor) {
  Time first{3};
  const Time second{std::move(first)};
  EXPECT_EQ(second, Time(3));
}

TEST(DimensionTime, Print) {
  EXPECT_EQ(Time().Print(), "");
  EXPECT_EQ(Time(-1).Print(), "T^(-1)");
  EXPECT_EQ(Time(0).Print(), "");
  EXPECT_EQ(Time(1).Print(), "T");
  EXPECT_EQ(Time(2).Print(), "T^2");
}

TEST(DimensionTime, SizeOf) {
  EXPECT_EQ(sizeof(Time{}), sizeof(int8_t));
}

TEST(DimensionTime, Stream) {
  constexpr Time dimension{3};
  std::ostringstream stream;
  stream << dimension;
  EXPECT_EQ(stream.str(), dimension.Print());
}

TEST(DimensionTime, Value) {
  EXPECT_EQ(Time().Value(), 0);
  EXPECT_EQ(Time(-1).Value(), -1);
  EXPECT_EQ(Time(0).Value(), 0);
  EXPECT_EQ(Time(1).Value(), 1);
  EXPECT_EQ(Time(2).Value(), 2);
}

}  // namespace

}  // namespace PhQ::Dimension
