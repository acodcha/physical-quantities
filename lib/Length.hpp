#pragma once

#include "Quantity/DimensionalScalar.hpp"
#include "Unit/Length.hpp"

namespace PhQ {

// Forward declarations.
class Area;
class Volume;
class Duration;
class Speed;
class Position;
class Displacement;
class Frequency;

class Length : public DimensionalScalarQuantity<Unit::Length> {

public:

  constexpr Length() noexcept : DimensionalScalarQuantity<Unit::Length>() {}

  constexpr Length(double value, Unit::Length unit) noexcept : DimensionalScalarQuantity<Unit::Length>(value, unit) {}

  constexpr Length(const Displacement& displacement) noexcept;

  constexpr bool operator==(const Length& length) const noexcept {
    return value_ == length.value_;
  }

  constexpr bool operator!=(const Length& length) const noexcept {
    return value_ != length.value_;
  }

  constexpr bool operator<(const Length& length) const noexcept {
    return value_ < length.value_;
  }

  constexpr bool operator<=(const Length& length) const noexcept {
    return value_ <= length.value_;
  }

  constexpr bool operator>(const Length& length) const noexcept {
    return value_ > length.value_;
  }

  constexpr bool operator>=(const Length& length) const noexcept {
    return value_ >= length.value_;
  }

  Length operator+(const Length& length) const noexcept {
    return {value_ + length.value_};
  }

  constexpr void operator+=(const Length& length) noexcept {
    value_ += length.value_;
  }

  Length operator-(const Length& length) const noexcept {
    return {value_ - length.value_};
  }

  constexpr void operator-=(const Length& length) noexcept {
    value_ -= length.value_;
  }

  constexpr Area operator*(const Length& length) const noexcept;

  constexpr Volume operator*(const Area& area) const noexcept;

  constexpr Speed operator*(const Frequency& frequency) const noexcept;

  Speed operator/(const Duration& time) const;

protected:

  constexpr Length(double value) noexcept : DimensionalScalarQuantity<Unit::Length>(value) {}

  friend class Area;

  friend class Volume;

  friend class Duration;

  friend class Speed;

  friend class Position;

  friend class Displacement;

  friend class Frequency;

};

} // namespace PhQ
