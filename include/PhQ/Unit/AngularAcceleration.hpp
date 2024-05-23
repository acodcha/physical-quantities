// Copyright © 2020-2024 Alexandre Coderre-Chabot
//
// This file is part of Physical Quantities (PhQ), a C++ library of physical quantities, physical
// models, and units of measure for scientific computation.
//
// Physical Quantities (PhQ) is hosted at:
//     https://github.com/acodcha/phq
//
// Physical Quantities (PhQ) is licensed under the MIT License:
//     https://mit-license.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute,
// sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM OUT
// OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef PHQ_UNIT_ANGULAR_ACCELERATION_HPP
#define PHQ_UNIT_ANGULAR_ACCELERATION_HPP

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
#include "../Dimension/LuminousIntensity.hpp"
#include "../Dimension/Mass.hpp"
#include "../Dimension/SubstanceAmount.hpp"
#include "../Dimension/Temperature.hpp"
#include "../Dimension/Time.hpp"
#include "../Dimensions.hpp"
#include "../Unit.hpp"
#include "../UnitSystem.hpp"

namespace PhQ {

namespace Unit {

/// \brief Angular acceleration units.
enum class AngularAcceleration : int8_t {
  /// \brief Radian per square second (rad/s^2) angular acceleration unit.
  RadianPerSquareSecond,

  /// \brief Radian per square minute (rad/min^2) angular acceleration unit.
  RadianPerSquareMinute,

  /// \brief Radian per square hour (rad/hr^2) angular acceleration unit.
  RadianPerSquareHour,

  /// \brief Degree per square second (deg/s^2) angular acceleration unit.
  DegreePerSquareSecond,

  /// \brief Degree per square minute (deg/min^2) angular acceleration unit.
  DegreePerSquareMinute,

  /// \brief Degree per square hour (deg/hr^2) angular acceleration unit.
  DegreePerSquareHour,

  /// \brief Arcminute per square second (arcmin/s^2) angular acceleration unit.
  ArcminutePerSquareSecond,

  /// \brief Arcminute per square minute (arcmin/min^2) angular acceleration unit.
  ArcminutePerSquareMinute,

  /// \brief Arcminute per square hour (arcmin/hr^2) angular acceleration unit.
  ArcminutePerSquareHour,

  /// \brief Arcsecond per square second (arcsec/s^2) angular acceleration unit.
  ArcsecondPerSquareSecond,

  /// \brief Arcsecond per square minute (arcsec/min^2) angular acceleration unit.
  ArcsecondPerSquareMinute,

  /// \brief Arcsecond per square hour (arcsec/hr^2) angular acceleration unit.
  ArcsecondPerSquareHour,

  /// \brief Revolution per square second (rev/s^2) angular acceleration unit.
  RevolutionPerSquareSecond,

  /// \brief Revolution per square minute (rev/min^2) angular acceleration unit.
  RevolutionPerSquareMinute,

