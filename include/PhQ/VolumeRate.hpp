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

#ifndef PHYSICAL_QUANTITIES_INCLUDE_PHQ_VOLUME_RATE_HPP
#define PHYSICAL_QUANTITIES_INCLUDE_PHQ_VOLUME_RATE_HPP

#include <cstddef>
#include <functional>
#include <ostream>

#include "DimensionalScalar.hpp"
#include "Frequency.hpp"
#include "Time.hpp"
#include "Unit/VolumeRate.hpp"
#include "Volume.hpp"

namespace PhQ {

// Volume rate. Can represent a time rate of change of a volume or a volume flow rate.
class VolumeRate : public DimensionalScalar<Unit::VolumeRate> {
public:
  // Default constructor. Constructs a volume rate with an uninitialized value.
  VolumeRate() = default;

  // Constructor. Constructs a volume rate with a given value expressed in a given volume rate unit.
  VolumeRate(const double value, const Unit::VolumeRate unit)
    : DimensionalScalar<Unit::VolumeRate>(value, unit) {}

  // Constructor. Constructs a volume rate from a given volume and time using the definition of
  // volume rate.
  constexpr VolumeRate(const Volume& volume, const Time& time)
    : VolumeRate(volume.Value() / time.Value()) {}

  // Constructor. Constructs a volume rate from a given volume and frequency using the definition of
  // volume rate.
  constexpr VolumeRate(const Volume& volume, const Frequency& frequency)
    : VolumeRate(volume.Value() * frequency.Value()) {}

  // Destructor. Destroys this volume rate.
  ~VolumeRate() noexcept = default;

  // Copy constructor. Constructs a volume rate by copying another one.
  constexpr VolumeRate(const VolumeRate& other) = default;

  // Move constructor. Constructs a volume rate by moving another one.
  constexpr VolumeRate(VolumeRate&& other) noexcept = default;

  // Copy assignment operator. Assigns this volume rate by copying another one.
  constexpr VolumeRate& operator=(const VolumeRate& other) = default;

  // Move assignment operator. Assigns this volume rate by moving another one.
  constexpr VolumeRate& operator=(VolumeRate&& other) noexcept = default;

  // Statically creates a volume rate of zero.
  static constexpr VolumeRate Zero() {
    return VolumeRate{0.0};
  }

  // Statically creates a volume rate with a given value expressed in a given volume rate unit.
  template <Unit::VolumeRate Unit>
  static constexpr VolumeRate Create(const double value) {
    return VolumeRate{StaticConvertCopy<Unit::VolumeRate, Unit, Standard<Unit::VolumeRate>>(value)};
  }

  constexpr VolumeRate operator+(const VolumeRate& volume_rate) const {
    return VolumeRate{value_ + volume_rate.value_};
  }

  constexpr VolumeRate operator-(const VolumeRate& volume_rate) const {
    return VolumeRate{value_ - volume_rate.value_};
  }

  constexpr VolumeRate operator*(const double number) const {
    return VolumeRate{value_ * number};
  }

  constexpr Volume operator*(const Time& time) const {
    return {*this, time};
  }

  constexpr VolumeRate operator/(const double number) const {
    return VolumeRate{value_ / number};
  }

  constexpr Volume operator/(const Frequency& frequency) const {
    return {*this, frequency};
  }

  constexpr Frequency operator/(const Volume& volume) const {
    return {*this, volume};
  }

  constexpr double operator/(const VolumeRate& volume_rate) const noexcept {
    return value_ / volume_rate.value_;
  }

  constexpr void operator+=(const VolumeRate& volume_rate) noexcept {
    value_ += volume_rate.value_;
  }

  constexpr void operator-=(const VolumeRate& volume_rate) noexcept {
    value_ -= volume_rate.value_;
  }

  constexpr void operator*=(const double number) noexcept {
    value_ *= number;
  }

  constexpr void operator/=(const double number) noexcept {
    value_ /= number;
  }

private:
  // Constructor. Constructs a volume rate with a given value expressed in the standard volume rate
  // unit.
  explicit constexpr VolumeRate(const double value) : DimensionalScalar<Unit::VolumeRate>(value) {}
};

inline constexpr bool operator==(const VolumeRate& left, const VolumeRate& right) noexcept {
  return left.Value() == right.Value();
}

inline constexpr bool operator!=(const VolumeRate& left, const VolumeRate& right) noexcept {
  return left.Value() != right.Value();
}

inline constexpr bool operator<(const VolumeRate& left, const VolumeRate& right) noexcept {
  return left.Value() < right.Value();
}

inline constexpr bool operator>(const VolumeRate& left, const VolumeRate& right) noexcept {
  return left.Value() > right.Value();
}

inline constexpr bool operator<=(const VolumeRate& left, const VolumeRate& right) noexcept {
  return left.Value() <= right.Value();
}

inline constexpr bool operator>=(const VolumeRate& left, const VolumeRate& right) noexcept {
  return left.Value() >= right.Value();
}

inline std::ostream& operator<<(std::ostream& stream, const VolumeRate& volume_rate) {
  stream << volume_rate.Print();
  return stream;
}

inline constexpr VolumeRate operator*(const double number, const VolumeRate& volume_rate) {
  return volume_rate * number;
}

inline constexpr Volume::Volume(const VolumeRate& volume_rate, const Time& time)
  : Volume(volume_rate.Value() * time.Value()) {}

inline constexpr Volume::Volume(const VolumeRate& volume_rate, const Frequency& frequency)
  : Volume(volume_rate.Value() / frequency.Value()) {}

inline constexpr Time::Time(const Volume& volume, const VolumeRate& volume_rate)
  : Time(volume.Value() / volume_rate.Value()) {}

inline constexpr Frequency::Frequency(const VolumeRate& volume_rate, const Volume& volume)
  : Frequency(volume_rate.Value() / volume.Value()) {}

inline constexpr Volume Time::operator*(const VolumeRate& volume_rate) const {
  return {volume_rate, *this};
}

inline constexpr VolumeRate Volume::operator*(const Frequency& frequency) const {
  return {*this, frequency};
}

inline constexpr Time Volume::operator/(const VolumeRate& volume_rate) const {
  return {*this, volume_rate};
}

inline constexpr VolumeRate Frequency::operator*(const Volume& volume) const {
  return {volume, *this};
}

inline constexpr VolumeRate Volume::operator/(const Time& time) const {
  return {*this, time};
}

}  // namespace PhQ

namespace std {

template <>
struct hash<PhQ::VolumeRate> {
  inline size_t operator()(const PhQ::VolumeRate& volume_rate) const {
    return hash<double>()(volume_rate.Value());
  }
};

}  // namespace std

#endif  // PHYSICAL_QUANTITIES_INCLUDE_PHQ_VOLUME_RATE_HPP
