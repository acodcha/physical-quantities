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

#ifndef PHQ_DYNAMIC_KINEMATIC_PRESSURE_HPP
#define PHQ_DYNAMIC_KINEMATIC_PRESSURE_HPP

#include <cmath>
#include <cstddef>
#include <functional>
#include <ostream>

#include "DimensionalScalar.hpp"
#include "DynamicPressure.hpp"
#include "MassDensity.hpp"
#include "Speed.hpp"
#include "StaticKinematicPressure.hpp"
#include "Unit/SpecificEnergy.hpp"

namespace PhQ {

/// \brief Dynamic kinematic pressure, which is dynamic pressure divided by mass density.
template <typename Number = double>
class DynamicKinematicPressure : public DimensionalScalar<Unit::SpecificEnergy, Number> {
public:
  /// \brief Default constructor. Constructs a dynamic kinematic pressure with an uninitialized
  /// value.
  DynamicKinematicPressure() = default;

  /// \brief Constructor. Constructs a dynamic kinematic pressure with a given value expressed in a
  /// given specific energy unit.
  DynamicKinematicPressure(const Number value, const Unit::SpecificEnergy unit)
    : DimensionalScalar<Unit::SpecificEnergy, Number>(value, unit) {}

  /// \brief Constructor. Constructs a dynamic kinematic pressure from a given speed using the
  /// definition of dynamic kinematic pressure.
  explicit constexpr DynamicKinematicPressure(const Speed<Number>& speed)
    : DynamicKinematicPressure<Number>(0.5 * std::pow(speed.Value(), 2)) {}

  /// \brief Constructor. Constructs a dynamic kinematic pressure from a given total kinematic
  /// pressure and static kinematic pressure using the definition of total kinematic pressure.
  constexpr DynamicKinematicPressure(
      const TotalKinematicPressure<Number>& total_kinematic_pressure,
      const StaticKinematicPressure<Number>& static_kinematic_pressure);

  /// \brief Constructor. Constructs a dynamic kinematic pressure from a given dynamic pressure and
  /// mass density using the definition of dynamic kinematic pressure.
  constexpr DynamicKinematicPressure(
      const DynamicPressure<Number>& dynamic_pressure, const MassDensity<Number>& mass_density)
    : DynamicKinematicPressure<Number>(dynamic_pressure.Value() / mass_density.Value()) {}

  /// \brief Destructor. Destroys this dynamic kinematic pressure.
  ~DynamicKinematicPressure() noexcept = default;

  /// \brief Copy constructor. Constructs a dynamic kinematic pressure by copying another one.
  constexpr DynamicKinematicPressure(const DynamicKinematicPressure<Number>& other) = default;

  /// \brief Copy constructor. Constructs a dynamic kinematic pressure by copying another one.
  template <typename OtherNumber>
  explicit constexpr DynamicKinematicPressure(const DynamicKinematicPressure<OtherNumber>& other)
    : DynamicKinematicPressure(static_cast<Number>(other.Value())) {}

  /// \brief Move constructor. Constructs a dynamic kinematic pressure by moving another one.
  constexpr DynamicKinematicPressure(DynamicKinematicPressure<Number>&& other) noexcept = default;

  /// \brief Copy assignment operator. Assigns this dynamic kinematic pressure by copying another
  /// one.
  constexpr DynamicKinematicPressure<Number>& operator=(
      const DynamicKinematicPressure<Number>& other) = default;

  /// \brief Copy assignment operator. Assigns this dynamic kinematic pressure by copying another
  /// one.
  template <typename OtherNumber>
  constexpr DynamicKinematicPressure<Number>& operator=(
      const DynamicKinematicPressure<OtherNumber>& other) {
    this->value = static_cast<Number>(other.Value());
    return *this;
  }

  /// \brief Move assignment operator. Assigns this dynamic kinematic pressure by moving another
  /// one.
  constexpr DynamicKinematicPressure<Number>& operator=(
      DynamicKinematicPressure<Number>&& other) noexcept = default;

  /// \brief Statically creates a dynamic kinematic pressure of zero.
  static constexpr DynamicKinematicPressure<Number> Zero() {
    return DynamicKinematicPressure<Number>{static_cast<Number>(0)};
  }

  /// \brief Statically creates a dynamic kinematic pressure with a given value expressed in a given
  /// specific energy unit.
  template <Unit::SpecificEnergy Unit>
  static constexpr DynamicKinematicPressure<Number> Create(const Number value) {
    return DynamicKinematicPressure<Number>{
        StaticConvertCopy<Unit::SpecificEnergy, Unit, Standard<Unit::SpecificEnergy>>(value)};
  }

  constexpr DynamicKinematicPressure<Number> operator+(
      const DynamicKinematicPressure<Number>& dynamic_kinematic_pressure) const {
    return DynamicKinematicPressure<Number>{this->value + dynamic_kinematic_pressure.value};
  }

