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

#include "../include/PhQ/VelocityGradient.hpp"

#include <array>
#include <functional>
#include <gtest/gtest.h>
#include <sstream>
#include <utility>

#include "../include/PhQ/DisplacementGradient.hpp"
#include "../include/PhQ/Dyad.hpp"
#include "../include/PhQ/Frequency.hpp"
#include "../include/PhQ/ScalarVelocityGradient.hpp"
#include "../include/PhQ/StrainRate.hpp"
#include "../include/PhQ/Time.hpp"
#include "../include/PhQ/Unit/Frequency.hpp"
#include "../include/PhQ/Unit/Time.hpp"

namespace PhQ {

namespace {

TEST(VelocityGradient, ArithmeticOperatorAddition) {
  EXPECT_EQ(
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz)
          + VelocityGradient(
              {2.0, -4.0, 6.0, -8.0, 10.0, -12.0, 14.0, -16.0, 18.0}, Unit::Frequency::Hertz),
      VelocityGradient(
          {3.0, -6.0, 9.0, -12.0, 15.0, -18.0, 21.0, -24.0, 27.0}, Unit::Frequency::Hertz));
}

TEST(VelocityGradient, ArithmeticOperatorDivision) {
  EXPECT_EQ(
      VelocityGradient(
          {2.0, -4.0, 6.0, -8.0, 10.0, -12.0, 14.0, -16.0, 18.0}, Unit::Frequency::Hertz)
          / 2.0,
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz));
  EXPECT_EQ(VelocityGradient(
                {2.0, -4.0, 6.0, -8.0, 10.0, -12.0, 14.0, -16.0, 18.0}, Unit::Frequency::Hertz)
                / Frequency(2.0, Unit::Frequency::Hertz),
            DisplacementGradient(1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0));
  EXPECT_EQ(
      DisplacementGradient(2.0, -4.0, 6.0, -8.0, 10.0, -12.0, 14.0, -16.0, 18.0)
          / Time(2.0, Unit::Time::Second),
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz));
}

TEST(VelocityGradient, ArithmeticOperatorMultiplication) {
  EXPECT_EQ(
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz)
          * 2.0,
      VelocityGradient(
          {2.0, -4.0, 6.0, -8.0, 10.0, -12.0, 14.0, -16.0, 18.0}, Unit::Frequency::Hertz));
  EXPECT_EQ(2.0
                * VelocityGradient(
                    {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz),
            VelocityGradient(
                {2.0, -4.0, 6.0, -8.0, 10.0, -12.0, 14.0, -16.0, 18.0}, Unit::Frequency::Hertz));
  EXPECT_EQ(
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz)
          * Time(2.0, Unit::Time::Second),
      DisplacementGradient(2.0, -4.0, 6.0, -8.0, 10.0, -12.0, 14.0, -16.0, 18.0));
  EXPECT_EQ(Time(2.0, Unit::Time::Second)
                * VelocityGradient(
                    {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz),
            DisplacementGradient(2.0, -4.0, 6.0, -8.0, 10.0, -12.0, 14.0, -16.0, 18.0));
  EXPECT_EQ(DisplacementGradient(1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0)
                * Frequency(2.0, Unit::Frequency::Hertz),
            VelocityGradient(
                {2.0, -4.0, 6.0, -8.0, 10.0, -12.0, 14.0, -16.0, 18.0}, Unit::Frequency::Hertz));
  EXPECT_EQ(Frequency(2.0, Unit::Frequency::Hertz)
                * DisplacementGradient(1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0),
            VelocityGradient(
                {2.0, -4.0, 6.0, -8.0, 10.0, -12.0, 14.0, -16.0, 18.0}, Unit::Frequency::Hertz));
}

TEST(VelocityGradient, ArithmeticOperatorSubtraction) {
  EXPECT_EQ(
      VelocityGradient(
          {3.0, -6.0, 9.0, -12.0, 15.0, -18.0, 21.0, -24.0, 27.0}, Unit::Frequency::Hertz)
          - VelocityGradient(
              {2.0, -4.0, 6.0, -8.0, 10.0, -12.0, 14.0, -16.0, 18.0}, Unit::Frequency::Hertz),
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz));
}

TEST(VelocityGradient, AssignmentOperatorAddition) {
  VelocityGradient velocity_gradient(
      {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz);
  velocity_gradient += VelocityGradient(
      {2.0, -4.0, 6.0, -8.0, 10.0, -12.0, 14.0, -16.0, 18.0}, Unit::Frequency::Hertz);
  EXPECT_EQ(velocity_gradient,
            VelocityGradient(
                {3.0, -6.0, 9.0, -12.0, 15.0, -18.0, 21.0, -24.0, 27.0}, Unit::Frequency::Hertz));
}

TEST(VelocityGradient, AssignmentOperatorDivision) {
  VelocityGradient velocity_gradient(
      {2.0, -4.0, 6.0, -8.0, 10.0, -12.0, 14.0, -16.0, 18.0}, Unit::Frequency::Hertz);
  velocity_gradient /= 2.0;
  EXPECT_EQ(velocity_gradient, VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0},
                                                Unit::Frequency::Hertz));
}

