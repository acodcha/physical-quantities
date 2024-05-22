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

#ifndef PHQ_TEMPERATURE_DIFFERENCE_HPP
#define PHQ_TEMPERATURE_DIFFERENCE_HPP

#include <cstddef>
#include <functional>
#include <ostream>

#include "DimensionalScalar.hpp"
#include "Unit/TemperatureDifference.hpp"

namespace PhQ {

// Forward declaration for class PhQ::TemperatureDifference.
template <typename Number>
class Length;

// Forward declaration for class PhQ::TemperatureDifference.
template <typename Number>
class LinearThermalExpansionCoefficient;

// Forward declaration for class PhQ::TemperatureDifference.
template <typename Number>
class ScalarStrain;

// Forward declaration for class PhQ::TemperatureDifference.
template <typename Number>
class ScalarTemperatureGradient;

// Forward declaration for class PhQ::TemperatureDifference.
template <typename Number>
class Strain;

// Forward declaration for class PhQ::TemperatureDifference.
template <typename Number>
class Temperature;

// Forward declaration for class PhQ::TemperatureDifference.
template <typename Number>
class VolumetricThermalExpansionCoefficient;

/// \brief Temperature difference. Not to be confused with temperature. For example, a temperature
/// difference of 20 kelvin is very different from a temperature of 20 kelvin.
template <typename Number = double>
class TemperatureDifference : public DimensionalScalar<Unit::TemperatureDifference, Number> {
public:
  /// \brief Default constructor. Constructs a temperature difference with an uninitialized value.
  TemperatureDifference() = default;

  /// \brief Constructor. Constructs a temperature difference with a given value expressed in a
  /// given temperature unit.
  TemperatureDifference(const Number value, const Unit::TemperatureDifference unit)
    : DimensionalScalar<Unit::TemperatureDifference, Number>(value, unit) {}

  /// \brief Constructor. Constructs a temperature difference from a given scalar temperature
  /// gradient and length using the definition of temperature gradient.
  constexpr TemperatureDifference(
      const ScalarTemperatureGradient<Number>& scalar_temperature_gradient,
      const Length<Number>& length);

  /// \brief Destructor. Destroys this temperature difference.
  ~TemperatureDifference() noexcept = default;

  /// \brief Copy constructor. Constructs a temperature difference by copying another one.
  constexpr TemperatureDifference(const TemperatureDifference<Number>& other) = default;

  /// \brief Copy constructor. Constructs a temperature difference by copying another one.
  template <typename OtherNumber>
  explicit constexpr TemperatureDifference(const TemperatureDifference<OtherNumber>& other)
    : TemperatureDifference(static_cast<Number>(other.Value())) {}

  /// \brief Move constructor. Constructs a temperature difference by moving another one.
  constexpr TemperatureDifference(TemperatureDifference<Number>&& other) noexcept = default;

  /// \brief Copy assignment operator. Assigns this temperature difference by copying another one.
  constexpr TemperatureDifference<Number>& operator=(
      const TemperatureDifference<Number>& other) = default;

  /// \brief Copy assignment operator. Assigns this temperature difference by copying another one.
  template <typename OtherNumber>
  constexpr TemperatureDifference<Number>& operator=(
      const TemperatureDifference<OtherNumber>& other) {
    this->value = static_cast<Number>(other.Value());
    return *this;
  }

  /// \brief Move assignment operator. Assigns this temperature difference by moving another one.
  constexpr TemperatureDifference<Number>& operator=(
      TemperatureDifference<Number>&& other) noexcept = default;

  /// \brief Statically creates a temperature difference of absolute zero.
  static constexpr TemperatureDifference<Number> Zero() {
    return TemperatureDifference<Number>{static_cast<Number>(0)};
  }

  /// \brief Statically creates a temperature difference with a given value expressed in a given
  /// temperature unit.
  template <Unit::TemperatureDifference Unit>
  static constexpr TemperatureDifference<Number> Create(const Number value) {
    return TemperatureDifference<Number>{
        StaticConvertCopy<Unit::TemperatureDifference, Unit, Standard<Unit::TemperatureDifference>>(
            value)};
  }

