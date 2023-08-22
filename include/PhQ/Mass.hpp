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

#ifndef PHYSICAL_QUANTITIES_INCLUDE_PHQ_MASS_HPP
#define PHYSICAL_QUANTITIES_INCLUDE_PHQ_MASS_HPP

#include "DimensionalScalarQuantity.hpp"
#include "Unit/Mass.hpp"

namespace PhQ {

// Forward declarations for class Mass.
class Time;
class Energy;
class Frequency;
class GasConstant;
class IsobaricHeatCapacity;
class IsochoricHeatCapacity;
class MassDensity;
class MassRate;
class Power;
class SpecificEnergy;
class SpecificGasConstant;
class SpecificIsobaricHeatCapacity;
class SpecificIsochoricHeatCapacity;
class SpecificPower;
class Volume;

// Mass.
class Mass : public DimensionalScalarQuantity<Unit::Mass> {
public:
  constexpr Mass() noexcept : DimensionalScalarQuantity<Unit::Mass>() {}

  Mass(const double value, const Unit::Mass unit) noexcept
    : DimensionalScalarQuantity<Unit::Mass>(value, unit) {}

  constexpr Mass(
      const MassDensity& mass_density, const Volume& volume) noexcept;

  constexpr Mass(const MassRate& mass_rate, const Time& time) noexcept;

  constexpr Mass(
      const MassRate& mass_rate, const Frequency& frequency) noexcept;

  constexpr Mass(
      const SpecificEnergy& specific_energy, const Energy& energy) noexcept;

  constexpr Mass(
      const SpecificPower& specific_power, const Power& power) noexcept;

  constexpr Mass(const SpecificGasConstant& specific_gas_constant,
                 const GasConstant& gas_constant) noexcept;

  constexpr Mass(
      const SpecificIsobaricHeatCapacity& specific_isobaric_heat_capacity,
      const IsobaricHeatCapacity& isobaric_heat_capacity) noexcept;

  constexpr Mass(
      const SpecificIsochoricHeatCapacity& specific_isochoric_heat_capacity,
      const IsochoricHeatCapacity& isochoric_heat_capacity) noexcept;

  static constexpr Mass Zero() noexcept { return Mass{0.0}; }

  template<Unit::Mass Unit>
  static constexpr Mass Create(const double value) noexcept {
    return Mass{
        StaticConvertCopy<Unit::Mass, Unit, Standard<Unit::Mass>>(value)};
  }

  constexpr Mass operator+(const Mass& mass) const noexcept {
    return Mass{value_ + mass.value_};
  }

  constexpr Mass operator-(const Mass& mass) const noexcept {
    return Mass{value_ - mass.value_};
  }

  constexpr Mass operator*(const double number) const noexcept {
    return Mass{value_ * number};
  }

  constexpr MassRate operator*(const Frequency& frequency) const noexcept;

  constexpr Energy operator*(
      const SpecificEnergy& specific_energy) const noexcept;

  constexpr Power operator*(const SpecificPower& specific_power) const noexcept;

  constexpr IsobaricHeatCapacity
  operator*(const SpecificIsobaricHeatCapacity& specific_isobaric_heat_capacity)
      const noexcept;

  constexpr IsochoricHeatCapacity operator*(
      const SpecificIsochoricHeatCapacity& specific_isochoric_heat_capacity)
      const noexcept;

  constexpr GasConstant operator*(
      const SpecificGasConstant& specific_gas_constant) const noexcept;

  constexpr Mass operator/(const double number) const noexcept {
    return Mass{value_ / number};
  }

  constexpr MassDensity operator/(const Volume& volume) const noexcept;

  constexpr MassRate operator/(const Time& time) const noexcept;

  constexpr Time operator/(const MassRate& mass_rate) const noexcept;

  constexpr double operator/(const Mass& mass) const noexcept {
    return value_ / mass.value_;
  }

  constexpr void operator+=(const Mass& mass) noexcept {
    value_ += mass.value_;
  }

  constexpr void operator-=(const Mass& mass) noexcept {
    value_ -= mass.value_;
  }

  constexpr void operator*=(const double number) noexcept { value_ *= number; }

  constexpr void operator/=(const double number) noexcept { value_ /= number; }

private:
  explicit constexpr Mass(const double value) noexcept
    : DimensionalScalarQuantity<Unit::Mass>(value) {}
};

inline constexpr bool operator==(const Mass& left, const Mass& right) noexcept {
  return left.Value() == right.Value();
}

inline constexpr bool operator!=(const Mass& left, const Mass& right) noexcept {
  return left.Value() != right.Value();
}

inline constexpr bool operator<(const Mass& left, const Mass& right) noexcept {
  return left.Value() < right.Value();
}

inline constexpr bool operator>(const Mass& left, const Mass& right) noexcept {
  return left.Value() > right.Value();
}

inline constexpr bool operator<=(const Mass& left, const Mass& right) noexcept {
  return left.Value() <= right.Value();
}

inline constexpr bool operator>=(const Mass& left, const Mass& right) noexcept {
  return left.Value() >= right.Value();
}

inline std::ostream& operator<<(
    std::ostream& stream, const Mass& mass) noexcept {
  stream << mass.Print();
  return stream;
}

inline constexpr Mass operator*(
    const double number, const Mass& mass) noexcept {
  return mass * number;
}

}  // namespace PhQ

namespace std {

template<> struct hash<PhQ::Mass> {
  inline size_t operator()(const PhQ::Mass& mass) const {
    return hash<double>()(mass.Value());
  }
};

}  // namespace std

#endif  // PHYSICAL_QUANTITIES_INCLUDE_PHQ_MASS_HPP
