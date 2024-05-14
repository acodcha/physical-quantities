// Copyright © 2020-2024 Alexandre Coderre-Chabot
//
// This file is part of Physical Quantities (PhQ), a C++ library of physical quantities, physical
// models, and units of measure for scientific computation.
//
// Physical Quantities (PhQ) is hosted at:
//     https://github.com/acodcha/physical-quantities
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

#ifndef PHQ_DISPLACEMENT_GRADIENT_HPP
#define PHQ_DISPLACEMENT_GRADIENT_HPP

#include <array>
#include <cstddef>
#include <functional>
#include <ostream>

#include "DimensionlessDyad.hpp"
#include "Dyad.hpp"
#include "ScalarDisplacementGradient.hpp"
#include "Strain.hpp"

namespace PhQ {

// Forward declaration for class PhQ::DisplacementGradient.
template <typename Number>
class VelocityGradient;

// Displacement gradient dyadic tensor. Gradient of the displacement vector. In general, this dyadic
// tensor is asymmetric. See also PhQ::ScalarDisplacementGradient.
template <typename Number = double>
class DisplacementGradient : public DimensionlessDyad<Number> {
public:
  // Default constructor. Constructs a displacement gradient tensor with an uninitialized value.
  DisplacementGradient() = default;

  // Constructor. Constructs a displacement gradient tensor whose value has the given xx, xy, xz,
  // yx, yy, yz, zx, zy, and zz Cartesian components.
  constexpr DisplacementGradient(
      const Number xx, const Number xy, const Number xz, const Number yx, const Number yy,
      const Number yz, const Number zx, const Number zy, const Number zz)
    : DimensionlessDyad<Number>(xx, xy, xz, yx, yy, yz, zx, zy, zz) {}

  // Constructor. Constructs a displacement gradient tensor from a given array representing its
  // value's xx, xy, xz, yx, yy, yz, zx, zy, and zz Cartesian components.
  explicit constexpr DisplacementGradient(const std::array<Number, 9>& xx_xy_xz_yx_yy_yz_zx_zy_zz)
    : DimensionlessDyad<Number>(xx_xy_xz_yx_yy_yz_zx_zy_zz) {}

  // Constructor. Constructs a displacement gradient tensor with a given value.
  explicit constexpr DisplacementGradient(const Dyad<Number>& value)
    : DimensionlessDyad<Number>(value) {}

  // Constructor. Constructs a displacement gradient tensor from a given velocity gradient tensor
  // and time using the definition of speed.
  constexpr DisplacementGradient(
      const VelocityGradient<Number>& velocity_gradient, const Time<Number>& time);

  // Constructor. Constructs a displacement gradient tensor from a given velocity gradient tensor
  // and frequency using the definition of speed.
  constexpr DisplacementGradient(
      const VelocityGradient<Number>& velocity_gradient, const Frequency<Number>& frequency);

  // Destructor. Destroys this displacement gradient tensor.
  ~DisplacementGradient() noexcept = default;

  // Copy constructor. Constructs a displacement gradient tensor by copying another one.
  constexpr DisplacementGradient(const DisplacementGradient<Number>& other) = default;

  // Copy constructor. Constructs a displacement gradient tensor by copying another one.
  template <typename OtherNumber>
  explicit constexpr DisplacementGradient(const DisplacementGradient<OtherNumber>& other)
    : DisplacementGradient(static_cast<Dyad<Number>>(other.Value())) {}

  // Move constructor. Constructs a displacement gradient tensor by moving another one.
  constexpr DisplacementGradient(DisplacementGradient<Number>&& other) noexcept = default;

  // Copy assignment operator. Assigns this displacement gradient tensor by copying another one.
  constexpr DisplacementGradient<Number>& operator=(
      const DisplacementGradient<Number>& other) = default;

  // Copy assignment operator. Assigns this displacement gradient tensor by copying another one.
  template <typename OtherNumber>
  constexpr DisplacementGradient<Number>& operator=(
      const DisplacementGradient<OtherNumber>& other) {
    this->value = static_cast<Dyad<Number>>(other.Value());
    return *this;
  }

  // Move assignment operator. Assigns this displacement gradient tensor by moving another one.
  constexpr DisplacementGradient<Number>& operator=(
      DisplacementGradient<Number>&& other) noexcept = default;

  // Statically creates a displacement gradient tensor of zero.
  static constexpr DisplacementGradient<Number> Zero() {
    return DisplacementGradient<Number>{Dyad<Number>::Zero()};
  }

  // Returns the xx Cartesian component of this displacement gradient tensor.
  [[nodiscard]] constexpr ScalarDisplacementGradient<Number> xx() const noexcept {
    return ScalarDisplacementGradient<Number>{this->value.xx()};
  }

  // Returns the xy Cartesian component of this displacement gradient tensor.
  [[nodiscard]] constexpr ScalarDisplacementGradient<Number> xy() const noexcept {
    return ScalarDisplacementGradient<Number>{this->value.xy()};
  }

  // Returns the xz Cartesian component of this displacement gradient tensor.
  [[nodiscard]] constexpr ScalarDisplacementGradient<Number> xz() const noexcept {
    return ScalarDisplacementGradient<Number>{this->value.xz()};
  }

  // Returns the yx Cartesian component of this displacement gradient tensor.
  [[nodiscard]] constexpr ScalarDisplacementGradient<Number> yx() const noexcept {
    return ScalarDisplacementGradient<Number>{this->value.yx()};
  }