  constexpr Temperature<Number> operator+(const Temperature<Number>& temperature) const;

  constexpr TemperatureDifference<Number> operator+(
      const TemperatureDifference<Number>& temperature_difference) const {
    return TemperatureDifference<Number>{this->value + temperature_difference.value};
  }

  constexpr Temperature<Number> operator-(const Temperature<Number>& temperature) const;

  constexpr TemperatureDifference<Number> operator-(
      const TemperatureDifference<Number>& temperature_difference) const {
    return TemperatureDifference<Number>{this->value - temperature_difference.value};
  }

  constexpr TemperatureDifference<Number> operator*(const Number number) const {
    return TemperatureDifference<Number>{this->value * number};
  }

  constexpr ScalarStrain<Number> operator*(
      const LinearThermalExpansionCoefficient<Number>& linear_thermal_expansion_coefficient) const;

  constexpr Strain<Number> operator*(
      const VolumetricThermalExpansionCoefficient<Number>& volumetric_thermal_expansion_coefficient)
      const;

  constexpr TemperatureDifference<Number> operator/(const Number number) const {
    return TemperatureDifference<Number>{this->value / number};
  }

  constexpr ScalarTemperatureGradient<Number> operator/(const Length<Number>& length) const;

  constexpr Number operator/(
      const TemperatureDifference<Number>& temperature_difference) const noexcept {
    return this->value / temperature_difference.value;
  }

  constexpr void operator+=(const TemperatureDifference<Number>& temperature_difference) noexcept {
    this->value += temperature_difference.value;
  }

  constexpr void operator-=(const TemperatureDifference<Number>& temperature_difference) noexcept {
    this->value -= temperature_difference.value;
  }

  constexpr void operator*=(const Number number) noexcept {
    this->value *= number;
  }

  constexpr void operator/=(const Number number) noexcept {
    this->value /= number;
  }

private:
  /// \brief Constructor. Constructs a temperature difference with a given value expressed in the
  /// standard temperature difference unit.
  explicit constexpr TemperatureDifference(const Number value)
    : DimensionalScalar<Unit::TemperatureDifference, Number>(value) {}

  template <typename OtherNumber>
  friend class Temperature;
};

template <typename Number>
inline constexpr bool operator==(const TemperatureDifference<Number>& left,
                                 const TemperatureDifference<Number>& right) noexcept {
  return left.Value() == right.Value();
}

template <typename Number>
inline constexpr bool operator!=(const TemperatureDifference<Number>& left,
                                 const TemperatureDifference<Number>& right) noexcept {
  return left.Value() != right.Value();
}

template <typename Number>
inline constexpr bool operator<(const TemperatureDifference<Number>& left,
                                const TemperatureDifference<Number>& right) noexcept {
  return left.Value() < right.Value();
}

template <typename Number>
inline constexpr bool operator>(const TemperatureDifference<Number>& left,
                                const TemperatureDifference<Number>& right) noexcept {
  return left.Value() > right.Value();
}

template <typename Number>
inline constexpr bool operator<=(const TemperatureDifference<Number>& left,
                                 const TemperatureDifference<Number>& right) noexcept {
  return left.Value() <= right.Value();
}

template <typename Number>
inline constexpr bool operator>=(const TemperatureDifference<Number>& left,
                                 const TemperatureDifference<Number>& right) noexcept {
  return left.Value() >= right.Value();
}

template <typename Number>
inline std::ostream& operator<<(
    std::ostream& stream, const TemperatureDifference<Number>& temperature_difference) {
  stream << temperature_difference.Print();
  return stream;
}

template <typename Number>
inline constexpr TemperatureDifference<Number> operator*(
    const Number number, const TemperatureDifference<Number>& temperature_difference) {
  return temperature_difference * number;
}

}  // namespace PhQ

namespace std {

template <typename Number>
struct hash<PhQ::TemperatureDifference<Number>> {
  inline size_t operator()(const PhQ::TemperatureDifference<Number>& temperature_difference) const {
    return hash<Number>()(temperature_difference.Value());
  }
};

}  // namespace std

#endif  // PHQ_TEMPERATURE_DIFFERENCE_HPP
