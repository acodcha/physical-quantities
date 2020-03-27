#pragma once

#include "Area.hpp"
#include "Unit/Volume.hpp"

namespace PhQ {

class Volume : public DimensionalScalarQuantity<Unit::Volume> {

public:

  constexpr Volume() noexcept : DimensionalScalarQuantity<Unit::Volume>() {}

  constexpr Volume(double value, Unit::Volume unit) noexcept : DimensionalScalarQuantity<Unit::Volume>(value, unit) {}

  constexpr bool operator==(const Volume& volume) const noexcept {
    return value_ == volume.value_;
  }

  constexpr bool operator!=(const Volume& volume) const noexcept {
    return value_ != volume.value_;
  }

  constexpr bool operator<(const Volume& volume) const noexcept {
    return value_ < volume.value_;
  }

  constexpr bool operator<=(const Volume& volume) const noexcept {
    return value_ <= volume.value_;
  }

  constexpr bool operator>(const Volume& volume) const noexcept {
    return value_ > volume.value_;
  }

  constexpr bool operator>=(const Volume& volume) const noexcept {
    return value_ >= volume.value_;
  }

  Volume operator+(const Volume& volume) const noexcept {
    return {value_ + volume.value_};
  }

  constexpr void operator+=(const Volume& volume) noexcept {
    value_ += volume.value_;
  }

  Volume operator-(const Volume& volume) const noexcept {
    return {value_ - volume.value_};
  }

  constexpr void operator-=(const Volume& volume) noexcept {
    value_ -= volume.value_;
  }

  Area operator/(const Length& length) const {
    if (length.value_ != 0.0) {
      return {value_ / length.value_};
    } else {
      throw std::runtime_error{"Division of " + print() + " by " + length.print() + "."};
    }
  }

  Length operator/(const Area& area) const {
    if (area.value_ != 0.0) {
      return {value_ / area.value_};
    } else {
      throw std::runtime_error{"Division of " + print() + " by " + area.print() + "."};
    }
  }

protected:

  constexpr Volume(double value) noexcept : DimensionalScalarQuantity<Unit::Volume>(value) {}

  friend class Area;

  friend class Length;

};

Volume Length::operator*(const Area& area) const noexcept {
  return {value_ * area.value_};
}

Volume Area::operator*(const Length& length) const noexcept {
  return {value_ * length.value_};
}


} // namespace PhQ
