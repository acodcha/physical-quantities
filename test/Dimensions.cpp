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

#include "../include/PhQ/Dimensions.hpp"

#include <cstdint>
#include <functional>
#include <gtest/gtest.h>
#include <sstream>
#include <utility>

#include "../include/PhQ/Dimension/ElectricCurrent.hpp"
#include "../include/PhQ/Dimension/Length.hpp"
#include "../include/PhQ/Dimension/LuminousIntensity.hpp"
#include "../include/PhQ/Dimension/Mass.hpp"
#include "../include/PhQ/Dimension/SubstanceAmount.hpp"
#include "../include/PhQ/Dimension/Temperature.hpp"
#include "../include/PhQ/Dimension/Time.hpp"

namespace PhQ {

namespace {

TEST(Dimensions, Accessors) {
  constexpr Dimensions dimensions{
      Dimension::Time(-3),
      Dimension::Length(-2),
      Dimension::Mass(-1),
      Dimension::ElectricCurrent(0),
      Dimension::Temperature(1),
      Dimension::SubstanceAmount(2),
      Dimension::LuminousIntensity(3)};
  EXPECT_EQ(dimensions.Time(), Dimension::Time(-3));
  EXPECT_EQ(dimensions.Length(), Dimension::Length(-2));
  EXPECT_EQ(dimensions.Mass(), Dimension::Mass(-1));
  EXPECT_EQ(dimensions.ElectricCurrent(), Dimension::ElectricCurrent(0));
  EXPECT_EQ(dimensions.Temperature(), Dimension::Temperature(1));
  EXPECT_EQ(dimensions.SubstanceAmount(), Dimension::SubstanceAmount(2));
  EXPECT_EQ(dimensions.LuminousIntensity(), Dimension::LuminousIntensity(3));
}

TEST(Dimensions, ComparisonOperators) {
  constexpr Dimensions first{
      Dimension::Time(-3),
      Dimension::Length(-2),
      Dimension::Mass(-1),
      Dimension::ElectricCurrent(0),
      Dimension::Temperature(1),
      Dimension::SubstanceAmount(2),
      Dimension::LuminousIntensity(3)};
  constexpr Dimensions second{
      Dimension::Time(-3),
      Dimension::Length(-2),
      Dimension::Mass(-1),
      Dimension::ElectricCurrent(0),
      Dimension::Temperature(1),
      Dimension::SubstanceAmount(2),
      Dimension::LuminousIntensity(4)};
  EXPECT_EQ(first, first);
  EXPECT_NE(first, second);
  EXPECT_LT(first, second);
  EXPECT_LE(first, first);
  EXPECT_LE(first, second);
  EXPECT_GT(second, first);
  EXPECT_GE(second, first);
  EXPECT_GE(first, first);
}

TEST(Dimensions, CopyAssignmentOperator) {
  constexpr Dimensions first{Dimension::Time(-2), Dimension::Length(1)};
  Dimensions second;
  second = first;
  EXPECT_EQ(second, first);
}

TEST(Dimensions, CopyConstructor) {
  constexpr Dimensions first{Dimension::Time(-2), Dimension::Length(1)};
  constexpr Dimensions second{first};
  EXPECT_EQ(second, first);
}

TEST(Dimensions, DefaultConstructor) {
  EXPECT_EQ(Dimensions{},
            Dimensions(Dimension::Time(0), Dimension::Length(0), Dimension::Mass(0),
                       Dimension::ElectricCurrent(0), Dimension::Temperature(0),
                       Dimension::SubstanceAmount(0), Dimension::LuminousIntensity(0)));
}

TEST(Dimensions, Hash) {
  constexpr Dimensions first;
  constexpr Dimensions second{Dimension::Time(3), Dimension::Length(0), Dimension::Mass(-1)};
  constexpr Dimensions third{
      Dimension::Time(3),
      Dimension::Length(0),
      Dimension::Mass(-1),
      Dimension::ElectricCurrent(0),
      Dimension::Temperature(0),
      Dimension::SubstanceAmount(0),
      Dimension::LuminousIntensity(1)};
  const std::hash<Dimensions> hasher;
  EXPECT_NE(hasher(first), hasher(second));
  EXPECT_NE(hasher(first), hasher(third));
  EXPECT_NE(hasher(second), hasher(third));
}

TEST(Dimensions, JSON) {
  EXPECT_EQ(Dimensions(Dimension::Time(-2), Dimension::Length(2), Dimension::Mass(1),
                       Dimension::ElectricCurrent(0), Dimension::Temperature(-1))
                .JSON(),
            "{\"time\":-2,\"length\":2,\"mass\":1,\"temperature\":-1}");
  EXPECT_EQ(Dimensions(Dimension::Time(0), Dimension::Length(0), Dimension::Mass(1),
                       Dimension::ElectricCurrent(0), Dimension::Temperature(0),
                       Dimension::SubstanceAmount(-1))
                .JSON(),
            "{\"mass\":1,\"substance_amount\":-1}");
}

TEST(Dimensions, MoveAssignmentOperator) {
  Dimensions first{Dimension::Time(-2), Dimension::Length(1)};
  Dimensions second;
  second = std::move(first);
  EXPECT_EQ(second, Dimensions(Dimension::Time(-2), Dimension::Length(1)));
}

TEST(Dimensions, MoveConstructor) {
  Dimensions first{Dimension::Time(-2), Dimension::Length(1)};
  const Dimensions second{std::move(first)};
  EXPECT_EQ(second, Dimensions(Dimension::Time(-2), Dimension::Length(1)));
}

TEST(Dimensions, Print) {
  EXPECT_EQ(Dimensions{}.Print(), "1");
  EXPECT_EQ(Dimensions{Dimension::Time(2)}.Print(), "T^2");
  EXPECT_EQ(Dimensions(Dimension::Time(1), Dimension::Length(-3)).Print(), "T·L^(-3)");
  EXPECT_EQ(Dimensions(Dimension::Time(-1), Dimension::Length(3), Dimension::Mass(0)).Print(),
            "T^(-1)·L^3");
  EXPECT_EQ(Dimensions(Dimension::Time(2), Dimension::Length(-2), Dimension::Mass(-1),
                       Dimension::ElectricCurrent(1))
                .Print(),
            "T^2·L^(-2)·M^(-1)·I");
  EXPECT_EQ(Dimensions(Dimension::Time(-2), Dimension::Length(2), Dimension::Mass(1),
                       Dimension::ElectricCurrent(0), Dimension::Temperature(-1))
                .Print(),
            "T^(-2)·L^2·M·Θ^(-1)");
  EXPECT_EQ(Dimensions(Dimension::Time(0), Dimension::Length(0), Dimension::Mass(1),
                       Dimension::ElectricCurrent(0), Dimension::Temperature(0),
                       Dimension::SubstanceAmount(-1))
                .Print(),
            "M·N^(-1)");
  EXPECT_EQ(Dimensions(Dimension::Time(0), Dimension::Length(0), Dimension::Mass(0),
                       Dimension::ElectricCurrent(0), Dimension::Temperature(-1),
                       Dimension::SubstanceAmount(0), Dimension::LuminousIntensity(1))
                .Print(),
            "Θ^(-1)·J");
}

TEST(Dimensions, SizeOf) {
  EXPECT_EQ(sizeof(Dimensions{}), 7 * sizeof(int8_t));
}

TEST(Dimensions, Stream) {
  std::ostringstream stream;
  stream << Dimensions(Dimension::Time(2), Dimension::Length(-2), Dimension::Mass(-1),
                       Dimension::ElectricCurrent(1));
  EXPECT_EQ(stream.str(), Dimensions(Dimension::Time(2), Dimension::Length(-2), Dimension::Mass(-1),
                                     Dimension::ElectricCurrent(1))
                              .Print());
}

TEST(Dimensions, XML) {
  EXPECT_EQ(Dimensions(Dimension::Time(-2), Dimension::Length(2), Dimension::Mass(1),
                       Dimension::ElectricCurrent(0), Dimension::Temperature(-1))
                .XML(),
            "<time>-2</time><length>2</length><mass>1</mass><temperature>-1</temperature>");
  EXPECT_EQ(Dimensions(Dimension::Time(0), Dimension::Length(0), Dimension::Mass(1),
                       Dimension::ElectricCurrent(0), Dimension::Temperature(0),
                       Dimension::SubstanceAmount(-1))
                .XML(),
            "<mass>1</mass><substance_amount>-1</substance_amount>");
}

TEST(Dimensions, YAML) {
  EXPECT_EQ(Dimensions(Dimension::Time(-2), Dimension::Length(2), Dimension::Mass(1),
                       Dimension::ElectricCurrent(0), Dimension::Temperature(-1))
                .YAML(),
            "{time:-2,length:2,mass:1,temperature:-1}");
  EXPECT_EQ(Dimensions(Dimension::Time(0), Dimension::Length(0), Dimension::Mass(1),
                       Dimension::ElectricCurrent(0), Dimension::Temperature(0),
                       Dimension::SubstanceAmount(-1))
                .YAML(),
            "{mass:1,substance_amount:-1}");
}

}  // namespace

}  // namespace PhQ
