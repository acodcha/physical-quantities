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

#ifndef PHYSICAL_QUANTITIES_INCLUDE_PHQ_AREA_VECTOR_HPP
#define PHYSICAL_QUANTITIES_INCLUDE_PHQ_AREA_VECTOR_HPP

#include "Angle.hpp"
#include "Area.hpp"
#include "DimensionalVectorQuantity.hpp"
#include "Direction.hpp"

namespace PhQ {

// Vector area.
class AreaVector : public DimensionalVectorQuantity<Unit::Area> {
public:
  constexpr AreaVector() noexcept : DimensionalVectorQuantity<Unit::Area>() {}

  AreaVector(const Value::Vector& value, const Unit::Area unit) noexcept
    : DimensionalVectorQuantity<Unit::Area>(value, unit) {}

  constexpr AreaVector(const Area& area, const Direction& direction) noexcept
    : AreaVector(area.Value() * direction.Value()) {}

  static constexpr AreaVector Zero() noexcept {
    return AreaVector{Value::Vector::Zero()};
  }

  template<Unit::Area Unit>
  static constexpr AreaVector Create(const Value::Vector& value) noexcept {
    return AreaVector{
        StaticConvertCopy<Unit::Area, Unit, Standard<Unit::Area>>(value)};
  }

  Area Magnitude() const noexcept { return {*this}; }

  PhQ::Angle Angle(const AreaVector& area_vector) const noexcept {
    return {*this, area_vector};
  }

  constexpr AreaVector operator+(const AreaVector& area_vector) const noexcept {
    return AreaVector{value_ + area_vector.value_};
  }

  constexpr AreaVector operator-(const AreaVector& area_vector) const noexcept {
    return AreaVector{value_ - area_vector.value_};
  }

  constexpr AreaVector operator*(const double number) const noexcept {
    return AreaVector{value_ * number};
  }

  constexpr AreaVector operator/(const double number) const noexcept {
    return AreaVector{value_ / number};
  }

  constexpr void operator+=(const AreaVector& area_vector) noexcept {
    value_ += area_vector.value_;
  }

  constexpr void operator-=(const AreaVector& area_vector) noexcept {
    value_ -= area_vector.value_;
  }

  constexpr void operator*=(const double number) noexcept { value_ *= number; }

  constexpr void operator/=(const double number) noexcept { value_ /= number; }

private:
  explicit constexpr AreaVector(const Value::Vector& value) noexcept
    : DimensionalVectorQuantity<Unit::Area>(value) {}
};

inline constexpr bool operator==(
    const AreaVector& left, const AreaVector& right) noexcept {
  return left.Value() == right.Value();
}

inline constexpr bool operator!=(
    const AreaVector& left, const AreaVector& right) noexcept {
  return left.Value() != right.Value();
}

inline constexpr bool operator<(
    const AreaVector& left, const AreaVector& right) noexcept {
  return left.Value() < right.Value();
}

inline constexpr bool operator>(
    const AreaVector& left, const AreaVector& right) noexcept {
  return left.Value() > right.Value();
}

inline constexpr bool operator<=(
    const AreaVector& left, const AreaVector& right) noexcept {
  return left.Value() <= right.Value();
}

inline constexpr bool operator>=(
    const AreaVector& left, const AreaVector& right) noexcept {
  return left.Value() >= right.Value();
}

inline std::ostream& operator<<(
    std::ostream& stream, const AreaVector& area_vector) noexcept {
  stream << area_vector.Print();
  return stream;
}

inline constexpr AreaVector operator*(
    const double number, const AreaVector& area_vector) noexcept {
  return area_vector * number;
}

inline Direction::Direction(const AreaVector& area_vector) noexcept
  : Direction(area_vector.Value()) {}

inline Angle::Angle(
    const AreaVector& area_vector_1, const AreaVector& area_vector_2) noexcept
  : Angle(area_vector_1.Value(), area_vector_2.Value()) {}

inline Area::Area(const AreaVector& area_vector) noexcept
  : Area(area_vector.Value().Magnitude()) {}

inline constexpr AreaVector Direction::operator*(
    const Area& area) const noexcept {
  return {area, *this};
}

inline constexpr AreaVector Area::operator*(
    const Direction& direction) const noexcept {
  return {*this, direction};
}

}  // namespace PhQ

namespace std {

template<> struct hash<PhQ::AreaVector> {
  inline size_t operator()(const PhQ::AreaVector& area_vector) const {
    return hash<PhQ::Value::Vector>()(area_vector.Value());
  }
};

}  // namespace std

#endif  // PHYSICAL_QUANTITIES_INCLUDE_PHQ_AREA_VECTOR_HPP
