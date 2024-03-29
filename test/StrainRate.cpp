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

#include "../include/PhQ/StrainRate.hpp"

#include <array>
#include <functional>
#include <gtest/gtest.h>
#include <sstream>
#include <utility>

#include "../include/PhQ/Frequency.hpp"
#include "../include/PhQ/ScalarStrainRate.hpp"
#include "../include/PhQ/Strain.hpp"
#include "../include/PhQ/SymmetricDyad.hpp"
#include "../include/PhQ/Time.hpp"
#include "../include/PhQ/Unit/Frequency.hpp"
#include "../include/PhQ/Unit/Time.hpp"

namespace PhQ {

namespace {

TEST(StrainRate, ArithmeticOperatorAddition) {
  EXPECT_EQ(StrainRate({1.0, -2.0, 3.0, -4.0, 5.0, -6.0}, Unit::Frequency::Hertz)
                + StrainRate({2.0, -4.0, 6.0, -8.0, 10.0, -12.0}, Unit::Frequency::Hertz),
            StrainRate({3.0, -6.0, 9.0, -12.0, 15.0, -18.0}, Unit::Frequency::Hertz));
}

TEST(StrainRate, ArithmeticOperatorDivision) {
  EXPECT_EQ(StrainRate({2.0, -4.0, 6.0, -8.0, 10.0, -12.0}, Unit::Frequency::Hertz) / 2.0,
            StrainRate({1.0, -2.0, 3.0, -4.0, 5.0, -6.0}, Unit::Frequency::Hertz));

  EXPECT_EQ(StrainRate({2.0, -4.0, 6.0, -8.0, 10.0, -12.0}, Unit::Frequency::Hertz)
                / Frequency(2.0, Unit::Frequency::Hertz),
            Strain(1.0, -2.0, 3.0, -4.0, 5.0, -6.0));

  EXPECT_EQ(Strain(2.0, -4.0, 6.0, -8.0, 10.0, -12.0) / Time(2.0, Unit::Time::Second),
            StrainRate({1.0, -2.0, 3.0, -4.0, 5.0, -6.0}, Unit::Frequency::Hertz));
}

TEST(StrainRate, ArithmeticOperatorMultiplication) {
  EXPECT_EQ(StrainRate({1.0, -2.0, 3.0, -4.0, 5.0, -6.0}, Unit::Frequency::Hertz) * 2.0,
            StrainRate({2.0, -4.0, 6.0, -8.0, 10.0, -12.0}, Unit::Frequency::Hertz));

  EXPECT_EQ(2.0 * StrainRate({1.0, -2.0, 3.0, -4.0, 5.0, -6.0}, Unit::Frequency::Hertz),
            StrainRate({2.0, -4.0, 6.0, -8.0, 10.0, -12.0}, Unit::Frequency::Hertz));

  EXPECT_EQ(StrainRate({1.0, -2.0, 3.0, -4.0, 5.0, -6.0}, Unit::Frequency::Hertz)
                * Time(2.0, Unit::Time::Second),
            Strain(2.0, -4.0, 6.0, -8.0, 10.0, -12.0));

  EXPECT_EQ(Time(2.0, Unit::Time::Second)
                * StrainRate({1.0, -2.0, 3.0, -4.0, 5.0, -6.0}, Unit::Frequency::Hertz),
            Strain(2.0, -4.0, 6.0, -8.0, 10.0, -12.0));

  EXPECT_EQ(Frequency(2.0, Unit::Frequency::Hertz) * Strain(1.0, -2.0, 3.0, -4.0, 5.0, -6.0),
            StrainRate({2.0, -4.0, 6.0, -8.0, 10.0, -12.0}, Unit::Frequency::Hertz));

  EXPECT_EQ(Strain(1.0, -2.0, 3.0, -4.0, 5.0, -6.0) * Frequency(2.0, Unit::Frequency::Hertz),
            StrainRate({2.0, -4.0, 6.0, -8.0, 10.0, -12.0}, Unit::Frequency::Hertz));
}

TEST(StrainRate, ArithmeticOperatorSubtraction) {
  EXPECT_EQ(StrainRate({3.0, -6.0, 9.0, -12.0, 15.0, -18.0}, Unit::Frequency::Hertz)
                - StrainRate({2.0, -4.0, 6.0, -8.0, 10.0, -12.0}, Unit::Frequency::Hertz),
            StrainRate({1.0, -2.0, 3.0, -4.0, 5.0, -6.0}, Unit::Frequency::Hertz));
}

TEST(StrainRate, AssignmentOperatorAddition) {
  StrainRate quantity({1.0, -2.0, 3.0, -4.0, 5.0, -6.0}, Unit::Frequency::Hertz);
  quantity += StrainRate({2.0, -4.0, 6.0, -8.0, 10.0, -12.0}, Unit::Frequency::Hertz);
  EXPECT_EQ(quantity, StrainRate({3.0, -6.0, 9.0, -12.0, 15.0, -18.0}, Unit::Frequency::Hertz));
}

TEST(StrainRate, AssignmentOperatorDivision) {
  StrainRate quantity({2.0, -4.0, 6.0, -8.0, 10.0, -12.0}, Unit::Frequency::Hertz);
  quantity /= 2.0;
  EXPECT_EQ(quantity, StrainRate({1.0, -2.0, 3.0, -4.0, 5.0, -6.0}, Unit::Frequency::Hertz));
}

TEST(StrainRate, AssignmentOperatorMultiplication) {
  StrainRate quantity({1.0, -2.0, 3.0, -4.0, 5.0, -6.0}, Unit::Frequency::Hertz);
  quantity *= 2.0;
  EXPECT_EQ(quantity, StrainRate({2.0, -4.0, 6.0, -8.0, 10.0, -12.0}, Unit::Frequency::Hertz));
}

TEST(StrainRate, AssignmentOperatorSubtraction) {
  StrainRate quantity({3.0, -6.0, 9.0, -12.0, 15.0, -18.0}, Unit::Frequency::Hertz);
  quantity -= StrainRate({2.0, -4.0, 6.0, -8.0, 10.0, -12.0}, Unit::Frequency::Hertz);
  EXPECT_EQ(quantity, StrainRate({1.0, -2.0, 3.0, -4.0, 5.0, -6.0}, Unit::Frequency::Hertz));
}

TEST(StrainRate, ComparisonOperators) {
  const StrainRate first({1.11, -2.22, 3.33, -4.44, 5.55, -6.660001}, Unit::Frequency::Hertz);
  const StrainRate second({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz);
  EXPECT_EQ(first, first);
  EXPECT_NE(first, second);
  EXPECT_LT(first, second);
  EXPECT_GT(second, first);
  EXPECT_LE(first, first);
  EXPECT_LE(first, second);
  EXPECT_GE(first, first);
  EXPECT_GE(second, first);
}

TEST(StrainRate, CopyAssignmentOperator) {
  const StrainRate first({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz);
  StrainRate second = StrainRate::Zero();
  second = first;
  EXPECT_EQ(second, StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz));
}

TEST(StrainRate, CopyConstructor) {
  const StrainRate first({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz);
  const StrainRate second{first};
  EXPECT_EQ(second, StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz));
}

TEST(StrainRate, Create) {
  constexpr StrainRate first =
      StrainRate::Create<Unit::Frequency::Hertz>(1.11, -2.22, 3.33, -4.44, 5.55, -6.66);
  EXPECT_EQ(first, StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz));

  constexpr StrainRate second = StrainRate::Create<Unit::Frequency::Hertz>(
      std::array<double, 6>{1.11, -2.22, 3.33, -4.44, 5.55, -6.66});
  EXPECT_EQ(second, StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz));