  /// \brief Revolution per square hour (rev/hr^2) angular acceleration unit.
  RevolutionPerSquareHour,
};

}  // namespace Unit

/// \brief Standard angular acceleration unit: radian per square second (rad/s^2).
template <>
inline constexpr const Unit::AngularAcceleration Standard<Unit::AngularAcceleration>{
    Unit::AngularAcceleration::RadianPerSquareSecond};

/// \brief Physical dimension set of angular acceleration units.
template <>
inline constexpr const Dimensions RelatedDimensions<Unit::AngularAcceleration>{
    Dimensions{Dimension::Time{-2}, Dimension::Length{0}, Dimension::Mass{0},
               Dimension::ElectricCurrent{0}, Dimension::Temperature{0},
               Dimension::SubstanceAmount{0}, Dimension::LuminousIntensity{0}}
};

inline std::ostream& operator<<(std::ostream& stream, const Unit::AngularAcceleration unit) {
  stream << Abbreviation(unit);
  return stream;
}

namespace Internal {

template <>
inline const std::map<UnitSystem, Unit::AngularAcceleration>
    ConsistentUnits<Unit::AngularAcceleration>{
        {UnitSystem::MetreKilogramSecondKelvin,  Unit::AngularAcceleration::RadianPerSquareSecond},
        {UnitSystem::MillimetreGramSecondKelvin, Unit::AngularAcceleration::RadianPerSquareSecond},
        {UnitSystem::FootPoundSecondRankine,     Unit::AngularAcceleration::RadianPerSquareSecond},
        {UnitSystem::InchPoundSecondRankine,     Unit::AngularAcceleration::RadianPerSquareSecond},
};

template <>
inline const std::map<Unit::AngularAcceleration, UnitSystem>
    RelatedUnitSystems<Unit::AngularAcceleration>{};

template <>
inline const std::map<Unit::AngularAcceleration, std::string_view>
    Abbreviations<Unit::AngularAcceleration>{
        {Unit::AngularAcceleration::RadianPerSquareSecond,     "rad/s^2"     },
        {Unit::AngularAcceleration::RadianPerSquareMinute,     "rad/min^2"   },
        {Unit::AngularAcceleration::RadianPerSquareHour,       "rad/hr^2"    },
        {Unit::AngularAcceleration::DegreePerSquareSecond,     "deg/s^2"     },
        {Unit::AngularAcceleration::DegreePerSquareMinute,     "deg/min^2"   },
        {Unit::AngularAcceleration::DegreePerSquareHour,       "deg/hr^2"    },
        {Unit::AngularAcceleration::ArcminutePerSquareSecond,  "arcmin/s^2"  },
        {Unit::AngularAcceleration::ArcminutePerSquareMinute,  "arcmin/min^2"},
        {Unit::AngularAcceleration::ArcminutePerSquareHour,    "arcmin/hr^2" },
        {Unit::AngularAcceleration::ArcsecondPerSquareSecond,  "arcsec/s^2"  },
        {Unit::AngularAcceleration::ArcsecondPerSquareMinute,  "arcsec/min^2"},
        {Unit::AngularAcceleration::ArcsecondPerSquareHour,    "arcsec/hr^2" },
        {Unit::AngularAcceleration::RevolutionPerSquareSecond, "rev/s^2"     },
        {Unit::AngularAcceleration::RevolutionPerSquareMinute, "rev/min^2"   },
        {Unit::AngularAcceleration::RevolutionPerSquareHour,   "rev/hr^2"    },
};

template <>
inline const std::unordered_map<std::string_view, Unit::AngularAcceleration> Spellings<
    Unit::AngularAcceleration>{
    {"rad/s^2",        Unit::AngularAcceleration::RadianPerSquareSecond    },
    {"rad/s2",         Unit::AngularAcceleration::RadianPerSquareSecond    },
    {"rad/s/s",        Unit::AngularAcceleration::RadianPerSquareSecond    },
    {"rad/min^2",      Unit::AngularAcceleration::RadianPerSquareMinute    },
    {"rad/min2",       Unit::AngularAcceleration::RadianPerSquareMinute    },
    {"rad/min/min",    Unit::AngularAcceleration::RadianPerSquareMinute    },
    {"rad/hr^2",       Unit::AngularAcceleration::RadianPerSquareHour      },
    {"rad/hr2",        Unit::AngularAcceleration::RadianPerSquareHour      },
    {"rad/hr/hr",      Unit::AngularAcceleration::RadianPerSquareHour      },
    {"°/s^2",          Unit::AngularAcceleration::DegreePerSquareSecond    },
    {"°/s2",           Unit::AngularAcceleration::DegreePerSquareSecond    },
    {"°/s/s",          Unit::AngularAcceleration::DegreePerSquareSecond    },
    {"deg/s^2",        Unit::AngularAcceleration::DegreePerSquareSecond    },
    {"deg/s2",         Unit::AngularAcceleration::DegreePerSquareSecond    },
    {"deg/s/s",        Unit::AngularAcceleration::DegreePerSquareSecond    },
    {"°/min^2",        Unit::AngularAcceleration::DegreePerSquareMinute    },
    {"°/min2",         Unit::AngularAcceleration::DegreePerSquareMinute    },
    {"°/min/min",      Unit::AngularAcceleration::DegreePerSquareMinute    },
    {"deg/min^2",      Unit::AngularAcceleration::DegreePerSquareMinute    },
    {"deg/min2",       Unit::AngularAcceleration::DegreePerSquareMinute    },
    {"deg/min/min",    Unit::AngularAcceleration::DegreePerSquareMinute    },
    {"°/hr^2",         Unit::AngularAcceleration::DegreePerSquareHour      },
    {"°/hr2",          Unit::AngularAcceleration::DegreePerSquareHour      },
    {"°/hr/hr",        Unit::AngularAcceleration::DegreePerSquareHour      },
    {"deg/hr^2",       Unit::AngularAcceleration::DegreePerSquareHour      },
    {"deg/hr2",        Unit::AngularAcceleration::DegreePerSquareHour      },
    {"deg/hr/hr",      Unit::AngularAcceleration::DegreePerSquareHour      },
    {"arcmin/s^2",     Unit::AngularAcceleration::ArcminutePerSquareSecond },
    {"arcmin/s2",      Unit::AngularAcceleration::ArcminutePerSquareSecond },
    {"arcmin/s/s",     Unit::AngularAcceleration::ArcminutePerSquareSecond },
    {"arcmin/min^2",   Unit::AngularAcceleration::ArcminutePerSquareMinute },
    {"arcmin/min2",    Unit::AngularAcceleration::ArcminutePerSquareMinute },
    {"arcmin/min/min", Unit::AngularAcceleration::ArcminutePerSquareMinute },
    {"arcmin/hr^2",    Unit::AngularAcceleration::ArcminutePerSquareHour   },
    {"arcmin/hr2",     Unit::AngularAcceleration::ArcminutePerSquareHour   },
    {"arcmin/hr/hr",   Unit::AngularAcceleration::ArcminutePerSquareHour   },
    {"arcsec/s^2",     Unit::AngularAcceleration::ArcsecondPerSquareSecond },
    {"arcsec/s2",      Unit::AngularAcceleration::ArcsecondPerSquareSecond },
    {"arcsec/s/s",     Unit::AngularAcceleration::ArcsecondPerSquareSecond },
    {"arcsec/min^2",   Unit::AngularAcceleration::ArcsecondPerSquareMinute },
    {"arcsec/min2",    Unit::AngularAcceleration::ArcsecondPerSquareMinute },
    {"arcsec/min/min", Unit::AngularAcceleration::ArcsecondPerSquareMinute },
    {"arcsec/hr^2",    Unit::AngularAcceleration::ArcsecondPerSquareHour   },
    {"arcsec/hr2",     Unit::AngularAcceleration::ArcsecondPerSquareHour   },
    {"arcsec/hr/hr",   Unit::AngularAcceleration::ArcsecondPerSquareHour   },
    {"rev/s^2",        Unit::AngularAcceleration::RevolutionPerSquareSecond},
    {"rev/s2",         Unit::AngularAcceleration::RevolutionPerSquareSecond},
    {"rev/s/s",        Unit::AngularAcceleration::RevolutionPerSquareSecond},
    {"rev/min^2",      Unit::AngularAcceleration::RevolutionPerSquareMinute},
    {"rev/min2",       Unit::AngularAcceleration::RevolutionPerSquareMinute},
    {"rev/min/min",    Unit::AngularAcceleration::RevolutionPerSquareMinute},
    {"rev/hr^2",       Unit::AngularAcceleration::RevolutionPerSquareHour  },
    {"rev/hr2",        Unit::AngularAcceleration::RevolutionPerSquareHour  },
    {"rev/hr/hr",      Unit::AngularAcceleration::RevolutionPerSquareHour  },
};

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::RadianPerSquareSecond>::
    FromStandard(Number& /*value*/) noexcept {}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::RadianPerSquareSecond>::ToStandard(
    Number& /*value*/) noexcept {}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration,
           Unit::AngularAcceleration::RadianPerSquareMinute>::FromStandard(Number& value) noexcept {
  value *= static_cast<Number>(3600.0L);
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::RadianPerSquareMinute>::ToStandard(
    Number& value) noexcept {
  value /= static_cast<Number>(3600.0L);
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::RadianPerSquareHour>::FromStandard(
    Number& value) noexcept {
  value *= static_cast<Number>(12960000.0L);
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::RadianPerSquareHour>::ToStandard(
    Number& value) noexcept {
  value /= static_cast<Number>(12960000.0L);
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration,
           Unit::AngularAcceleration::DegreePerSquareSecond>::FromStandard(Number& value) noexcept {
  value *= static_cast<Number>(180.0L) / Pi<Number>;
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::DegreePerSquareSecond>::ToStandard(
    Number& value) noexcept {
  value *= Pi<Number> / static_cast<Number>(180.0L);
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration,
           Unit::AngularAcceleration::DegreePerSquareMinute>::FromStandard(Number& value) noexcept {
  value *= static_cast<Number>(648000.0L) / Pi<Number>;
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::DegreePerSquareMinute>::ToStandard(
    Number& value) noexcept {
  value *= Pi<Number> / static_cast<Number>(648000.0L);
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::DegreePerSquareHour>::FromStandard(
    Number& value) noexcept {
  value *= static_cast<Number>(2332800000.0L) / Pi<Number>;
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::DegreePerSquareHour>::ToStandard(
    Number& value) noexcept {
  value *= Pi<Number> / static_cast<Number>(2332800000.0L);
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::ArcminutePerSquareSecond>::
    FromStandard(Number& value) noexcept {
  value *= static_cast<Number>(10800.0L) / Pi<Number>;
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::ArcminutePerSquareSecond>::
    ToStandard(Number& value) noexcept {
  value *= Pi<Number> / static_cast<Number>(10800.0L);
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::ArcminutePerSquareMinute>::
    FromStandard(Number& value) noexcept {
  value *= static_cast<Number>(38880000.0L) / Pi<Number>;
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::ArcminutePerSquareMinute>::
    ToStandard(Number& value) noexcept {
  value *= Pi<Number> / static_cast<Number>(38880000.0L);
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::ArcminutePerSquareHour>::
    FromStandard(Number& value) noexcept {
  value *= static_cast<Number>(139968000000.0L) / Pi<Number>;
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration,
           Unit::AngularAcceleration::ArcminutePerSquareHour>::ToStandard(Number& value) noexcept {
  value *= Pi<Number> / static_cast<Number>(139968000000.0L);
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::ArcsecondPerSquareSecond>::
    FromStandard(Number& value) noexcept {
  value *= static_cast<Number>(648000.0L) / Pi<Number>;
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::ArcsecondPerSquareSecond>::
    ToStandard(Number& value) noexcept {
  value *= Pi<Number> / static_cast<Number>(648000.0L);
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::ArcsecondPerSquareMinute>::
    FromStandard(Number& value) noexcept {
  value *= static_cast<Number>(2332800000.0L) / Pi<Number>;
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::ArcsecondPerSquareMinute>::
    ToStandard(Number& value) noexcept {
  value *= Pi<Number> / static_cast<Number>(2332800000.0L);
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::ArcsecondPerSquareHour>::
    FromStandard(Number& value) noexcept {
  value *= static_cast<Number>(8398080000000.0L) / Pi<Number>;
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration,
           Unit::AngularAcceleration::ArcsecondPerSquareHour>::ToStandard(Number& value) noexcept {
  value *= Pi<Number> / static_cast<Number>(8398080000000.0L);
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::RevolutionPerSquareSecond>::
    FromStandard(Number& value) noexcept {
  value *= static_cast<Number>(0.5L) / Pi<Number>;
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::RevolutionPerSquareSecond>::
    ToStandard(Number& value) noexcept {
  value *= static_cast<Number>(2.0L) * Pi<Number>;
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::RevolutionPerSquareMinute>::
    FromStandard(Number& value) noexcept {
  value *= static_cast<Number>(1800.0L) / Pi<Number>;
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::RevolutionPerSquareMinute>::
    ToStandard(Number& value) noexcept {
  value *= Pi<Number> / static_cast<Number>(1800.0L);
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration, Unit::AngularAcceleration::RevolutionPerSquareHour>::
    FromStandard(Number& value) noexcept {
  value *= static_cast<Number>(6480000.0L) / Pi<Number>;
}

template <>
template <typename Number>
inline constexpr void
Conversion<Unit::AngularAcceleration,
           Unit::AngularAcceleration::RevolutionPerSquareHour>::ToStandard(Number& value) noexcept {
  value *= Pi<Number> / static_cast<Number>(6480000.0L);
}

template <typename Number>
inline const std::map<Unit::AngularAcceleration,
                      std::function<void(Number* values, const std::size_t size)>>
    MapOfConversionsFromStandard<Unit::AngularAcceleration, Number>{
        {Unit::AngularAcceleration::RadianPerSquareSecond,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::RadianPerSquareSecond>::FromStandard<Number>    },
        {Unit::AngularAcceleration::RadianPerSquareMinute,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::RadianPerSquareMinute>::FromStandard<Number>    },
        {Unit::AngularAcceleration::RadianPerSquareHour,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::RadianPerSquareHour>::FromStandard<Number>      },
        {Unit::AngularAcceleration::DegreePerSquareSecond,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::DegreePerSquareSecond>::FromStandard<Number>    },
        {Unit::AngularAcceleration::DegreePerSquareMinute,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::DegreePerSquareMinute>::FromStandard<Number>    },
        {Unit::AngularAcceleration::DegreePerSquareHour,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::DegreePerSquareHour>::FromStandard<Number>      },
        {Unit::AngularAcceleration::ArcminutePerSquareSecond,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::ArcminutePerSquareSecond>::FromStandard<Number> },
        {Unit::AngularAcceleration::ArcminutePerSquareMinute,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::ArcminutePerSquareMinute>::FromStandard<Number> },
        {Unit::AngularAcceleration::ArcminutePerSquareHour,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::ArcminutePerSquareHour>::FromStandard<Number>   },
        {Unit::AngularAcceleration::ArcsecondPerSquareSecond,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::ArcsecondPerSquareSecond>::FromStandard<Number> },
        {Unit::AngularAcceleration::ArcsecondPerSquareMinute,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::ArcsecondPerSquareMinute>::FromStandard<Number> },
        {Unit::AngularAcceleration::ArcsecondPerSquareHour,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::ArcsecondPerSquareHour>::FromStandard<Number>   },
        {Unit::AngularAcceleration::RevolutionPerSquareSecond,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::RevolutionPerSquareSecond>::FromStandard<Number>},
        {Unit::AngularAcceleration::RevolutionPerSquareMinute,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::RevolutionPerSquareMinute>::FromStandard<Number>},
        {Unit::AngularAcceleration::RevolutionPerSquareHour,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::RevolutionPerSquareHour>::FromStandard<Number>  },
};

template <typename Number>
inline const std::map<Unit::AngularAcceleration,
                      std::function<void(Number* const values, const std::size_t size)>>
    MapOfConversionsToStandard<Unit::AngularAcceleration, Number>{
        {Unit::AngularAcceleration::RadianPerSquareSecond,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::RadianPerSquareSecond>::ToStandard<Number>    },
        {Unit::AngularAcceleration::RadianPerSquareMinute,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::RadianPerSquareMinute>::ToStandard<Number>    },
        {Unit::AngularAcceleration::RadianPerSquareHour,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::RadianPerSquareHour>::ToStandard<Number>      },
        {Unit::AngularAcceleration::DegreePerSquareSecond,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::DegreePerSquareSecond>::ToStandard<Number>    },
        {Unit::AngularAcceleration::DegreePerSquareMinute,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::DegreePerSquareMinute>::ToStandard<Number>    },
        {Unit::AngularAcceleration::DegreePerSquareHour,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::DegreePerSquareHour>::ToStandard<Number>      },
        {Unit::AngularAcceleration::ArcminutePerSquareSecond,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::ArcminutePerSquareSecond>::ToStandard<Number> },
        {Unit::AngularAcceleration::ArcminutePerSquareMinute,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::ArcminutePerSquareMinute>::ToStandard<Number> },
        {Unit::AngularAcceleration::ArcminutePerSquareHour,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::ArcminutePerSquareHour>::ToStandard<Number>   },
        {Unit::AngularAcceleration::ArcsecondPerSquareSecond,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::ArcsecondPerSquareSecond>::ToStandard<Number> },
        {Unit::AngularAcceleration::ArcsecondPerSquareMinute,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::ArcsecondPerSquareMinute>::ToStandard<Number> },
        {Unit::AngularAcceleration::ArcsecondPerSquareHour,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::ArcsecondPerSquareHour>::ToStandard<Number>   },
        {Unit::AngularAcceleration::RevolutionPerSquareSecond,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::RevolutionPerSquareSecond>::ToStandard<Number>},
        {Unit::AngularAcceleration::RevolutionPerSquareMinute,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::RevolutionPerSquareMinute>::ToStandard<Number>},
        {Unit::AngularAcceleration::RevolutionPerSquareHour,
         Conversions<Unit::AngularAcceleration,
         Unit::AngularAcceleration::RevolutionPerSquareHour>::ToStandard<Number>  },
};

}  // namespace Internal

}  // namespace PhQ

#endif  // PHQ_UNIT_ANGULAR_ACCELERATION_HPP
