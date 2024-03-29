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

#include "../include/PhQ/Acceleration.hpp"

#include <array>
#include <functional>
#include <gtest/gtest.h>
#include <sstream>
#include <utility>

#include "../include/PhQ/Angle.hpp"
#include "../include/PhQ/Direction.hpp"
#include "../include/PhQ/Frequency.hpp"
#include "../include/PhQ/ScalarAcceleration.hpp"
#include "../include/PhQ/Time.hpp"
#include "../include/PhQ/Unit/Acceleration.hpp"
#include "../include/PhQ/Unit/Angle.hpp"
#include "../include/PhQ/Unit/Frequency.hpp"
#include "../include/PhQ/Unit/Speed.hpp"
#include "../include/PhQ/Unit/Time.hpp"
#include "../include/PhQ/Vector.hpp"
#include "../include/PhQ/Velocity.hpp"

namespace PhQ {

namespace {

TEST(Acceleration, Angle) {
  EXPECT_EQ(Acceleration({0.0, -2.22, 0.0}, Unit::Acceleration::MetrePerSquareSecond)
                .Angle(Acceleration({0.0, 0.0, 3.33}, Unit::Acceleration::MetrePerSquareSecond)),
            Angle(90.0, Unit::Angle::Degree));
}

TEST(Acceleration, ArithmeticOperatorAddition) {
  EXPECT_EQ(Acceleration({1.0, -2.0, 3.0}, Unit::Acceleration::MetrePerSquareSecond)
                + Acceleration({2.0, -4.0, 6.0}, Unit::Acceleration::MetrePerSquareSecond),
            Acceleration({3.0, -6.0, 9.0}, Unit::Acceleration::MetrePerSquareSecond));
}

TEST(Acceleration, ArithmeticOperatorDivision) {
  EXPECT_EQ(Acceleration({2.0, -4.0, 6.0}, Unit::Acceleration::MetrePerSquareSecond) / 2.0,
            Acceleration({1.0, -2.0, 3.0}, Unit::Acceleration::MetrePerSquareSecond));

  EXPECT_EQ(Acceleration({2.0, -4.0, 6.0}, Unit::Acceleration::MetrePerSquareSecond)
                / Frequency(2.0, Unit::Frequency::Hertz),
            Velocity({1.0, -2.0, 3.0}, Unit::Speed::MetrePerSecond));

  EXPECT_EQ(Velocity({2.0, -4.0, 6.0}, Unit::Speed::MetrePerSecond) / Time(2.0, Unit::Time::Second),
            Acceleration({1.0, -2.0, 3.0}, Unit::Acceleration::MetrePerSquareSecond));
}

TEST(Acceleration, ArithmeticOperatorMultiplication) {
  EXPECT_EQ(Acceleration({1.0, -2.0, 3.0}, Unit::Acceleration::MetrePerSquareSecond) * 2.0,
            Acceleration({2.0, -4.0, 6.0}, Unit::Acceleration::MetrePerSquareSecond));

  EXPECT_EQ(2.0 * Acceleration({1.0, -2.0, 3.0}, Unit::Acceleration::MetrePerSquareSecond),
            Acceleration({2.0, -4.0, 6.0}, Unit::Acceleration::MetrePerSquareSecond));

  EXPECT_EQ(
      Direction(2.0, -3.0, 6.0) * ScalarAcceleration(7.0, Unit::Acceleration::MetrePerSquareSecond),
      Acceleration({2.0, -3.0, 6.0}, Unit::Acceleration::MetrePerSquareSecond));

  EXPECT_EQ(
      ScalarAcceleration(7.0, Unit::Acceleration::MetrePerSquareSecond) * Direction(2.0, -3.0, 6.0),
      Acceleration({2.0, -3.0, 6.0}, Unit::Acceleration::MetrePerSquareSecond));

  EXPECT_EQ(Acceleration({1.0, -2.0, 3.0}, Unit::Acceleration::MetrePerSquareSecond)
                * Time(2.0, Unit::Time::Second),
            Velocity({2.0, -4.0, 6.0}, Unit::Speed::MetrePerSecond));

  EXPECT_EQ(Time(2.0, Unit::Time::Second)
                * Acceleration({1.0, -2.0, 3.0}, Unit::Acceleration::MetrePerSquareSecond),
            Velocity({2.0, -4.0, 6.0}, Unit::Speed::MetrePerSecond));

  EXPECT_EQ(Velocity({1.0, -2.0, 3.0}, Unit::Speed::MetrePerSecond)
                * Frequency(2.0, Unit::Frequency::Hertz),
            Acceleration({2.0, -4.0, 6.0}, Unit::Acceleration::MetrePerSquareSecond));
}

TEST(Acceleration, ArithmeticOperatorSubtraction) {
  EXPECT_EQ(Acceleration({3.0, -6.0, 9.0}, Unit::Acceleration::MetrePerSquareSecond)
                - Acceleration({2.0, -4.0, 6.0}, Unit::Acceleration::MetrePerSquareSecond),
            Acceleration({1.0, -2.0, 3.0}, Unit::Acceleration::MetrePerSquareSecond));
}

TEST(Acceleration, AssignmentOperatorAddition) {
  Acceleration quantity({1.0, -2.0, 3.0}, Unit::Acceleration::MetrePerSquareSecond);
  quantity += Acceleration({2.0, -4.0, 6.0}, Unit::Acceleration::MetrePerSquareSecond);
  EXPECT_EQ(quantity, Acceleration({3.0, -6.0, 9.0}, Unit::Acceleration::MetrePerSquareSecond));
}

TEST(Acceleration, AssignmentOperatorDivision) {
  Acceleration quantity({2.0, -4.0, 6.0}, Unit::Acceleration::MetrePerSquareSecond);
  quantity /= 2.0;
  EXPECT_EQ(quantity, Acceleration({1.0, -2.0, 3.0}, Unit::Acceleration::MetrePerSquareSecond));
}

TEST(Acceleration, AssignmentOperatorMultiplication) {
  Acceleration quantity({1.0, -2.0, 3.0}, Unit::Acceleration::MetrePerSquareSecond);
  quantity *= 2.0;
  EXPECT_EQ(quantity, Acceleration({2.0, -4.0, 6.0}, Unit::Acceleration::MetrePerSquareSecond));
}

TEST(Acceleration, AssignmentOperatorSubtraction) {
  Acceleration quantity({3.0, -6.0, 9.0}, Unit::Acceleration::MetrePerSquareSecond);
  quantity -= Acceleration({2.0, -4.0, 6.0}, Unit::Acceleration::MetrePerSquareSecond);
  EXPECT_EQ(quantity, Acceleration({1.0, -2.0, 3.0}, Unit::Acceleration::MetrePerSquareSecond));
}

TEST(Acceleration, ComparisonOperators) {
  const Acceleration first({1.11, -2.22, 3.33}, Unit::Acceleration::MetrePerSquareSecond);
  const Acceleration second({1.11, -2.22, 3.330001}, Unit::Acceleration::MetrePerSquareSecond);
  EXPECT_EQ(first, first);
  EXPECT_NE(first, second);
  EXPECT_LT(first, second);
  EXPECT_GT(second, first);
  EXPECT_LE(first, first);
  EXPECT_LE(first, second);
  EXPECT_GE(first, first);
  EXPECT_GE(second, first);
}

TEST(Acceleration, CopyAssignmentOperator) {
  const Acceleration first({1.11, -2.22, 3.33}, Unit::Acceleration::MetrePerSquareSecond);
  Acceleration second = Acceleration::Zero();
  second = first;
  EXPECT_EQ(second, first);
}

TEST(Acceleration, CopyConstructor) {
  const Acceleration first({1.11, -2.22, 3.33}, Unit::Acceleration::MetrePerSquareSecond);
  const Acceleration second{first};
  EXPECT_EQ(second, first);
}

TEST(Acceleration, Create) {
  constexpr Acceleration first =
      Acceleration::Create<Unit::Acceleration::MetrePerSquareSecond>(1.11, -2.22, 3.33);
  EXPECT_EQ(first, Acceleration({1.11, -2.22, 3.33}, Unit::Acceleration::MetrePerSquareSecond));

  constexpr Acceleration second = Acceleration::Create<Unit::Acceleration::MetrePerSquareSecond>(
      std::array<double, 3>{1.11, -2.22, 3.33});
  EXPECT_EQ(second, Acceleration({1.11, -2.22, 3.33}, Unit::Acceleration::MetrePerSquareSecond));

  constexpr Acceleration third =
      Acceleration::Create<Unit::Acceleration::MetrePerSquareSecond>(Vector{1.11, -2.22, 3.33});
  EXPECT_EQ(third, Acceleration({1.11, -2.22, 3.33}, Unit::Acceleration::MetrePerSquareSecond));
}

TEST(Acceleration, DefaultConstructor) {
  EXPECT_NO_THROW(Acceleration{});
}

TEST(Acceleration, Dimensions) {
  EXPECT_EQ(Acceleration::Dimensions(), RelatedDimensions<Unit::Acceleration>);
}

TEST(Acceleration, Direction) {
  EXPECT_EQ(Acceleration({2.0, -3.0, 6.0}, Unit::Acceleration::MetrePerSquareSecond).Direction(),
            Direction(2.0, -3.0, 6.0));
}

TEST(Acceleration, Hash) {
  const Acceleration first({1.11, -2.22, 3.33}, Unit::Acceleration::MillimetrePerSquareSecond);
  const Acceleration second({1.11, -2.22, 3.330001}, Unit::Acceleration::MillimetrePerSquareSecond);
  const Acceleration third({1.11, 2.22, 3.33}, Unit::Acceleration::MillimetrePerSquareSecond);
  const std::hash<Acceleration> hash;
  EXPECT_NE(hash(first), hash(second));
  EXPECT_NE(hash(first), hash(third));
  EXPECT_NE(hash(second), hash(third));
}

TEST(Acceleration, JSON) {
  EXPECT_EQ(Acceleration({1.11, -2.22, 3.33}, Unit::Acceleration::MetrePerSquareSecond).JSON(),
            "{\"value\":{\"x\":1.110000000000000,\"y\":-2.220000000000000,"
            "\"z\":3.330000000000000},\"unit\":\"m/s^2\"}");
  EXPECT_EQ(Acceleration({0.0, -2.22, 0.0}, Unit::Acceleration::MillimetrePerSquareSecond)
                .JSON(Unit::Acceleration::MillimetrePerSquareSecond),
            "{\"value\":{\"x\":0,\"y\":-2.220000000000000,\"z\":0},\"unit\":"
            "\"mm/s^2\"}");
}

TEST(Acceleration, Magnitude) {
  EXPECT_EQ(Acceleration({2.0, -3.0, 6.0}, Unit::Acceleration::MetrePerSquareSecond).Magnitude(),
            ScalarAcceleration(7.0, Unit::Acceleration::MetrePerSquareSecond));
}

TEST(Acceleration, MiscellaneousConstructors) {
  EXPECT_EQ(Direction(Acceleration({1.11, -2.22, 3.33}, Unit::Acceleration::MetrePerSquareSecond)),
            Direction(1.11, -2.22, 3.33));

  EXPECT_EQ(Angle(Acceleration({0.0, -2.22, 0.0}, Unit::Acceleration::MetrePerSquareSecond),
                  Acceleration({0.0, 0.0, 3.33}, Unit::Acceleration::MetrePerSquareSecond)),
            Angle(90.0, Unit::Angle::Degree));

  EXPECT_EQ(Velocity(Acceleration({1.0, -2.0, 3.0}, Unit::Acceleration::MetrePerSquareSecond),
                     Time(2.0, Unit::Time::Second)),
            Velocity({2.0, -4.0, 6.0}, Unit::Speed::MetrePerSecond));

  EXPECT_EQ(Velocity(Acceleration({2.0, -4.0, 6.0}, Unit::Acceleration::MetrePerSquareSecond),
                     Frequency(2.0, Unit::Frequency::Hertz)),
            Velocity({1.0, -2.0, 3.0}, Unit::Speed::MetrePerSecond));
}

TEST(Acceleration, MoveAssignmentOperator) {
  Acceleration first({1.11, -2.22, 3.33}, Unit::Acceleration::MetrePerSquareSecond);
  Acceleration second = Acceleration::Zero();
  second = std::move(first);
  EXPECT_EQ(second, Acceleration({1.11, -2.22, 3.33}, Unit::Acceleration::MetrePerSquareSecond));
}

TEST(Acceleration, MoveConstructor) {
  Acceleration first({1.11, -2.22, 3.33}, Unit::Acceleration::MetrePerSquareSecond);
  const Acceleration second{std::move(first)};
  EXPECT_EQ(second, Acceleration({1.11, -2.22, 3.33}, Unit::Acceleration::MetrePerSquareSecond));
}

TEST(Acceleration, MutableValue) {
  Acceleration quantity({1.11, -2.22, 3.33}, Unit::Acceleration::MetrePerSquareSecond);
  Vector& value = quantity.MutableValue();
  value = Vector{-4.44, 5.55, -6.66};
  EXPECT_EQ(quantity.Value(), Vector(-4.44, 5.55, -6.66));
}

TEST(Acceleration, Print) {
  EXPECT_EQ(Acceleration({1.11, -2.22, 3.33}, Unit::Acceleration::MetrePerSquareSecond).Print(),
            "(1.110000000000000, -2.220000000000000, 3.330000000000000) m/s^2");
  EXPECT_EQ(Acceleration({0.0, -2.22, 0.0}, Unit::Acceleration::MillimetrePerSquareSecond)
                .Print(Unit::Acceleration::MillimetrePerSquareSecond),
            "(0, -2.220000000000000, 0) mm/s^2");
}

TEST(Acceleration, SetValue) {
  Acceleration quantity({1.11, -2.22, 3.33}, Unit::Acceleration::MetrePerSquareSecond);
  quantity.SetValue({-4.44, 5.55, -6.66});
  EXPECT_EQ(quantity.Value(), Vector(-4.44, 5.55, -6.66));
}

TEST(Acceleration, SizeOf) {
  EXPECT_EQ(sizeof(Acceleration{}), 3 * sizeof(double));
}

TEST(Acceleration, StandardConstructor) {
  EXPECT_NO_THROW(Acceleration({1.11, -2.22, 3.33}, Unit::Acceleration::MillimetrePerSquareSecond));
}

TEST(Acceleration, StaticValue) {
  constexpr Acceleration quantity =
      Acceleration::Create<Unit::Acceleration::MillimetrePerSquareSecond>(1.11, -2.22, 3.33);
  constexpr Vector value = quantity.StaticValue<Unit::Acceleration::MillimetrePerSquareSecond>();
  EXPECT_EQ(value, Vector(1.11, -2.22, 3.33));
}

TEST(Acceleration, Stream) {
  std::ostringstream stream;
  stream << Acceleration({1.11, -2.22, 3.33}, Unit::Acceleration::MillimetrePerSquareSecond);
  EXPECT_EQ(
      stream.str(),
      Acceleration({1.11, -2.22, 3.33}, Unit::Acceleration::MillimetrePerSquareSecond).Print());
}

TEST(Acceleration, Unit) {
  EXPECT_EQ(Acceleration::Unit(), Standard<Unit::Acceleration>);
}

TEST(Acceleration, Value) {
  EXPECT_EQ(Acceleration({1.11, -2.22, 3.33}, Unit::Acceleration::MetrePerSquareSecond).Value(),
            Vector(1.11, -2.22, 3.33));
  EXPECT_EQ(Acceleration({1.11, -2.22, 3.33}, Unit::Acceleration::MillimetrePerSquareSecond)
                .Value(Unit::Acceleration::MillimetrePerSquareSecond),
            Vector(1.11, -2.22, 3.33));
}

TEST(Acceleration, XML) {
  EXPECT_EQ(Acceleration({1.11, -2.22, 3.33}, Unit::Acceleration::MetrePerSquareSecond).XML(),
            "<value><x>1.110000000000000</x><y>-2.220000000000000</"
            "y><z>3.330000000000000</z></value><unit>m/s^2</unit>");
  EXPECT_EQ(Acceleration({0.0, -2.22, 0.0}, Unit::Acceleration::MillimetrePerSquareSecond)
                .XML(Unit::Acceleration::MillimetrePerSquareSecond),
            "<value><x>0</x><y>-2.220000000000000</y><z>0</z></value><unit>mm/"
            "s^2</unit>");
}

TEST(Acceleration, XYZ) {
  EXPECT_EQ(Acceleration({1.11, -2.22, 3.33}, Unit::Acceleration::MetrePerSquareSecond).x(),
            ScalarAcceleration(1.11, Unit::Acceleration::MetrePerSquareSecond));
  EXPECT_EQ(Acceleration({1.11, -2.22, 3.33}, Unit::Acceleration::MetrePerSquareSecond).y(),
            ScalarAcceleration(-2.22, Unit::Acceleration::MetrePerSquareSecond));
  EXPECT_EQ(Acceleration({1.11, -2.22, 3.33}, Unit::Acceleration::MetrePerSquareSecond).z(),
            ScalarAcceleration(3.33, Unit::Acceleration::MetrePerSquareSecond));
}

TEST(Acceleration, YAML) {
  EXPECT_EQ(Acceleration({1.11, -2.22, 3.33}, Unit::Acceleration::MetrePerSquareSecond).YAML(),
            "{value:{x:1.110000000000000,y:-2.220000000000000,z:3."
            "330000000000000},unit:\"m/s^2\"}");
  EXPECT_EQ(Acceleration({0.0, -2.22, 0.0}, Unit::Acceleration::MillimetrePerSquareSecond)
                .YAML(Unit::Acceleration::MillimetrePerSquareSecond),
            "{value:{x:0,y:-2.220000000000000,z:0},unit:\"mm/s^2\"}");
}

TEST(Acceleration, Zero) {
  EXPECT_EQ(Acceleration::Zero(),
            Acceleration({0.0, 0.0, 0.0}, Unit::Acceleration::MetrePerSquareSecond));
}

}  // namespace

}  // namespace PhQ