  constexpr StrainRate third = StrainRate::Create<Unit::Frequency::Hertz>(
      SymmetricDyad{1.11, -2.22, 3.33, -4.44, 5.55, -6.66});
  EXPECT_EQ(third, StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz));
}

TEST(StrainRate, DefaultConstructor) {
  EXPECT_NO_THROW(StrainRate{});
}

TEST(StrainRate, Dimensions) {
  EXPECT_EQ(StrainRate::Dimensions(), RelatedDimensions<Unit::Frequency>);
}

TEST(StrainRate, Hash) {
  const StrainRate first({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Kilohertz);
  const StrainRate second({1.11, -2.22, 3.33, -4.44, 5.55, -6.660001}, Unit::Frequency::Kilohertz);
  const StrainRate third({1.11, -2.22, 3.33, 4.44, 5.55, -6.66}, Unit::Frequency::Kilohertz);
  const std::hash<StrainRate> hash;
  EXPECT_NE(hash(first), hash(second));
  EXPECT_NE(hash(first), hash(third));
  EXPECT_NE(hash(second), hash(third));
}

TEST(StrainRate, JSON) {
  EXPECT_EQ(StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz).JSON(),
            "{\"value\":{\"xx\":1.110000000000000,\"xy\":-2.220000000000000,\"xz\":3."
            "330000000000000,\"yy\":-4.440000000000000,\"yz\":5.550000000000000,\"zz\":-6."
            "660000000000000},\"unit\":\"Hz\"}");
  EXPECT_EQ(StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Kilohertz)
                .JSON(Unit::Frequency::Kilohertz),
            "{\"value\":{\"xx\":1.110000000000000,\"xy\":-2.220000000000000,\"xz\":3."
            "330000000000000,\"yy\":-4.440000000000000,\"yz\":5.550000000000000,\"zz\":-6."
            "660000000000000},\"unit\":\"kHz\"}");
}

