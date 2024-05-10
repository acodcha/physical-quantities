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

#ifndef PHQ_ISENTROPIC_BULK_MODULUS_HPP
#define PHQ_ISENTROPIC_BULK_MODULUS_HPP

#include <cstddef>
#include <functional>
#include <ostream>

#include "DimensionalScalar.hpp"
#include "Unit/Pressure.hpp"

namespace PhQ {

// Forward declaration for class PhQ::IsentropicBulkModulus.
template <typename Number>
class MassDensity;

// Forward declaration for class PhQ::IsentropicBulkModulus.
template <typename Number>
class SoundSpeed;

// Isentropic bulk modulus. Not to be confused with the isothermal bulk modulus.
template <typename Number = double>
class IsentropicBulkModulus : public DimensionalScalar<Unit::Pressure, Number> {
public:
  // Default constructor. Constructs an isentropic bulk modulus with an uninitialized value.
  IsentropicBulkModulus() = default;

  // Constructor. Constructs an isentropic bulk modulus with a given value expressed in a given
  // pressure unit.
  IsentropicBulkModulus(const Number value, const Unit::Pressure unit)
    : DimensionalScalar<Unit::Pressure, Number>(value, unit) {}

  // Constructor. Constructs an isentropic bulk modulus from a given mass density and sound speed
  // using the definition of the isentropic bulk modulus.
  constexpr IsentropicBulkModulus(
      const MassDensity<Number>& mass_density, const SoundSpeed<Number>& sound_speed);

  // Destructor. Destroys this isentropic bulk modulus.
  ~IsentropicBulkModulus() noexcept = default;

  // Copy constructor. Constructs an isentropic bulk modulus by copying another one.
  constexpr IsentropicBulkModulus(const IsentropicBulkModulus<Number>& other) = default;

  // Copy constructor. Constructs a isentropic bulk modulus by copying another one.
  template <typename OtherNumber>
  explicit constexpr IsentropicBulkModulus(const IsentropicBulkModulus<OtherNumber>& other)
    : value(static_cast<Number>(other.Value())) {}

  // Move constructor. Constructs an isentropic bulk modulus by moving another one.
  constexpr IsentropicBulkModulus(IsentropicBulkModulus<Number>&& other) noexcept = default;

  // Copy assignment operator. Assigns this isentropic bulk modulus by copying another one.
  constexpr IsentropicBulkModulus<Number>& operator=(
      const IsentropicBulkModulus<Number>& other) = default;

  // Copy assignment operator. Assigns this isentropic bulk modulus by copying another one.
  template <typename OtherNumber>
  constexpr IsentropicBulkModulus<Number>& operator=(
      const IsentropicBulkModulus<OtherNumber>& other) {
    value = static_cast<Number>(other.Value());
    return *this;
  }

  // Move assignment operator. Assigns this isentropic bulk modulus by moving another one.
  constexpr IsentropicBulkModulus<Number>& operator=(
      IsentropicBulkModulus<Number>&& other) noexcept = default;

  // Statically creates an isentropic bulk modulus of zero.
  static constexpr IsentropicBulkModulus<Number> Zero() {
    return IsentropicBulkModulus<Number>{static_cast<Number>(0)};
  }

  // Statically creates an isentropic bulk modulus with a given value expressed in a given pressure
  // unit.
  template <Unit::Pressure Unit>
  static constexpr IsentropicBulkModulus<Number> Create(const Number value) {
    return IsentropicBulkModulus<Number>{
        StaticConvertCopy<Unit::Pressure, Unit, Standard<Unit::Pressure>>(value)};
  }

  constexpr IsentropicBulkModulus<Number> operator+(
      const IsentropicBulkModulus<Number>& isentropic_bulk_modulus) const {
    return IsentropicBulkModulus<Number>{value + isentropic_bulk_modulus.value};
  }

  constexpr IsentropicBulkModulus<Number> operator-(
      const IsentropicBulkModulus<Number>& isentropic_bulk_modulus) const {
    return IsentropicBulkModulus<Number>{value - isentropic_bulk_modulus.value};
  }

  constexpr IsentropicBulkModulus<Number> operator*(const Number number) const {
    return IsentropicBulkModulus<Number>{value * number};
  }

  constexpr IsentropicBulkModulus<Number> operator/(const Number number) const {
    return IsentropicBulkModulus<Number>{value / number};
  }

  constexpr Number operator/(
      const IsentropicBulkModulus<Number>& isentropic_bulk_modulus) const noexcept {
    return value / isentropic_bulk_modulus.value;
  }

  constexpr void operator+=(const IsentropicBulkModulus<Number>& isentropic_bulk_modulus) noexcept {
    value += isentropic_bulk_modulus.value;
  }

  constexpr void operator-=(const IsentropicBulkModulus<Number>& isentropic_bulk_modulus) noexcept {
    value -= isentropic_bulk_modulus.value;
  }

  constexpr void operator*=(const Number number) noexcept {
    value *= number;
  }

  constexpr void operator/=(const Number number) noexcept {
    value /= number;
  }

private:
  // Constructor. Constructs an isentropic bulk modulus with a given value expressed in the standard
  // pressure unit.
  explicit constexpr IsentropicBulkModulus(const Number value)
    : DimensionalScalar<Unit::Pressure, Number>(value) {}
};

template <typename Number>
inline constexpr bool operator==(const IsentropicBulkModulus<Number>& left,
                                 const IsentropicBulkModulus<Number>& right) noexcept {
  return left.Value() == right.Value();
}

template <typename Number>
inline constexpr bool operator!=(const IsentropicBulkModulus<Number>& left,
                                 const IsentropicBulkModulus<Number>& right) noexcept {
  return left.Value() != right.Value();
}

template <typename Number>
inline constexpr bool operator<(const IsentropicBulkModulus<Number>& left,
                                const IsentropicBulkModulus<Number>& right) noexcept {
  return left.Value() < right.Value();
}

template <typename Number>
inline constexpr bool operator>(const IsentropicBulkModulus<Number>& left,
                                const IsentropicBulkModulus<Number>& right) noexcept {
  return left.Value() > right.Value();
}

template <typename Number>
inline constexpr bool operator<=(const IsentropicBulkModulus<Number>& left,
                                 const IsentropicBulkModulus<Number>& right) noexcept {
  return left.Value() <= right.Value();
}

template <typename Number>
inline constexpr bool operator>=(const IsentropicBulkModulus<Number>& left,
                                 const IsentropicBulkModulus<Number>& right) noexcept {
  return left.Value() >= right.Value();
}

template <typename Number>
inline std::ostream& operator<<(
    std::ostream& stream, const IsentropicBulkModulus<Number>& isentropic_bulk_modulus) {
  stream << isentropic_bulk_modulus.Print();
  return stream;
}

template <typename Number>
inline constexpr IsentropicBulkModulus<Number> operator*(
    const Number number, const IsentropicBulkModulus<Number>& isentropic_bulk_modulus) {
  return isentropic_bulk_modulus * number;
}

}  // namespace PhQ

namespace std {

template <typename Number>
struct hash<PhQ::IsentropicBulkModulus<Number>> {
  inline size_t operator()(
      const PhQ::IsentropicBulkModulus<Number>& isentropic_bulk_modulus) const {
    return hash<Number>()(isentropic_bulk_modulus.Value());
  }
};

}  // namespace std

#endif  // PHQ_ISENTROPIC_BULK_MODULUS_HPP