TEST(VelocityGradient, AssignmentOperatorMultiplication) {
  VelocityGradient velocity_gradient(
      {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz);
  velocity_gradient *= 2.0;
  EXPECT_EQ(velocity_gradient,
            VelocityGradient(
                {2.0, -4.0, 6.0, -8.0, 10.0, -12.0, 14.0, -16.0, 18.0}, Unit::Frequency::Hertz));
}

TEST(VelocityGradient, AssignmentOperatorSubtraction) {
  VelocityGradient velocity_gradient(
      {3.0, -6.0, 9.0, -12.0, 15.0, -18.0, 21.0, -24.0, 27.0}, Unit::Frequency::Hertz);
  velocity_gradient -= VelocityGradient(
      {2.0, -4.0, 6.0, -8.0, 10.0, -12.0, 14.0, -16.0, 18.0}, Unit::Frequency::Hertz);
  EXPECT_EQ(velocity_gradient, VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0},
                                                Unit::Frequency::Hertz));
}

TEST(VelocityGradient, ComparisonOperators) {
  const VelocityGradient first(
      {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz);
  const VelocityGradient second(
      {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.000001}, Unit::Frequency::Hertz);
  EXPECT_EQ(first, first);
  EXPECT_NE(first, second);
  EXPECT_LT(first, second);
  EXPECT_GT(second, first);
  EXPECT_LE(first, first);
  EXPECT_LE(first, second);
  EXPECT_GE(first, first);
  EXPECT_GE(second, first);
}

TEST(VelocityGradient, CopyAssignmentOperator) {
  const VelocityGradient first(
      {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz);
  VelocityGradient second = VelocityGradient::Zero();
  second = first;
  EXPECT_EQ(second, VelocityGradient(
                        {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz));
}

TEST(VelocityGradient, CopyConstructor) {
  const VelocityGradient first(
      {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz);
  const VelocityGradient second{first};
  EXPECT_EQ(second, VelocityGradient(
                        {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz));
}

TEST(VelocityGradient, Create) {
  {
    constexpr VelocityGradient velocity_gradient = VelocityGradient::Create<Unit::Frequency::Hertz>(
        1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0);
    EXPECT_EQ(velocity_gradient, VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0},
                                                  Unit::Frequency::Hertz));
  }
  {
    constexpr VelocityGradient velocity_gradient = VelocityGradient::Create<Unit::Frequency::Hertz>(
        std::array<double, 9>{1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0});
    EXPECT_EQ(velocity_gradient, VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0},
                                                  Unit::Frequency::Hertz));
  }
  {
    constexpr VelocityGradient velocity_gradient = VelocityGradient::Create<Unit::Frequency::Hertz>(
        Dyad{1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0});
    EXPECT_EQ(velocity_gradient, VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0},
                                                  Unit::Frequency::Hertz));
  }
}

TEST(VelocityGradient, DefaultConstructor) {
  EXPECT_NO_THROW(VelocityGradient{});
}

TEST(VelocityGradient, Dimensions) {
  EXPECT_EQ(VelocityGradient::Dimensions(), RelatedDimensions<Unit::Frequency>);
}

