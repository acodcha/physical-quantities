// Copyright 2020-2023 Alexandre Coderre-Chabot
// This file is part of Physical Quantities (PhQ), a C++17 header-only library of physical quantities, physical models, and units of measure for scientific computation.
// Physical Quantities is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// Physical Quantities is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
// You should have received a copy of the GNU Lesser General Public License along with Physical Quantities. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "SpecificEnergy.hpp"
#include "Unit/SpecificPower.hpp"

namespace PhQ {

class SpecificPower : public DimensionalScalarQuantity<Unit::SpecificPower> {

public:

  constexpr SpecificPower() noexcept : DimensionalScalarQuantity<Unit::SpecificPower>() {}

  SpecificPower(double value, Unit::SpecificPower unit) noexcept : DimensionalScalarQuantity<Unit::SpecificPower>(value, unit) {}

  constexpr SpecificPower(const SpecificEnergy& specific_energy, const Time& time) noexcept : SpecificPower(specific_energy.Value() / time.Value()) {}

  constexpr SpecificPower(const SpecificEnergy& specific_energy, const Frequency& frequency) noexcept : SpecificPower(specific_energy.Value() * frequency.Value()) {}

  constexpr SpecificPower(const Power& power, const Mass& mass) noexcept : SpecificPower(power.Value() / mass.Value()) {}

  constexpr bool operator==(const SpecificPower& specific_power) const noexcept {
    return value_ == specific_power.value_;
  }

  constexpr bool operator!=(const SpecificPower& specific_power) const noexcept {
    return value_ != specific_power.value_;
  }

  constexpr bool operator<(const SpecificPower& specific_power) const noexcept {
    return value_ < specific_power.value_;
  }

  constexpr bool operator<=(const SpecificPower& specific_power) const noexcept {
    return value_ <= specific_power.value_;
  }

  constexpr bool operator>(const SpecificPower& specific_power) const noexcept {
    return value_ > specific_power.value_;
  }

  constexpr bool operator>=(const SpecificPower& specific_power) const noexcept {
    return value_ >= specific_power.value_;
  }

  SpecificPower operator+(const SpecificPower& specific_power) const noexcept {
    return {value_ + specific_power.value_};
  }

  constexpr void operator+=(const SpecificPower& specific_power) noexcept {
    value_ += specific_power.value_;
  }

  SpecificPower operator-(const SpecificPower& specific_power) const noexcept {
    return {value_ - specific_power.value_};
  }

  constexpr void operator-=(const SpecificPower& specific_power) noexcept {
    value_ -= specific_power.value_;
  }

  SpecificEnergy operator*(const Time& time) const noexcept {
    return {*this, time};
  }

  Power operator*(const Mass& mass) const noexcept {
    return {*this, mass};
  }

  SpecificEnergy operator/(const Frequency& frequency) const noexcept {
    return {*this, frequency};
  }

  Frequency operator/(const SpecificEnergy& specific_energy) const noexcept {
    return {*this, specific_energy};
  }

protected:

  constexpr SpecificPower(double value) noexcept : DimensionalScalarQuantity<Unit::SpecificPower>(value) {}

};

constexpr Time::Time(const SpecificPower& specific_power, const SpecificEnergy& specific_energy) noexcept : Time(specific_energy.Value() / specific_power.Value()) {}

constexpr Frequency::Frequency(const SpecificPower& specific_power, const SpecificEnergy& specific_energy) noexcept : Frequency(specific_power.Value() / specific_energy.Value()) {}

constexpr Mass::Mass(const SpecificPower& specific_power, const Power& power) noexcept : Mass(power.Value() / specific_power.Value()) {}

constexpr Power::Power(const SpecificPower& specific_power, const Mass& mass) noexcept : Power(specific_power.Value() * mass.Value()) {}

constexpr SpecificEnergy::SpecificEnergy(const SpecificPower& specific_power, const Time& time) noexcept : SpecificEnergy(specific_power.Value() * time.Value()) {}

constexpr SpecificEnergy::SpecificEnergy(const SpecificPower& specific_power, const Frequency& frequency) noexcept : SpecificEnergy(specific_power.Value() / frequency.Value()) {}

Power Mass::operator*(const SpecificPower& specific_power) const noexcept {
  return {specific_power, *this};
}

Mass Power::operator/(const SpecificPower& specific_power) const noexcept {
  return {specific_power, *this};
}

SpecificEnergy Time::operator*(const SpecificPower& specific_power) const noexcept {
  return {specific_power, *this};
}

SpecificPower Frequency::operator*(const SpecificEnergy& specific_energy) const noexcept {
  return {specific_energy, *this};
}

SpecificPower Power::operator/(const Mass& mass) const noexcept {
  return {*this, mass};
}

SpecificPower SpecificEnergy::operator*(const Frequency& frequency) const noexcept {
  return {*this, frequency};
}

SpecificPower SpecificEnergy::operator/(const Time& time) const noexcept {
  return {*this, time};
}

Time SpecificEnergy::operator/(const SpecificPower& specific_power) const noexcept {
  return {specific_power, *this};
}

} // namespace PhQ

namespace std {

template <> struct hash<PhQ::SpecificPower> {
  size_t operator()(const PhQ::SpecificPower& specific_power) const {
    return hash<double>()(specific_power.Value());
  }
};

} // namespace std
