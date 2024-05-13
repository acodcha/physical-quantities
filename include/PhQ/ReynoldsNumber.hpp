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

#ifndef PHQ_REYNOLDS_NUMBER_HPP
#define PHQ_REYNOLDS_NUMBER_HPP

#include <cstddef>
#include <functional>
#include <ostream>

#include "DimensionlessScalar.hpp"
#include "DynamicViscosity.hpp"
#include "KinematicViscosity.hpp"
#include "Length.hpp"
#include "MassDensity.hpp"
#include "Speed.hpp"

namespace PhQ {

// Reynolds number of a fluid flow.
template <typename Number = double>
class ReynoldsNumber : public DimensionlessScalar<Number> {
public:
  // Default constructor. Constructs a Reynolds number with an uninitialized value.
  ReynoldsNumber() = default;

  // Constructor. Constructs a Reynolds number with a given value.
  explicit constexpr ReynoldsNumber(const Number value) : DimensionlessScalar<Number>(value) {}

  // Constructor. Constructs a Reynolds number from a given mass density, speed, length, and dynamic
  // viscosity using the definition of the Reynolds number.
  constexpr ReynoldsNumber(
      const MassDensity<Number>& mass_density, const Speed<Number>& speed,
      const Length<Number>& length, const DynamicViscosity<Number>& dynamic_viscosity)
    : ReynoldsNumber<Number>(
        mass_density.Value() * speed.Value() * length.Value() / dynamic_viscosity.Value()) {}

  // Constructor. Constructs a Reynolds number from a given speed, length, and kinematic viscosity
  // using the definition of the Reynolds number.
  constexpr ReynoldsNumber(const Speed<Number>& speed, const Length<Number>& length,
                           const KinematicViscosity<Number>& kinematic_viscosity)
    : ReynoldsNumber<Number>(speed.Value() * length.Value() / kinematic_viscosity.Value()) {}

  // Destructor. Destroys this Reynolds number.
  ~ReynoldsNumber() noexcept = default;

  // Copy constructor. Constructs a Reynolds number by copying another one.
  constexpr ReynoldsNumber(const ReynoldsNumber<Number>& other) = default;

  // Copy constructor. Constructs a Reynolds number by copying another one.
  template <typename OtherNumber>
  explicit constexpr ReynoldsNumber(const ReynoldsNumber<OtherNumber>& other)
    : ReynoldsNumber(static_cast<Number>(other.Value())) {}

  // Move constructor. Constructs a Reynolds number by moving another one.
  constexpr ReynoldsNumber(ReynoldsNumber<Number>&& other) noexcept = default;

  // Copy assignment operator. Assigns this Reynolds number by copying another one.
  constexpr ReynoldsNumber<Number>& operator=(const ReynoldsNumber<Number>& other) = default;

  // Copy assignment operator. Assigns this Reynolds number by copying another one.
  template <typename OtherNumber>
  constexpr ReynoldsNumber<Number>& operator=(const ReynoldsNumber<OtherNumber>& other) {
    this->value = static_cast<Number>(other.Value());
    return *this;
  }

  // Move assignment operator. Assigns this Reynolds number by moving another one.
  constexpr ReynoldsNumber<Number>& operator=(ReynoldsNumber<Number>&& other) noexcept = default;

  // Statically creates a Reynolds number of zero.
  static constexpr ReynoldsNumber<Number> Zero() {
    return ReynoldsNumber<Number>{static_cast<Number>(0)};
  }

  [[nodiscard]] constexpr PhQ::DynamicViscosity<Number> DynamicViscosity(
      const PhQ::MassDensity<Number>& mass_density, const PhQ::Speed<Number>& speed,
      const PhQ::Length<Number>& length) const {
    return PhQ::DynamicViscosity<Number>{mass_density, speed, length, *this};
  }

  [[nodiscard]] constexpr PhQ::KinematicViscosity<Number> KinematicViscosity(
      const PhQ::Speed<Number>& speed, const PhQ::Length<Number>& length) const {
    return PhQ::KinematicViscosity<Number>{speed, length, *this};
  }

  [[nodiscard]] constexpr PhQ::Length<Number> Length(
      const PhQ::DynamicViscosity<Number>& dynamic_viscosity,
      const PhQ::MassDensity<Number>& mass_density, const PhQ::Speed<Number>& speed) const {
    return PhQ::Length<Number>{*this, dynamic_viscosity, mass_density, speed};
  }

  [[nodiscard]] constexpr PhQ::Length<Number> Length(
      const PhQ::KinematicViscosity<Number>& kinematic_viscosity,
      const PhQ::Speed<Number>& speed) const {
    return PhQ::Length<Number>{*this, kinematic_viscosity, speed};
  }

  [[nodiscard]] constexpr PhQ::MassDensity<Number> MassDensity(
      const PhQ::DynamicViscosity<Number>& dynamic_viscosity, const PhQ::Speed<Number>& speed,
      const PhQ::Length<Number>& length) const {
    return PhQ::MassDensity<Number>{*this, dynamic_viscosity, speed, length};
  }

  [[nodiscard]] constexpr PhQ::Speed<Number> Speed(
      const PhQ::DynamicViscosity<Number>& dynamic_viscosity,
      const PhQ::MassDensity<Number>& mass_density, const PhQ::Length<Number>& length) const {
    return PhQ::Speed<Number>{*this, dynamic_viscosity, mass_density, length};
  }

  [[nodiscard]] constexpr PhQ::Speed<Number> Speed(
      const PhQ::KinematicViscosity<Number>& kinematic_viscosity,
      const PhQ::Length<Number>& length) const {
    return PhQ::Speed<Number>{*this, kinematic_viscosity, length};
  }

