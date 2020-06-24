// Copyright 2020 Alexandre Coderre-Chabot
// This file is part of PhysicalQuantities, a C++17 library of physical quantities, units of measure, and related concepts for scientific computation.
// PhysicalQuantities is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// PhysicalQuantities is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
// You should have received a copy of the GNU Lesser General Public License along with PhysicalQuantities. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "Area.hpp"
#include "Unit/Force.hpp"

namespace PhQ {

// Forward declarations.
class Direction;
class Force;
class StaticPressure;

class ForceMagnitude : public DimensionalScalarQuantity<Unit::Force> {

public:

  constexpr ForceMagnitude() noexcept : DimensionalScalarQuantity<Unit::Force>() {}

  constexpr ForceMagnitude(double value, Unit::Force unit) noexcept : DimensionalScalarQuantity<Unit::Force>(value, unit) {}

  constexpr ForceMagnitude(const Force& force) noexcept;

  constexpr ForceMagnitude(const StaticPressure& static_pressure, const Area& area) noexcept;

  constexpr bool operator==(const ForceMagnitude& force_magnitude) const noexcept {
    return value_ == force_magnitude.value_;
  }

  constexpr bool operator!=(const ForceMagnitude& force_magnitude) const noexcept {
    return value_ != force_magnitude.value_;
  }

  constexpr bool operator<(const ForceMagnitude& force_magnitude) const noexcept {
    return value_ < force_magnitude.value_;
  }

  constexpr bool operator<=(const ForceMagnitude& force_magnitude) const noexcept {
    return value_ <= force_magnitude.value_;
  }

  constexpr bool operator>(const ForceMagnitude& force_magnitude) const noexcept {
    return value_ > force_magnitude.value_;
  }

  constexpr bool operator>=(const ForceMagnitude& force_magnitude) const noexcept {
    return value_ >= force_magnitude.value_;
  }

  constexpr ForceMagnitude operator+(const ForceMagnitude& force_magnitude) const noexcept {
    return {value_ + force_magnitude.value_};
  }

  constexpr void operator+=(const ForceMagnitude& force_magnitude) noexcept {
    value_ += force_magnitude.value_;
  }

  constexpr ForceMagnitude operator-(const ForceMagnitude& force_magnitude) const noexcept {
    return {value_ - force_magnitude.value_};
  }

  constexpr void operator-=(const ForceMagnitude& force_magnitude) noexcept {
    value_ -= force_magnitude.value_;
  }

  constexpr Force operator*(const Direction& direction) const noexcept;

  constexpr StaticPressure operator/(const Area& area) const noexcept;

protected:

  constexpr ForceMagnitude(double value) noexcept : DimensionalScalarQuantity<Unit::Force>(value) {}

};

template <> constexpr bool sort(const ForceMagnitude& force_magnitude_1, const ForceMagnitude& force_magnitude_2) noexcept {
  return sort(force_magnitude_1.value(), force_magnitude_2.value());
}

} // namespace PhQ