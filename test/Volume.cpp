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

#include "../include/PhQ/Volume.hpp"

#include <functional>
#include <gtest/gtest.h>
#include <sstream>
#include <utility>

#include "../include/PhQ/Area.hpp"
#include "../include/PhQ/Length.hpp"
#include "../include/PhQ/Unit/Area.hpp"
#include "../include/PhQ/Unit/Length.hpp"
#include "../include/PhQ/Unit/Volume.hpp"

namespace PhQ {

namespace {

TEST(Volume, ArithmeticOperatorAddition) {
  EXPECT_EQ(Volume(1.0, Unit::Volume::CubicMetre) + Volume(2.0, Unit::Volume::CubicMetre),
            Volume(3.0, Unit::Volume::CubicMetre));
}

TEST(Volume, ArithmeticOperatorDivision) {
  EXPECT_EQ(Volume(8.0, Unit::Volume::CubicMetre) / 2.0, Volume(4.0, Unit::Volume::CubicMetre));
  EXPECT_EQ(Volume(8.0, Unit::Volume::CubicMetre) / Volume(2.0, Unit::Volume::CubicMetre), 4.0);
  EXPECT_EQ(Volume(8.0, Unit::Volume::CubicMetre) / Length(4.0, Unit::Length::Metre),
            Area(2.0, Unit::Area::SquareMetre));
  EXPECT_EQ(Volume(8.0, Unit::Volume::CubicMetre) / Area(4.0, Unit::Area::SquareMetre),
            Length(2.0, Unit::Length::Metre));
}

TEST(Volume, ArithmeticOperatorMultiplication) {
  EXPECT_EQ(Volume(4.0, Unit::Volume::CubicMetre) * 2.0, Volume(8.0, Unit::Volume::CubicMetre));
  EXPECT_EQ(2.0 * Volume(4.0, Unit::Volume::CubicMetre), Volume(8.0, Unit::Volume::CubicMetre));
  EXPECT_EQ(Length(4.0, Unit::Length::Metre) * Area(2.0, Unit::Area::SquareMetre),
            Volume(8.0, Unit::Volume::CubicMetre));
  EXPECT_EQ(Area(4.0, Unit::Area::SquareMetre) * Length(2.0, Unit::Length::Metre),
            Volume(8.0, Unit::Volume::CubicMetre));
}

TEST(Volume, ArithmeticOperatorSubtraction) {
  EXPECT_EQ(Volume(3.0, Unit::Volume::CubicMetre) - Volume(2.0, Unit::Volume::CubicMetre),
            Volume(1.0, Unit::Volume::CubicMetre));
}

TEST(Volume, AssignmentOperatorAddition) {
  Volume volume{1.0, Unit::Volume::CubicMetre};
  volume += Volume(2.0, Unit::Volume::CubicMetre);
  EXPECT_EQ(volume, Volume(3.0, Unit::Volume::CubicMetre));
}

TEST(Volume, AssignmentOperatorDivision) {
  Volume volume{8.0, Unit::Volume::CubicMetre};
  volume /= 2.0;
  EXPECT_EQ(volume, Volume(4.0, Unit::Volume::CubicMetre));
}

TEST(Volume, AssignmentOperatorMultiplication) {
  Volume volume{4.0, Unit::Volume::CubicMetre};
  volume *= 2.0;
  EXPECT_EQ(volume, Volume(8.0, Unit::Volume::CubicMetre));
}

TEST(Volume, AssignmentOperatorSubtraction) {
  Volume volume{3.0, Unit::Volume::CubicMetre};
  volume -= Volume(2.0, Unit::Volume::CubicMetre);
  EXPECT_EQ(volume, Volume(1.0, Unit::Volume::CubicMetre));
}

TEST(Volume, ComparisonOperators) {
  const Volume first{1.0, Unit::Volume::CubicMetre};
  const Volume second{2.0, Unit::Volume::CubicMetre};
  EXPECT_EQ(first, first);
  EXPECT_NE(first, second);
  EXPECT_LT(first, second);
  EXPECT_GT(second, first);
  EXPECT_LE(first, first);
  EXPECT_LE(first, second);
  EXPECT_GE(first, first);
  EXPECT_GE(second, first);
}

TEST(Volume, CopyAssignmentOperator) {
  const Volume first{1.0, Unit::Volume::CubicMetre};
  Volume second = Volume<>::Zero();
  second = first;
  EXPECT_EQ(second, first);
}

TEST(Volume, CopyConstructor) {
  const Volume first{1.0, Unit::Volume::CubicMetre};
  const Volume second{first};
  EXPECT_EQ(second, first);
}

TEST(Volume, Create) {
  constexpr Volume volume = Volume<>::Create<Unit::Volume::CubicMetre>(1.0);
  EXPECT_EQ(volume, Volume(1.0, Unit::Volume::CubicMetre));
}

TEST(Volume, DefaultConstructor) {
  EXPECT_NO_THROW(Volume<>{});
}

TEST(Volume, Dimensions) {
  EXPECT_EQ(Volume<>::Dimensions(), RelatedDimensions<Unit::Volume>);
}

TEST(Volume, Hash) {
  const Volume first{1.0, Unit::Volume::CubicMetre};
  const Volume second{1.000001, Unit::Volume::CubicMetre};
  const Volume third{-1.0, Unit::Volume::CubicMetre};
  const std::hash<Volume<>> hash;
  EXPECT_NE(hash(first), hash(second));
  EXPECT_NE(hash(first), hash(third));
  EXPECT_NE(hash(second), hash(third));
}

TEST(Volume, JSON) {
  EXPECT_EQ(Volume(1.0, Unit::Volume::CubicMetre).JSON(),
            "{\"value\":" + Print(1.0) + ",\"unit\":\"m^3\"}");
  EXPECT_EQ(Volume(1.0, Unit::Volume::CubicMillimetre).JSON(Unit::Volume::CubicMillimetre),
            "{\"value\":" + Print(1.0) + ",\"unit\":\"mm^3\"}");
}

TEST(Volume, MoveAssignmentOperator) {
  Volume first{1.0, Unit::Volume::CubicMetre};
  Volume second = Volume<>::Zero();
  second = std::move(first);
  EXPECT_EQ(second, Volume(1.0, Unit::Volume::CubicMetre));
}

TEST(Volume, MoveConstructor) {
  Volume first{1.0, Unit::Volume::CubicMetre};
  const Volume second{std::move(first)};
  EXPECT_EQ(second, Volume(1.0, Unit::Volume::CubicMetre));
}

TEST(Volume, MutableValue) {
  Volume volume{1.0, Unit::Volume::CubicMetre};
  double& value = volume.MutableValue();
  value = 2.0;
  EXPECT_EQ(volume.Value(), 2.0);
}

TEST(Volume, Print) {
  EXPECT_EQ(Volume(1.0, Unit::Volume::CubicMetre).Print(), Print(1.0) + " m^3");
  EXPECT_EQ(Volume(1.0, Unit::Volume::CubicMillimetre).Print(Unit::Volume::CubicMillimetre),
            Print(1.0) + " mm^3");
}

TEST(Volume, SetValue) {
  Volume volume{1.0, Unit::Volume::CubicMetre};
  volume.SetValue(2.0);
  EXPECT_EQ(volume.Value(), 2.0);
}

TEST(Volume, SizeOf) {
  EXPECT_EQ(sizeof(Volume<>{}), sizeof(double));
}

TEST(Volume, StandardConstructor) {
  EXPECT_NO_THROW(Volume(1.0, Unit::Volume::CubicMillimetre));
}

TEST(Volume, StaticValue) {
  constexpr Volume volume = Volume<>::Create<Unit::Volume::CubicMillimetre>(1.0);
  constexpr double value = volume.StaticValue<Unit::Volume::CubicMillimetre>();
  EXPECT_EQ(value, 1.0);
}

TEST(Volume, Stream) {
  std::ostringstream stream;
  stream << Volume(1.0, Unit::Volume::CubicMetre);
  EXPECT_EQ(stream.str(), Volume(1.0, Unit::Volume::CubicMetre).Print());
}

TEST(Volume, Unit) {
  EXPECT_EQ(Volume<>::Unit(), Standard<Unit::Volume>);
}

TEST(Volume, Value) {
  EXPECT_EQ(Volume(1.0, Unit::Volume::CubicMetre).Value(), 1.0);
  EXPECT_EQ(Volume(1.0, Unit::Volume::CubicMillimetre).Value(Unit::Volume::CubicMillimetre), 1.0);
}

TEST(Volume, XML) {
  EXPECT_EQ(Volume(1.0, Unit::Volume::CubicMetre).XML(),
            "<value>" + Print(1.0) + "</value><unit>m^3</unit>");
  EXPECT_EQ(Volume(1.0, Unit::Volume::CubicMillimetre).XML(Unit::Volume::CubicMillimetre),
            "<value>" + Print(1.0) + "</value><unit>mm^3</unit>");
}

TEST(Volume, YAML) {
  EXPECT_EQ(
      Volume(1.0, Unit::Volume::CubicMetre).YAML(), "{value:" + Print(1.0) + ",unit:\"m^3\"}");
  EXPECT_EQ(Volume(1.0, Unit::Volume::CubicMillimetre).YAML(Unit::Volume::CubicMillimetre),
            "{value:" + Print(1.0) + ",unit:\"mm^3\"}");
}

TEST(Volume, Zero) {
  EXPECT_EQ(Volume<>::Zero(), Volume(0.0, Unit::Volume::CubicMetre));
}

}  // namespace

}  // namespace PhQ