  // Returns the yy Cartesian component of this displacement gradient tensor.
  [[nodiscard]] constexpr ScalarDisplacementGradient<Number> yy() const noexcept {
    return ScalarDisplacementGradient<Number>{this->value.yy()};
  }

  // Returns the yz Cartesian component of this displacement gradient tensor.
  [[nodiscard]] constexpr ScalarDisplacementGradient<Number> yz() const noexcept {
    return ScalarDisplacementGradient<Number>{this->value.yz()};
  }

  // Returns the zx Cartesian component of this displacement gradient tensor.
  [[nodiscard]] constexpr ScalarDisplacementGradient<Number> zx() const noexcept {
    return ScalarDisplacementGradient<Number>{this->value.zx()};
  }

  // Returns the zy Cartesian component of this displacement gradient tensor.
  [[nodiscard]] constexpr ScalarDisplacementGradient<Number> zy() const noexcept {
    return ScalarDisplacementGradient<Number>{this->value.zy()};
  }

  // Returns the zz Cartesian component of this displacement gradient tensor.
  [[nodiscard]] constexpr ScalarDisplacementGradient<Number> zz() const noexcept {
    return ScalarDisplacementGradient<Number>{this->value.zz()};
  }

  // Creates a strain tensor from this displacement gradient tensor using the definition of the
  // strain tensor.
  [[nodiscard]] constexpr PhQ::Strain<Number> Strain() const {
    return PhQ::Strain<Number>{*this};
  }

  constexpr DisplacementGradient<Number> operator+(
      const DisplacementGradient<Number>& displacement_gradient) const {
    return DisplacementGradient<Number>{this->value + displacement_gradient.value};
  }

  constexpr DisplacementGradient<Number> operator-(
      const DisplacementGradient<Number>& displacement_gradient) const {
    return DisplacementGradient<Number>{this->value - displacement_gradient.value};
  }

  constexpr DisplacementGradient<Number> operator*(const Number number) const {
    return DisplacementGradient<Number>{this->value * number};
  }

  constexpr VelocityGradient<Number> operator*(const Frequency<Number>& frequency) const;

  constexpr DisplacementGradient<Number> operator/(const Number number) const {
    return DisplacementGradient<Number>{this->value / number};
  }

  constexpr VelocityGradient<Number> operator/(const Time<Number>& time) const;

  constexpr void operator+=(const DisplacementGradient<Number>& displacement_gradient) noexcept {
    this->value += displacement_gradient.value;
  }

  constexpr void operator-=(const DisplacementGradient<Number>& displacement_gradient) noexcept {
    this->value -= displacement_gradient.value;
  }

  constexpr void operator*=(const Number number) noexcept {
    this->value *= number;
  }

  constexpr void operator/=(const Number number) noexcept {
    this->value /= number;
  }
};

template <typename Number>
inline constexpr bool operator==(
    const DisplacementGradient<Number>& left, const DisplacementGradient<Number>& right) noexcept {
  return left.Value() == right.Value();
}

template <typename Number>
inline constexpr bool operator!=(
    const DisplacementGradient<Number>& left, const DisplacementGradient<Number>& right) noexcept {
  return left.Value() != right.Value();
}

template <typename Number>
inline constexpr bool operator<(
    const DisplacementGradient<Number>& left, const DisplacementGradient<Number>& right) noexcept {
  return left.Value() < right.Value();
}

template <typename Number>
inline constexpr bool operator>(
    const DisplacementGradient<Number>& left, const DisplacementGradient<Number>& right) noexcept {
  return left.Value() > right.Value();
}

template <typename Number>
inline constexpr bool operator<=(
    const DisplacementGradient<Number>& left, const DisplacementGradient<Number>& right) noexcept {
  return left.Value() <= right.Value();
}

template <typename Number>
inline constexpr bool operator>=(
    const DisplacementGradient<Number>& left, const DisplacementGradient<Number>& right) noexcept {
  return left.Value() >= right.Value();
}

template <typename Number>
inline std::ostream& operator<<(
    std::ostream& stream, const DisplacementGradient<Number>& displacement_gradient) {
  stream << displacement_gradient.Print();
  return stream;
}

template <typename Number>
inline constexpr DisplacementGradient<Number> operator*(
    const Number number, const DisplacementGradient<Number>& displacement_gradient) {
  return displacement_gradient * number;
}

template <typename Number>
inline constexpr Strain<Number>::Strain(const DisplacementGradient<Number>& displacement_gradient)
  : Strain<Number>(displacement_gradient.Value().xx(),
                   0.5 * (displacement_gradient.Value().xy() + displacement_gradient.Value().yx()),
                   0.5 * (displacement_gradient.Value().xz() + displacement_gradient.Value().zx()),
                   displacement_gradient.Value().yy(),
                   0.5 * (displacement_gradient.Value().yz() + displacement_gradient.Value().zy()),
                   displacement_gradient.Value().zz()) {}

}  // namespace PhQ

namespace std {

template <typename Number>
struct hash<PhQ::DisplacementGradient<Number>> {
  inline size_t operator()(const PhQ::DisplacementGradient<Number>& displacement_gradient) const {
    return hash<PhQ::Dyad<Number>>()(displacement_gradient.Value());
  }
};

}  // namespace std

#endif  // PHQ_DISPLACEMENT_GRADIENT_HPP
