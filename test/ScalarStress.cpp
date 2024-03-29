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

#include "../include/PhQ/ScalarStress.hpp"

#include <functional>
#include <gtest/gtest.h>
#include <sstream>
#include <utility>

#include "../include/PhQ/Unit/Pressure.hpp"

namespace PhQ {

namespace {

TEST(ScalarStress, ArithmeticOperatorAddition) {
  EXPECT_EQ(ScalarStress(1.0, Unit::Pressure::Pascal) + ScalarStress(2.0, Unit::Pressure::Pascal),
            ScalarStress(3.0, Unit::Pressure::Pascal));
}

TEST(ScalarStress, ArithmeticOperatorDivision) {
  EXPECT_EQ(
      ScalarStress(8.0, Unit::Pressure::Pascal) / 2.0, ScalarStress(4.0, Unit::Pressure::Pascal));

  EXPECT_EQ(
      ScalarStress(8.0, Unit::Pressure::Pascal) / ScalarStress(2.0, Unit::Pressure::Pascal), 4.0);
}

TEST(ScalarStress, ArithmeticOperatorMultiplication) {
  EXPECT_EQ(
      ScalarStress(4.0, Unit::Pressure::Pascal) * 2.0, ScalarStress(8.0, Unit::Pressure::Pascal));

  EXPECT_EQ(
      2.0 * ScalarStress(4.0, Unit::Pressure::Pascal), ScalarStress(8.0, Unit::Pressure::Pascal));
}

TEST(ScalarStress, ArithmeticOperatorSubtraction) {
  EXPECT_EQ(ScalarStress(3.0, Unit::Pressure::Pascal) - ScalarStress(2.0, Unit::Pressure::Pascal),
            ScalarStress(1.0, Unit::Pressure::Pascal));
}

TEST(ScalarStress, AssignmentOperatorAddition) {
  ScalarStress quantity{1.0, Unit::Pressure::Pascal};
  quantity += ScalarStress(2.0, Unit::Pressure::Pascal);
  EXPECT_EQ(quantity, ScalarStress(3.0, Unit::Pressure::Pascal));
}

TEST(ScalarStress, AssignmentOperatorDivision) {
  ScalarStress quantity{8.0, Unit::Pressure::Pascal};
  quantity /= 2.0;
  EXPECT_EQ(quantity, ScalarStress(4.0, Unit::Pressure::Pascal));
}

TEST(ScalarStress, AssignmentOperatorMultiplication) {
  ScalarStress quantity{4.0, Unit::Pressure::Pascal};
  quantity *= 2.0;
  EXPECT_EQ(quantity, ScalarStress(8.0, Unit::Pressure::Pascal));
}

TEST(ScalarStress, AssignmentOperatorSubtraction) {
  ScalarStress quantity{3.0, Unit::Pressure::Pascal};
  quantity -= ScalarStress(2.0, Unit::Pressure::Pascal);
  EXPECT_EQ(quantity, ScalarStress(1.0, Unit::Pressure::Pascal));
}

TEST(ScalarStress, ComparisonOperators) {
  const ScalarStress first{0.1, Unit::Pressure::Pascal};
  const ScalarStress second{0.2, Unit::Pressure::Pascal};
  EXPECT_EQ(first, first);
  EXPECT_NE(first, second);
  EXPECT_LT(first, second);
  EXPECT_GT(second, first);
  EXPECT_LE(first, first);
  EXPECT_LE(first, second);
  EXPECT_GE(first, first);
  EXPECT_GE(second, first);
}

TEST(ScalarStress, CopyAssignmentOperator) {
  const ScalarStress first{1.11, Unit::Pressure::Pascal};
  ScalarStress second = ScalarStress::Zero();
  second = first;
  EXPECT_EQ(second, first);
}

TEST(ScalarStress, CopyConstructor) {
  const ScalarStress first{1.11, Unit::Pressure::Pascal};
  const ScalarStress second{first};
  EXPECT_EQ(second, first);
}

TEST(ScalarStress, Create) {
  constexpr ScalarStress quantity = ScalarStress::Create<Unit::Pressure::Pascal>(1.11);
  EXPECT_EQ(quantity, ScalarStress(1.11, Unit::Pressure::Pascal));
}

TEST(ScalarStress, DefaultConstructor) {
  EXPECT_NO_THROW(ScalarStress{});
}

TEST(ScalarStress, Dimensions) {
  EXPECT_EQ(ScalarStress::Dimensions(), RelatedDimensions<Unit::Pressure>);
}

TEST(ScalarStress, Hash) {
  const ScalarStress first{1.11, Unit::Pressure::Kilopascal};
  const ScalarStress second{1.110001, Unit::Pressure::Kilopascal};
  const ScalarStress third{-1.11, Unit::Pressure::Kilopascal};
  const std::hash<ScalarStress> hash;
  EXPECT_NE(hash(first), hash(second));
  EXPECT_NE(hash(first), hash(third));
  EXPECT_NE(hash(second), hash(third));
}

TEST(ScalarStress, JSON) {
  EXPECT_EQ(ScalarStress(1.11, Unit::Pressure::Pascal).JSON(),
            "{\"value\":1.110000000000000,\"unit\":\"Pa\"}");
  EXPECT_EQ(ScalarStress(-2.22, Unit::Pressure::Kilopascal).JSON(Unit::Pressure::Kilopascal),
            "{\"value\":-2.220000000000000,\"unit\":\"kPa\"}");
}

TEST(ScalarStress, MoveAssignmentOperator) {
  ScalarStress first{1.11, Unit::Pressure::Pascal};
  ScalarStress second = ScalarStress::Zero();
  second = std::move(first);
  EXPECT_EQ(second, ScalarStress(1.11, Unit::Pressure::Pascal));
}

TEST(ScalarStress, MoveConstructor) {
  ScalarStress first{1.11, Unit::Pressure::Pascal};
  const ScalarStress second{std::move(first)};
  EXPECT_EQ(second, ScalarStress(1.11, Unit::Pressure::Pascal));
}

TEST(ScalarStress, MutableValue) {
  ScalarStress quantity{1.11, Unit::Pressure::Pascal};
  double& value = quantity.MutableValue();
  value = 2.22;
  EXPECT_EQ(quantity.Value(), 2.22);
}

TEST(ScalarStress, Print) {
  EXPECT_EQ(ScalarStress(1.11, Unit::Pressure::Pascal).Print(), "1.110000000000000 Pa");
  EXPECT_EQ(ScalarStress(-2.22, Unit::Pressure::Kilopascal).Print(Unit::Pressure::Kilopascal),
            "-2.220000000000000 kPa");
}

TEST(ScalarStress, SetValue) {
  ScalarStress quantity{1.11, Unit::Pressure::Pascal};
  quantity.SetValue(2.22);
  EXPECT_EQ(quantity.Value(), 2.22);
}

TEST(ScalarStress, SizeOf) {
  EXPECT_EQ(sizeof(ScalarStress{}), sizeof(double));
}

TEST(ScalarStress, StandardConstructor) {
  EXPECT_NO_THROW(ScalarStress(1.11, Unit::Pressure::Kilopascal));
}

TEST(ScalarStress, StaticValue) {
  constexpr ScalarStress quantity = ScalarStress::Create<Unit::Pressure::Kilopascal>(1.11);
  constexpr double value = quantity.StaticValue<Unit::Pressure::Kilopascal>();
  EXPECT_EQ(value, 1.11);
}

TEST(ScalarStress, Stream) {
  std::ostringstream stream;
  stream << ScalarStress(1.11, Unit::Pressure::Pascal);
  EXPECT_EQ(stream.str(), ScalarStress(1.11, Unit::Pressure::Pascal).Print());
}

TEST(ScalarStress, Unit) {
  EXPECT_EQ(ScalarStress::Unit(), Standard<Unit::Pressure>);
}

TEST(ScalarStress, Value) {
  EXPECT_EQ(ScalarStress(1.11, Unit::Pressure::Pascal).Value(), 1.11);
  EXPECT_EQ(ScalarStress(1.11, Unit::Pressure::Kilopascal).Value(Unit::Pressure::Kilopascal), 1.11);
}

TEST(ScalarStress, XML) {
  EXPECT_EQ(ScalarStress(1.11, Unit::Pressure::Pascal).XML(),
            "<value>1.110000000000000</value><unit>Pa</unit>");
  EXPECT_EQ(ScalarStress(-2.22, Unit::Pressure::Kilopascal).XML(Unit::Pressure::Kilopascal),
            "<value>-2.220000000000000</value><unit>kPa</unit>");
}

TEST(ScalarStress, YAML) {
  EXPECT_EQ(
      ScalarStress(1.11, Unit::Pressure::Pascal).YAML(), "{value:1.110000000000000,unit:\"Pa\"}");
  EXPECT_EQ(ScalarStress(-2.22, Unit::Pressure::Kilopascal).YAML(Unit::Pressure::Kilopascal),
            "{value:-2.220000000000000,unit:\"kPa\"}");
}

TEST(ScalarStress, Zero) {
  EXPECT_EQ(ScalarStress::Zero(), ScalarStress(0.0, Unit::Pressure::Pascal));
}

}  // namespace

}  // namespace PhQ
