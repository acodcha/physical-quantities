// Copyright 2020-2023 Alexandre Coderre-Chabot
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

#include "../../include/PhQ/Unit/TemperatureGradient.hpp"

#include <gtest/gtest.h>

#include "../Unit.hpp"

namespace PhQ::Unit {

namespace {

constexpr std::array<TemperatureGradient, 8> Units = {
    TemperatureGradient::KelvinPerMetre,
    TemperatureGradient::KelvinPerMillimetre,
    TemperatureGradient::CelsiusPerMetre,
    TemperatureGradient::CelsiusPerMillimetre,
    TemperatureGradient::RankinePerFoot,
    TemperatureGradient::RankinePerInch,
    TemperatureGradient::FahrenheitPerFoot,
    TemperatureGradient::FahrenheitPerInch,
};

TEST(UnitTemperatureGradient, Abbreviation) {
  EXPECT_EQ(Abbreviation(TemperatureGradient::KelvinPerMetre), "K/m");
  EXPECT_EQ(Abbreviation(TemperatureGradient::KelvinPerMillimetre), "K/mm");
  EXPECT_EQ(Abbreviation(TemperatureGradient::CelsiusPerMetre), "°C/m");
  EXPECT_EQ(Abbreviation(TemperatureGradient::CelsiusPerMillimetre), "°C/mm");
  EXPECT_EQ(Abbreviation(TemperatureGradient::RankinePerFoot), "°R/ft");
  EXPECT_EQ(Abbreviation(TemperatureGradient::RankinePerInch), "°R/in");
  EXPECT_EQ(Abbreviation(TemperatureGradient::FahrenheitPerFoot), "°F/ft");
  EXPECT_EQ(Abbreviation(TemperatureGradient::FahrenheitPerInch), "°F/in");
}

TEST(UnitTemperatureGradient, ConsistentUnit) {
  EXPECT_EQ(ConsistentUnit<TemperatureGradient>(
                UnitSystem::MetreKilogramSecondKelvin),
            TemperatureGradient::KelvinPerMetre);
  EXPECT_EQ(ConsistentUnit<TemperatureGradient>(
                UnitSystem::MillimetreGramSecondKelvin),
            TemperatureGradient::KelvinPerMillimetre);
  EXPECT_EQ(
      ConsistentUnit<TemperatureGradient>(UnitSystem::FootPoundSecondRankine),
      TemperatureGradient::RankinePerFoot);
  EXPECT_EQ(
      ConsistentUnit<TemperatureGradient>(UnitSystem::InchPoundSecondRankine),
      TemperatureGradient::RankinePerInch);
}

TEST(UnitTemperatureGradient, ConvertFromStandard) {
  constexpr double value{10.0};
  Internal::TestUnitConversions<
      TemperatureGradient, TemperatureGradient::KelvinPerMetre,
      TemperatureGradient::KelvinPerMetre>(value, value);
  Internal::TestUnitConversions<
      TemperatureGradient, TemperatureGradient::KelvinPerMetre,
      TemperatureGradient::KelvinPerMillimetre>(value, value * 0.001);
  Internal::TestUnitConversions<
      TemperatureGradient, TemperatureGradient::KelvinPerMetre,
      TemperatureGradient::CelsiusPerMetre>(value, value);
  Internal::TestUnitConversions<
      TemperatureGradient, TemperatureGradient::KelvinPerMetre,
      TemperatureGradient::CelsiusPerMillimetre>(value, value * 0.001);
  Internal::TestUnitConversions<
      TemperatureGradient, TemperatureGradient::KelvinPerMetre,
      TemperatureGradient::RankinePerFoot>(value, value * 1.8 * 0.3048);
  Internal::TestUnitConversions<
      TemperatureGradient, TemperatureGradient::KelvinPerMetre,
      TemperatureGradient::RankinePerInch>(value, value * 1.8 * 0.0254);
  Internal::TestUnitConversions<
      TemperatureGradient, TemperatureGradient::KelvinPerMetre,
      TemperatureGradient::FahrenheitPerFoot>(value, value * 1.8 * 0.3048);
  Internal::TestUnitConversions<
      TemperatureGradient, TemperatureGradient::KelvinPerMetre,
      TemperatureGradient::FahrenheitPerInch>(value, value * 1.8 * 0.0254);
}

TEST(UnitTemperatureGradient, ConvertToStandard) {
  constexpr double value{10.0};
  Internal::TestUnitConversions<
      TemperatureGradient, TemperatureGradient::KelvinPerMetre,
      TemperatureGradient::KelvinPerMetre>(value, value);
  Internal::TestUnitConversions<
      TemperatureGradient, TemperatureGradient::KelvinPerMillimetre,
      TemperatureGradient::KelvinPerMetre>(value, value * 1000.0);
  Internal::TestUnitConversions<
      TemperatureGradient, TemperatureGradient::CelsiusPerMetre,
      TemperatureGradient::KelvinPerMetre>(value, value);
  Internal::TestUnitConversions<
      TemperatureGradient, TemperatureGradient::CelsiusPerMillimetre,
      TemperatureGradient::KelvinPerMetre>(value, value * 1000.0);
  Internal::TestUnitConversions<
      TemperatureGradient, TemperatureGradient::RankinePerFoot,
      TemperatureGradient::KelvinPerMetre>(value, value / (1.8 * 0.3048));
  Internal::TestUnitConversions<
      TemperatureGradient, TemperatureGradient::RankinePerInch,
      TemperatureGradient::KelvinPerMetre>(value, value / (1.8 * 0.0254));
  Internal::TestUnitConversions<
      TemperatureGradient, TemperatureGradient::FahrenheitPerFoot,
      TemperatureGradient::KelvinPerMetre>(value, value / (1.8 * 0.3048));
  Internal::TestUnitConversions<
      TemperatureGradient, TemperatureGradient::FahrenheitPerInch,
      TemperatureGradient::KelvinPerMetre>(value, value / (1.8 * 0.0254));
}

TEST(UnitTemperatureGradient, Parse) {
  EXPECT_EQ(Parse<TemperatureGradient>("Hello world!"), std::nullopt);
  EXPECT_EQ(
      Parse<TemperatureGradient>("K/m"), TemperatureGradient::KelvinPerMetre);
  EXPECT_EQ(Parse<TemperatureGradient>("K/mm"),
            TemperatureGradient::KelvinPerMillimetre);
  EXPECT_EQ(
      Parse<TemperatureGradient>("°C/m"), TemperatureGradient::CelsiusPerMetre);
  EXPECT_EQ(Parse<TemperatureGradient>("°C/mm"),
            TemperatureGradient::CelsiusPerMillimetre);
  EXPECT_EQ(
      Parse<TemperatureGradient>("°R/ft"), TemperatureGradient::RankinePerFoot);
  EXPECT_EQ(
      Parse<TemperatureGradient>("°R/in"), TemperatureGradient::RankinePerInch);
  EXPECT_EQ(Parse<TemperatureGradient>("°F/ft"),
            TemperatureGradient::FahrenheitPerFoot);
  EXPECT_EQ(Parse<TemperatureGradient>("°F/in"),
            TemperatureGradient::FahrenheitPerInch);
}

TEST(UnitTemperatureGradient, RelatedDimensions) {
  EXPECT_EQ(
      RelatedDimensions<TemperatureGradient>,
      Dimensions(Dimension::Time{}, Dimension::Length{-1}, Dimension::Mass{},
                 Dimension::ElectricCurrent{}, Dimension::Temperature{1}));
}

TEST(UnitTemperatureGradient, RelatedUnitSystem) {
  EXPECT_EQ(RelatedUnitSystem(TemperatureGradient::KelvinPerMetre),
            UnitSystem::MetreKilogramSecondKelvin);
  EXPECT_EQ(RelatedUnitSystem(TemperatureGradient::KelvinPerMillimetre),
            UnitSystem::MillimetreGramSecondKelvin);
  EXPECT_EQ(
      RelatedUnitSystem(TemperatureGradient::CelsiusPerMetre), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(TemperatureGradient::CelsiusPerMillimetre),
            std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(TemperatureGradient::RankinePerFoot),
            UnitSystem::FootPoundSecondRankine);
  EXPECT_EQ(RelatedUnitSystem(TemperatureGradient::RankinePerInch),
            UnitSystem::InchPoundSecondRankine);
  EXPECT_EQ(
      RelatedUnitSystem(TemperatureGradient::FahrenheitPerFoot), std::nullopt);
  EXPECT_EQ(
      RelatedUnitSystem(TemperatureGradient::FahrenheitPerInch), std::nullopt);
}

TEST(UnitTemperatureGradient, Standard) {
  EXPECT_EQ(Standard<TemperatureGradient>, TemperatureGradient::KelvinPerMetre);
}

TEST(UnitTemperatureGradient, Stream) {
  std::ostringstream stream;
  stream << TemperatureGradient::KelvinPerMetre;
  EXPECT_EQ(stream.str(), Abbreviation(TemperatureGradient::KelvinPerMetre));
}

}  // namespace

}  // namespace PhQ::Unit
