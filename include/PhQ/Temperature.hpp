// Copyright 2020-2023 Alexandre Coderre-Chabot
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

#ifndef PHYSICAL_QUANTITIES_INCLUDE_PHQ_TEMPERATURE_HPP
#define PHYSICAL_QUANTITIES_INCLUDE_PHQ_TEMPERATURE_HPP

#include <cstddef>
#include <functional>
#include <ostream>

#include "DimensionalScalar.hpp"
#include "TemperatureDifference.hpp"
#include "Unit/Temperature.hpp"

namespace PhQ {

// Temperature.
class Temperature : public DimensionalScalar<Unit::Temperature> {
public:
  // Default constructor. Constructs a temperature with an uninitialized value.
  Temperature() = default;

  // Constructor. Constructs a temperature with a given value expressed in a given temperature unit.
  Temperature(const double value, const Unit::Temperature unit)
    : DimensionalScalar<Unit::Temperature>(value, unit) {}

  // Destructor. Destroys this temperature.
  ~Temperature() noexcept = default;

  // Copy constructor. Constructs a temperature by copying another one.
  constexpr Temperature(const Temperature& other) = default;

  // Move constructor. Constructs a temperature by moving another one.
  constexpr Temperature(Temperature&& other) noexcept = default;

  // Copy assignment operator. Assigns this temperature by copying another one.
  constexpr Temperature& operator=(const Temperature& other) = default;

  // Move assignment operator. Assigns this temperature by moving another one.
  constexpr Temperature& operator=(Temperature&& other) noexcept = default;

  // Statically creates a temperature of absolute zero.
  static constexpr Temperature Zero() {
    return Temperature{0.0};
  }

  // Statically creates a temperature with a given value expressed in a given temperature unit.
  template <Unit::Temperature Unit>
  static constexpr Temperature Create(const double value) {
    return Temperature{
        StaticConvertCopy<Unit::Temperature, Unit, Standard<Unit::Temperature>>(value)};
  }

  constexpr Temperature operator+(const Temperature& temperature) const {
    return Temperature{value_ + temperature.value_};
  }

  constexpr Temperature operator+(const TemperatureDifference& temperature_difference) const {
    return Temperature{value_ + temperature_difference.Value()};
  }

  constexpr TemperatureDifference operator-(const Temperature& temperature) const {
    return TemperatureDifference{value_ - temperature.value_};
  }

  constexpr Temperature operator-(const TemperatureDifference& temperature_difference) const {
    return Temperature{value_ - temperature_difference.Value()};
  }

  constexpr Temperature operator*(const double number) const {
    return Temperature{value_ * number};
  }

  constexpr Temperature operator/(const double number) const {
    return Temperature{value_ / number};
  }

  constexpr double operator/(const Temperature& temperature) const noexcept {
    return value_ / temperature.value_;
  }

  constexpr void operator+=(const Temperature& temperature) noexcept {
    value_ += temperature.value_;
  }

  constexpr void operator+=(const TemperatureDifference& temperature_difference) noexcept {
    value_ += temperature_difference.Value();
  }

  constexpr void operator-=(const Temperature& temperature) noexcept {
    value_ -= temperature.value_;
  }

  constexpr void operator-=(const TemperatureDifference& temperature_difference) noexcept {
    value_ -= temperature_difference.Value();
  }

  constexpr void operator*=(const double number) noexcept {
    value_ *= number;
  }

  constexpr void operator/=(const double number) noexcept {
    value_ /= number;
  }

private:
  // Constructor. Constructs a temperature with a given value expressed in the standard temperature
  // unit.
  explicit constexpr Temperature(const double value)
    : DimensionalScalar<Unit::Temperature>(value) {}

  friend class TemperatureDifference;
};

inline constexpr bool operator==(const Temperature& left, const Temperature& right) noexcept {
  return left.Value() == right.Value();
}

inline constexpr bool operator!=(const Temperature& left, const Temperature& right) noexcept {
  return left.Value() != right.Value();
}

inline constexpr bool operator<(const Temperature& left, const Temperature& right) noexcept {
  return left.Value() < right.Value();
}

inline constexpr bool operator>(const Temperature& left, const Temperature& right) noexcept {
  return left.Value() > right.Value();
}

inline constexpr bool operator<=(const Temperature& left, const Temperature& right) noexcept {
  return left.Value() <= right.Value();
}

inline constexpr bool operator>=(const Temperature& left, const Temperature& right) noexcept {
  return left.Value() >= right.Value();
}

inline std::ostream& operator<<(std::ostream& stream, const Temperature& temperature) {
  stream << temperature.Print();
  return stream;
}

inline constexpr Temperature operator*(const double number, const Temperature& temperature) {
  return temperature * number;
}

inline constexpr Temperature TemperatureDifference::operator+(
    const Temperature& temperature) const {
  return Temperature{value_ + temperature.Value()};
}

inline constexpr Temperature TemperatureDifference::operator-(
    const Temperature& temperature) const {
  return Temperature{value_ - temperature.Value()};
}

}  // namespace PhQ

namespace std {

template <>
struct hash<PhQ::Temperature> {
  inline size_t operator()(const PhQ::Temperature& temperature) const {
    return hash<double>()(temperature.Value());
  }
};

}  // namespace std

#endif  // PHYSICAL_QUANTITIES_INCLUDE_PHQ_TEMPERATURE_HPP
