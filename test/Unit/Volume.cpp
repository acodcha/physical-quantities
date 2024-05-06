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

#include "../../include/PhQ/Unit/Volume.hpp"

#include <array>
#include <cmath>
#include <gtest/gtest.h>
#include <optional>
#include <sstream>

#include "../../include/PhQ/Base.hpp"
#include "../../include/PhQ/Dimension/Length.hpp"
#include "../../include/PhQ/Dimension/Time.hpp"
#include "../../include/PhQ/Dimensions.hpp"
#include "../../include/PhQ/UnitSystem.hpp"
#include "../Unit.hpp"

namespace PhQ::Unit {

namespace {

constexpr std::array<Volume, 15> Units = {
    Volume::CubicNauticalMile, Volume::CubicMile,       Volume::CubicKilometre,
    Volume::CubicMetre,        Volume::CubicYard,       Volume::CubicFoot,
    Volume::CubicDecimetre,    Volume::Litre,           Volume::CubicInch,
    Volume::CubicCentimetre,   Volume::Millilitre,      Volume::CubicMillimetre,
    Volume::CubicMilliinch,    Volume::CubicMicrometre, Volume::CubicMicroinch,
};

TEST(UnitVolume, Abbreviation) {
  EXPECT_EQ(Abbreviation(Volume::CubicNauticalMile), "nmi^3");
  EXPECT_EQ(Abbreviation(Volume::CubicMile), "mi^3");
  EXPECT_EQ(Abbreviation(Volume::CubicKilometre), "km^3");
  EXPECT_EQ(Abbreviation(Volume::CubicMetre), "m^3");
  EXPECT_EQ(Abbreviation(Volume::CubicYard), "yd^3");
  EXPECT_EQ(Abbreviation(Volume::CubicFoot), "ft^3");
  EXPECT_EQ(Abbreviation(Volume::CubicDecimetre), "dm^3");
  EXPECT_EQ(Abbreviation(Volume::Litre), "L");
  EXPECT_EQ(Abbreviation(Volume::CubicInch), "in^3");
  EXPECT_EQ(Abbreviation(Volume::CubicCentimetre), "cm^3");
  EXPECT_EQ(Abbreviation(Volume::Millilitre), "mL");
  EXPECT_EQ(Abbreviation(Volume::CubicMillimetre), "mm^3");
  EXPECT_EQ(Abbreviation(Volume::CubicMilliinch), "mil^3");
  EXPECT_EQ(Abbreviation(Volume::CubicMicrometre), "μm^3");
  EXPECT_EQ(Abbreviation(Volume::CubicMicroinch), "μin^3");
}

TEST(UnitVolume, ConsistentUnit) {
  EXPECT_EQ(ConsistentUnit<Volume>(UnitSystem::MetreKilogramSecondKelvin), Volume::CubicMetre);
  EXPECT_EQ(
      ConsistentUnit<Volume>(UnitSystem::MillimetreGramSecondKelvin), Volume::CubicMillimetre);
  EXPECT_EQ(ConsistentUnit<Volume>(UnitSystem::FootPoundSecondRankine), Volume::CubicFoot);
  EXPECT_EQ(ConsistentUnit<Volume>(UnitSystem::InchPoundSecondRankine), Volume::CubicInch);
}

TEST(UnitVolume, ConvertAndConvertCopy) {
  constexpr long double value{1.234567890123456789L};
  Internal::TestConvertAndConvertCopy<Volume>(
      Volume::CubicMetre, Volume::CubicNauticalMile, value, value / std::pow(1852.0L, 3));
  Internal::TestConvertAndConvertCopy<Volume>(
      Volume::CubicMetre, Volume::CubicMile, value, value / std::pow(1609.344L, 3));
  Internal::TestConvertAndConvertCopy<Volume>(
      Volume::CubicMetre, Volume::CubicKilometre, value, value * std::pow(0.001L, 3));
  Internal::TestConvertAndConvertCopy<Volume>(Volume::CubicMetre, Volume::CubicMetre, value, value);
  Internal::TestConvertAndConvertCopy<Volume>(
      Volume::CubicMetre, Volume::CubicYard, value, value / std::pow(0.9144L, 3));
  Internal::TestConvertAndConvertCopy<Volume>(
      Volume::CubicMetre, Volume::CubicFoot, value, value / std::pow(0.3048L, 3));
  Internal::TestConvertAndConvertCopy<Volume>(
      Volume::CubicMetre, Volume::CubicDecimetre, value, value * std::pow(10.0L, 3));
  Internal::TestConvertAndConvertCopy<Volume>(
      Volume::CubicMetre, Volume::Litre, value, value * std::pow(10.0L, 3));
  Internal::TestConvertAndConvertCopy<Volume>(
      Volume::CubicMetre, Volume::CubicInch, value, value / std::pow(0.0254L, 3));
  Internal::TestConvertAndConvertCopy<Volume>(
      Volume::CubicMetre, Volume::CubicCentimetre, value, value * std::pow(100.0L, 3));
  Internal::TestConvertAndConvertCopy<Volume>(
      Volume::CubicMetre, Volume::Millilitre, value, value * std::pow(100.0L, 3));
  Internal::TestConvertAndConvertCopy<Volume>(
      Volume::CubicMetre, Volume::CubicMillimetre, value, value * std::pow(1000.0L, 3));
  Internal::TestConvertAndConvertCopy<Volume>(
      Volume::CubicMetre, Volume::CubicMilliinch, value, value / std::pow(0.0000254L, 3));
  Internal::TestConvertAndConvertCopy<Volume>(
      Volume::CubicMetre, Volume::CubicMicrometre, value, value * std::pow(1000000.0L, 3));
  Internal::TestConvertAndConvertCopy<Volume>(
      Volume::CubicMetre, Volume::CubicMicroinch, value, value / std::pow(0.0000000254L, 3));
}

TEST(UnitVolume, Parse) {
  EXPECT_EQ(Parse<Volume>("Hello world!"), std::nullopt);
  EXPECT_EQ(Parse<Volume>("nmi^3"), Volume::CubicNauticalMile);
  EXPECT_EQ(Parse<Volume>("mi^3"), Volume::CubicMile);
  EXPECT_EQ(Parse<Volume>("km^3"), Volume::CubicKilometre);
  EXPECT_EQ(Parse<Volume>("m^3"), Volume::CubicMetre);
  EXPECT_EQ(Parse<Volume>("yd^3"), Volume::CubicYard);
  EXPECT_EQ(Parse<Volume>("ft^3"), Volume::CubicFoot);
  EXPECT_EQ(Parse<Volume>("dm^3"), Volume::CubicDecimetre);
  EXPECT_EQ(Parse<Volume>("L"), Volume::Litre);
  EXPECT_EQ(Parse<Volume>("in^3"), Volume::CubicInch);
  EXPECT_EQ(Parse<Volume>("cm^3"), Volume::CubicCentimetre);
  EXPECT_EQ(Parse<Volume>("mL"), Volume::Millilitre);
  EXPECT_EQ(Parse<Volume>("mm^3"), Volume::CubicMillimetre);
  EXPECT_EQ(Parse<Volume>("mil^3"), Volume::CubicMilliinch);
  EXPECT_EQ(Parse<Volume>("μm^3"), Volume::CubicMicrometre);
  EXPECT_EQ(Parse<Volume>("μin^3"), Volume::CubicMicroinch);
}

TEST(UnitVolume, RelatedDimensions) {
  EXPECT_EQ(RelatedDimensions<Volume>, Dimensions(Dimension::Time{0}, Dimension::Length{3}));
}

TEST(UnitVolume, RelatedUnitSystem) {
  EXPECT_EQ(RelatedUnitSystem(Volume::CubicNauticalMile), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Volume::CubicMile), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Volume::CubicKilometre), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Volume::CubicMetre), UnitSystem::MetreKilogramSecondKelvin);
  EXPECT_EQ(RelatedUnitSystem(Volume::CubicYard), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Volume::CubicFoot), UnitSystem::FootPoundSecondRankine);
  EXPECT_EQ(RelatedUnitSystem(Volume::CubicDecimetre), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Volume::Litre), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Volume::CubicInch), UnitSystem::InchPoundSecondRankine);
  EXPECT_EQ(RelatedUnitSystem(Volume::CubicCentimetre), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Volume::Millilitre), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Volume::CubicMillimetre), UnitSystem::MillimetreGramSecondKelvin);
  EXPECT_EQ(RelatedUnitSystem(Volume::CubicMilliinch), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Volume::CubicMicrometre), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Volume::CubicMicroinch), std::nullopt);
}

TEST(UnitVolume, Standard) {
  EXPECT_EQ(Standard<Volume>, Volume::CubicMetre);
}

TEST(UnitVolume, StaticConvertCopy) {
  constexpr long double value{1.234567890123456789L};
  Internal::TestStaticConvertCopy<Volume, Volume::CubicMetre, Volume::CubicFoot>(
      value, value / std::pow(0.3048L, 3));
}

TEST(UnitVolume, Stream) {
  std::ostringstream stream;
  stream << Volume::CubicMetre;
  EXPECT_EQ(stream.str(), Abbreviation(Volume::CubicMetre));
}

}  // namespace

}  // namespace PhQ::Unit