TEST(StrainRate, MiscellaneousConstructors) {
  EXPECT_EQ(StrainRate(Strain(2.0, -4.0, 6.0, -8.0, 10.0, -12.0), Time(2.0, Unit::Time::Second)),
            StrainRate({1.0, -2.0, 3.0, -4.0, 5.0, -6.0}, Unit::Frequency::Hertz));

  EXPECT_EQ(
      StrainRate(Strain(1.0, -2.0, 3.0, -4.0, 5.0, -6.0), Frequency(2.0, Unit::Frequency::Hertz)),
      StrainRate({2.0, -4.0, 6.0, -8.0, 10.0, -12.0}, Unit::Frequency::Hertz));

  EXPECT_EQ(Strain(StrainRate({1.0, -2.0, 3.0, -4.0, 5.0, -6.0}, Unit::Frequency::Hertz),
                   Time(2.0, Unit::Time::Second)),
            Strain(2.0, -4.0, 6.0, -8.0, 10.0, -12.0));

  EXPECT_EQ(Strain(StrainRate({2.0, -4.0, 6.0, -8.0, 10.0, -12.0}, Unit::Frequency::Hertz),
                   Frequency(2.0, Unit::Frequency::Hertz)),
            Strain(1.0, -2.0, 3.0, -4.0, 5.0, -6.0));
}

TEST(StrainRate, MoveAssignmentOperator) {
  StrainRate first({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz);
  StrainRate second = StrainRate::Zero();
  second = std::move(first);
  EXPECT_EQ(second, StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz));
}

TEST(StrainRate, MoveConstructor) {
  StrainRate first({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz);
  const StrainRate second{std::move(first)};
  EXPECT_EQ(second, StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz));
}

TEST(StrainRate, MutableValue) {
  StrainRate quantity({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz);
  SymmetricDyad& value = quantity.MutableValue();
  value = SymmetricDyad{-7.77, 8.88, -9.99, 10.10, -11.11, 12.12};
  EXPECT_EQ(quantity.Value(), SymmetricDyad(-7.77, 8.88, -9.99, 10.10, -11.11, 12.12));
}

TEST(StrainRate, Print) {
  EXPECT_EQ(StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz).Print(),
            "(1.110000000000000, -2.220000000000000, 3.330000000000000; -4.440000000000000, "
            "5.550000000000000; -6.660000000000000) Hz");
  EXPECT_EQ(StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Kilohertz)
                .Print(Unit::Frequency::Kilohertz),
            "(1.110000000000000, -2.220000000000000, 3.330000000000000; -4.440000000000000, "
            "5.550000000000000; -6.660000000000000) kHz");
}

TEST(StrainRate, SetValue) {
  StrainRate quantity({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz);
  quantity.SetValue(SymmetricDyad(-7.77, 8.88, -9.99, 10.10, -11.11, 12.12));
  EXPECT_EQ(quantity.Value(), SymmetricDyad(-7.77, 8.88, -9.99, 10.10, -11.11, 12.12));
}

TEST(StrainRate, SizeOf) {
  EXPECT_EQ(sizeof(StrainRate{}), 6 * sizeof(double));
}

TEST(StrainRate, StandardConstructor) {
  EXPECT_NO_THROW(StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz));
}

