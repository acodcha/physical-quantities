#pragma once

#include "AngularSpeed.hpp"
#include "Unit/AngularAcceleration.hpp"

namespace PhQ {


class AngularAccelerationMagnitude : public DimensionalScalarQuantity<Unit::AngularAcceleration> {

public:

  constexpr AngularAccelerationMagnitude() noexcept : DimensionalScalarQuantity<Unit::AngularAcceleration>() {}

  constexpr AngularAccelerationMagnitude(double value, Unit::AngularAcceleration unit) noexcept : DimensionalScalarQuantity<Unit::AngularAcceleration>(value, unit) {}

  constexpr bool operator==(const AngularAccelerationMagnitude& angular_acceleration_magnitude) const noexcept {
    return value_ == angular_acceleration_magnitude.value_;
  }

  constexpr bool operator!=(const AngularAccelerationMagnitude& angular_acceleration_magnitude) const noexcept {
    return value_ != angular_acceleration_magnitude.value_;
  }

  constexpr bool operator<(const AngularAccelerationMagnitude& angular_acceleration_magnitude) const noexcept {
    return value_ < angular_acceleration_magnitude.value_;
  }

  constexpr bool operator<=(const AngularAccelerationMagnitude& angular_acceleration_magnitude) const noexcept {
    return value_ <= angular_acceleration_magnitude.value_;
  }

  constexpr bool operator>(const AngularAccelerationMagnitude& angular_acceleration_magnitude) const noexcept {
    return value_ > angular_acceleration_magnitude.value_;
  }

  constexpr bool operator>=(const AngularAccelerationMagnitude& angular_acceleration_magnitude) const noexcept {
    return value_ >= angular_acceleration_magnitude.value_;
  }

  constexpr AngularAccelerationMagnitude operator+(const AngularAccelerationMagnitude& angular_acceleration_magnitude) const noexcept {
    return {value_ + angular_acceleration_magnitude.value_};
  }

  constexpr void operator+=(const AngularAccelerationMagnitude& angular_acceleration_magnitude) noexcept {
    value_ += angular_acceleration_magnitude.value_;
  }

  constexpr AngularAccelerationMagnitude operator-(const AngularAccelerationMagnitude& angular_acceleration_magnitude) const noexcept {
    return {value_ - angular_acceleration_magnitude.value_};
  }

  constexpr void operator-=(const AngularAccelerationMagnitude& angular_acceleration_magnitude) noexcept {
    value_ -= angular_acceleration_magnitude.value_;
  }

  constexpr AngularSpeed operator*(const Duration& duration) const noexcept {
    return {value_ * duration.value_};
  }

  AngularSpeed operator/(const Frequency& frequency) const {
    if (frequency.value_ != 0.0) {
      return {value_ / frequency.value_};
    } else {
      throw std::runtime_error{"Division of " + print() + " by " + frequency.print() + "."};
    }
  }

protected:

  constexpr AngularAccelerationMagnitude(double value) noexcept : DimensionalScalarQuantity<Unit::AngularAcceleration>(value) {}

  friend class AngularSpeed;
  friend class Duration;
  friend class Frequency;

};

constexpr AngularAccelerationMagnitude Frequency::operator*(const AngularSpeed& angular_speed) const noexcept {
  return {value_ * angular_speed.value_};
}

constexpr AngularAccelerationMagnitude AngularSpeed::operator*(const Frequency& frequency) const noexcept {
  return {value_ * frequency.value_};
}

AngularAccelerationMagnitude AngularSpeed::operator/(const Duration& duration) const {
  if (duration.value_ != 0.0) {
    return {value_ / duration.value_};
  } else {
    throw std::runtime_error{"Division of " + print() + " by " + duration.print() + "."};
  }
}

} // namespace PhQ