// Copyright 2020 Alexandre Coderre-Chabot
// This file is part of PhysicalQuantities, a C++17 library of physical quantities, units of measure, and related concepts for scientific computation.
// PhysicalQuantities is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// PhysicalQuantities is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
// You should have received a copy of the GNU Lesser General Public License along with PhysicalQuantities. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "Quantity/DimensionlessSymmetricDyadic.hpp"

namespace PhQ {

class Duration;
class Frequency;
class StrainRate;

class Strain : public DimensionlessSymmetricDyadicQuantity {

public:

  Strain() noexcept : DimensionlessSymmetricDyadicQuantity() {}

  constexpr Strain(const Value::SymmetricDyadic& value) noexcept : DimensionlessSymmetricDyadicQuantity(value) {}

  constexpr bool operator==(const Strain& strain) const noexcept {
    return value_ == strain.value_;
  }

  constexpr bool operator!=(const Strain& strain) const noexcept {
    return value_ != strain.value_;
  }

  constexpr Strain operator+(const Strain& strain) const noexcept {
    return {value_ + strain.value_};
  }

  constexpr void operator+=(const Strain& strain) noexcept {
    value_ += strain.value_;
  }

  constexpr Strain operator-(const Strain& strain) const noexcept {
    return {value_ - strain.value_};
  }

  constexpr void operator-=(const Strain& strain) noexcept {
    value_ -= strain.value_;
  }

  constexpr StrainRate operator*(const Frequency& frequency) const noexcept;

  StrainRate operator/(const Duration& duration) const;

  friend class Duration;
  friend class Frequency;
  friend class StrainRate;

};

} // namespace PhQ