TEST(VelocityGradient, Hash) {
  const VelocityGradient first(
      {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Kilohertz);
  const VelocityGradient second(
      {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.000001}, Unit::Frequency::Kilohertz);
  const VelocityGradient third(
      {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, 8.0, 9.0}, Unit::Frequency::Kilohertz);
  const std::hash<VelocityGradient> hash;
  EXPECT_NE(hash(first), hash(second));
  EXPECT_NE(hash(first), hash(third));
  EXPECT_NE(hash(second), hash(third));
}

TEST(VelocityGradient, JSON) {
  EXPECT_EQ(
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz)
          .JSON(),
      "{\"value\":{\"xx\":" + Print(1.0) + ",\"xy\":" + Print(-2.0) + ",\"xz\":" + Print(3.0)
          + ",\"yx\":" + Print(-4.0) + ",\"yy\":" + Print(5.0) + ",\"yz\":" + Print(-6.0)
          + ",\"zx\":" + Print(7.0) + ",\"zy\":" + Print(-8.0) + ",\"zz\":" + Print(9.0)
          + "},\"unit\":\"Hz\"}");
  EXPECT_EQ(VelocityGradient(
                {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Kilohertz)
                .JSON(Unit::Frequency::Kilohertz),
            "{\"value\":{\"xx\":" + Print(1.0) + ",\"xy\":" + Print(-2.0) + ",\"xz\":" + Print(3.0)
                + ",\"yx\":" + Print(-4.0) + ",\"yy\":" + Print(5.0) + ",\"yz\":" + Print(-6.0)
                + ",\"zx\":" + Print(7.0) + ",\"zy\":" + Print(-8.0) + ",\"zz\":" + Print(9.0)
                + "},\"unit\":\"kHz\"}");
}

TEST(VelocityGradient, MiscellaneousConstructors) {
  EXPECT_EQ(
      VelocityGradient(DisplacementGradient(2.0, -4.0, 6.0, -8.0, 10.0, -12.0, 14.0, -16.0, 18.0),
                       Time(2.0, Unit::Time::Second)),
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz));
  EXPECT_EQ(VelocityGradient(DisplacementGradient(1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0),
                             Frequency(2.0, Unit::Frequency::Hertz)),
            VelocityGradient(
                {2.0, -4.0, 6.0, -8.0, 10.0, -12.0, 14.0, -16.0, 18.0}, Unit::Frequency::Hertz));
  EXPECT_EQ(DisplacementGradient(VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0},
                                                  Unit::Frequency::Hertz),
                                 Time(2.0, Unit::Time::Second)),
            DisplacementGradient(2.0, -4.0, 6.0, -8.0, 10.0, -12.0, 14.0, -16.0, 18.0));
  EXPECT_EQ(
      DisplacementGradient(VelocityGradient({2.0, -4.0, 6.0, -8.0, 10.0, -12.0, 14.0, -16.0, 18.0},
                                            Unit::Frequency::Hertz),
                           Frequency(2.0, Unit::Frequency::Hertz)),
      DisplacementGradient(1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0));
  EXPECT_EQ(StrainRate(VelocityGradient(
                {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz)),
            StrainRate({1.0, -3.0, 5.0, 5.0, -7.0, 9.0}, Unit::Frequency::Hertz));
}

TEST(VelocityGradient, MiscellaneousMethods) {
  EXPECT_EQ(
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz)
          .StrainRate(),
      StrainRate({1.0, -3.0, 5.0, 5.0, -7.0, 9.0}, Unit::Frequency::Hertz));
}

