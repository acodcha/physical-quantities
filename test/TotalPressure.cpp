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

#include "../include/PhQ/TotalPressure.hpp"

#include <functional>
#include <gtest/gtest.h>
#include <sstream>
#include <utility>

#include "../include/PhQ/DynamicPressure.hpp"
#include "../include/PhQ/StaticPressure.hpp"
#include "../include/PhQ/Unit/Pressure.hpp"

namespace PhQ {

namespace {

TEST(TotalPressure, ArithmeticOperatorAddition) {
  EXPECT_EQ(TotalPressure(1.0, Unit::Pressure::Pascal) + TotalPressure(2.0, Unit::Pressure::Pascal),
            TotalPressure(3.0, Unit::Pressure::Pascal));

  EXPECT_EQ(
      StaticPressure(2.0, Unit::Pressure::Pascal) + DynamicPressure(1.0, Unit::Pressure::Pascal),
      TotalPressure(3.0, Unit::Pressure::Pascal));

  EXPECT_EQ(
      DynamicPressure(1.0, Unit::Pressure::Pascal) + StaticPressure(2.0, Unit::Pressure::Pascal),
      TotalPressure(3.0, Unit::Pressure::Pascal));
}

TEST(TotalPressure, ArithmeticOperatorDivision) {
  EXPECT_EQ(
      TotalPressure(8.0, Unit::Pressure::Pascal) / 2.0, TotalPressure(4.0, Unit::Pressure::Pascal));

  EXPECT_EQ(
      TotalPressure(8.0, Unit::Pressure::Pascal) / TotalPressure(2.0, Unit::Pressure::Pascal), 4.0);
}

TEST(TotalPressure, ArithmeticOperatorMultiplication) {
  EXPECT_EQ(
      TotalPressure(4.0, Unit::Pressure::Pascal) * 2.0, TotalPressure(8.0, Unit::Pressure::Pascal));

  EXPECT_EQ(
      2.0 * TotalPressure(4.0, Unit::Pressure::Pascal), TotalPressure(8.0, Unit::Pressure::Pascal));
}

TEST(TotalPressure, ArithmeticOperatorSubtraction) {
  EXPECT_EQ(TotalPressure(3.0, Unit::Pressure::Pascal) - TotalPressure(2.0, Unit::Pressure::Pascal),
            TotalPressure(1.0, Unit::Pressure::Pascal));

  EXPECT_EQ(
      TotalPressure(3.0, Unit::Pressure::Pascal) - StaticPressure(2.0, Unit::Pressure::Pascal),
      DynamicPressure(1.0, Unit::Pressure::Pascal));

  EXPECT_EQ(
      TotalPressure(3.0, Unit::Pressure::Pascal) - DynamicPressure(1.0, Unit::Pressure::Pascal),
      StaticPressure(2.0, Unit::Pressure::Pascal));
}

TEST(TotalPressure, AssignmentOperatorAddition) {
  TotalPressure quantity{1.0, Unit::Pressure::Pascal};
  quantity += TotalPressure(2.0, Unit::Pressure::Pascal);
  EXPECT_EQ(quantity, TotalPressure(3.0, Unit::Pressure::Pascal));
}

TEST(TotalPressure, AssignmentOperatorDivision) {
  TotalPressure quantity{8.0, Unit::Pressure::Pascal};
  quantity /= 2.0;
  EXPECT_EQ(quantity, TotalPressure(4.0, Unit::Pressure::Pascal));
}

TEST(TotalPressure, AssignmentOperatorMultiplication) {
  TotalPressure quantity{4.0, Unit::Pressure::Pascal};
  quantity *= 2.0;
  EXPECT_EQ(quantity, TotalPressure(8.0, Unit::Pressure::Pascal));
}

TEST(TotalPressure, AssignmentOperatorSubtraction) {
  TotalPressure quantity{3.0, Unit::Pressure::Pascal};
  quantity -= TotalPressure(2.0, Unit::Pressure::Pascal);
  EXPECT_EQ(quantity, TotalPressure(1.0, Unit::Pressure::Pascal));
}

TEST(TotalPressure, ComparisonOperators) {
  const TotalPressure first{1.11, Unit::Pressure::Pascal};
  const TotalPressure second{2.22, Unit::Pressure::Pascal};
  EXPECT_EQ(first, first);
  EXPECT_NE(first, second);
  EXPECT_LT(first, second);
  EXPECT_GT(second, first);
  EXPECT_LE(first, first);
  EXPECT_LE(first, second);
  EXPECT_GE(first, first);
  EXPECT_GE(second, first);
}

TEST(TotalPressure, CopyAssignmentOperator) {
  const TotalPressure first{1.11, Unit::Pressure::Pascal};
  TotalPressure second = TotalPressure::Zero();
  second = first;
  EXPECT_EQ(second, first);
}

TEST(TotalPressure, CopyConstructor) {
  const TotalPressure first{1.11, Unit::Pressure::Pascal};
  const TotalPressure second{first};
  EXPECT_EQ(second, first);
}

TEST(TotalPressure, Create) {
  constexpr TotalPressure quantity = TotalPressure::Create<Unit::Pressure::Pascal>(1.11);
  EXPECT_EQ(quantity, TotalPressure(1.11, Unit::Pressure::Pascal));
}

TEST(TotalPressure, DefaultConstructor) {
  EXPECT_NO_THROW(TotalPressure{});
}

TEST(TotalPressure, Dimensions) {
  EXPECT_EQ(TotalPressure::Dimensions(), RelatedDimensions<Unit::Pressure>);
}

TEST(TotalPressure, Hash) {
  const TotalPressure first{1.11, Unit::Pressure::Kilopascal};
  const TotalPressure second{1.110001, Unit::Pressure::Kilopascal};
  const TotalPressure third{-1.11, Unit::Pressure::Kilopascal};
  const std::hash<TotalPressure> hasher;
  EXPECT_NE(hasher(first), hasher(second));
  EXPECT_NE(hasher(first), hasher(third));
  EXPECT_NE(hasher(second), hasher(third));
}

TEST(TotalPressure, JSON) {
  EXPECT_EQ(TotalPressure(1.11, Unit::Pressure::Pascal).JSON(),
            "{\"value\":1.110000000000000,\"unit\":\"Pa\"}");
  EXPECT_EQ(TotalPressure(-2.22, Unit::Pressure::Kilopascal).JSON(Unit::Pressure::Kilopascal),
            "{\"value\":-2.220000000000000,\"unit\":\"kPa\"}");
}

TEST(TotalPressure, MiscellaneousConstructors) {
  EXPECT_EQ(TotalPressure(StaticPressure(2.0, Unit::Pressure::Pascal),
                          DynamicPressure(1.0, Unit::Pressure::Pascal)),
            TotalPressure(3.0, Unit::Pressure::Pascal));

  EXPECT_EQ(StaticPressure(TotalPressure(3.0, Unit::Pressure::Pascal),
                           DynamicPressure(1.0, Unit::Pressure::Pascal)),
            StaticPressure(2.0, Unit::Pressure::Pascal));

  EXPECT_EQ(DynamicPressure(TotalPressure(3.0, Unit::Pressure::Pascal),
                            StaticPressure(2.0, Unit::Pressure::Pascal)),
            DynamicPressure(1.0, Unit::Pressure::Pascal));
}

TEST(TotalPressure, MoveAssignmentOperator) {
  TotalPressure first{1.11, Unit::Pressure::Pascal};
  TotalPressure second = TotalPressure::Zero();
  second = std::move(first);
  EXPECT_EQ(second, TotalPressure(1.11, Unit::Pressure::Pascal));
}

TEST(TotalPressure, MoveConstructor) {
  TotalPressure first{1.11, Unit::Pressure::Pascal};
  const TotalPressure second{std::move(first)};
  EXPECT_EQ(second, TotalPressure(1.11, Unit::Pressure::Pascal));
}

TEST(TotalPressure, MutableValue) {
  TotalPressure quantity{1.11, Unit::Pressure::Pascal};
  double& value = quantity.MutableValue();
  value = 2.22;
  EXPECT_EQ(quantity.Value(), 2.22);
}

TEST(TotalPressure, Print) {
  EXPECT_EQ(TotalPressure(1.11, Unit::Pressure::Pascal).Print(), "1.110000000000000 Pa");
  EXPECT_EQ(TotalPressure(-2.22, Unit::Pressure::Kilopascal).Print(Unit::Pressure::Kilopascal),
            "-2.220000000000000 kPa");
}

TEST(TotalPressure, SetValue) {
  TotalPressure quantity{1.11, Unit::Pressure::Pascal};
  quantity.SetValue(2.22);
  EXPECT_EQ(quantity.Value(), 2.22);
}

TEST(TotalPressure, SizeOf) {
  EXPECT_EQ(sizeof(TotalPressure{}), sizeof(double));
}

TEST(TotalPressure, StandardConstructor) {
  EXPECT_NO_THROW(TotalPressure(1.11, Unit::Pressure::Kilopascal));
}

TEST(TotalPressure, StaticValue) {
  constexpr TotalPressure quantity = TotalPressure::Create<Unit::Pressure::Kilopascal>(1.11);
  constexpr double value = quantity.StaticValue<Unit::Pressure::Kilopascal>();
  EXPECT_EQ(value, 1.11);
}

TEST(TotalPressure, Stream) {
  std::ostringstream stream;
  stream << TotalPressure(1.11, Unit::Pressure::Pascal);
  EXPECT_EQ(stream.str(), TotalPressure(1.11, Unit::Pressure::Pascal).Print());
}

TEST(TotalPressure, Unit) {
  EXPECT_EQ(TotalPressure::Unit(), Standard<Unit::Pressure>);
}

TEST(TotalPressure, Value) {
  EXPECT_EQ(TotalPressure(1.11, Unit::Pressure::Pascal).Value(), 1.11);
  EXPECT_EQ(
      TotalPressure(1.11, Unit::Pressure::Kilopascal).Value(Unit::Pressure::Kilopascal), 1.11);
}

TEST(TotalPressure, XML) {
  EXPECT_EQ(TotalPressure(1.11, Unit::Pressure::Pascal).XML(),
            "<value>1.110000000000000</value><unit>Pa</unit>");
  EXPECT_EQ(TotalPressure(-2.22, Unit::Pressure::Kilopascal).XML(Unit::Pressure::Kilopascal),
            "<value>-2.220000000000000</value><unit>kPa</unit>");
}

TEST(TotalPressure, YAML) {
  EXPECT_EQ(
      TotalPressure(1.11, Unit::Pressure::Pascal).YAML(), "{value:1.110000000000000,unit:\"Pa\"}");
  EXPECT_EQ(TotalPressure(-2.22, Unit::Pressure::Kilopascal).YAML(Unit::Pressure::Kilopascal),
            "{value:-2.220000000000000,unit:\"kPa\"}");
}

TEST(TotalPressure, Zero) {
  EXPECT_EQ(TotalPressure::Zero(), TotalPressure(0.0, Unit::Pressure::Pascal));
}

}  // namespace

}  // namespace PhQ