TEST(StrainRate, StaticValue) {
  constexpr StrainRate quantity =
      StrainRate::Create<Unit::Frequency::Kilohertz>(1.11, -2.22, 3.33, -4.44, 5.55, -6.66);
  constexpr SymmetricDyad value = quantity.StaticValue<Unit::Frequency::Kilohertz>();
  EXPECT_EQ(value, SymmetricDyad(1.11, -2.22, 3.33, -4.44, 5.55, -6.66));
}

TEST(StrainRate, Stream) {
  std::ostringstream stream;
  stream << StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz);
  EXPECT_EQ(stream.str(),
            StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz).Print());
}

TEST(StrainRate, Value) {
  EXPECT_EQ(StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz).Value(),
            SymmetricDyad(1.11, -2.22, 3.33, -4.44, 5.55, -6.66));
  EXPECT_EQ(StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Kilohertz)
                .Value(Unit::Frequency::Kilohertz),
            SymmetricDyad(1.11, -2.22, 3.33, -4.44, 5.55, -6.66));
}

TEST(StrainRate, XML) {
  EXPECT_EQ(StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz).XML(),
            "<value><xx>1.110000000000000</xx><xy>-2.220000000000000</xy><xz>3.330000000000000</"
            "xz><yy>-4.440000000000000</yy><yz>5.550000000000000</yz><zz>-6.660000000000000</zz></"
            "value><unit>Hz</unit>");
  EXPECT_EQ(StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Kilohertz)
                .XML(Unit::Frequency::Kilohertz),
            "<value><xx>1.110000000000000</xx><xy>-2.220000000000000</xy><xz>3.330000000000000</"
            "xz><yy>-4.440000000000000</yy><yz>5.550000000000000</yz><zz>-6.660000000000000</zz></"
            "value><unit>kHz</unit>");
}

TEST(StrainRate, XYZ) {
  EXPECT_EQ(StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz).xx(),
            ScalarStrainRate(1.11, Unit::Frequency::Hertz));
  EXPECT_EQ(StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz).xy(),
            ScalarStrainRate(-2.22, Unit::Frequency::Hertz));
  EXPECT_EQ(StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz).xz(),
            ScalarStrainRate(3.33, Unit::Frequency::Hertz));
  EXPECT_EQ(StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz).yx(),
            ScalarStrainRate(-2.22, Unit::Frequency::Hertz));
  EXPECT_EQ(StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz).yy(),
            ScalarStrainRate(-4.44, Unit::Frequency::Hertz));
  EXPECT_EQ(StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz).yz(),
            ScalarStrainRate(5.55, Unit::Frequency::Hertz));
  EXPECT_EQ(StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz).zx(),
            ScalarStrainRate(3.33, Unit::Frequency::Hertz));
  EXPECT_EQ(StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz).zy(),
            ScalarStrainRate(5.55, Unit::Frequency::Hertz));
  EXPECT_EQ(StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz).zz(),
            ScalarStrainRate(-6.66, Unit::Frequency::Hertz));
}

TEST(StrainRate, YAML) {
  EXPECT_EQ(StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Hertz).YAML(),
            "{value:{xx:1.110000000000000,xy:-2.220000000000000,xz:3.330000000000000,yy:-4."
            "440000000000000,yz:5.550000000000000,zz:-6.660000000000000},unit:\"Hz\"}");
  EXPECT_EQ(StrainRate({1.11, -2.22, 3.33, -4.44, 5.55, -6.66}, Unit::Frequency::Kilohertz)
                .YAML(Unit::Frequency::Kilohertz),
            "{value:{xx:1.110000000000000,xy:-2.220000000000000,xz:3.330000000000000,yy:-4."
            "440000000000000,yz:5.550000000000000,zz:-6.660000000000000},unit:\"kHz\"}");
}

TEST(StrainRate, Zero) {
  EXPECT_EQ(StrainRate::Zero(), StrainRate({0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, Unit::Frequency::Hertz));
}

}  // namespace

}  // namespace PhQ
