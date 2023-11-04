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

#include "../../include/PhQ/Unit/Acceleration.hpp"

#include <gtest/gtest.h>

#include "../Unit.hpp"

namespace PhQ::Unit {

namespace {

constexpr std::array<Acceleration, 36> Units = {
    Acceleration::MilePerSquareSecond,
    Acceleration::MilePerSquareMinute,
    Acceleration::MilePerSquareHour,
    Acceleration::KilometrePerSquareSecond,
    Acceleration::KilometrePerSquareMinute,
    Acceleration::KilometrePerSquareHour,
    Acceleration::YardPerSquareSecond,
    Acceleration::YardPerSquareMinute,
    Acceleration::YardPerSquareHour,
    Acceleration::MetrePerSquareSecond,
    Acceleration::MetrePerSquareMinute,
    Acceleration::MetrePerSquareHour,
    Acceleration::FootPerSquareSecond,
    Acceleration::FootPerSquareMinute,
    Acceleration::FootPerSquareHour,
    Acceleration::DecimetrePerSquareSecond,
    Acceleration::DecimetrePerSquareMinute,
    Acceleration::DecimetrePerSquareHour,
    Acceleration::InchPerSquareSecond,
    Acceleration::InchPerSquareMinute,
    Acceleration::InchPerSquareHour,
    Acceleration::CentimetrePerSquareSecond,
    Acceleration::CentimetrePerSquareMinute,
    Acceleration::CentimetrePerSquareHour,
    Acceleration::MillimetrePerSquareSecond,
    Acceleration::MillimetrePerSquareMinute,
    Acceleration::MillimetrePerSquareHour,
    Acceleration::MilliinchPerSquareSecond,
    Acceleration::MilliinchPerSquareMinute,
    Acceleration::MilliinchPerSquareHour,
    Acceleration::MicrometrePerSquareSecond,
    Acceleration::MicrometrePerSquareMinute,
    Acceleration::MicrometrePerSquareHour,
    Acceleration::MicroinchPerSquareSecond,
    Acceleration::MicroinchPerSquareMinute,
    Acceleration::MicroinchPerSquareHour,
};

TEST(UnitAcceleration, Abbreviation) {
  EXPECT_EQ(Abbreviation(Acceleration::MilePerSquareSecond), "mi/s^2");
  EXPECT_EQ(Abbreviation(Acceleration::KilometrePerSquareSecond), "km/s^2");
  EXPECT_EQ(Abbreviation(Acceleration::YardPerSquareSecond), "yd/s^2");
  EXPECT_EQ(Abbreviation(Acceleration::MetrePerSquareSecond), "m/s^2");
  EXPECT_EQ(Abbreviation(Acceleration::FootPerSquareSecond), "ft/s^2");
  EXPECT_EQ(Abbreviation(Acceleration::DecimetrePerSquareSecond), "dm/s^2");
  EXPECT_EQ(Abbreviation(Acceleration::InchPerSquareSecond), "in/s^2");
  EXPECT_EQ(Abbreviation(Acceleration::CentimetrePerSquareSecond), "cm/s^2");
  EXPECT_EQ(Abbreviation(Acceleration::MillimetrePerSquareSecond), "mm/s^2");
  EXPECT_EQ(Abbreviation(Acceleration::MilliinchPerSquareSecond), "mil/s^2");
  EXPECT_EQ(Abbreviation(Acceleration::MicrometrePerSquareSecond), "μm/s^2");
  EXPECT_EQ(Abbreviation(Acceleration::MicroinchPerSquareSecond), "μin/s^2");
  EXPECT_EQ(Abbreviation(Acceleration::MilePerSquareMinute), "mi/min^2");
  EXPECT_EQ(Abbreviation(Acceleration::KilometrePerSquareMinute), "km/min^2");
  EXPECT_EQ(Abbreviation(Acceleration::YardPerSquareMinute), "yd/min^2");
  EXPECT_EQ(Abbreviation(Acceleration::MetrePerSquareMinute), "m/min^2");
  EXPECT_EQ(Abbreviation(Acceleration::FootPerSquareMinute), "ft/min^2");
  EXPECT_EQ(Abbreviation(Acceleration::DecimetrePerSquareMinute), "dm/min^2");
  EXPECT_EQ(Abbreviation(Acceleration::InchPerSquareMinute), "in/min^2");
  EXPECT_EQ(Abbreviation(Acceleration::CentimetrePerSquareMinute), "cm/min^2");
  EXPECT_EQ(Abbreviation(Acceleration::MillimetrePerSquareMinute), "mm/min^2");
  EXPECT_EQ(Abbreviation(Acceleration::MilliinchPerSquareMinute), "mil/min^2");
  EXPECT_EQ(Abbreviation(Acceleration::MicrometrePerSquareMinute), "μm/min^2");
  EXPECT_EQ(Abbreviation(Acceleration::MicroinchPerSquareMinute), "μin/min^2");
  EXPECT_EQ(Abbreviation(Acceleration::MilePerSquareHour), "mi/hr^2");
  EXPECT_EQ(Abbreviation(Acceleration::KilometrePerSquareHour), "km/hr^2");
  EXPECT_EQ(Abbreviation(Acceleration::YardPerSquareHour), "yd/hr^2");
  EXPECT_EQ(Abbreviation(Acceleration::MetrePerSquareHour), "m/hr^2");
  EXPECT_EQ(Abbreviation(Acceleration::FootPerSquareHour), "ft/hr^2");
  EXPECT_EQ(Abbreviation(Acceleration::DecimetrePerSquareHour), "dm/hr^2");
  EXPECT_EQ(Abbreviation(Acceleration::InchPerSquareHour), "in/hr^2");
  EXPECT_EQ(Abbreviation(Acceleration::CentimetrePerSquareHour), "cm/hr^2");
  EXPECT_EQ(Abbreviation(Acceleration::MillimetrePerSquareHour), "mm/hr^2");
  EXPECT_EQ(Abbreviation(Acceleration::MilliinchPerSquareHour), "mil/hr^2");
  EXPECT_EQ(Abbreviation(Acceleration::MicrometrePerSquareHour), "μm/hr^2");
  EXPECT_EQ(Abbreviation(Acceleration::MicroinchPerSquareHour), "μin/hr^2");
}

TEST(UnitAcceleration, ConsistentUnit) {
  EXPECT_EQ(ConsistentUnit<Acceleration>(UnitSystem::MetreKilogramSecondKelvin),
            Acceleration::MetrePerSquareSecond);
  EXPECT_EQ(
      ConsistentUnit<Acceleration>(UnitSystem::MillimetreGramSecondKelvin),
      Acceleration::MillimetrePerSquareSecond);
  EXPECT_EQ(ConsistentUnit<Acceleration>(UnitSystem::FootPoundSecondRankine),
            Acceleration::FootPerSquareSecond);
  EXPECT_EQ(ConsistentUnit<Acceleration>(UnitSystem::InchPoundSecondRankine),
            Acceleration::InchPerSquareSecond);
}

TEST(UnitAcceleration, ConvertFromStandard) {
  constexpr double value{10.0};
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::MilePerSquareSecond>(value, value / 1609.344);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::KilometrePerSquareSecond>(value, value * 0.001);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::MetrePerSquareSecond>(value, value);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::YardPerSquareSecond>(value, value / 0.9144);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::FootPerSquareSecond>(value, value / 0.3048);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::DecimetrePerSquareSecond>(value, value * 10.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::InchPerSquareSecond>(value, value / 0.0254);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::CentimetrePerSquareSecond>(value, value * 100.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::MillimetrePerSquareSecond>(value, value * 1000.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::MilliinchPerSquareSecond>(value, value / 0.0000254);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::MicrometrePerSquareSecond>(value, value * 1000000.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::MicroinchPerSquareSecond>(value, value / 0.0000000254);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::MilePerSquareMinute>(value, value / 1609.344 * 3600.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::KilometrePerSquareMinute>(value, value * 0.001 * 3600.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::MetrePerSquareMinute>(value, value * 3600.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::YardPerSquareMinute>(value, value / 0.9144 * 3600.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::FootPerSquareMinute>(value, value / 0.3048 * 3600.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::DecimetrePerSquareMinute>(value, value * 10.0 * 3600.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::InchPerSquareMinute>(value, value / 0.0254 * 3600.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::CentimetrePerSquareMinute>(value, value * 100.0 * 3600.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::MillimetrePerSquareMinute>(value, value * 1000.0 * 3600.0);
  Internal::TestUnitConversions<Acceleration,
                                Acceleration::MetrePerSquareSecond,
                                Acceleration::MilliinchPerSquareMinute>(
      value, value / 0.0000254 * 3600.0);
  Internal::TestUnitConversions<Acceleration,
                                Acceleration::MetrePerSquareSecond,
                                Acceleration::MicrometrePerSquareMinute>(
      value, value * 1000000.0 * 3600.0);
  Internal::TestUnitConversions<Acceleration,
                                Acceleration::MetrePerSquareSecond,
                                Acceleration::MicroinchPerSquareMinute>(
      value, value / 0.0000000254 * 3600.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::MilePerSquareHour>(value, value / 1609.344 * 12960000.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::KilometrePerSquareHour>(value, value * 0.001 * 12960000.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::MetrePerSquareHour>(value, value * 12960000.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::YardPerSquareHour>(value, value / 0.9144 * 12960000.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::FootPerSquareHour>(value, value / 0.3048 * 12960000.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::DecimetrePerSquareHour>(value, value * 10.0 * 12960000.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::InchPerSquareHour>(value, value / 0.0254 * 12960000.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::CentimetrePerSquareHour>(value, value * 100.0 * 12960000.0);
  Internal::TestUnitConversions<Acceleration,
                                Acceleration::MetrePerSquareSecond,
                                Acceleration::MillimetrePerSquareHour>(
      value, value * 1000.0 * 12960000.0);
  Internal::TestUnitConversions<Acceleration,
                                Acceleration::MetrePerSquareSecond,
                                Acceleration::MilliinchPerSquareHour>(
      value, value / 0.0000254 * 12960000.0);
  Internal::TestUnitConversions<Acceleration,
                                Acceleration::MetrePerSquareSecond,
                                Acceleration::MicrometrePerSquareHour>(
      value, value * 1000000.0 * 12960000.0);
  Internal::TestUnitConversions<Acceleration,
                                Acceleration::MetrePerSquareSecond,
                                Acceleration::MicroinchPerSquareHour>(
      value, value / 0.0000000254 * 12960000.0);
}

TEST(UnitAcceleration, ConvertToStandard) {
  constexpr double value{10.0};
  Internal::TestUnitConversions<Acceleration, Acceleration::MilePerSquareSecond,
                                Acceleration::MetrePerSquareSecond>(
      value, value * 1609.344);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::KilometrePerSquareSecond,
      Acceleration::MetrePerSquareSecond>(value, value * 1000.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareSecond,
      Acceleration::MetrePerSquareSecond>(value, value);
  Internal::TestUnitConversions<Acceleration, Acceleration::YardPerSquareSecond,
                                Acceleration::MetrePerSquareSecond>(
      value, value * 0.9144);
  Internal::TestUnitConversions<Acceleration, Acceleration::FootPerSquareSecond,
                                Acceleration::MetrePerSquareSecond>(
      value, value * 0.3048);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::DecimetrePerSquareSecond,
      Acceleration::MetrePerSquareSecond>(value, value * 0.1);
  Internal::TestUnitConversions<Acceleration, Acceleration::InchPerSquareSecond,
                                Acceleration::MetrePerSquareSecond>(
      value, value * 0.0254);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::CentimetrePerSquareSecond,
      Acceleration::MetrePerSquareSecond>(value, value * 0.01);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MillimetrePerSquareSecond,
      Acceleration::MetrePerSquareSecond>(value, value * 0.001);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MilliinchPerSquareSecond,
      Acceleration::MetrePerSquareSecond>(value, value * 0.0000254);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MicrometrePerSquareSecond,
      Acceleration::MetrePerSquareSecond>(value, value * 0.000001);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MicroinchPerSquareSecond,
      Acceleration::MetrePerSquareSecond>(value, value * 0.0000000254);
  Internal::TestUnitConversions<Acceleration, Acceleration::MilePerSquareMinute,
                                Acceleration::MetrePerSquareSecond>(
      value, value * 1609.344 / 3600.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::KilometrePerSquareMinute,
      Acceleration::MetrePerSquareSecond>(value, value * 1000.0 / 3600.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MetrePerSquareMinute,
      Acceleration::MetrePerSquareSecond>(value, value / 3600.0);
  Internal::TestUnitConversions<Acceleration, Acceleration::YardPerSquareMinute,
                                Acceleration::MetrePerSquareSecond>(
      value, value * 0.9144 / 3600.0);
  Internal::TestUnitConversions<Acceleration, Acceleration::FootPerSquareMinute,
                                Acceleration::MetrePerSquareSecond>(
      value, value * 0.3048 / 3600.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::DecimetrePerSquareMinute,
      Acceleration::MetrePerSquareSecond>(value, value * 0.1 / 3600.0);
  Internal::TestUnitConversions<Acceleration, Acceleration::InchPerSquareMinute,
                                Acceleration::MetrePerSquareSecond>(
      value, value * 0.0254 / 3600.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::CentimetrePerSquareMinute,
      Acceleration::MetrePerSquareSecond>(value, value * 0.01 / 3600.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MillimetrePerSquareMinute,
      Acceleration::MetrePerSquareSecond>(value, value * 0.001 / 3600.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MilliinchPerSquareMinute,
      Acceleration::MetrePerSquareSecond>(value, value * 0.0000254 / 3600.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MicrometrePerSquareMinute,
      Acceleration::MetrePerSquareSecond>(value, value * 0.000001 / 3600.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MicroinchPerSquareMinute,
      Acceleration::MetrePerSquareSecond>(value, value * 0.0000000254 / 3600.0);
  Internal::TestUnitConversions<Acceleration, Acceleration::MilePerSquareHour,
                                Acceleration::MetrePerSquareSecond>(
      value, value * 1609.344 / 12960000.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::KilometrePerSquareHour,
      Acceleration::MetrePerSquareSecond>(value, value * 1000.0 / 12960000.0);
  Internal::TestUnitConversions<Acceleration, Acceleration::MetrePerSquareHour,
                                Acceleration::MetrePerSquareSecond>(
      value, value / 12960000.0);
  Internal::TestUnitConversions<Acceleration, Acceleration::YardPerSquareHour,
                                Acceleration::MetrePerSquareSecond>(
      value, value * 0.9144 / 12960000.0);
  Internal::TestUnitConversions<Acceleration, Acceleration::FootPerSquareHour,
                                Acceleration::MetrePerSquareSecond>(
      value, value * 0.3048 / 12960000.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::DecimetrePerSquareHour,
      Acceleration::MetrePerSquareSecond>(value, value * 0.1 / 12960000.0);
  Internal::TestUnitConversions<Acceleration, Acceleration::InchPerSquareHour,
                                Acceleration::MetrePerSquareSecond>(
      value, value * 0.0254 / 12960000.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::CentimetrePerSquareHour,
      Acceleration::MetrePerSquareSecond>(value, value * 0.01 / 12960000.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MillimetrePerSquareHour,
      Acceleration::MetrePerSquareSecond>(value, value * 0.001 / 12960000.0);
  Internal::TestUnitConversions<Acceleration,
                                Acceleration::MilliinchPerSquareHour,
                                Acceleration::MetrePerSquareSecond>(
      value, value * 0.0000254 / 12960000.0);
  Internal::TestUnitConversions<
      Acceleration, Acceleration::MicrometrePerSquareHour,
      Acceleration::MetrePerSquareSecond>(value, value * 0.000001 / 12960000.0);
  Internal::TestUnitConversions<Acceleration,
                                Acceleration::MicroinchPerSquareHour,
                                Acceleration::MetrePerSquareSecond>(
      value, value * 0.0000000254 / 12960000.0);
}

TEST(UnitAcceleration, Parse) {
  EXPECT_EQ(Parse<Acceleration>("Hello world!"), std::nullopt);
  EXPECT_EQ(Parse<Acceleration>("mi/s^2"), Acceleration::MilePerSquareSecond);
  EXPECT_EQ(
      Parse<Acceleration>("km/s^2"), Acceleration::KilometrePerSquareSecond);
  EXPECT_EQ(Parse<Acceleration>("yd/s^2"), Acceleration::YardPerSquareSecond);
  EXPECT_EQ(Parse<Acceleration>("m/s^2"), Acceleration::MetrePerSquareSecond);
  EXPECT_EQ(Parse<Acceleration>("ft/s^2"), Acceleration::FootPerSquareSecond);
  EXPECT_EQ(
      Parse<Acceleration>("dm/s^2"), Acceleration::DecimetrePerSquareSecond);
  EXPECT_EQ(Parse<Acceleration>("in/s^2"), Acceleration::InchPerSquareSecond);
  EXPECT_EQ(
      Parse<Acceleration>("cm/s^2"), Acceleration::CentimetrePerSquareSecond);
  EXPECT_EQ(
      Parse<Acceleration>("mm/s^2"), Acceleration::MillimetrePerSquareSecond);
  EXPECT_EQ(
      Parse<Acceleration>("mil/s^2"), Acceleration::MilliinchPerSquareSecond);
  EXPECT_EQ(
      Parse<Acceleration>("μm/s^2"), Acceleration::MicrometrePerSquareSecond);
  EXPECT_EQ(
      Parse<Acceleration>("μin/s^2"), Acceleration::MicroinchPerSquareSecond);
  EXPECT_EQ(Parse<Acceleration>("mi/min^2"), Acceleration::MilePerSquareMinute);
  EXPECT_EQ(
      Parse<Acceleration>("km/min^2"), Acceleration::KilometrePerSquareMinute);
  EXPECT_EQ(Parse<Acceleration>("yd/min^2"), Acceleration::YardPerSquareMinute);
  EXPECT_EQ(Parse<Acceleration>("m/min^2"), Acceleration::MetrePerSquareMinute);
  EXPECT_EQ(Parse<Acceleration>("ft/min^2"), Acceleration::FootPerSquareMinute);
  EXPECT_EQ(
      Parse<Acceleration>("dm/min^2"), Acceleration::DecimetrePerSquareMinute);
  EXPECT_EQ(Parse<Acceleration>("in/min^2"), Acceleration::InchPerSquareMinute);
  EXPECT_EQ(
      Parse<Acceleration>("cm/min^2"), Acceleration::CentimetrePerSquareMinute);
  EXPECT_EQ(
      Parse<Acceleration>("mm/min^2"), Acceleration::MillimetrePerSquareMinute);
  EXPECT_EQ(
      Parse<Acceleration>("mil/min^2"), Acceleration::MilliinchPerSquareMinute);
  EXPECT_EQ(
      Parse<Acceleration>("μm/min^2"), Acceleration::MicrometrePerSquareMinute);
  EXPECT_EQ(
      Parse<Acceleration>("μin/min^2"), Acceleration::MicroinchPerSquareMinute);
  EXPECT_EQ(Parse<Acceleration>("mi/hr^2"), Acceleration::MilePerSquareHour);
  EXPECT_EQ(
      Parse<Acceleration>("km/hr^2"), Acceleration::KilometrePerSquareHour);
  EXPECT_EQ(Parse<Acceleration>("yd/hr^2"), Acceleration::YardPerSquareHour);
  EXPECT_EQ(Parse<Acceleration>("m/hr^2"), Acceleration::MetrePerSquareHour);
  EXPECT_EQ(Parse<Acceleration>("ft/hr^2"), Acceleration::FootPerSquareHour);
  EXPECT_EQ(
      Parse<Acceleration>("dm/hr^2"), Acceleration::DecimetrePerSquareHour);
  EXPECT_EQ(Parse<Acceleration>("in/hr^2"), Acceleration::InchPerSquareHour);
  EXPECT_EQ(
      Parse<Acceleration>("cm/hr^2"), Acceleration::CentimetrePerSquareHour);
  EXPECT_EQ(
      Parse<Acceleration>("mm/hr^2"), Acceleration::MillimetrePerSquareHour);
  EXPECT_EQ(
      Parse<Acceleration>("mil/hr^2"), Acceleration::MilliinchPerSquareHour);
  EXPECT_EQ(
      Parse<Acceleration>("μm/hr^2"), Acceleration::MicrometrePerSquareHour);
  EXPECT_EQ(
      Parse<Acceleration>("μin/hr^2"), Acceleration::MicroinchPerSquareHour);
}

TEST(UnitAcceleration, RelatedDimensions) {
  EXPECT_EQ(RelatedDimensions<Acceleration>,
            Dimensions(Dimension::Time{-2}, Dimension::Length{1}));
}

TEST(UnitAcceleration, RelatedUnitSystem) {
  EXPECT_EQ(RelatedUnitSystem(Acceleration::MilePerSquareSecond), std::nullopt);
  EXPECT_EQ(
      RelatedUnitSystem(Acceleration::KilometrePerSquareSecond), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Acceleration::YardPerSquareSecond), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Acceleration::MetrePerSquareSecond),
            UnitSystem::MetreKilogramSecondKelvin);
  EXPECT_EQ(RelatedUnitSystem(Acceleration::FootPerSquareSecond),
            UnitSystem::FootPoundSecondRankine);
  EXPECT_EQ(
      RelatedUnitSystem(Acceleration::DecimetrePerSquareSecond), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Acceleration::InchPerSquareSecond),
            UnitSystem::InchPoundSecondRankine);
  EXPECT_EQ(
      RelatedUnitSystem(Acceleration::CentimetrePerSquareSecond), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Acceleration::MillimetrePerSquareSecond),
            UnitSystem::MillimetreGramSecondKelvin);
  EXPECT_EQ(
      RelatedUnitSystem(Acceleration::MilliinchPerSquareSecond), std::nullopt);
  EXPECT_EQ(
      RelatedUnitSystem(Acceleration::MicrometrePerSquareSecond), std::nullopt);
  EXPECT_EQ(
      RelatedUnitSystem(Acceleration::MicroinchPerSquareSecond), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Acceleration::MilePerSquareMinute), std::nullopt);
  EXPECT_EQ(
      RelatedUnitSystem(Acceleration::KilometrePerSquareMinute), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Acceleration::YardPerSquareMinute), std::nullopt);
  EXPECT_EQ(
      RelatedUnitSystem(Acceleration::MetrePerSquareMinute), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Acceleration::FootPerSquareMinute), std::nullopt);
  EXPECT_EQ(
      RelatedUnitSystem(Acceleration::DecimetrePerSquareMinute), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Acceleration::InchPerSquareMinute), std::nullopt);
  EXPECT_EQ(
      RelatedUnitSystem(Acceleration::CentimetrePerSquareMinute), std::nullopt);
  EXPECT_EQ(
      RelatedUnitSystem(Acceleration::MillimetrePerSquareMinute), std::nullopt);
  EXPECT_EQ(
      RelatedUnitSystem(Acceleration::MilliinchPerSquareMinute), std::nullopt);
  EXPECT_EQ(
      RelatedUnitSystem(Acceleration::MicrometrePerSquareMinute), std::nullopt);
  EXPECT_EQ(
      RelatedUnitSystem(Acceleration::MicroinchPerSquareMinute), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Acceleration::MilePerSquareHour), std::nullopt);
  EXPECT_EQ(
      RelatedUnitSystem(Acceleration::KilometrePerSquareHour), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Acceleration::YardPerSquareHour), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Acceleration::MetrePerSquareHour), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Acceleration::FootPerSquareHour), std::nullopt);
  EXPECT_EQ(
      RelatedUnitSystem(Acceleration::DecimetrePerSquareHour), std::nullopt);
  EXPECT_EQ(RelatedUnitSystem(Acceleration::InchPerSquareHour), std::nullopt);
  EXPECT_EQ(
      RelatedUnitSystem(Acceleration::CentimetrePerSquareHour), std::nullopt);
  EXPECT_EQ(
      RelatedUnitSystem(Acceleration::MillimetrePerSquareHour), std::nullopt);
  EXPECT_EQ(
      RelatedUnitSystem(Acceleration::MilliinchPerSquareHour), std::nullopt);
  EXPECT_EQ(
      RelatedUnitSystem(Acceleration::MicrometrePerSquareHour), std::nullopt);
  EXPECT_EQ(
      RelatedUnitSystem(Acceleration::MicroinchPerSquareHour), std::nullopt);
}

TEST(UnitAcceleration, Standard) {
  EXPECT_EQ(Standard<Acceleration>, Acceleration::MetrePerSquareSecond);
}

TEST(UnitAcceleration, Stream) {
  std::ostringstream stream;
  stream << Acceleration::MetrePerSquareSecond;
  EXPECT_EQ(stream.str(), Abbreviation(Acceleration::MetrePerSquareSecond));
}

}  // namespace

}  // namespace PhQ::Unit
