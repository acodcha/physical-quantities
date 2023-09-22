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

#ifndef PHYSICAL_QUANTITIES_INCLUDE_PHQ_ANGULAR_ACCELERATION_MAGNITUDE_HPP
#define PHYSICAL_QUANTITIES_INCLUDE_PHQ_ANGULAR_ACCELERATION_MAGNITUDE_HPP

#include "AngularSpeed.hpp"
#include "Unit/AngularAcceleration.hpp"

namespace PhQ {

// Planar angular acceleration scalar. Magnitude of angular acceleration vector.
// Time rate of change of angular speed. Typically measured in radians per
// square second.
class AngularAccelerationMagnitude
  : public DimensionalScalarQuantity<Unit::AngularAcceleration> {
public:
  constexpr AngularAccelerationMagnitude()
    : DimensionalScalarQuantity<Unit::AngularAcceleration>() {}

  AngularAccelerationMagnitude(
      const double value, const Unit::AngularAcceleration unit)
    : DimensionalScalarQuantity<Unit::AngularAcceleration>(value, unit) {}

  constexpr AngularAccelerationMagnitude(
      const AngularSpeed& angular_speed, const Time& time)
    : AngularAccelerationMagnitude(angular_speed.Value() / time.Value()) {}

  constexpr AngularAccelerationMagnitude(
      const AngularSpeed& angular_speed, const Frequency& frequency)
    : AngularAccelerationMagnitude(angular_speed.Value() * frequency.Value()) {}

  static constexpr AngularAccelerationMagnitude Zero() {
    return AngularAccelerationMagnitude{0.0};
  }

  template <Unit::AngularAcceleration Unit>
  static constexpr AngularAccelerationMagnitude Create(const double value) {
    return AngularAccelerationMagnitude{
        StaticConvertCopy<Unit::AngularAcceleration, Unit,
                          Standard<Unit::AngularAcceleration>>(value)};
  }

  constexpr AngularAccelerationMagnitude
  operator+(const AngularAccelerationMagnitude& angular_acceleration_magnitude)
      const {
    return AngularAccelerationMagnitude{
        value_ + angular_acceleration_magnitude.value_};
  }

  constexpr AngularAccelerationMagnitude
  operator-(const AngularAccelerationMagnitude& angular_acceleration_magnitude)
      const {
    return AngularAccelerationMagnitude{
        value_ - angular_acceleration_magnitude.value_};
  }

  constexpr AngularAccelerationMagnitude operator*(const double number) const {
    return AngularAccelerationMagnitude{value_ * number};
  }

  constexpr AngularSpeed operator*(const Time& time) const {
    return {*this, time};
  }

  constexpr AngularAccelerationMagnitude operator/(const double number) const {
    return AngularAccelerationMagnitude{value_ / number};
  }

  constexpr AngularSpeed operator/(const Frequency& frequency) const {
    return {*this, frequency};
  }

  constexpr Frequency operator/(const AngularSpeed& angular_speed) const {
    return {*this, angular_speed};
  }

  constexpr double
  operator/(const AngularAccelerationMagnitude& angular_acceleration_magnitude)
      const noexcept {
    return value_ / angular_acceleration_magnitude.value_;
  }

  constexpr void operator+=(const AngularAccelerationMagnitude&
                                angular_acceleration_magnitude) noexcept {
    value_ += angular_acceleration_magnitude.value_;
  }

  constexpr void operator-=(const AngularAccelerationMagnitude&
                                angular_acceleration_magnitude) noexcept {
    value_ -= angular_acceleration_magnitude.value_;
  }

  constexpr void operator*=(const double number) noexcept {
    value_ *= number;
  }

  constexpr void operator/=(const double number) noexcept {
    value_ /= number;
  }

private:
  explicit constexpr AngularAccelerationMagnitude(const double value)
    : DimensionalScalarQuantity<Unit::AngularAcceleration>(value) {}
};

inline constexpr bool operator==(
    const AngularAccelerationMagnitude& left,
    const AngularAccelerationMagnitude& right) noexcept {
  return left.Value() == right.Value();
}

inline constexpr bool operator!=(
    const AngularAccelerationMagnitude& left,
    const AngularAccelerationMagnitude& right) noexcept {
  return left.Value() != right.Value();
}

inline constexpr bool operator<(
    const AngularAccelerationMagnitude& left,
    const AngularAccelerationMagnitude& right) noexcept {
  return left.Value() < right.Value();
}

inline constexpr bool operator>(
    const AngularAccelerationMagnitude& left,
    const AngularAccelerationMagnitude& right) noexcept {
  return left.Value() > right.Value();
}

inline constexpr bool operator<=(
    const AngularAccelerationMagnitude& left,
    const AngularAccelerationMagnitude& right) noexcept {
  return left.Value() <= right.Value();
}

inline constexpr bool operator>=(
    const AngularAccelerationMagnitude& left,
    const AngularAccelerationMagnitude& right) noexcept {
  return left.Value() >= right.Value();
}

inline std::ostream& operator<<(
    std::ostream& stream,
    const AngularAccelerationMagnitude& angular_acceleration_magnitude) {
  stream << angular_acceleration_magnitude.Print();
  return stream;
}

inline constexpr AngularAccelerationMagnitude operator*(
    const double number,
    const AngularAccelerationMagnitude& angular_acceleration_magnitude) {
  return angular_acceleration_magnitude * number;
}

inline constexpr Time::Time(
    const AngularAccelerationMagnitude& angular_acceleration_magnitude,
    const AngularSpeed& angular_speed)
  : Time(angular_speed.Value() / angular_acceleration_magnitude.Value()) {}

inline constexpr Frequency::Frequency(
    const AngularAccelerationMagnitude& angular_acceleration_magnitude,
    const AngularSpeed& angular_speed)
  : Frequency(angular_acceleration_magnitude.Value() / angular_speed.Value()) {}

inline constexpr AngularSpeed::AngularSpeed(
    const AngularAccelerationMagnitude& angular_acceleration_magnitude,
    const Time& time)
  : AngularSpeed(angular_acceleration_magnitude.Value() * time.Value()) {}

inline constexpr AngularSpeed::AngularSpeed(
    const AngularAccelerationMagnitude& angular_acceleration_magnitude,
    const Frequency& frequency)
  : AngularSpeed(angular_acceleration_magnitude.Value() / frequency.Value()) {}

inline constexpr AngularAccelerationMagnitude Frequency::operator*(
    const AngularSpeed& angular_speed) const {
  return {angular_speed, *this};
}

inline constexpr AngularAccelerationMagnitude AngularSpeed::operator*(
    const Frequency& frequency) const {
  return {*this, frequency};
}

inline constexpr AngularAccelerationMagnitude AngularSpeed::operator/(
    const Time& time) const {
  return {*this, time};
}

inline constexpr Time AngularSpeed::operator/(
    const AngularAccelerationMagnitude& angular_acceleration_magnitude) const {
  return {angular_acceleration_magnitude, *this};
}

}  // namespace PhQ

namespace std {

template <>
struct hash<PhQ::AngularAccelerationMagnitude> {
  inline size_t operator()(
      const PhQ::AngularAccelerationMagnitude& angular_acceleration_magnitude)
      const {
    return hash<double>()(angular_acceleration_magnitude.Value());
  }
};

}  // namespace std

#endif  // PHYSICAL_QUANTITIES_INCLUDE_PHQ_ANGULAR_ACCELERATION_MAGNITUDE_HPP
