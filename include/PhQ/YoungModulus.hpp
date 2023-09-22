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

#ifndef PHYSICAL_QUANTITIES_INCLUDE_PHQ_YOUNG_MODULUS_HPP
#define PHYSICAL_QUANTITIES_INCLUDE_PHQ_YOUNG_MODULUS_HPP

#include "DimensionalScalarQuantity.hpp"
#include "Unit/Pressure.hpp"

namespace PhQ {

// Young's modulus of elasticity of a deformable solid material. A measure of a
// deformable solid material's elastic modulus.
class YoungModulus : public DimensionalScalarQuantity<Unit::Pressure> {
public:
  constexpr YoungModulus() : DimensionalScalarQuantity<Unit::Pressure>() {}

  YoungModulus(const double value, const Unit::Pressure unit)
    : DimensionalScalarQuantity<Unit::Pressure>(value, unit) {}

  static constexpr YoungModulus Zero() {
    return YoungModulus{0.0};
  }

  template <Unit::Pressure Unit>
  static constexpr YoungModulus Create(const double value) {
    return YoungModulus{
        StaticConvertCopy<Unit::Pressure, Unit, Standard<Unit::Pressure>>(
            value)};
  }

  constexpr YoungModulus operator+(const YoungModulus& young_modulus) const {
    return YoungModulus{value_ + young_modulus.value_};
  }

  constexpr YoungModulus operator-(const YoungModulus& young_modulus) const {
    return YoungModulus{value_ - young_modulus.value_};
  }

  constexpr YoungModulus operator*(const double number) const {
    return YoungModulus{value_ * number};
  }

  constexpr YoungModulus operator/(const double number) const {
    return YoungModulus{value_ / number};
  }

  constexpr double operator/(const YoungModulus& young_modulus) const noexcept {
    return value_ / young_modulus.value_;
  }

  constexpr void operator+=(const YoungModulus& young_modulus) noexcept {
    value_ += young_modulus.value_;
  }

  constexpr void operator-=(const YoungModulus& young_modulus) noexcept {
    value_ -= young_modulus.value_;
  }

  constexpr void operator*=(const double number) noexcept {
    value_ *= number;
  }

  constexpr void operator/=(const double number) noexcept {
    value_ /= number;
  }

private:
  explicit constexpr YoungModulus(const double value)
    : DimensionalScalarQuantity<Unit::Pressure>(value) {}
};

inline constexpr bool operator==(
    const YoungModulus& left, const YoungModulus& right) noexcept {
  return left.Value() == right.Value();
}

inline constexpr bool operator!=(
    const YoungModulus& left, const YoungModulus& right) noexcept {
  return left.Value() != right.Value();
}

inline constexpr bool operator<(
    const YoungModulus& left, const YoungModulus& right) noexcept {
  return left.Value() < right.Value();
}

inline constexpr bool operator>(
    const YoungModulus& left, const YoungModulus& right) noexcept {
  return left.Value() > right.Value();
}

inline constexpr bool operator<=(
    const YoungModulus& left, const YoungModulus& right) noexcept {
  return left.Value() <= right.Value();
}

inline constexpr bool operator>=(
    const YoungModulus& left, const YoungModulus& right) noexcept {
  return left.Value() >= right.Value();
}

inline std::ostream& operator<<(
    std::ostream& stream, const YoungModulus& young_modulus) {
  stream << young_modulus.Print();
  return stream;
}

inline constexpr YoungModulus operator*(
    const double number, const YoungModulus& young_modulus) {
  return young_modulus * number;
}

}  // namespace PhQ

namespace std {

template <>
struct hash<PhQ::YoungModulus> {
  inline size_t operator()(const PhQ::YoungModulus& young_modulus) const {
    return hash<double>()(young_modulus.Value());
  }
};

}  // namespace std

#endif  // PHYSICAL_QUANTITIES_INCLUDE_PHQ_YOUNG_MODULUS_HPP
