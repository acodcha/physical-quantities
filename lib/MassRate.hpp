// Copyright 2020 Alexandre Coderre-Chabot
// This file is part of PhysicalQuantities, a C++17 library of physical quantities, units of measure, and related concepts for scientific computation.
// PhysicalQuantities is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// PhysicalQuantities is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
// You should have received a copy of the GNU Lesser General Public License along with PhysicalQuantities. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "Frequency.hpp"
#include "Mass.hpp"
#include "Unit/MassRate.hpp"

namespace PhQ {

class MassRate : public DimensionalScalarQuantity<Unit::MassRate> {

public:

  constexpr MassRate() noexcept : DimensionalScalarQuantity<Unit::MassRate>() {}

  constexpr MassRate(double value, Unit::MassRate unit) noexcept : DimensionalScalarQuantity<Unit::MassRate>(value, unit) {}

  constexpr bool operator==(const MassRate& mass_rate) const noexcept {
    return value_ == mass_rate.value_;
  }

  constexpr bool operator!=(const MassRate& mass_rate) const noexcept {
    return value_ != mass_rate.value_;
  }

  constexpr bool operator<(const MassRate& mass_rate) const noexcept {
    return value_ < mass_rate.value_;
  }

  constexpr bool operator<=(const MassRate& mass_rate) const noexcept {
    return value_ <= mass_rate.value_;
  }

  constexpr bool operator>(const MassRate& mass_rate) const noexcept {
    return value_ > mass_rate.value_;
  }

  constexpr bool operator>=(const MassRate& mass_rate) const noexcept {
    return value_ >= mass_rate.value_;
  }

  MassRate operator+(const MassRate& mass_rate) const noexcept {
    return {value_ + mass_rate.value_};
  }

  constexpr void operator+=(const MassRate& mass_rate) noexcept {
    value_ += mass_rate.value_;
  }

  MassRate operator-(const MassRate& mass_rate) const noexcept {
    return {value_ - mass_rate.value_};
  }

  constexpr void operator-=(const MassRate& mass_rate) noexcept {
    value_ -= mass_rate.value_;
  }

  constexpr Mass operator*(const Duration& duration) const noexcept {
    return {value_ * duration.value_};
  }

  Mass operator/(const Frequency& frequency) const {
    if (frequency.value_ != 0.0) {
      return {value_ / frequency.value_};
    } else {
      throw std::runtime_error{"Division of " + print() + " by " + frequency.print() + "."};
    }
  }

  Frequency operator/(const Mass& mass) const {
    if (mass.value_ != 0.0) {
      return {value_ / mass.value_};
    } else {
      throw std::runtime_error{"Division of " + print() + " by " + mass.print() + "."};
    }
  }

protected:

  constexpr MassRate(double value) noexcept : DimensionalScalarQuantity<Unit::MassRate>(value) {}

  friend class Duration;
  friend class Frequency;
  friend class Mass;

};

template <> constexpr bool sort(const MassRate& mass_rate_1, const MassRate& mass_rate_2) noexcept {
  return mass_rate_1.value() < mass_rate_2.value();
}

constexpr Mass Duration::operator*(const MassRate& mass_rate) const noexcept {
  return {value_ * mass_rate.value_};
}

constexpr MassRate Mass::operator*(const Frequency& frequency) const noexcept {
  return {value_ * frequency.value_};
}

constexpr MassRate Frequency::operator*(const Mass& mass) const noexcept {
  return {value_ * mass.value_};
}

MassRate Mass::operator/(const Duration& duration) const {
  if (duration.value_ != 0.0) {
    return {value_ / duration.value_};
  } else {
    throw std::runtime_error{"Division of " + print() + " by " + duration.print() + "."};
  }
}

} // namespace PhQ