  constexpr TotalKinematicPressure<Number> operator+(
      const StaticKinematicPressure<Number>& static_kinematic_pressure) const;

  constexpr DynamicKinematicPressure<Number> operator-(
      const DynamicKinematicPressure<Number>& dynamic_kinematic_pressure) const {
    return DynamicKinematicPressure<Number>{this->value - dynamic_kinematic_pressure.value};
  }

  constexpr DynamicKinematicPressure<Number> operator*(const Number number) const {
    return DynamicKinematicPressure<Number>{this->value * number};
  }

  constexpr DynamicKinematicPressure<Number> operator/(const Number number) const {
    return DynamicKinematicPressure<Number>{this->value / number};
  }

  constexpr Number operator/(
      const DynamicKinematicPressure<Number>& dynamic_kinematic_pressure) const noexcept {
    return this->value / dynamic_kinematic_pressure.value;
  }

  constexpr void operator+=(
      const DynamicKinematicPressure<Number>& dynamic_kinematic_pressure) noexcept {
    this->value += dynamic_kinematic_pressure.value;
  }

  constexpr void operator-=(
      const DynamicKinematicPressure<Number>& dynamic_kinematic_pressure) noexcept {
    this->value -= dynamic_kinematic_pressure.value;
  }

  constexpr void operator*=(const Number number) noexcept {
    this->value *= number;
  }

  constexpr void operator/=(const Number number) noexcept {
    this->value /= number;
  }

private:
  /// \brief Constructor. Constructs a dynamic kinematic pressure with a given value expressed in
  /// the standard specific energy unit.
  explicit constexpr DynamicKinematicPressure(const Number value)
    : DimensionalScalar<Unit::SpecificEnergy, Number>(value) {}
};

template <typename Number>
inline constexpr bool operator==(const DynamicKinematicPressure<Number>& left,
                                 const DynamicKinematicPressure<Number>& right) noexcept {
  return left.Value() == right.Value();
}

template <typename Number>
inline constexpr bool operator!=(const DynamicKinematicPressure<Number>& left,
                                 const DynamicKinematicPressure<Number>& right) noexcept {
  return left.Value() != right.Value();
}

template <typename Number>
inline constexpr bool operator<(const DynamicKinematicPressure<Number>& left,
                                const DynamicKinematicPressure<Number>& right) noexcept {
  return left.Value() < right.Value();
}

template <typename Number>
inline constexpr bool operator>(const DynamicKinematicPressure<Number>& left,
                                const DynamicKinematicPressure<Number>& right) noexcept {
  return left.Value() > right.Value();
}

template <typename Number>
inline constexpr bool operator<=(const DynamicKinematicPressure<Number>& left,
                                 const DynamicKinematicPressure<Number>& right) noexcept {
  return left.Value() <= right.Value();
}

template <typename Number>
inline constexpr bool operator>=(const DynamicKinematicPressure<Number>& left,
                                 const DynamicKinematicPressure<Number>& right) noexcept {
  return left.Value() >= right.Value();
}

template <typename Number>
inline std::ostream& operator<<(
    std::ostream& stream, const DynamicKinematicPressure<Number>& dynamic_kinematic_pressure) {
  stream << dynamic_kinematic_pressure.Print();
  return stream;
}

template <typename Number>
inline constexpr DynamicKinematicPressure<Number> operator*(
    const Number number, const DynamicKinematicPressure<Number>& dynamic_kinematic_pressure) {
  return dynamic_kinematic_pressure * number;
}

template <typename Number>
inline Speed<Number>::Speed(const DynamicKinematicPressure<Number>& dynamic_kinematic_pressure)
  : Speed<Number>(std::sqrt(2.0 * dynamic_kinematic_pressure.Value())) {}

template <typename Number>
inline constexpr DynamicPressure<Number>::DynamicPressure(
    const MassDensity<Number>& mass_density,
    const DynamicKinematicPressure<Number>& dynamic_kinematic_pressure)
  : DynamicPressure<Number>(mass_density.Value() * dynamic_kinematic_pressure.Value()) {}

template <typename Number>
inline constexpr DynamicKinematicPressure<Number> DynamicPressure<Number>::operator/(
    const MassDensity<Number>& mass_density) const {
  return DynamicKinematicPressure<Number>{*this, mass_density};
}

}  // namespace PhQ

namespace std {

template <typename Number>
struct hash<PhQ::DynamicKinematicPressure<Number>> {
  inline size_t operator()(
      const PhQ::DynamicKinematicPressure<Number>& dynamic_kinematic_pressure) const {
    return hash<Number>()(dynamic_kinematic_pressure.Value());
  }
};

}  // namespace std

#endif  // PHQ_DYNAMIC_KINEMATIC_PRESSURE_HPP
