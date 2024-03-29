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

#include "../include/PhQ/Displacement.hpp"

#include <array>
#include <functional>
#include <gtest/gtest.h>
#include <sstream>
#include <utility>

#include "../include/PhQ/Angle.hpp"
#include "../include/PhQ/Direction.hpp"
#include "../include/PhQ/Length.hpp"
#include "../include/PhQ/Unit/Angle.hpp"
#include "../include/PhQ/Unit/Length.hpp"
#include "../include/PhQ/Vector.hpp"

namespace PhQ {

namespace {

TEST(Displacement, Angle) {
  EXPECT_EQ(Displacement({0.0, -2.22, 0.0}, Unit::Length::Metre)
                .Angle(Displacement({0.0, 0.0, 3.33}, Unit::Length::Metre)),
            Angle(90.0, Unit::Angle::Degree));
}

TEST(Displacement, ArithmeticOperatorAddition) {
  EXPECT_EQ(Displacement({1.0, -2.0, 3.0}, Unit::Length::Metre)
                + Displacement({2.0, -4.0, 6.0}, Unit::Length::Metre),
            Displacement({3.0, -6.0, 9.0}, Unit::Length::Metre));
}

TEST(Displacement, ArithmeticOperatorDivision) {
  EXPECT_EQ(Displacement({2.0, -4.0, 6.0}, Unit::Length::Metre) / 2.0,
            Displacement({1.0, -2.0, 3.0}, Unit::Length::Metre));
}

TEST(Displacement, ArithmeticOperatorMultiplication) {
  EXPECT_EQ(Displacement({1.0, -2.0, 3.0}, Unit::Length::Metre) * 2.0,
            Displacement({2.0, -4.0, 6.0}, Unit::Length::Metre));

  EXPECT_EQ(2.0 * Displacement({1.0, -2.0, 3.0}, Unit::Length::Metre),
            Displacement({2.0, -4.0, 6.0}, Unit::Length::Metre));
}

TEST(Displacement, ArithmeticOperatorSubtraction) {
  EXPECT_EQ(Displacement({3.0, -6.0, 9.0}, Unit::Length::Metre)
                - Displacement({2.0, -4.0, 6.0}, Unit::Length::Metre),
            Displacement({1.0, -2.0, 3.0}, Unit::Length::Metre));
}

TEST(Displacement, AssignmentOperatorAddition) {
  Displacement quantity({1.0, -2.0, 3.0}, Unit::Length::Metre);
  quantity += Displacement({2.0, -4.0, 6.0}, Unit::Length::Metre);
  EXPECT_EQ(quantity, Displacement({3.0, -6.0, 9.0}, Unit::Length::Metre));
}

TEST(Displacement, AssignmentOperatorDivision) {
  Displacement quantity({2.0, -4.0, 6.0}, Unit::Length::Metre);
  quantity /= 2.0;
  EXPECT_EQ(quantity, Displacement({1.0, -2.0, 3.0}, Unit::Length::Metre));
}

TEST(Displacement, AssignmentOperatorMultiplication) {
  Displacement quantity({1.0, -2.0, 3.0}, Unit::Length::Metre);
  quantity *= 2.0;
  EXPECT_EQ(quantity, Displacement({2.0, -4.0, 6.0}, Unit::Length::Metre));
}

TEST(Displacement, AssignmentOperatorSubtraction) {
  Displacement quantity({3.0, -6.0, 9.0}, Unit::Length::Metre);
  quantity -= Displacement({2.0, -4.0, 6.0}, Unit::Length::Metre);
  EXPECT_EQ(quantity, Displacement({1.0, -2.0, 3.0}, Unit::Length::Metre));
}

TEST(Displacement, ComparisonOperators) {
  const Displacement first({1.11, -2.22, 3.33}, Unit::Length::Metre);
  const Displacement second({1.11, -2.22, 3.330001}, Unit::Length::Metre);
  EXPECT_EQ(first, first);
  EXPECT_NE(first, second);
  EXPECT_LT(first, second);
  EXPECT_GT(second, first);
  EXPECT_LE(first, first);
  EXPECT_LE(first, second);
  EXPECT_GE(first, first);
  EXPECT_GE(second, first);
}

TEST(Displacement, CopyAssignmentOperator) {
  const Displacement first({1.11, -2.22, 3.33}, Unit::Length::Metre);
  Displacement second = Displacement::Zero();
  second = first;
  EXPECT_EQ(second, first);
}

TEST(Displacement, CopyConstructor) {
  const Displacement first({1.11, -2.22, 3.33}, Unit::Length::Metre);
  const Displacement second{first};
  EXPECT_EQ(second, first);
}

TEST(Displacement, Create) {
  constexpr Displacement first = Displacement::Create<Unit::Length::Metre>(1.11, -2.22, 3.33);
  EXPECT_EQ(first, Displacement({1.11, -2.22, 3.33}, Unit::Length::Metre));

  constexpr Displacement second =
      Displacement::Create<Unit::Length::Metre>(std::array<double, 3>{1.11, -2.22, 3.33});
  EXPECT_EQ(second, Displacement({1.11, -2.22, 3.33}, Unit::Length::Metre));

  constexpr Displacement third =
      Displacement::Create<Unit::Length::Metre>(Vector{1.11, -2.22, 3.33});
  EXPECT_EQ(third, Displacement({1.11, -2.22, 3.33}, Unit::Length::Metre));
}

TEST(Displacement, DefaultConstructor) {
  EXPECT_NO_THROW(Displacement{});
}

TEST(Displacement, Dimensions) {
  EXPECT_EQ(Displacement::Dimensions(), RelatedDimensions<Unit::Length>);
}

TEST(Displacement, Direction) {
  EXPECT_EQ(
      Displacement({2.0, -3.0, 6.0}, Unit::Length::Metre).Direction(), Direction(2.0, -3.0, 6.0));
}

TEST(Displacement, Hash) {
  const Displacement first({1.11, -2.22, 3.33}, Unit::Length::Millimetre);
  const Displacement second({1.11, -2.22, 3.330001}, Unit::Length::Millimetre);
  const Displacement third({1.11, 2.22, 3.33}, Unit::Length::Millimetre);
  const std::hash<Displacement> hash;
  EXPECT_NE(hash(first), hash(second));
  EXPECT_NE(hash(first), hash(third));
  EXPECT_NE(hash(second), hash(third));
}

TEST(Displacement, JSON) {
  EXPECT_EQ(Displacement({1.11, -2.22, 3.33}, Unit::Length::Metre).JSON(),
            "{\"value\":{\"x\":1.110000000000000,\"y\":-2.220000000000000,\"z\":3.330000000000000},"
            "\"unit\":\"m\"}");
  EXPECT_EQ(
      Displacement({0.0, -2.22, 0.0}, Unit::Length::Millimetre).JSON(Unit::Length::Millimetre),
      "{\"value\":{\"x\":0,\"y\":-2.220000000000000,\"z\":0},\"unit\":\"mm\"}");
}

TEST(Displacement, Magnitude) {
  EXPECT_EQ(Displacement({2.0, -3.0, 6.0}, Unit::Length::Metre).Magnitude(),
            Length(7.0, Unit::Length::Metre));
}

TEST(Displacement, MiscellaneousConstructors) {
  EXPECT_EQ(Direction(Displacement({1.11, -2.22, 3.33}, Unit::Length::Metre)),
            Direction(1.11, -2.22, 3.33));

  EXPECT_EQ(Angle(Displacement({0.0, -2.22, 0.0}, Unit::Length::Metre),
                  Displacement({0.0, 0.0, 3.33}, Unit::Length::Metre)),
            Angle(90.0, Unit::Angle::Degree));
}

TEST(Displacement, MoveAssignmentOperator) {
  Displacement first({1.11, -2.22, 3.33}, Unit::Length::Metre);
  Displacement second = Displacement::Zero();
  second = std::move(first);
  EXPECT_EQ(second, Displacement({1.11, -2.22, 3.33}, Unit::Length::Metre));
}

TEST(Displacement, MoveConstructor) {
  Displacement first({1.11, -2.22, 3.33}, Unit::Length::Metre);
  const Displacement second{std::move(first)};
  EXPECT_EQ(second, Displacement({1.11, -2.22, 3.33}, Unit::Length::Metre));
}

TEST(Displacement, MutableValue) {
  Displacement quantity({1.11, -2.22, 3.33}, Unit::Length::Metre);
  Vector& value = quantity.MutableValue();
  value = Vector{-4.44, 5.55, -6.66};
  EXPECT_EQ(quantity.Value(), Vector(-4.44, 5.55, -6.66));
}

TEST(Displacement, Print) {
  EXPECT_EQ(Displacement({1.11, -2.22, 3.33}, Unit::Length::Metre).Print(),
            "(1.110000000000000, -2.220000000000000, 3.330000000000000) m");
  EXPECT_EQ(
      Displacement({0.0, -2.22, 0.0}, Unit::Length::Millimetre).Print(Unit::Length::Millimetre),
      "(0, -2.220000000000000, 0) mm");
}

TEST(Displacement, SetValue) {
  Displacement quantity({1.11, -2.22, 3.33}, Unit::Length::Metre);
  quantity.SetValue({-4.44, 5.55, -6.66});
  EXPECT_EQ(quantity.Value(), Vector(-4.44, 5.55, -6.66));
}

TEST(Displacement, SizeOf) {
  EXPECT_EQ(sizeof(Displacement{}), 3 * sizeof(double));
}

TEST(Displacement, StandardConstructor) {
  EXPECT_NO_THROW(Displacement({1.11, -2.22, 3.33}, Unit::Length::Millimetre));
}

TEST(Displacement, StaticValue) {
  constexpr Displacement quantity =
      Displacement::Create<Unit::Length::Millimetre>(1.11, -2.22, 3.33);
  constexpr Vector value = quantity.StaticValue<Unit::Length::Millimetre>();
  EXPECT_EQ(value, Vector(1.11, -2.22, 3.33));
}

TEST(Displacement, Stream) {
  std::ostringstream stream;
  stream << Displacement({1.11, -2.22, 3.33}, Unit::Length::Metre);
  EXPECT_EQ(stream.str(), Displacement({1.11, -2.22, 3.33}, Unit::Length::Metre).Print());
}

TEST(Displacement, Unit) {
  EXPECT_EQ(Displacement::Unit(), Standard<Unit::Length>);
}

TEST(Displacement, Value) {
  EXPECT_EQ(
      Displacement({1.11, -2.22, 3.33}, Unit::Length::Metre).Value(), Vector(1.11, -2.22, 3.33));
  EXPECT_EQ(
      Displacement({1.11, -2.22, 3.33}, Unit::Length::Millimetre).Value(Unit::Length::Millimetre),
      Vector(1.11, -2.22, 3.33));
}

TEST(Displacement, XML) {
  EXPECT_EQ(Displacement({1.11, -2.22, 3.33}, Unit::Length::Metre).XML(),
            "<value><x>1.110000000000000</x><y>-2.220000000000000</y><z>3.330000000000000</z></"
            "value><unit>m</unit>");
  EXPECT_EQ(Displacement({0.0, -2.22, 0.0}, Unit::Length::Millimetre).XML(Unit::Length::Millimetre),
            "<value><x>0</x><y>-2.220000000000000</y><z>0</z></value><unit>mm</unit>");
}

TEST(Displacement, XYZ) {
  EXPECT_EQ(Displacement({1.11, -2.22, 3.33}, Unit::Length::Metre).x(),
            Length(1.11, Unit::Length::Metre));
  EXPECT_EQ(Displacement({1.11, -2.22, 3.33}, Unit::Length::Metre).y(),
            Length(-2.22, Unit::Length::Metre));
  EXPECT_EQ(Displacement({1.11, -2.22, 3.33}, Unit::Length::Metre).z(),
            Length(3.33, Unit::Length::Metre));
}

TEST(Displacement, YAML) {
  EXPECT_EQ(Displacement({1.11, -2.22, 3.33}, Unit::Length::Metre).YAML(),
            "{value:{x:1.110000000000000,y:-2.220000000000000,z:3.330000000000000},unit:\"m\"}");
  EXPECT_EQ(
      Displacement({0.0, -2.22, 0.0}, Unit::Length::Millimetre).YAML(Unit::Length::Millimetre),
      "{value:{x:0,y:-2.220000000000000,z:0},unit:\"mm\"}");
}

TEST(Displacement, Zero) {
  EXPECT_EQ(Displacement::Zero(), Displacement({0.0, 0.0, 0.0}, Unit::Length::Metre));
}

}  // namespace

}  // namespace PhQ