  constexpr ReynoldsNumber<Number> operator+(const ReynoldsNumber<Number>& reynolds_number) const {
    return ReynoldsNumber<Number>{this->value + reynolds_number.value};
  }

  constexpr ReynoldsNumber<Number> operator-(const ReynoldsNumber<Number>& reynolds_number) const {
    return ReynoldsNumber<Number>{this->value - reynolds_number.value};
  }

  constexpr ReynoldsNumber<Number> operator*(const Number number) const {
    return ReynoldsNumber<Number>{this->value * number};
  }

  constexpr ReynoldsNumber<Number> operator/(const Number number) const {
    return ReynoldsNumber<Number>{this->value / number};
  }

  constexpr Number operator/(const ReynoldsNumber<Number>& reynolds_number) const noexcept {
    return this->value / reynolds_number.value;
  }

  constexpr void operator+=(const ReynoldsNumber<Number>& reynolds_number) noexcept {
    this->value += reynolds_number.value;
  }

  constexpr void operator-=(const ReynoldsNumber<Number>& reynolds_number) noexcept {
    this->value -= reynolds_number.value;
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
    const ReynoldsNumber<Number>& left, const ReynoldsNumber<Number>& right) noexcept {
  return left.Value() == right.Value();
}

template <typename Number>
inline constexpr bool operator!=(
    const ReynoldsNumber<Number>& left, const ReynoldsNumber<Number>& right) noexcept {
  return left.Value() != right.Value();
}

template <typename Number>
inline constexpr bool operator<(
    const ReynoldsNumber<Number>& left, const ReynoldsNumber<Number>& right) noexcept {
  return left.Value() < right.Value();
}

template <typename Number>
inline constexpr bool operator>(
    const ReynoldsNumber<Number>& left, const ReynoldsNumber<Number>& right) noexcept {
  return left.Value() > right.Value();
}

template <typename Number>
inline constexpr bool operator<=(
    const ReynoldsNumber<Number>& left, const ReynoldsNumber<Number>& right) noexcept {
  return left.Value() <= right.Value();
}

template <typename Number>
inline constexpr bool operator>=(
    const ReynoldsNumber<Number>& left, const ReynoldsNumber<Number>& right) noexcept {
  return left.Value() >= right.Value();
}

template <typename Number>
inline std::ostream& operator<<(
    std::ostream& stream, const ReynoldsNumber<Number>& reynolds_number) {
  stream << reynolds_number.Print();
  return stream;
}

template <typename Number>
inline constexpr ReynoldsNumber<Number> operator*(
    const Number number, const ReynoldsNumber<Number>& reynolds_number) {
  return ReynoldsNumber<Number>{number * reynolds_number.Value()};
}

template <typename Number>
inline constexpr Length<Number>::Length(
    const ReynoldsNumber<Number>& reynolds_number,
    const DynamicViscosity<Number>& dynamic_viscosity, const MassDensity<Number>& mass_density,
    const Speed<Number>& speed)
  : Length<Number>(reynolds_number.Value() * dynamic_viscosity.Value()
                   / (mass_density.Value() * speed.Value())) {}

template <typename Number>
inline constexpr Length<Number>::Length(
    const ReynoldsNumber<Number>& reynolds_number,
    const KinematicViscosity<Number>& kinematic_viscosity, const Speed<Number>& speed)
  : Length<Number>(reynolds_number.Value() * kinematic_viscosity.Value() / speed.Value()) {}

template <typename Number>
inline constexpr Speed<Number>::Speed(
    const ReynoldsNumber<Number>& reynolds_number,
    const DynamicViscosity<Number>& dynamic_viscosity, const MassDensity<Number>& mass_density,
    const Length<Number>& length)
  : Speed<Number>(reynolds_number.Value() * dynamic_viscosity.Value()
                  / (mass_density.Value() * length.Value())) {}

template <typename Number>
inline constexpr Speed<Number>::Speed(
    const ReynoldsNumber<Number>& reynolds_number,
    const KinematicViscosity<Number>& kinematic_viscosity, const Length<Number>& length)
  : Speed<Number>(reynolds_number.Value() * kinematic_viscosity.Value() / length.Value()) {}

template <typename Number>
inline constexpr MassDensity<Number>::MassDensity(
    const ReynoldsNumber<Number>& reynolds_number,
    const DynamicViscosity<Number>& dynamic_viscosity, const Speed<Number>& speed,
    const Length<Number>& length)
  : MassDensity<Number>(
      reynolds_number.Value() * dynamic_viscosity.Value() / (speed.Value() * length.Value())) {}

template <typename Number>
inline constexpr KinematicViscosity<Number>::KinematicViscosity(
    const Speed<Number>& speed, const Length<Number>& length,
    const ReynoldsNumber<Number>& reynolds_number)
  : KinematicViscosity<Number>(speed.Value() * length.Value() / reynolds_number.Value()) {}

template <typename Number>
inline constexpr DynamicViscosity<Number>::DynamicViscosity(
    const MassDensity<Number>& mass_density, const Speed<Number>& speed,
    const Length<Number>& length, const ReynoldsNumber<Number>& reynolds_number)
  : DynamicViscosity<Number>(
      mass_density.Value() * speed.Value() * length.Value() / reynolds_number.Value()) {}

}  // namespace PhQ

namespace std {

template <typename Number>
struct hash<PhQ::ReynoldsNumber<Number>> {
  inline size_t operator()(const PhQ::ReynoldsNumber<Number>& reynolds_number) const {
    return hash<Number>()(reynolds_number.Value());
  }
};

}  // namespace std

#endif  // PHQ_REYNOLDS_NUMBER_HPP
