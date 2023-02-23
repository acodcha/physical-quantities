// Copyright 2020 Alexandre Coderre-Chabot
//
// This file is part of Physical Quantities (PhQ), a C++ library of physical
// quantities, physical models, and units of measure for scientific computation.
//
// Physical Quantities is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at your
// option) any later version. Physical Quantities is distributed in the hope
// that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details. You should have received a
// copy of the GNU Lesser General Public License along with Physical Quantities.
// If not, see <https://www.gnu.org/licenses/>.

#include "../../include/PhQ/Unit/DynamicViscosity.hpp"

#include <gtest/gtest.h>

#include "Base.hpp"

namespace PhQ::Unit {

namespace {

constexpr std::array<DynamicViscosity, 6> Units = {
    DynamicViscosity::PascalSecond,
    DynamicViscosity::KilopascalSecond,
    DynamicViscosity::MegapascalSecond,
    DynamicViscosity::GigapascalSecond,
    DynamicViscosity::PoundSecondPerSquareFoot,
    DynamicViscosity::PoundSecondPerSquareInch,
};

TEST(UnitDynamicViscosity, Abbreviation) {
  EXPECT_EQ(Abbreviation(DynamicViscosity::PascalSecond), "Pa·s");
  EXPECT_EQ(Abbreviation(DynamicViscosity::KilopascalSecond), "kPa·s");
  EXPECT_EQ(Abbreviation(DynamicViscosity::MegapascalSecond), "MPa·s");
  EXPECT_EQ(Abbreviation(DynamicViscosity::GigapascalSecond), "GPa·s");
  EXPECT_EQ(Abbreviation(DynamicViscosity::PoundSecondPerSquareFoot),
            "lbf·s/ft^2");
  EXPECT_EQ(Abbreviation(DynamicViscosity::PoundSecondPerSquareInch),
            "lbf·s/in^2");
}

TEST(UnitDynamicViscosity, ConsistentUnit) {
  EXPECT_EQ(
      ConsistentUnit<DynamicViscosity>(UnitSystem::MetreKilogramSecondKelvin),
      DynamicViscosity::PascalSecond);
  EXPECT_EQ(
      ConsistentUnit<DynamicViscosity>(UnitSystem::MillimetreGramSecondKelvin),
      DynamicViscosity::PascalSecond);
  EXPECT_EQ(
      ConsistentUnit<DynamicViscosity>(UnitSystem::FootPoundSecondRankine),
      DynamicViscosity::PoundSecondPerSquareFoot);
  EXPECT_EQ(
      ConsistentUnit<DynamicViscosity>(UnitSystem::InchPoundSecondRankine),
      DynamicViscosity::PoundSecondPerSquareInch);
}

TEST(UnitDynamicViscosity, ConvertFromStandard) {
  constexpr double value{10.0};
  EXPECT_DOUBLE_EQ(ConvertCopy(value, DynamicViscosity::PascalSecond,
                               DynamicViscosity::PascalSecond),
                   value);
  EXPECT_DOUBLE_EQ(ConvertCopy(value, DynamicViscosity::PascalSecond,
                               DynamicViscosity::KilopascalSecond),
                   value * 0.001);
  EXPECT_DOUBLE_EQ(ConvertCopy(value, DynamicViscosity::PascalSecond,
                               DynamicViscosity::MegapascalSecond),
                   value * 0.000001);
  EXPECT_DOUBLE_EQ(ConvertCopy(value, DynamicViscosity::PascalSecond,
                               DynamicViscosity::GigapascalSecond),
                   value * 0.000000001);
  EXPECT_DOUBLE_EQ(ConvertCopy(value, DynamicViscosity::PascalSecond,
                               DynamicViscosity::PoundSecondPerSquareFoot),
                   value * std::pow(0.3048, 2) / (0.45359237 * 9.80665));
  EXPECT_DOUBLE_EQ(ConvertCopy(value, DynamicViscosity::PascalSecond,
                               DynamicViscosity::PoundSecondPerSquareInch),
                   value * std::pow(0.0254, 2) / (0.45359237 * 9.80665));
}

TEST(UnitDynamicViscosity, ConvertToStandard) {
  constexpr double value{10.0};
  EXPECT_DOUBLE_EQ(ConvertCopy(value, DynamicViscosity::PascalSecond,
                               DynamicViscosity::PascalSecond),
                   value);
  EXPECT_DOUBLE_EQ(ConvertCopy(value, DynamicViscosity::KilopascalSecond,
                               DynamicViscosity::PascalSecond),
                   value * 1000.0);
  EXPECT_DOUBLE_EQ(ConvertCopy(value, DynamicViscosity::MegapascalSecond,
                               DynamicViscosity::PascalSecond),
                   value * 1000000.0);
  EXPECT_DOUBLE_EQ(ConvertCopy(value, DynamicViscosity::GigapascalSecond,
                               DynamicViscosity::PascalSecond),
                   value * 1000000000.0);
  EXPECT_DOUBLE_EQ(
      ConvertCopy(value, DynamicViscosity::PoundSecondPerSquareFoot,
                  DynamicViscosity::PascalSecond),
      value * 0.45359237 * 9.80665 / std::pow(0.3048, 2));
  EXPECT_DOUBLE_EQ(
      ConvertCopy(value, DynamicViscosity::PoundSecondPerSquareInch,
                  DynamicViscosity::PascalSecond),
      value * 0.45359237 * 9.80665 / std::pow(0.0254, 2));
}

TEST(UnitDynamicViscosity, ConvertVerification) {
  double value{10.0};
  std::array<double, 3> array{10.0, -20.0, 30.0};
  std::vector<double> std_vector{10.0, -20.0, 30.0, -40.0};
  Value::Vector value_vector{10.0, -20.0, 30.0};
  Value::SymmetricDyad symdyad{10.0, -20.0, 30.0, -40.0, 50.0, -60.0};
  Value::Dyad dyad{10.0, -20.0, 30.0, -40.0, 50.0, -60.0, 70.0, -80.0, 90.0};
  for (const DynamicViscosity old_unit : Units) {
    for (const DynamicViscosity new_unit : Units) {
      Convert(value, old_unit, new_unit);
      Convert(array, old_unit, new_unit);
      Convert(std_vector, old_unit, new_unit);
      Convert(value_vector, old_unit, new_unit);
      Convert(symdyad, old_unit, new_unit);
      Convert(dyad, old_unit, new_unit);
    }
  }
}

TEST(UnitDynamicViscosity, DimensionSet) {
  EXPECT_EQ(Dimensions<DynamicViscosity>,
            Dimension::Set(Dimension::Time{-1}, Dimension::Length{-1},
                           Dimension::Mass{1}));
}

TEST(UnitDynamicViscosity, Parse) {
  EXPECT_EQ(Parse<DynamicViscosity>("Hello world!"), std::nullopt);
  EXPECT_EQ(Parse<DynamicViscosity>("Pa·s"), DynamicViscosity::PascalSecond);
  EXPECT_EQ(Parse<DynamicViscosity>("kPa·s"),
            DynamicViscosity::KilopascalSecond);
  EXPECT_EQ(Parse<DynamicViscosity>("MPa·s"),
            DynamicViscosity::MegapascalSecond);
  EXPECT_EQ(Parse<DynamicViscosity>("GPa·s"),
            DynamicViscosity::GigapascalSecond);
  EXPECT_EQ(Parse<DynamicViscosity>("lbf·s/ft^2"),
            DynamicViscosity::PoundSecondPerSquareFoot);
  EXPECT_EQ(Parse<DynamicViscosity>("lbf·s/in^2"),
            DynamicViscosity::PoundSecondPerSquareInch);
}

TEST(UnitDynamicViscosity, RelatedUnitSystem) {
  EXPECT_EQ(RelatedUnitSystem(DynamicViscosity::PascalSecond), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(DynamicViscosity::KilopascalSecond),
            std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(DynamicViscosity::MegapascalSecond),
            std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(DynamicViscosity::GigapascalSecond),
            std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(DynamicViscosity::PoundSecondPerSquareFoot),
            UnitSystem::FootPoundSecondRankine);
  EXPECT_EQ(RelatedUnitSystem(DynamicViscosity::PoundSecondPerSquareInch),
            UnitSystem::InchPoundSecondRankine);
}

TEST(UnitDynamicViscosity, StandardUnit) {
  EXPECT_EQ(StandardUnit<DynamicViscosity>, DynamicViscosity::PascalSecond);
}

}  // namespace

}  // namespace PhQ::Unit