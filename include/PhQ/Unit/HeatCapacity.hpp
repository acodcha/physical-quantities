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

#ifndef PHYSICAL_QUANTITIES_INCLUDE_PHQ_UNIT_HEAT_CAPACITY_HPP
#define PHYSICAL_QUANTITIES_INCLUDE_PHQ_UNIT_HEAT_CAPACITY_HPP

#include <cstddef>
#include <cstdint>
#include <functional>
#include <map>
#include <ostream>
#include <string_view>
#include <unordered_map>

#include "../Base.hpp"
#include "../Dimension/ElectricCurrent.hpp"
#include "../Dimension/Length.hpp"
#include "../Dimension/Mass.hpp"
#include "../Dimension/Temperature.hpp"
#include "../Dimension/Time.hpp"
#include "../Dimensions.hpp"
#include "../Unit.hpp"
#include "../UnitSystem.hpp"

namespace PhQ {

namespace Unit {

// Heat capacity units.
enum class HeatCapacity : int8_t {
  // Joule per kelvin (J/K) heat capacity unit.
  JoulePerKelvin,

  // Nanojoule per kelvin (nJ/K) heat capacity unit.
  NanojoulePerKelvin,

  // Foot-pound per degree Rankine (ft·lbf/°R) heat capacity unit.
  FootPoundPerRankine,

