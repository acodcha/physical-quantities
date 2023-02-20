// Copyright 2020 Alexandre Coderre-Chabot
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

#ifndef PHYSICAL_QUANTITIES_INCLUDE_PHQ_VALUE_VECTOR_HPP
#define PHYSICAL_QUANTITIES_INCLUDE_PHQ_VALUE_VECTOR_HPP

#include "../Direction.hpp"

namespace PhQ {

namespace Value {

class Vector {
public:
  constexpr Vector() noexcept : x_(), y_(), z_() {}

  constexpr Vector(const double x, const double y, const double z) noexcept
      : x_(x), y_(y), z_(z) {}

  constexpr Vector(const std::array<double, 3>& x_y_z) noexcept
      : x_(x_y_z[0]), y_(x_y_z[1]), z_(x_y_z[2]) {}

  constexpr Vector(double value, const Direction& direction) noexcept
      : x_(value * direction.x()),
        y_(value * direction.y()),
        z_(value * direction.z()) {}

  static constexpr Vector Zero() noexcept { return {0.0, 0.0, 0.0}; }

  inline constexpr double x() const noexcept { return x_; }

  inline constexpr double y() const noexcept { return y_; }

  inline constexpr double z() const noexcept { return z_; }

  inline constexpr double MagnitudeSquared() const noexcept {
    return x_ * x_ + y_ * y_ + z_ * z_;
  }

  inline double Magnitude() const noexcept {
    return std::sqrt(MagnitudeSquared());
  }

  PhQ::Direction Direction() const { return {*this}; }

  constexpr double Dot(const PhQ::Direction& direction) const noexcept {
    return x_ * direction.x() + y_ * direction.y() + z_ * direction.z();
  }

  constexpr double Dot(const Vector& vector) const noexcept {
    return x_ * vector.x_ + y_ * vector.y_ + z_ * vector.z_;
  }

  constexpr Vector Cross(const PhQ::Direction& direction) const noexcept {
    return {y_ * direction.z() - z_ * direction.y(),
            z_ * direction.x() - x_ * direction.z(),
            x_ * direction.y() - y_ * direction.x()};
  }

  constexpr Vector Cross(const Vector& vector) const noexcept {
    return {y_ * vector.z_ - z_ * vector.y_, z_ * vector.x_ - x_ * vector.z_,
            x_ * vector.y_ - y_ * vector.x_};
  }

  constexpr Dyad Dyadic(const PhQ::Direction& direction) const noexcept;

  constexpr Dyad Dyadic(const Vector& vector) const noexcept;

  constexpr PhQ::Angle Angle(const PhQ::Direction& direction) const noexcept;

  constexpr PhQ::Angle Angle(const Vector& vector) const noexcept;

  std::string Print() const noexcept {
    return "(" + PhQ::Print(x_) + ", " + PhQ::Print(y_) + ", " +
           PhQ::Print(z_) + ")";
  }

  std::string Json() const noexcept {
    return "{\"x\":" + PhQ::Print(x_) + ",\"y\":" + PhQ::Print(y_) +
           ",\"z\":" + PhQ::Print(z_) + "}";
  }

  std::string Xml() const noexcept {
    return "<x>" + PhQ::Print(x_) + "</x><y>" + PhQ::Print(y_) + "</y><z>" +
           PhQ::Print(z_) + "</z>";
  }

  std::string Yaml() const noexcept {
    return "{x:" + PhQ::Print(x_) + ",y:" + PhQ::Print(y_) +
           ",z:" + PhQ::Print(z_) + "}";
  }

  constexpr void operator+=(const Vector& vector) noexcept {
    x_ += vector.x_;
    y_ += vector.y_;
    z_ += vector.z_;
  }

  constexpr void operator-=(const Vector& vector) noexcept {
    x_ -= vector.x_;
    y_ -= vector.y_;
    z_ -= vector.z_;
  }

  constexpr void operator*=(const double real) noexcept {
    x_ *= real;
    y_ *= real;
    z_ *= real;
  }

  constexpr void operator/=(const double real) noexcept {
    x_ /= real;
    y_ /= real;
    z_ /= real;
  }

private:
  double x_;

  double y_;

  double z_;
};

constexpr bool operator==(const Vector& left, const Vector& right) noexcept {
  return left.x() == right.x() && left.y() == right.y() &&
         left.z() == right.z();
}

constexpr bool operator!=(const Vector& left, const Vector& right) noexcept {
  return left.x() != right.x() || left.y() != right.y() ||
         left.z() != right.z();
}

constexpr Vector operator+(const Vector& left, const Vector& right) noexcept {
  return {left.x() + right.x(), left.y() + right.y(), left.z() + right.z()};
}

constexpr Vector operator-(const Vector& left, const Vector& right) noexcept {
  return {left.x() - right.x(), left.y() - right.y(), left.z() - right.z()};
}

constexpr Vector operator*(const Vector& vector, const double real) noexcept {
  return {vector.x() * real, vector.y() * real, vector.z() * real};
}

constexpr Vector operator*(const double real, const Vector& vector) noexcept {
  return {vector * real};
}

constexpr Vector operator/(const Vector& vector, const double real) noexcept {
  return {vector.x() / real, vector.y() / real, vector.z() / real};
}

std::ostream& operator<<(std::ostream& stream, const Vector& vector) noexcept {
  stream << vector.Print();
  return stream;
}

}  // namespace Value

Direction::Direction(const Value::Vector& vector)
    : Direction(vector.x(), vector.y(), vector.z()) {}

constexpr double Direction::Dot(const Value::Vector& vector) const noexcept {
  return x_y_z_[0] * vector.x() + x_y_z_[1] * vector.y() +
         x_y_z_[2] * vector.z();
}

constexpr Value::Vector Direction::Cross(
    const Value::Vector& vector) const noexcept {
  return {x_y_z_[1] * vector.z() - x_y_z_[2] * vector.y(),
          x_y_z_[2] * vector.x() - x_y_z_[0] * vector.z(),
          x_y_z_[0] * vector.y() - x_y_z_[1] * vector.x()};
}

}  // namespace PhQ

namespace std {

template <>
struct hash<PhQ::Value::Vector> {
  size_t operator()(const PhQ::Value::Vector& vector) const {
    size_t result = 17;
    result = 31 * result + hash<double>()(vector.x());
    result = 31 * result + hash<double>()(vector.y());
    result = 31 * result + hash<double>()(vector.z());
    return result;
  }
};

}  // namespace std

#endif  // PHYSICAL_QUANTITIES_INCLUDE_PHQ_VALUE_VECTOR_HPP
