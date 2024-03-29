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

#include "../include/PhQ/ScalarStrain.hpp"

#include <functional>
#include <gtest/gtest.h>
#include <sstream>
#include <utility>

#include "../include/PhQ/Dimensions.hpp"

namespace PhQ {

namespace {

TEST(ScalarStrain, ArithmeticOperatorAddition) {
  EXPECT_EQ(ScalarStrain(1.0) + ScalarStrain(2.0), ScalarStrain(3.0));
}

TEST(ScalarStrain, ArithmeticOperatorDivision) {
  EXPECT_EQ(ScalarStrain(8.0) / 2.0, ScalarStrain(4.0));

  EXPECT_EQ(ScalarStrain(8.0) / ScalarStrain(2.0), 4.0);
}

TEST(ScalarStrain, ArithmeticOperatorMultiplication) {
  EXPECT_EQ(ScalarStrain(4.0) * 2.0, ScalarStrain(8.0));

  EXPECT_EQ(2.0 * ScalarStrain(4.0), ScalarStrain(8.0));
}

TEST(ScalarStrain, ArithmeticOperatorSubtraction) {
  EXPECT_EQ(ScalarStrain(3.0) - ScalarStrain(2.0), ScalarStrain(1.0));
}

TEST(ScalarStrain, AssignmentOperatorAddition) {
  ScalarStrain quantity{1.0};
  quantity += ScalarStrain(2.0);
  EXPECT_EQ(quantity, ScalarStrain(3.0));
}

TEST(ScalarStrain, AssignmentOperatorDivision) {
  ScalarStrain quantity{8.0};
  quantity /= 2.0;
  EXPECT_EQ(quantity, ScalarStrain(4.0));
}

TEST(ScalarStrain, AssignmentOperatorMultiplication) {
  ScalarStrain quantity{4.0};
  quantity *= 2.0;
  EXPECT_EQ(quantity, ScalarStrain(8.0));
}

TEST(ScalarStrain, AssignmentOperatorSubtraction) {
  ScalarStrain quantity{3.0};
  quantity -= ScalarStrain(2.0);
  EXPECT_EQ(quantity, ScalarStrain(1.0));
}

TEST(ScalarStrain, ComparisonOperators) {
  const ScalarStrain first{1.11};
  const ScalarStrain second{2.22};
  EXPECT_EQ(first, first);
  EXPECT_NE(first, second);
  EXPECT_LT(first, second);
  EXPECT_GT(second, first);
  EXPECT_LE(first, first);
  EXPECT_LE(first, second);
  EXPECT_GE(first, first);
  EXPECT_GE(second, first);
}

TEST(ScalarStrain, CopyAssignmentOperator) {
  const ScalarStrain first{1.11};
  ScalarStrain second = ScalarStrain::Zero();
  second = first;
  EXPECT_EQ(second, first);
}

TEST(ScalarStrain, CopyConstructor) {
  const ScalarStrain first{1.11};
  const ScalarStrain second{first};
  EXPECT_EQ(second, first);
}

TEST(ScalarStrain, DefaultConstructor) {
  EXPECT_NO_THROW(ScalarStrain{});
}

TEST(ScalarStrain, Dimensions) {
  EXPECT_EQ(ScalarStrain::Dimensions(), Dimensionless);
}

TEST(ScalarStrain, Hash) {
  const ScalarStrain first{1.11};
  const ScalarStrain second{1.110001};
  const ScalarStrain third{-1.11};
  const std::hash<ScalarStrain> hash;
  EXPECT_NE(hash(first), hash(second));
  EXPECT_NE(hash(first), hash(third));
  EXPECT_NE(hash(second), hash(third));
}

TEST(ScalarStrain, JSON) {
  EXPECT_EQ(ScalarStrain(1.11).JSON(), "1.110000000000000");
}

TEST(ScalarStrain, MoveAssignmentOperator) {
  ScalarStrain first{1.11};
  ScalarStrain second = ScalarStrain::Zero();
  second = std::move(first);
  EXPECT_EQ(second, ScalarStrain(1.11));
}

TEST(ScalarStrain, MoveConstructor) {
  ScalarStrain first{1.11};
  const ScalarStrain second{std::move(first)};
  EXPECT_EQ(second, ScalarStrain(1.11));
}

TEST(ScalarStrain, MutableValue) {
  ScalarStrain quantity{1.11};
  double& value = quantity.MutableValue();
  value = 2.22;
  EXPECT_EQ(quantity.Value(), 2.22);
}

TEST(ScalarStrain, Print) {
  EXPECT_EQ(ScalarStrain(1.11).Print(), "1.110000000000000");
}

TEST(ScalarStrain, SetValue) {
  ScalarStrain quantity{1.11};
  quantity.SetValue(2.22);
  EXPECT_EQ(quantity.Value(), 2.22);
}

TEST(ScalarStrain, SizeOf) {
  EXPECT_EQ(sizeof(ScalarStrain{}), sizeof(double));
}

TEST(ScalarStrain, StandardConstructor) {
  EXPECT_NO_THROW(ScalarStrain(1.11));
}

TEST(ScalarStrain, Stream) {
  std::ostringstream stream;
  stream << ScalarStrain(1.11);
  EXPECT_EQ(stream.str(), ScalarStrain(1.11).Print());
}

TEST(ScalarStrain, Value) {
  EXPECT_EQ(ScalarStrain(1.11).Value(), 1.11);
}

TEST(ScalarStrain, XML) {
  EXPECT_EQ(ScalarStrain(1.11).XML(), "1.110000000000000");
}

TEST(ScalarStrain, YAML) {
  EXPECT_EQ(ScalarStrain(1.11).YAML(), "1.110000000000000");
}

TEST(ScalarStrain, Zero) {
  EXPECT_EQ(ScalarStrain::Zero(), ScalarStrain(0.0));
}

}  // namespace

}  // namespace PhQ
