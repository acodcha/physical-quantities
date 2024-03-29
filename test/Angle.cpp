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

#include "../include/PhQ/Angle.hpp"

#include <functional>
#include <gtest/gtest.h>
#include <sstream>
#include <utility>

#include "../include/PhQ/Unit/Angle.hpp"
#include "../include/PhQ/Vector.hpp"

namespace PhQ {

namespace {

TEST(Angle, ArithmeticOperatorAddition) {
  EXPECT_EQ(Angle(1.0, Unit::Angle::Radian) + Angle(2.0, Unit::Angle::Radian),
            Angle(3.0, Unit::Angle::Radian));
}

TEST(Angle, ArithmeticOperatorDivision) {
  EXPECT_EQ(Angle(8.0, Unit::Angle::Radian) / 2.0, Angle(4.0, Unit::Angle::Radian));

  EXPECT_EQ(Angle(8.0, Unit::Angle::Radian) / Angle(2.0, Unit::Angle::Radian), 4.0);
}

TEST(Angle, ArithmeticOperatorMultiplication) {
  EXPECT_EQ(Angle(4.0, Unit::Angle::Radian) * 2.0, Angle(8.0, Unit::Angle::Radian));

  EXPECT_EQ(2.0 * Angle(4.0, Unit::Angle::Radian), Angle(8.0, Unit::Angle::Radian));
}

TEST(Angle, ArithmeticOperatorSubtraction) {
  EXPECT_EQ(Angle(3.0, Unit::Angle::Radian) - Angle(2.0, Unit::Angle::Radian),
            Angle(1.0, Unit::Angle::Radian));
}

TEST(Angle, AssignmentOperatorAddition) {
  Angle quantity{1.0, Unit::Angle::Radian};
  quantity += Angle(2.0, Unit::Angle::Radian);
  EXPECT_EQ(quantity, Angle(3.0, Unit::Angle::Radian));
}

TEST(Angle, AssignmentOperatorDivision) {
  Angle quantity{8.0, Unit::Angle::Radian};
  quantity /= 2.0;
  EXPECT_EQ(quantity, Angle(4.0, Unit::Angle::Radian));
}

TEST(Angle, AssignmentOperatorMultiplication) {
  Angle quantity{4.0, Unit::Angle::Radian};
  quantity *= 2.0;
  EXPECT_EQ(quantity, Angle(8.0, Unit::Angle::Radian));
}

TEST(Angle, AssignmentOperatorSubtraction) {
  Angle quantity{3.0, Unit::Angle::Radian};
  quantity -= Angle(2.0, Unit::Angle::Radian);
  EXPECT_EQ(quantity, Angle(1.0, Unit::Angle::Radian));
}

TEST(Angle, ComparisonOperators) {
  const Angle first{1.11, Unit::Angle::Radian};
  const Angle second{2.22, Unit::Angle::Radian};
  EXPECT_EQ(first, first);
  EXPECT_NE(first, second);
  EXPECT_LT(first, second);
  EXPECT_GT(second, first);
  EXPECT_LE(first, first);
  EXPECT_LE(first, second);
  EXPECT_GE(first, first);
  EXPECT_GE(second, first);
}

TEST(Angle, CopyAssignmentOperator) {
  const Angle first{1.11, Unit::Angle::Radian};
  Angle second = Angle::Zero();
  second = first;
  EXPECT_EQ(second, first);
}

TEST(Angle, CopyConstructor) {
  const Angle first{1.11, Unit::Angle::Radian};
  const Angle second{first};
  EXPECT_EQ(second, first);
}

TEST(Angle, Create) {
  constexpr Angle quantity = Angle::Create<Unit::Angle::Radian>(1.11);
  EXPECT_EQ(quantity, Angle(1.11, Unit::Angle::Radian));
}

TEST(Angle, DefaultConstructor) {
  EXPECT_NO_THROW(Angle{});
}

TEST(Angle, Dimensions) {
  EXPECT_EQ(Angle::Dimensions(), RelatedDimensions<Unit::Angle>);
}

TEST(Angle, Hash) {
  const Angle first{1.11, Unit::Angle::Degree};
  const Angle second{1.110001, Unit::Angle::Degree};
  const Angle third{-1.11, Unit::Angle::Degree};
  const std::hash<Angle> hash;
  EXPECT_NE(hash(first), hash(second));
  EXPECT_NE(hash(first), hash(third));
  EXPECT_NE(hash(second), hash(third));
}

TEST(Angle, JSON) {
  EXPECT_EQ(
      Angle(1.11, Unit::Angle::Radian).JSON(), "{\"value\":1.110000000000000,\"unit\":\"rad\"}");
  EXPECT_EQ(Angle(-2.22, Unit::Angle::Degree).JSON(Unit::Angle::Degree),
            "{\"value\":-2.220000000000000,\"unit\":\"deg\"}");
}

TEST(Angle, MiscellaneousConstructors) {
  const Vector first{1.0, 0.0, 0.0};
  const Vector second{0.0, 0.0, -1.0};
  EXPECT_DOUBLE_EQ(Angle(first, second).Value(), Angle(90.0, Unit::Angle::Degree).Value());
}

TEST(Angle, MiscellaneousMethods) {
  const Vector first{1.0, 0.0, 0.0};
  const Vector second{0.0, 0.0, -1.0};
  EXPECT_DOUBLE_EQ(first.Angle(second).Value(), Angle(90.0, Unit::Angle::Degree).Value());
}

TEST(Angle, MoveAssignmentOperator) {
  Angle first{1.11, Unit::Angle::Radian};
  Angle second = Angle::Zero();
  second = std::move(first);
  EXPECT_EQ(second, Angle(1.11, Unit::Angle::Radian));
}

TEST(Angle, MoveConstructor) {
  Angle first{1.11, Unit::Angle::Radian};
  const Angle second{std::move(first)};
  EXPECT_EQ(second, Angle(1.11, Unit::Angle::Radian));
}

TEST(Angle, MutableValue) {
  Angle quantity{1.11, Unit::Angle::Radian};
  double& value = quantity.MutableValue();
  value = 2.22;
  EXPECT_EQ(quantity.Value(), 2.22);
}

TEST(Angle, Print) {
  EXPECT_EQ(Angle(1.11, Unit::Angle::Radian).Print(), "1.110000000000000 rad");
  EXPECT_EQ(Angle(-2.22, Unit::Angle::Degree).Print(Unit::Angle::Degree), "-2.220000000000000 deg");
}

TEST(Angle, SetValue) {
  Angle quantity{1.11, Unit::Angle::Radian};
  quantity.SetValue(2.22);
  EXPECT_EQ(quantity.Value(), 2.22);
}

TEST(Angle, SizeOf) {
  EXPECT_EQ(sizeof(Angle{}), sizeof(double));
}

TEST(Angle, StandardConstructor) {
  EXPECT_NO_THROW(Angle(1.11, Unit::Angle::Degree));
}

TEST(Angle, StaticValue) {
  constexpr Angle quantity = Angle::Create<Unit::Angle::Degree>(1.11);
  constexpr double value = quantity.StaticValue<Unit::Angle::Degree>();
  EXPECT_EQ(value, 1.11);
}

TEST(Angle, Stream) {
  std::ostringstream stream;
  stream << Angle(1.11, Unit::Angle::Radian);
  EXPECT_EQ(stream.str(), Angle(1.11, Unit::Angle::Radian).Print());
}

TEST(Angle, Unit) {
  EXPECT_EQ(Angle::Unit(), Standard<Unit::Angle>);
}

TEST(Angle, Value) {
  EXPECT_EQ(Angle(1.11, Unit::Angle::Radian).Value(), 1.11);
  EXPECT_EQ(Angle(1.11, Unit::Angle::Degree).Value(Unit::Angle::Degree), 1.11);
}

TEST(Angle, XML) {
  EXPECT_EQ(
      Angle(1.11, Unit::Angle::Radian).XML(), "<value>1.110000000000000</value><unit>rad</unit>");
  EXPECT_EQ(Angle(-2.22, Unit::Angle::Degree).XML(Unit::Angle::Degree),
            "<value>-2.220000000000000</value><unit>deg</unit>");
}

TEST(Angle, YAML) {
  EXPECT_EQ(Angle(1.11, Unit::Angle::Radian).YAML(), "{value:1.110000000000000,unit:\"rad\"}");
  EXPECT_EQ(Angle(-2.22, Unit::Angle::Degree).YAML(Unit::Angle::Degree),
            "{value:-2.220000000000000,unit:\"deg\"}");
}

TEST(Angle, Zero) {
  EXPECT_EQ(Angle::Zero(), Angle(0.0, Unit::Angle::Radian));
}

}  // namespace

}  // namespace PhQ
