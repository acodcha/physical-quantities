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

#ifndef PHQ_DIMENSIONLESS_DYAD_HPP
#define PHQ_DIMENSIONLESS_DYAD_HPP

#include <array>
#include <cstddef>
#include <functional>
#include <ostream>
#include <string>

#include "Base.hpp"
#include "Dimensions.hpp"
#include "Dyad.hpp"

namespace PhQ {

// Abstract base class that represents any dimensionless dyadic tensor physical quantity. Such a
// physical quantity is composed only of a value where the value is a three-dimensional dyadic
// tensor. The tensor may be non-symmetric. Such a physical quantity has no unit of measure and no
// dimension set.
class DimensionlessDyad {
public:
  // Physical dimension set of this dimensionless physical quantity. Since this physical quantity is
  // dimensionless, its physical dimension set is simply the null set.
  static constexpr PhQ::Dimensions Dimensions() {
    return Dimensionless;
  }

  // Value of this dimensionless physical quantity.
  [[nodiscard]] constexpr const Dyad<double>& Value() const noexcept {
    return value;
  }

  // Returns the value of this dimensionless physical quantity as a mutable value.
  constexpr Dyad<double>& MutableValue() noexcept {
    return value;
  }

  // Sets the value of this dimensionless physical quantity to the given value.
  constexpr void SetValue(const Dyad<double>& value) noexcept {
    this->value = value;
  }

  // Prints this dimensionless physical quantity as a string. This dimensionless physical quantity's
  // value is printed to double floating point precision.
  [[nodiscard]] std::string Print() const {
    return value.Print();
  }

  // Serializes this dimensionless physical quantity as a JSON message.
  [[nodiscard]] std::string JSON() const {
    return value.JSON();
  }

  // Serializes this dimensionless physical quantity as an XML message.
  [[nodiscard]] std::string XML() const {
    return value.XML();
  }

  // Serializes this dimensionless physical quantity as a YAML message.
  [[nodiscard]] std::string YAML() const {
    return value.YAML();
  }

protected:
  // Default constructor. Constructs a dimensionless dyadic tensor physical quantity with an
  // uninitialized value.
  DimensionlessDyad() = default;

  // Constructor. Constructs a dimensionless dyadic tensor physical quantity whose value has the
  // given xx, xy, xz, yx, yy, yz, zx, zy, and zz Cartesian components.
  constexpr DimensionlessDyad(
      const double xx, const double xy, const double xz, const double yx, const double yy,
      const double yz, const double zx, const double zy, const double zz)
    : value(xx, xy, xz, yx, yy, yz, zx, zy, zz) {}

  // Constructor. Constructs a dimensionless dyadic tensor physical quantity from a given array
  // representing its value's xx, xy, xz, yx, yy, yz, zx, zy, and zz Cartesian components.
  explicit constexpr DimensionlessDyad(const std::array<double, 9>& xx_xy_xz_yx_yy_yz_zx_zy_zz)
    : value(xx_xy_xz_yx_yy_yz_zx_zy_zz) {}

  // Constructor. Constructs a dimensionless dyadic tensor physical quantity with a given value.
  explicit constexpr DimensionlessDyad(const Dyad<double>& value) : value(value) {}

  // Destructor. Destroys this dimensionless dyadic tensor physical quantity.
  ~DimensionlessDyad() noexcept = default;

  // Copy constructor. Constructs a dimensionless dyadic tensor physical quantity by copying another
  // one.
  constexpr DimensionlessDyad(const DimensionlessDyad& other) = default;

  // Move constructor. Constructs a dimensionless dyadic tensor physical quantity by moving another
  // one.
  constexpr DimensionlessDyad(DimensionlessDyad&& other) noexcept = default;

  // Copy assignment operator. Assigns this dimensionless dyadic tensor physical quantity by copying
  // another one.
  constexpr DimensionlessDyad& operator=(const DimensionlessDyad& other) = default;

  // Move assignment operator. Assigns this dimensionless dyadic tensor physical quantity by moving
  // another one.
  constexpr DimensionlessDyad& operator=(DimensionlessDyad&& other) noexcept = default;

  // Value of this dimensionless dyadic tensor physical quantity.
  Dyad<double> value;
};

inline std::ostream& operator<<(std::ostream& stream, const DimensionlessDyad& quantity) {
  stream << quantity.Print();
  return stream;
}

}  // namespace PhQ

namespace std {

template <>
struct hash<PhQ::DimensionlessDyad> {
  inline size_t operator()(const PhQ::DimensionlessDyad& quantity) const {
    return hash<PhQ::Dyad<double>>()(quantity.Value());
  }
};

}  // namespace std

#endif  // PHQ_DIMENSIONLESS_DYAD_HPP