TEST(VelocityGradient, MoveAssignmentOperator) {
  VelocityGradient first({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz);
  VelocityGradient second = VelocityGradient::Zero();
  second = std::move(first);
  EXPECT_EQ(second, VelocityGradient(
                        {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz));
}

TEST(VelocityGradient, MoveConstructor) {
  VelocityGradient first({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz);
  const VelocityGradient second{std::move(first)};
  EXPECT_EQ(second, VelocityGradient(
                        {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz));
}

TEST(VelocityGradient, MutableValue) {
  VelocityGradient velocity_gradient(
      {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz);
  Dyad<double>& value = velocity_gradient.MutableValue();
  value = Dyad{-10.10, 11.0, -12.12, 13.13, -14.14, 15.15, -16.16, 17.17, -18.18};
  EXPECT_EQ(velocity_gradient.Value(),
            Dyad(-10.10, 11.0, -12.12, 13.13, -14.14, 15.15, -16.16, 17.17, -18.18));
}

TEST(VelocityGradient, Print) {
  EXPECT_EQ(
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz)
          .Print(),
      "(" + Print(1.0) + ", " + Print(-2.0) + ", " + Print(3.0) + "; " + Print(-4.0) + ", "
          + Print(5.0) + ", " + Print(-6.0) + "; " + Print(7.0) + ", " + Print(-8.0) + ", "
          + Print(9.0) + ") Hz");
  EXPECT_EQ(VelocityGradient(
                {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Kilohertz)
                .Print(Unit::Frequency::Kilohertz),
            "(" + Print(1.0) + ", " + Print(-2.0) + ", " + Print(3.0) + "; " + Print(-4.0) + ", "
                + Print(5.0) + ", " + Print(-6.0) + "; " + Print(7.0) + ", " + Print(-8.0) + ", "
                + Print(9.0) + ") kHz");
}

TEST(VelocityGradient, SetValue) {
  VelocityGradient velocity_gradient(
      {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz);
  velocity_gradient.SetValue(
      Dyad(-10.10, 11.0, -12.12, 13.13, -14.14, 15.15, -16.16, 17.17, -18.18));
  EXPECT_EQ(velocity_gradient.Value(),
            Dyad(-10.10, 11.0, -12.12, 13.13, -14.14, 15.15, -16.16, 17.17, -18.18));
}

TEST(VelocityGradient, SizeOf) {
  EXPECT_EQ(sizeof(VelocityGradient{}), 9 * sizeof(double));
}

TEST(VelocityGradient, StandardConstructor) {
  EXPECT_NO_THROW(
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz));
}

TEST(VelocityGradient, StaticValue) {
  constexpr VelocityGradient velocity_gradient =
      VelocityGradient::Create<Unit::Frequency::Kilohertz>(
          1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0);
  constexpr Dyad value = velocity_gradient.StaticValue<Unit::Frequency::Kilohertz>();
  EXPECT_EQ(value, Dyad(1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0));
}

TEST(VelocityGradient, Stream) {
  std::ostringstream stream;
  stream << VelocityGradient(
      {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz);
  EXPECT_EQ(
      stream.str(),
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz)
          .Print());
}

TEST(VelocityGradient, Value) {
  EXPECT_EQ(
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz)
          .Value(),
      Dyad(1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0));
  EXPECT_EQ(VelocityGradient(
                {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Kilohertz)
                .Value(Unit::Frequency::Kilohertz),
            Dyad(1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0));
}

TEST(VelocityGradient, XML) {
  EXPECT_EQ(
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz)
          .XML(),
      "<value><xx>" + Print(1.0) + "</xx><xy>" + Print(-2.0) + "</xy><xz>" + Print(3.0)
          + "</xz><yx>" + Print(-4.0) + "</yx><yy>" + Print(5.0) + "</yy><yz>" + Print(-6.0)
          + "</yz><zx>" + Print(7.0) + "</zx><zy>" + Print(-8.0) + "</zy><zz>" + Print(9.0)
          + "</zz></value><unit>Hz</unit>");
  EXPECT_EQ(VelocityGradient(
                {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Kilohertz)
                .XML(Unit::Frequency::Kilohertz),
            "<value><xx>" + Print(1.0) + "</xx><xy>" + Print(-2.0) + "</xy><xz>" + Print(3.0)
                + "</xz><yx>" + Print(-4.0) + "</yx><yy>" + Print(5.0) + "</yy><yz>" + Print(-6.0)
                + "</yz><zx>" + Print(7.0) + "</zx><zy>" + Print(-8.0) + "</zy><zz>" + Print(9.0)
                + "</zz></value><unit>kHz</unit>");
}

TEST(VelocityGradient, XYZ) {
  EXPECT_EQ(
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz)
          .xx(),
      ScalarVelocityGradient(1.0, Unit::Frequency::Hertz));
  EXPECT_EQ(
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz)
          .xy(),
      ScalarVelocityGradient(-2.0, Unit::Frequency::Hertz));
  EXPECT_EQ(
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz)
          .xz(),
      ScalarVelocityGradient(3.0, Unit::Frequency::Hertz));
  EXPECT_EQ(
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz)
          .yx(),
      ScalarVelocityGradient(-4.0, Unit::Frequency::Hertz));
  EXPECT_EQ(
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz)
          .yy(),
      ScalarVelocityGradient(5.0, Unit::Frequency::Hertz));
  EXPECT_EQ(
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz)
          .yz(),
      ScalarVelocityGradient(-6.0, Unit::Frequency::Hertz));
  EXPECT_EQ(
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz)
          .zx(),
      ScalarVelocityGradient(7.0, Unit::Frequency::Hertz));
  EXPECT_EQ(
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz)
          .zy(),
      ScalarVelocityGradient(-8.0, Unit::Frequency::Hertz));
  EXPECT_EQ(
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz)
          .zz(),
      ScalarVelocityGradient(9.0, Unit::Frequency::Hertz));
}

TEST(VelocityGradient, YAML) {
  EXPECT_EQ(
      VelocityGradient({1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Hertz)
          .YAML(),
      "{value:{xx:" + Print(1.0) + ",xy:" + Print(-2.0) + ",xz:" + Print(3.0) + ",yx:" + Print(-4.0)
          + ",yy:" + Print(5.0) + ",yz:" + Print(-6.0) + ",zx:" + Print(7.0) + ",zy:" + Print(-8.0)
          + ",zz:" + Print(9.0) + "},unit:\"Hz\"}");
  EXPECT_EQ(VelocityGradient(
                {1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0}, Unit::Frequency::Kilohertz)
                .YAML(Unit::Frequency::Kilohertz),
            "{value:{xx:" + Print(1.0) + ",xy:" + Print(-2.0) + ",xz:" + Print(3.0) + ",yx:"
                + Print(-4.0) + ",yy:" + Print(5.0) + ",yz:" + Print(-6.0) + ",zx:" + Print(7.0)
                + ",zy:" + Print(-8.0) + ",zz:" + Print(9.0) + "},unit:\"kHz\"}");
}

TEST(VelocityGradient, Zero) {
  EXPECT_EQ(
      VelocityGradient::Zero(),
      VelocityGradient({0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, Unit::Frequency::Hertz));
}

}  // namespace

}  // namespace PhQ
