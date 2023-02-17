// Copyright 2020 Alexandre Coderre-Chabot
// This file is part of Physical Quantities (PhQ), a C++ library of physical quantities, physical models, and units of measure for scientific computation.
// Physical Quantities is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// Physical Quantities is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
// You should have received a copy of the GNU Lesser General Public License along with Physical Quantities. If not, see <https://www.gnu.org/licenses/>.

#ifndef PHYSICAL_QUANTITIES_INCLUDE_PHQ_DIRECTION_HPP
#define PHYSICAL_QUANTITIES_INCLUDE_PHQ_DIRECTION_HPP

#include "Base/String.hpp"

namespace PhQ {

namespace Value {
class Vector;
class SymmetricDyadic;
class Dyadic;
}  // namespace Value

class Acceleration;
class AccelerationMagnitude;
class Area;
class AreaVector;
class Angle;
class Displacement;
class Force;
class ForceMagnitude;
class HeatFlux;
class HeatFluxMagnitude;
class Length;
class Position;
class Speed;
class StaticPressure;
class TemperatureGradient;
class TemperatureGradientMagnitude;
class Traction;
class Velocity;

class Direction {
public:
  constexpr Direction() noexcept : x_(1.0), y_(0.0), z_(0.0) {}

  Direction(const double x, const double y, const double z) {
    const double magnitude{std::sqrt(x * x + y * y + z * z)};
    if (magnitude > 0.0) {
      x_ = x / magnitude;
      y_ = y / magnitude;
      z_ = z / magnitude;
    } else {
      throw std::runtime_error{"Attempting to create a direction from (0, 0, 0)."};
    }
  }

  constexpr Direction(const Value::Vector& vector);

  constexpr Direction(const Acceleration& acceleration);

  constexpr Direction(const AreaVector& area_vector);

  constexpr Direction(const Displacement& displacement);

  constexpr Direction(const Force& force);

  constexpr Direction(const HeatFlux& heat_flux);

  constexpr Direction(const Position& position);

  constexpr Direction(const TemperatureGradient& temperature_gradient);

  constexpr Direction(const Traction& traction);

  constexpr Direction(const Velocity& velocity);

  constexpr double x() const noexcept {
    return x_;
  }

  constexpr double y() const noexcept {
    return y_;
  }

  constexpr double z() const noexcept {
    return z_;
  }

  constexpr double magnitude() const noexcept {
    return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
  }

  constexpr double dot(const Direction& direction) const noexcept {
    return x_ * direction.x_ + y_ * direction.y_ + z_ * direction.z_;
  }

  constexpr double dot(const Value::Vector& vector) const noexcept;

  Direction cross(const Direction& direction) const noexcept {
    return {
        y_ * direction.z_ - z_ * direction.y_,
        z_ * direction.x_ - x_ * direction.z_,
        x_ * direction.y_ - y_ * direction.x_};
  }

  constexpr Value::Vector cross(const Value::Vector& vector) const noexcept;

  constexpr Value::Dyadic dyadic(const Direction& direction) const noexcept;

  constexpr Value::Dyadic dyadic(const Value::Vector& vector) const noexcept;

  constexpr Angle angle(const Direction& direction) const noexcept;

  constexpr Angle angle(const Value::Vector& vector) const noexcept;

  std::string print() const noexcept {
    return "(" + PhQ::print(x_) + ", " + PhQ::print(y_) + ", " + PhQ::print(z_) + ")";
  }

  std::string json() const noexcept {
    return "{\"x\":" + PhQ::print(x_) + ",\"y\":" + PhQ::print(y_) + ",\"z\":" + PhQ::print(z_) + "}";
  }

  std::string xml() const noexcept {
    return "<x>" + PhQ::print(x_) + "</x><y>" + PhQ::print(y_) + "</y><z>" + PhQ::print(z_) + "</z>";
  }

  std::string yaml() const noexcept {
    return "{x:" + PhQ::print(x_) + ",y:" + PhQ::print(y_) + ",z:" + PhQ::print(z_) + "}";
  }

  constexpr Acceleration operator*(const AccelerationMagnitude& acceleration_magnitude) const noexcept;

  constexpr AreaVector operator*(const Area& area) const noexcept;

  constexpr Displacement operator*(const Length& length) const noexcept;

  constexpr Force operator*(const ForceMagnitude& force_magnitude) const noexcept;

  constexpr HeatFlux operator*(const HeatFluxMagnitude& heat_flux_magnitude) const noexcept;

  constexpr Traction operator*(const StaticPressure& static_pressure) const noexcept;

  constexpr Velocity operator*(const Speed& speed) const noexcept;

  constexpr TemperatureGradient operator*(const TemperatureGradientMagnitude& temperature_gradient_magnitude) const noexcept;

private:
  double x_;

  double y_;

  double z_;
};

constexpr bool operator==(const Direction& left, const Direction& right) noexcept {
  return left.x() == right.x() && left.y() == right.y() && left.z() == right.z();
}

constexpr bool operator!=(const Direction& left, const Direction& right) noexcept {
  return left.x() != right.x() || left.y() != right.y() || left.z() != right.z();
}

std::ostream& operator<<(std::ostream& output_stream, const Direction& direction) noexcept {
  output_stream << direction.print();
  return output_stream;
}

}  // namespace PhQ

namespace std {

template <> struct hash<PhQ::Direction> {
  size_t operator()(const PhQ::Direction& direction) const {
    size_t result = 17;
    result = 31 * result + hash<double>()(direction.x());
    result = 31 * result + hash<double>()(direction.y());
    result = 31 * result + hash<double>()(direction.z());
    return result;
  }
};

}  // namespace std

#endif  // PHYSICAL_QUANTITIES_INCLUDE_PHQ_DIRECTION_HPP
