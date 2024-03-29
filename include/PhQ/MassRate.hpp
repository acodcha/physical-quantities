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

#ifndef PHYSICAL_QUANTITIES_INCLUDE_PHQ_MASS_RATE_HPP
#define PHYSICAL_QUANTITIES_INCLUDE_PHQ_MASS_RATE_HPP

#include <cstddef>
#include <functional>
#include <ostream>

#include "DimensionalScalar.hpp"
#include "Frequency.hpp"
#include "Mass.hpp"
#include "Time.hpp"
#include "Unit/MassRate.hpp"

namespace PhQ {

// Mass rate. Can represent the time rate of change of a mass or a mass flow
// rate.
class MassRate : public DimensionalScalar<Unit::MassRate> {
public:
  // Default constructor. Constructs a mass rate with an uninitialized value.
  MassRate() = default;

  // Constructor. Constructs a mass rate with a given value expressed in a given mass rate unit.
  MassRate(const double value, const Unit::MassRate unit)
    : DimensionalScalar<Unit::MassRate>(value, unit) {}

  // Constructor. Constructs a mass rate from a given mass and time using the definition of mass
  // rate.
  constexpr MassRate(const Mass& mass, const Time& time) : MassRate(mass.Value() / time.Value()) {}

  // Constructor. Constructs a mass rate from a given mass and frequency using the definition of
  // mass rate.
  constexpr MassRate(const Mass& mass, const Frequency& frequency)
    : MassRate(mass.Value() * frequency.Value()) {}

  // Destructor. Destroys this mass rate.
  ~MassRate() noexcept = default;

  // Copy constructor. Constructs a mass rate by copying another one.
  constexpr MassRate(const MassRate& other) = default;

  // Move constructor. Constructs a mass rate by moving another one.
  constexpr MassRate(MassRate&& other) noexcept = default;

  // Copy assignment operator. Assigns this mass rate by copying another one.
  constexpr MassRate& operator=(const MassRate& other) = default;

  // Move assignment operator. Assigns this mass rate by moving another one.
  constexpr MassRate& operator=(MassRate&& other) noexcept = default;

  // Statically creates a mass rate of zero.
  static constexpr MassRate Zero() {
    return MassRate{0.0};
  }

  // Statically creates a mass rate with a given value expressed in a given mass rate unit.
  template <Unit::MassRate Unit>
  static constexpr MassRate Create(const double value) {
    return MassRate{StaticConvertCopy<Unit::MassRate, Unit, Standard<Unit::MassRate>>(value)};
  }

  constexpr MassRate operator+(const MassRate& mass_rate) const {
    return MassRate{value_ + mass_rate.value_};
  }

  constexpr MassRate operator-(const MassRate& mass_rate) const {
    return MassRate{value_ - mass_rate.value_};
  }

  constexpr MassRate operator*(const double number) const {
    return MassRate{value_ * number};
  }

  constexpr Mass operator*(const Time& time) const {
    return {*this, time};
  }

  constexpr MassRate operator/(const double number) const {
    return MassRate{value_ / number};
  }

  constexpr Frequency operator/(const Mass& mass) const {
    return {*this, mass};
  }

  constexpr Mass operator/(const Frequency& frequency) const {
    return {*this, frequency};
  }

  constexpr double operator/(const MassRate& mass_rate) const noexcept {
    return value_ / mass_rate.value_;
  }

  constexpr void operator+=(const MassRate& mass_rate) noexcept {
    value_ += mass_rate.value_;
  }

  constexpr void operator-=(const MassRate& mass_rate) noexcept {
    value_ -= mass_rate.value_;
  }

  constexpr void operator*=(const double number) noexcept {
    value_ *= number;
  }

  constexpr void operator/=(const double number) noexcept {
    value_ /= number;
  }

private:
  // Constructor. Constructs a mass rate with a given value expressed in the standard mass rate
  // unit.
  explicit constexpr MassRate(const double value) : DimensionalScalar<Unit::MassRate>(value) {}
};

inline constexpr bool operator==(const MassRate& left, const MassRate& right) noexcept {
  return left.Value() == right.Value();
}

inline constexpr bool operator!=(const MassRate& left, const MassRate& right) noexcept {
  return left.Value() != right.Value();
}

inline constexpr bool operator<(const MassRate& left, const MassRate& right) noexcept {
  return left.Value() < right.Value();
}

inline constexpr bool operator>(const MassRate& left, const MassRate& right) noexcept {
  return left.Value() > right.Value();
}

inline constexpr bool operator<=(const MassRate& left, const MassRate& right) noexcept {
  return left.Value() <= right.Value();
}

inline constexpr bool operator>=(const MassRate& left, const MassRate& right) noexcept {
  return left.Value() >= right.Value();
}

inline std::ostream& operator<<(std::ostream& stream, const MassRate& mass_rate) {
  stream << mass_rate.Print();
  return stream;
}

inline constexpr MassRate operator*(const double number, const MassRate& mass_rate) {
  return mass_rate * number;
}

inline constexpr Time::Time(const Mass& mass, const MassRate& mass_rate)
  : Time(mass.Value() / mass_rate.Value()) {}

inline constexpr Frequency::Frequency(const MassRate& mass_rate, const Mass& mass)
  : Frequency(mass_rate.Value() / mass.Value()) {}

inline constexpr Mass::Mass(const MassRate& mass_rate, const Time& time)
  : Mass(mass_rate.Value() * time.Value()) {}

inline constexpr Mass::Mass(const MassRate& mass_rate, const Frequency& frequency)
  : Mass(mass_rate.Value() / frequency.Value()) {}

inline constexpr Mass Time::operator*(const MassRate& mass_rate) const {
  return {mass_rate, *this};
}

inline constexpr MassRate Mass::operator*(const Frequency& frequency) const {
  return {*this, frequency};
}

inline constexpr MassRate Frequency::operator*(const Mass& mass) const {
  return {mass, *this};
}

inline constexpr MassRate Mass::operator/(const Time& time) const {
  return {*this, time};
}

inline constexpr Time Mass::operator/(const MassRate& mass_rate) const {
  return {*this, mass_rate};
}

}  // namespace PhQ

namespace std {

template <>
struct hash<PhQ::MassRate> {
  inline size_t operator()(const PhQ::MassRate& mass_rate) const {
    return hash<double>()(mass_rate.Value());
  }
};

}  // namespace std

#endif  // PHYSICAL_QUANTITIES_INCLUDE_PHQ_MASS_RATE_HPP
