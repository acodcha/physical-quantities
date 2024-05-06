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

#ifndef PHQ_UNIT_POWER_HPP
#define PHQ_UNIT_POWER_HPP

#include <cstddef>
#include <cstdint>
#include <functional>
#include <map>
#include <ostream>
#include <string_view>
#include <unordered_map>

#include "../Base.hpp"
#include "../Dimension/Length.hpp"
#include "../Dimension/Mass.hpp"
#include "../Dimension/Time.hpp"
#include "../Dimensions.hpp"
#include "../Unit.hpp"
#include "../UnitSystem.hpp"

namespace PhQ {

namespace Unit {

// Power units.
enum class Power : int8_t {
  // Watt (W) power unit.
  Watt,

  // Milliwatt (mW) power unit.
  Milliwatt,

  // Microwatt (μW) power unit.
  Microwatt,

  // Nanowatt (nW) power unit.
  Nanowatt,

  // Kilowatt (kW) power unit.
  Kilowatt,

  // Megawatt (MW) power unit.
  Megawatt,

  // Gigawatt (GW) power unit.
  Gigawatt,

  // Foot-pound per second (ft·lbf/s) power unit.
  FootPoundPerSecond,

  // Inch-pound per second (in·lbf/s) power unit.
  InchPoundPerSecond,
};

}  // namespace Unit

// Standard power unit: watt (W).
template <>
inline constexpr const Unit::Power Standard<Unit::Power>{Unit::Power::Watt};

// Physical dimension set of power units.
template <>
inline constexpr const Dimensions RelatedDimensions<Unit::Power>{
    Dimensions{Dimension::Time{-3}, Dimension::Length{2}, Dimension::Mass{1}}
};

inline std::ostream& operator<<(std::ostream& stream, const Unit::Power unit) {
  stream << Abbreviation(unit);
  return stream;
}

namespace Internal {

template <>
inline const std::map<UnitSystem, Unit::Power> ConsistentUnits<Unit::Power>{
    {UnitSystem::MetreKilogramSecondKelvin,  Unit::Power::Watt              },
    {UnitSystem::MillimetreGramSecondKelvin, Unit::Power::Nanowatt          },
    {UnitSystem::FootPoundSecondRankine,     Unit::Power::FootPoundPerSecond},
    {UnitSystem::InchPoundSecondRankine,     Unit::Power::InchPoundPerSecond},
};

template <>
inline const std::map<Unit::Power, UnitSystem> RelatedUnitSystems<Unit::Power>{
    {Unit::Power::Watt,               UnitSystem::MetreKilogramSecondKelvin },
    {Unit::Power::Nanowatt,           UnitSystem::MillimetreGramSecondKelvin},
    {Unit::Power::FootPoundPerSecond, UnitSystem::FootPoundSecondRankine    },
    {Unit::Power::InchPoundPerSecond, UnitSystem::InchPoundSecondRankine    },
};

template <>
inline const std::map<Unit::Power, std::string_view> Abbreviations<Unit::Power>{
    {Unit::Power::Watt,               "W"       },
    {Unit::Power::Milliwatt,          "mW"      },
    {Unit::Power::Microwatt,          "μW"      },
    {Unit::Power::Nanowatt,           "nW"      },
    {Unit::Power::Kilowatt,           "kW"      },
    {Unit::Power::Megawatt,           "MW"      },
    {Unit::Power::Gigawatt,           "GW"      },
    {Unit::Power::FootPoundPerSecond, "ft·lbf/s"},
    {Unit::Power::InchPoundPerSecond, "in·lbf/s"},
};

template <>
inline const std::unordered_map<std::string_view, Unit::Power> Spellings<Unit::Power>{
    {"W",          Unit::Power::Watt              },
    {"J/s",        Unit::Power::Watt              },
    {"N·m/s",      Unit::Power::Watt              },
    {"N*m/s",      Unit::Power::Watt              },
    {"kg·m^2/s^3", Unit::Power::Watt              },
    {"kg*m^2/s^3", Unit::Power::Watt              },
    {"kg·m2/s3",   Unit::Power::Watt              },
    {"kg*m2/s3",   Unit::Power::Watt              },
    {"mW",         Unit::Power::Milliwatt         },
    {"mJ/s",       Unit::Power::Milliwatt         },
    {"μW",         Unit::Power::Microwatt         },
    {"μJ/s",       Unit::Power::Microwatt         },
    {"uW",         Unit::Power::Microwatt         },
    {"uJ/s",       Unit::Power::Microwatt         },
    {"nW",         Unit::Power::Nanowatt          },
    {"nJ/s",       Unit::Power::Nanowatt          },
    {"μN·mm/s",    Unit::Power::Nanowatt          },
    {"μN*mm/s",    Unit::Power::Nanowatt          },
    {"uN·mm/s",    Unit::Power::Nanowatt          },
    {"uN*mm/s",    Unit::Power::Nanowatt          },
    {"g·mm^2/s^3", Unit::Power::Nanowatt          },
    {"g*mm^2/s^3", Unit::Power::Nanowatt          },
    {"g·mm2/s3",   Unit::Power::Nanowatt          },
    {"g*mm2/s3",   Unit::Power::Nanowatt          },
    {"kW",         Unit::Power::Kilowatt          },
    {"kJ/s",       Unit::Power::Kilowatt          },
    {"MW",         Unit::Power::Megawatt          },
    {"MJ/s",       Unit::Power::Megawatt          },
    {"GW",         Unit::Power::Gigawatt          },
    {"GJ/s",       Unit::Power::Gigawatt          },
    {"ft·lbf/s",   Unit::Power::FootPoundPerSecond},
    {"ft*lbf/s",   Unit::Power::FootPoundPerSecond},
    {"ft·lb/s",    Unit::Power::FootPoundPerSecond},
    {"ft*lb/s",    Unit::Power::FootPoundPerSecond},
    {"in·lbf/s",   Unit::Power::InchPoundPerSecond},
    {"in*lbf/s",   Unit::Power::InchPoundPerSecond},
    {"in·lb/s",    Unit::Power::InchPoundPerSecond},
    {"in*lb/s",    Unit::Power::InchPoundPerSecond},
};

template <>
template <typename Number>
inline constexpr void Conversion<Unit::Power, Unit::Power::Watt>::FromStandard(
    Number& /*value*/) noexcept {}

template <>
template <typename Number>
inline constexpr void Conversion<Unit::Power, Unit::Power::Watt>::ToStandard(
    Number& /*value*/) noexcept {}

template <>
template <typename Number>
inline constexpr void Conversion<Unit::Power, Unit::Power::Milliwatt>::FromStandard(
    Number& value) noexcept {
  value *= static_cast<Number>(1000.0L);
}

template <>
template <typename Number>
inline constexpr void Conversion<Unit::Power, Unit::Power::Milliwatt>::ToStandard(
    Number& value) noexcept {
  value *= static_cast<Number>(0.001L);
}

template <>
template <typename Number>
inline constexpr void Conversion<Unit::Power, Unit::Power::Microwatt>::FromStandard(
    Number& value) noexcept {
  value *= static_cast<Number>(1000000.0L);
}

template <>
template <typename Number>
inline constexpr void Conversion<Unit::Power, Unit::Power::Microwatt>::ToStandard(
    Number& value) noexcept {
  value *= static_cast<Number>(0.000001L);
}

template <>
template <typename Number>
inline constexpr void Conversion<Unit::Power, Unit::Power::Nanowatt>::FromStandard(
    Number& value) noexcept {
  value *= static_cast<Number>(1000000000.0L);
}

template <>
template <typename Number>
inline constexpr void Conversion<Unit::Power, Unit::Power::Nanowatt>::ToStandard(
    Number& value) noexcept {
  value *= static_cast<Number>(0.000000001L);
}

template <>
template <typename Number>
inline constexpr void Conversion<Unit::Power, Unit::Power::Kilowatt>::FromStandard(
    Number& value) noexcept {
  value *= static_cast<Number>(0.001L);
}

template <>
template <typename Number>
inline constexpr void Conversion<Unit::Power, Unit::Power::Kilowatt>::ToStandard(
    Number& value) noexcept {
  value *= static_cast<Number>(1000.0L);
}

template <>
template <typename Number>
inline constexpr void Conversion<Unit::Power, Unit::Power::Megawatt>::FromStandard(
    Number& value) noexcept {
  value *= static_cast<Number>(0.000001L);
}

template <>
template <typename Number>
inline constexpr void Conversion<Unit::Power, Unit::Power::Megawatt>::ToStandard(
    Number& value) noexcept {
  value *= static_cast<Number>(1000000.0L);
}

template <>
template <typename Number>
inline constexpr void Conversion<Unit::Power, Unit::Power::Gigawatt>::FromStandard(
    Number& value) noexcept {
  value *= static_cast<Number>(0.000000001L);
}

template <>
template <typename Number>
inline constexpr void Conversion<Unit::Power, Unit::Power::Gigawatt>::ToStandard(
    Number& value) noexcept {
  value *= static_cast<Number>(1000000000.0L);
}

template <>
template <typename Number>
inline constexpr void Conversion<Unit::Power, Unit::Power::FootPoundPerSecond>::FromStandard(
    Number& value) noexcept {
  value /= (static_cast<Number>(0.3048L) * static_cast<Number>(0.45359237L)
            * static_cast<Number>(9.80665L));
}

template <>
template <typename Number>
inline constexpr void Conversion<Unit::Power, Unit::Power::FootPoundPerSecond>::ToStandard(
    Number& value) noexcept {
  value *= static_cast<Number>(0.3048L) * static_cast<Number>(0.45359237L)
           * static_cast<Number>(9.80665L);
}

template <>
template <typename Number>
inline constexpr void Conversion<Unit::Power, Unit::Power::InchPoundPerSecond>::FromStandard(
    Number& value) noexcept {
  value /= (static_cast<Number>(0.0254L) * static_cast<Number>(0.45359237L)
            * static_cast<Number>(9.80665L));
}

template <>
template <typename Number>
inline constexpr void Conversion<Unit::Power, Unit::Power::InchPoundPerSecond>::ToStandard(
    Number& value) noexcept {
  value *= static_cast<Number>(0.0254L) * static_cast<Number>(0.45359237L)
           * static_cast<Number>(9.80665L);
}

template <typename Number>
inline const std::map<Unit::Power, std::function<void(Number* values, const std::size_t size)>>
    MapOfConversionsFromStandard<Unit::Power, Number>{
        {Unit::Power::Watt,               Conversions<Unit::Power, Unit::Power::Watt>::FromStandard<Number>              },
        {Unit::Power::Milliwatt,
         Conversions<Unit::Power,                                  Unit::Power::Milliwatt>::FromStandard<Number>         },
        {Unit::Power::Microwatt,
         Conversions<Unit::Power,                                  Unit::Power::Microwatt>::FromStandard<Number>         },
        {Unit::Power::Nanowatt,
         Conversions<Unit::Power,                                  Unit::Power::Nanowatt>::FromStandard<Number>          },
        {Unit::Power::Kilowatt,
         Conversions<Unit::Power,                                  Unit::Power::Kilowatt>::FromStandard<Number>          },
        {Unit::Power::Megawatt,
         Conversions<Unit::Power,                                  Unit::Power::Megawatt>::FromStandard<Number>          },
        {Unit::Power::Gigawatt,
         Conversions<Unit::Power,                                  Unit::Power::Gigawatt>::FromStandard<Number>          },
        {Unit::Power::FootPoundPerSecond,
         Conversions<Unit::Power,                                  Unit::Power::FootPoundPerSecond>::FromStandard<Number>},
        {Unit::Power::InchPoundPerSecond,
         Conversions<Unit::Power,                                  Unit::Power::InchPoundPerSecond>::FromStandard<Number>},
};

template <typename Number>
inline const std::map<Unit::Power,
                      std::function<void(Number* const values, const std::size_t size)>>
    MapOfConversionsToStandard<Unit::Power, Number>{
        {Unit::Power::Watt,               Conversions<Unit::Power, Unit::Power::Watt>::ToStandard<Number>              },
        {Unit::Power::Milliwatt,
         Conversions<Unit::Power,                                  Unit::Power::Milliwatt>::ToStandard<Number>         },
        {Unit::Power::Microwatt,
         Conversions<Unit::Power,                                  Unit::Power::Microwatt>::ToStandard<Number>         },
        {Unit::Power::Nanowatt,
         Conversions<Unit::Power,                                  Unit::Power::Nanowatt>::ToStandard<Number>          },
        {Unit::Power::Kilowatt,
         Conversions<Unit::Power,                                  Unit::Power::Kilowatt>::ToStandard<Number>          },
        {Unit::Power::Megawatt,
         Conversions<Unit::Power,                                  Unit::Power::Megawatt>::ToStandard<Number>          },
        {Unit::Power::Gigawatt,
         Conversions<Unit::Power,                                  Unit::Power::Gigawatt>::ToStandard<Number>          },
        {Unit::Power::FootPoundPerSecond,
         Conversions<Unit::Power,                                  Unit::Power::FootPoundPerSecond>::ToStandard<Number>},
        {Unit::Power::InchPoundPerSecond,
         Conversions<Unit::Power,                                  Unit::Power::InchPoundPerSecond>::ToStandard<Number>},
};

}  // namespace Internal

}  // namespace PhQ

#endif  // PHQ_UNIT_POWER_HPP
