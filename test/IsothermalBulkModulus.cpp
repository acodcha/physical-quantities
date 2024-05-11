// Copyright 2020-2024 Alexandre Coderre-Chabot
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

#include "../include/PhQ/IsothermalBulkModulus.hpp"

#include <functional>
#include <gtest/gtest.h>
#include <sstream>
#include <utility>

#include "../include/PhQ/Unit/Pressure.hpp"

namespace PhQ {

namespace {

TEST(IsothermalBulkModulus, ArithmeticOperatorAddition) {
  EXPECT_EQ(IsothermalBulkModulus(1.0, Unit::Pressure::Pascal)
                + IsothermalBulkModulus(2.0, Unit::Pressure::Pascal),
            IsothermalBulkModulus(3.0, Unit::Pressure::Pascal));
}

TEST(IsothermalBulkModulus, ArithmeticOperatorDivision) {
  EXPECT_EQ(IsothermalBulkModulus(8.0, Unit::Pressure::Pascal) / 2.0,
            IsothermalBulkModulus(4.0, Unit::Pressure::Pascal));
  EXPECT_EQ(IsothermalBulkModulus(8.0, Unit::Pressure::Pascal)
                / IsothermalBulkModulus(2.0, Unit::Pressure::Pascal),
            4.0);
}

TEST(IsothermalBulkModulus, ArithmeticOperatorMultiplication) {
  EXPECT_EQ(IsothermalBulkModulus(4.0, Unit::Pressure::Pascal) * 2.0,
            IsothermalBulkModulus(8.0, Unit::Pressure::Pascal));
  EXPECT_EQ(2.0 * IsothermalBulkModulus(4.0, Unit::Pressure::Pascal),
            IsothermalBulkModulus(8.0, Unit::Pressure::Pascal));
}

TEST(IsothermalBulkModulus, ArithmeticOperatorSubtraction) {
  EXPECT_EQ(IsothermalBulkModulus(3.0, Unit::Pressure::Pascal)
                - IsothermalBulkModulus(2.0, Unit::Pressure::Pascal),
            IsothermalBulkModulus(1.0, Unit::Pressure::Pascal));
}

TEST(IsothermalBulkModulus, AssignmentOperatorAddition) {
  IsothermalBulkModulus isothermal_bulk_modulus{1.0, Unit::Pressure::Pascal};
  isothermal_bulk_modulus += IsothermalBulkModulus(2.0, Unit::Pressure::Pascal);
  EXPECT_EQ(isothermal_bulk_modulus, IsothermalBulkModulus(3.0, Unit::Pressure::Pascal));
}

TEST(IsothermalBulkModulus, AssignmentOperatorDivision) {
  IsothermalBulkModulus isothermal_bulk_modulus{8.0, Unit::Pressure::Pascal};
  isothermal_bulk_modulus /= 2.0;
  EXPECT_EQ(isothermal_bulk_modulus, IsothermalBulkModulus(4.0, Unit::Pressure::Pascal));
}

TEST(IsothermalBulkModulus, AssignmentOperatorMultiplication) {
  IsothermalBulkModulus isothermal_bulk_modulus{4.0, Unit::Pressure::Pascal};
  isothermal_bulk_modulus *= 2.0;
  EXPECT_EQ(isothermal_bulk_modulus, IsothermalBulkModulus(8.0, Unit::Pressure::Pascal));
}

TEST(IsothermalBulkModulus, AssignmentOperatorSubtraction) {
  IsothermalBulkModulus isothermal_bulk_modulus{3.0, Unit::Pressure::Pascal};
  isothermal_bulk_modulus -= IsothermalBulkModulus(2.0, Unit::Pressure::Pascal);
  EXPECT_EQ(isothermal_bulk_modulus, IsothermalBulkModulus(1.0, Unit::Pressure::Pascal));
}

TEST(IsothermalBulkModulus, ComparisonOperators) {
  const IsothermalBulkModulus first{1.0, Unit::Pressure::Pascal};
  const IsothermalBulkModulus second{2.0, Unit::Pressure::Pascal};
  EXPECT_EQ(first, first);
  EXPECT_NE(first, second);
  EXPECT_LT(first, second);
  EXPECT_GT(second, first);
  EXPECT_LE(first, first);
  EXPECT_LE(first, second);
  EXPECT_GE(first, first);
  EXPECT_GE(second, first);
}

TEST(IsothermalBulkModulus, CopyAssignmentOperator) {
  const IsothermalBulkModulus first{1.0, Unit::Pressure::Pascal};
  IsothermalBulkModulus second = IsothermalBulkModulus<>::Zero();
  second = first;
  EXPECT_EQ(second, first);
}

TEST(IsothermalBulkModulus, CopyConstructor) {
  const IsothermalBulkModulus first{1.0, Unit::Pressure::Pascal};
  const IsothermalBulkModulus second{first};
  EXPECT_EQ(second, first);
}

TEST(IsothermalBulkModulus, Create) {
  constexpr IsothermalBulkModulus isothermal_bulk_modulus =
      IsothermalBulkModulus<>::Create<Unit::Pressure::Pascal>(1.0);
  EXPECT_EQ(isothermal_bulk_modulus, IsothermalBulkModulus(1.0, Unit::Pressure::Pascal));
}

TEST(IsothermalBulkModulus, DefaultConstructor) {
  EXPECT_NO_THROW(IsothermalBulkModulus<>{});
}

TEST(IsothermalBulkModulus, Dimensions) {
  EXPECT_EQ(IsothermalBulkModulus<>::Dimensions(), RelatedDimensions<Unit::Pressure>);
}

TEST(IsothermalBulkModulus, Hash) {
  const IsothermalBulkModulus first{1.0, Unit::Pressure::Kilopascal};
  const IsothermalBulkModulus second{1.00001, Unit::Pressure::Kilopascal};
  const IsothermalBulkModulus third{-1.0, Unit::Pressure::Kilopascal};
  const std::hash<IsothermalBulkModulus<>> hash;
  EXPECT_NE(hash(first), hash(second));
  EXPECT_NE(hash(first), hash(third));
  EXPECT_NE(hash(second), hash(third));
}

TEST(IsothermalBulkModulus, JSON) {
  EXPECT_EQ(IsothermalBulkModulus(1.0, Unit::Pressure::Pascal).JSON(),
            "{\"value\":" + Print(1.0) + ",\"unit\":\"Pa\"}");
  EXPECT_EQ(IsothermalBulkModulus(1.0, Unit::Pressure::Kilopascal).JSON(Unit::Pressure::Kilopascal),
            "{\"value\":" + Print(1.0) + ",\"unit\":\"kPa\"}");
}

TEST(IsothermalBulkModulus, MoveAssignmentOperator) {
  IsothermalBulkModulus first{1.0, Unit::Pressure::Pascal};
  IsothermalBulkModulus second = IsothermalBulkModulus<>::Zero();
  second = std::move(first);
  EXPECT_EQ(second, IsothermalBulkModulus(1.0, Unit::Pressure::Pascal));
}

TEST(IsothermalBulkModulus, MoveConstructor) {
  IsothermalBulkModulus first{1.0, Unit::Pressure::Pascal};
  const IsothermalBulkModulus second{std::move(first)};
  EXPECT_EQ(second, IsothermalBulkModulus(1.0, Unit::Pressure::Pascal));
}

TEST(IsothermalBulkModulus, MutableValue) {
  IsothermalBulkModulus isothermal_bulk_modulus{1.0, Unit::Pressure::Pascal};
  double& value = isothermal_bulk_modulus.MutableValue();
  value = 2.0;
  EXPECT_EQ(isothermal_bulk_modulus.Value(), 2.0);
}

TEST(IsothermalBulkModulus, Print) {
  EXPECT_EQ(IsothermalBulkModulus(1.0, Unit::Pressure::Pascal).Print(), Print(1.0) + " Pa");
  EXPECT_EQ(
      IsothermalBulkModulus(1.0, Unit::Pressure::Kilopascal).Print(Unit::Pressure::Kilopascal),
      Print(1.0) + " kPa");
}

TEST(IsothermalBulkModulus, SetValue) {
  IsothermalBulkModulus isothermal_bulk_modulus{1.0, Unit::Pressure::Pascal};
  isothermal_bulk_modulus.SetValue(2.0);
  EXPECT_EQ(isothermal_bulk_modulus.Value(), 2.0);
}

TEST(IsothermalBulkModulus, SizeOf) {
  EXPECT_EQ(sizeof(IsothermalBulkModulus<>{}), sizeof(double));
}

TEST(IsothermalBulkModulus, StandardConstructor) {
  EXPECT_NO_THROW(IsothermalBulkModulus(1.0, Unit::Pressure::Kilopascal));
}

TEST(IsothermalBulkModulus, StaticValue) {
  constexpr IsothermalBulkModulus isothermal_bulk_modulus =
      IsothermalBulkModulus<>::Create<Unit::Pressure::Kilopascal>(2.0);
  constexpr double value = isothermal_bulk_modulus.StaticValue<Unit::Pressure::Kilopascal>();
  EXPECT_EQ(value, 2.0);
}

TEST(IsothermalBulkModulus, Stream) {
  std::ostringstream stream;
  stream << IsothermalBulkModulus(1.0, Unit::Pressure::Pascal);
  EXPECT_EQ(stream.str(), IsothermalBulkModulus(1.0, Unit::Pressure::Pascal).Print());
}

TEST(IsothermalBulkModulus, Unit) {
  EXPECT_EQ(IsothermalBulkModulus<>::Unit(), Standard<Unit::Pressure>);
}

TEST(IsothermalBulkModulus, Value) {
  EXPECT_EQ(IsothermalBulkModulus(1.0, Unit::Pressure::Pascal).Value(), 1.0);
  EXPECT_EQ(
      IsothermalBulkModulus(2.0, Unit::Pressure::Kilopascal).Value(Unit::Pressure::Kilopascal),
      2.0);
}

TEST(IsothermalBulkModulus, XML) {
  EXPECT_EQ(IsothermalBulkModulus(1.0, Unit::Pressure::Pascal).XML(),
            "<value>" + Print(1.0) + "</value><unit>Pa</unit>");
  EXPECT_EQ(IsothermalBulkModulus(1.0, Unit::Pressure::Kilopascal).XML(Unit::Pressure::Kilopascal),
            "<value>" + Print(1.0) + "</value><unit>kPa</unit>");
}

TEST(IsothermalBulkModulus, YAML) {
  EXPECT_EQ(IsothermalBulkModulus(1.0, Unit::Pressure::Pascal).YAML(),
            "{value:" + Print(1.0) + ",unit:\"Pa\"}");
  EXPECT_EQ(IsothermalBulkModulus(1.0, Unit::Pressure::Kilopascal).YAML(Unit::Pressure::Kilopascal),
            "{value:" + Print(1.0) + ",unit:\"kPa\"}");
}

TEST(IsothermalBulkModulus, Zero) {
  EXPECT_EQ(IsothermalBulkModulus<>::Zero(), IsothermalBulkModulus(0.0, Unit::Pressure::Pascal));
}

}  // namespace

}  // namespace PhQ