  // Inch-pound per degree Rankine (in·lbf/°R) heat capacity unit.
  InchPoundPerRankine,
};

}  // namespace Unit

// Standard heat capacity unit: joule per kelvin (J/K).
template <>
inline constexpr const Unit::HeatCapacity Standard<Unit::HeatCapacity>{
    Unit::HeatCapacity::JoulePerKelvin};

// Physical dimension set of heat capacity units.
template <>
inline constexpr const Dimensions RelatedDimensions<Unit::HeatCapacity>{
    Dimensions{Dimension::Time{-2}, Dimension::Length{2}, Dimension::Mass{1},
               Dimension::ElectricCurrent{}, Dimension::Temperature{-1}}
};

inline std::ostream& operator<<(std::ostream& stream, const Unit::HeatCapacity unit) {
  stream << Abbreviation(unit);
  return stream;
}

namespace Internal {

template <>
inline const std::map<UnitSystem, Unit::HeatCapacity> ConsistentUnits<Unit::HeatCapacity>{
    {UnitSystem::MetreKilogramSecondKelvin,  Unit::HeatCapacity::JoulePerKelvin     },
    {UnitSystem::MillimetreGramSecondKelvin, Unit::HeatCapacity::NanojoulePerKelvin },
    {UnitSystem::FootPoundSecondRankine,     Unit::HeatCapacity::FootPoundPerRankine},
    {UnitSystem::InchPoundSecondRankine,     Unit::HeatCapacity::InchPoundPerRankine},
};

template <>
inline const std::map<Unit::HeatCapacity, UnitSystem> RelatedUnitSystems<Unit::HeatCapacity>{
    {Unit::HeatCapacity::JoulePerKelvin,      UnitSystem::MetreKilogramSecondKelvin },
    {Unit::HeatCapacity::NanojoulePerKelvin,  UnitSystem::MillimetreGramSecondKelvin},
    {Unit::HeatCapacity::FootPoundPerRankine, UnitSystem::FootPoundSecondRankine    },
    {Unit::HeatCapacity::InchPoundPerRankine, UnitSystem::InchPoundSecondRankine    },
};

template <>
inline const std::map<Unit::HeatCapacity, std::string_view> Abbreviations<Unit::HeatCapacity>{
    {Unit::HeatCapacity::JoulePerKelvin,      "J/K"      },
    {Unit::HeatCapacity::NanojoulePerKelvin,  "nJ/K"     },
    {Unit::HeatCapacity::FootPoundPerRankine, "ft·lbf/°R"},
    {Unit::HeatCapacity::InchPoundPerRankine, "in·lbf/°R"},
};

template <>
inline const std::unordered_map<std::string_view, Unit::HeatCapacity> Spellings<Unit::HeatCapacity>{
    {"J/K",            Unit::HeatCapacity::JoulePerKelvin     },
    {"N·m/K",          Unit::HeatCapacity::JoulePerKelvin     },
    {"N*m/K",          Unit::HeatCapacity::JoulePerKelvin     },
    {"kg·m^2/s^2/K",   Unit::HeatCapacity::JoulePerKelvin     },
    {"kg*m^2/s^2/K",   Unit::HeatCapacity::JoulePerKelvin     },
    {"kg·m2/s2/K",     Unit::HeatCapacity::JoulePerKelvin     },
    {"kg*m2/s2/K",     Unit::HeatCapacity::JoulePerKelvin     },
    {"kg·m^2/(s^2·K)", Unit::HeatCapacity::JoulePerKelvin     },
    {"kg*m^2/(s^2*K)", Unit::HeatCapacity::JoulePerKelvin     },
    {"kg·m2/(s2·K)",   Unit::HeatCapacity::JoulePerKelvin     },
    {"kg*m2/(s2*K)",   Unit::HeatCapacity::JoulePerKelvin     },
    {"nJ/K",           Unit::HeatCapacity::NanojoulePerKelvin },
    {"μN·mm/K",        Unit::HeatCapacity::NanojoulePerKelvin },
    {"μN*mm/K",        Unit::HeatCapacity::NanojoulePerKelvin },
    {"uN·mm/K",        Unit::HeatCapacity::NanojoulePerKelvin },
    {"uN*mm/K",        Unit::HeatCapacity::NanojoulePerKelvin },
    {"g·mm^2/s^2/K",   Unit::HeatCapacity::NanojoulePerKelvin },
    {"g*mm^2/s^2/K",   Unit::HeatCapacity::NanojoulePerKelvin },
    {"g·mm2/s2/K",     Unit::HeatCapacity::NanojoulePerKelvin },
    {"g*mm2/s2/K",     Unit::HeatCapacity::NanojoulePerKelvin },
    {"g·mm^2/(s^2·K)", Unit::HeatCapacity::NanojoulePerKelvin },
    {"g*mm^2/(s^2*K)", Unit::HeatCapacity::NanojoulePerKelvin },
    {"g·mm2/(s2·K)",   Unit::HeatCapacity::NanojoulePerKelvin },
    {"g*mm2/(s2*K)",   Unit::HeatCapacity::NanojoulePerKelvin },
    {"ft·lbf/°R",      Unit::HeatCapacity::FootPoundPerRankine},
    {"ft·lbf/R",       Unit::HeatCapacity::FootPoundPerRankine},
    {"ft*lbf/°R",      Unit::HeatCapacity::FootPoundPerRankine},
    {"ft*lbf/R",       Unit::HeatCapacity::FootPoundPerRankine},
    {"ft·lb/°R",       Unit::HeatCapacity::FootPoundPerRankine},
    {"ft·lb/R",        Unit::HeatCapacity::FootPoundPerRankine},
    {"ft*lb/°R",       Unit::HeatCapacity::FootPoundPerRankine},
    {"ft*lb/R",        Unit::HeatCapacity::FootPoundPerRankine},
    {"in·lbf/°R",      Unit::HeatCapacity::InchPoundPerRankine},
    {"in·lbf/R",       Unit::HeatCapacity::InchPoundPerRankine},
    {"in*lbf/°R",      Unit::HeatCapacity::InchPoundPerRankine},
    {"in*lbf/R",       Unit::HeatCapacity::InchPoundPerRankine},
    {"in·lb/°R",       Unit::HeatCapacity::InchPoundPerRankine},
    {"in·lb/R",        Unit::HeatCapacity::InchPoundPerRankine},
    {"in*lb/°R",       Unit::HeatCapacity::InchPoundPerRankine},
    {"in*lb/R",        Unit::HeatCapacity::InchPoundPerRankine},
};

template <>
inline constexpr void
ConversionFromStandard<Unit::HeatCapacity, Unit::HeatCapacity::JoulePerKelvin>(
    double& /*value*/) noexcept {}

template <>
inline constexpr void
ConversionFromStandard<Unit::HeatCapacity, Unit::HeatCapacity::NanojoulePerKelvin>(
    double& value) noexcept {
  value *= 1000000000.0;
}

template <>
inline constexpr void
ConversionFromStandard<Unit::HeatCapacity, Unit::HeatCapacity::FootPoundPerRankine>(
    double& value) noexcept {
  value /= 0.3048 * 0.45359237 * 9.80665 * 1.8;
}

template <>
inline constexpr void
ConversionFromStandard<Unit::HeatCapacity, Unit::HeatCapacity::InchPoundPerRankine>(
    double& value) noexcept {
  value /= 0.0254 * 0.45359237 * 9.80665 * 1.8;
}

template <>
inline constexpr void ConversionToStandard<Unit::HeatCapacity, Unit::HeatCapacity::JoulePerKelvin>(
    double& /*value*/) noexcept {}

template <>
inline constexpr void
ConversionToStandard<Unit::HeatCapacity, Unit::HeatCapacity::NanojoulePerKelvin>(
    double& value) noexcept {
  value *= 0.000000001;
}

template <>
inline constexpr void
ConversionToStandard<Unit::HeatCapacity, Unit::HeatCapacity::FootPoundPerRankine>(
    double& value) noexcept {
  value *= 0.3048 * 0.45359237 * 9.80665 * 1.8;
}

template <>
inline constexpr void
ConversionToStandard<Unit::HeatCapacity, Unit::HeatCapacity::InchPoundPerRankine>(
    double& value) noexcept {
  value *= 0.0254 * 0.45359237 * 9.80665 * 1.8;
}

template <>
inline const std::map<Unit::HeatCapacity,
                      std::function<void(double* values, const std::size_t size)>>
    MapOfConversionsFromStandard<Unit::HeatCapacity>{
        {Unit::HeatCapacity::JoulePerKelvin,
         ConversionsFromStandard<Unit::HeatCapacity, Unit::HeatCapacity::JoulePerKelvin>     },
        {Unit::HeatCapacity::NanojoulePerKelvin,
         ConversionsFromStandard<Unit::HeatCapacity, Unit::HeatCapacity::NanojoulePerKelvin> },
        {Unit::HeatCapacity::FootPoundPerRankine,
         ConversionsFromStandard<Unit::HeatCapacity, Unit::HeatCapacity::FootPoundPerRankine>},
        {Unit::HeatCapacity::InchPoundPerRankine,
         ConversionsFromStandard<Unit::HeatCapacity, Unit::HeatCapacity::InchPoundPerRankine>},
};

template <>
inline const std::map<Unit::HeatCapacity,
                      std::function<void(double* const values, const std::size_t size)>>
    MapOfConversionsToStandard<Unit::HeatCapacity>{
        {Unit::HeatCapacity::JoulePerKelvin,
         ConversionsToStandard<Unit::HeatCapacity, Unit::HeatCapacity::JoulePerKelvin>     },
        {Unit::HeatCapacity::NanojoulePerKelvin,
         ConversionsToStandard<Unit::HeatCapacity, Unit::HeatCapacity::NanojoulePerKelvin> },
        {Unit::HeatCapacity::FootPoundPerRankine,
         ConversionsToStandard<Unit::HeatCapacity, Unit::HeatCapacity::FootPoundPerRankine>},
        {Unit::HeatCapacity::InchPoundPerRankine,
         ConversionsToStandard<Unit::HeatCapacity, Unit::HeatCapacity::InchPoundPerRankine>},
};

}  // namespace Internal

}  // namespace PhQ

#endif  // PHYSICAL_QUANTITIES_INCLUDE_PHQ_UNIT_HEAT_CAPACITY_HPP
