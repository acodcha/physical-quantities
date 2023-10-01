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

#ifndef PHYSICAL_QUANTITIES_INCLUDE_PHQ_DYNAMIC_KINEMATIC_PRESSURE_HPP
#define PHYSICAL_QUANTITIES_INCLUDE_PHQ_DYNAMIC_KINEMATIC_PRESSURE_HPP

#include "DynamicPressure.hpp"
#include "StaticKinematicPressure.hpp"

namespace PhQ {

// Forward declaration for class DynamicKinematicPressure.
class TotalKinematicPressure;

// Dynamic kinematic pressure. Dynamic pressure is the component of pressure
// arising from a fluid's kinetic energy. Kinematic pressure is pressure divided
// by mass density, so dynamic kinematic pressure is dynamic pressure divided by
// mass density.
class DynamicKinematicPressure
  : public DimensionalScalarQuantity<Unit::SpecificEnergy> {
public:
  // Default constructor. Constructs a dynamic kinematic pressure with an
  // uninitialized value.
  DynamicKinematicPressure() = default;

  // Constructor. Constructs a dynamic kinematic pressure with a given value
  // expressed in a given specific energy unit.
  DynamicKinematicPressure(const double value, const Unit::SpecificEnergy unit)
    : DimensionalScalarQuantity<Unit::SpecificEnergy>(value, unit) {}

  // Constructor. Constructs a dynamic kinematic pressure from a given speed
  // using the definition of dynamic kinematic pressure.
  constexpr DynamicKinematicPressure(const Speed& speed)
    : DynamicKinematicPressure(0.5 * std::pow(speed.Value(), 2)) {}

  // Constructor. Constructs a dynamic kinematic pressure from a given total
  // kinematic pressure and static kinematic pressure using the definition of
  // total kinematic pressure.
  constexpr DynamicKinematicPressure(
      const TotalKinematicPressure& total_kinematic_pressure,
      const StaticKinematicPressure& static_kinematic_pressure);

  // Constructor. Constructs a dynamic kinematic pressure from a given dynamic
  // pressure and mass density using the definition of dynamic kinematic
  // pressure.
  constexpr DynamicKinematicPressure(
      const DynamicPressure& dynamic_pressure, const MassDensity& mass_density)
    : DynamicKinematicPressure(
        dynamic_pressure.Value() / mass_density.Value()) {}

  // Destructor. Destroys this dynamic kinematic pressure.
  ~DynamicKinematicPressure() noexcept = default;

  // Copy constructor. Constructs a dynamic kinematic pressure by copying
  // another one.
  constexpr DynamicKinematicPressure(
      const DynamicKinematicPressure& other) = default;

  // Move constructor. Constructs a dynamic kinematic pressure by moving another
  // one.
  constexpr DynamicKinematicPressure(
      DynamicKinematicPressure&& other) noexcept = default;

  // Copy assignment operator. Assigns this dynamic kinematic pressure by
  // copying another one.
  constexpr DynamicKinematicPressure& operator=(
      const DynamicKinematicPressure& other) = default;

  // Move assignment operator. Assigns this dynamic kinematic pressure by moving
  // another one.
  constexpr DynamicKinematicPressure& operator=(
      DynamicKinematicPressure&& other) noexcept = default;

  // Statically creates a dynamic kinematic pressure of zero.
  static constexpr DynamicKinematicPressure Zero() {
    return DynamicKinematicPressure{0.0};
  }

  // Statically creates a dynamic kinematic pressure with a given value
  // expressed in a given specific energy unit.
  template <Unit::SpecificEnergy Unit>
  static constexpr DynamicKinematicPressure Create(const double value) {
    return DynamicKinematicPressure{
        StaticConvertCopy<Unit::SpecificEnergy, Unit,
                          Standard<Unit::SpecificEnergy>>(value)};
  }

  constexpr DynamicKinematicPressure operator+(
      const DynamicKinematicPressure& dynamic_kinematic_pressure) const {
    return DynamicKinematicPressure{value_ + dynamic_kinematic_pressure.value_};
  }

  constexpr TotalKinematicPressure operator+(
      const StaticKinematicPressure& static_kinematic_pressure) const;

  constexpr DynamicKinematicPressure operator-(
      const DynamicKinematicPressure& dynamic_kinematic_pressure) const {
    return DynamicKinematicPressure{value_ - dynamic_kinematic_pressure.value_};
  }

  constexpr DynamicKinematicPressure operator*(const double number) const {
    return DynamicKinematicPressure{value_ * number};
  }

  constexpr DynamicKinematicPressure operator/(const double number) const {
    return DynamicKinematicPressure{value_ / number};
  }

  constexpr double
  operator/(const DynamicKinematicPressure& dynamic_kinematic_pressure)
      const noexcept {
    return value_ / dynamic_kinematic_pressure.value_;
  }

  constexpr void operator+=(
      const DynamicKinematicPressure& dynamic_kinematic_pressure) noexcept {
    value_ += dynamic_kinematic_pressure.value_;
  }

  constexpr void operator-=(
      const DynamicKinematicPressure& dynamic_kinematic_pressure) noexcept {
    value_ -= dynamic_kinematic_pressure.value_;
  }

  constexpr void operator*=(const double number) noexcept {
    value_ *= number;
  }

  constexpr void operator/=(const double number) noexcept {
    value_ /= number;
  }

private:
  // Constructor. Constructs a dynamic kinematic pressure with a given value
  // expressed in the standard specific energy unit.
  explicit constexpr DynamicKinematicPressure(const double value)
    : DimensionalScalarQuantity<Unit::SpecificEnergy>(value) {}
};

inline constexpr bool operator==(
    const DynamicKinematicPressure& left,
    const DynamicKinematicPressure& right) noexcept {
  return left.Value() == right.Value();
}

inline constexpr bool operator!=(
    const DynamicKinematicPressure& left,
    const DynamicKinematicPressure& right) noexcept {
  return left.Value() != right.Value();
}

inline constexpr bool operator<(
    const DynamicKinematicPressure& left,
    const DynamicKinematicPressure& right) noexcept {
  return left.Value() < right.Value();
}

inline constexpr bool operator>(
    const DynamicKinematicPressure& left,
    const DynamicKinematicPressure& right) noexcept {
  return left.Value() > right.Value();
}

inline constexpr bool operator<=(
    const DynamicKinematicPressure& left,
    const DynamicKinematicPressure& right) noexcept {
  return left.Value() <= right.Value();
}

inline constexpr bool operator>=(
    const DynamicKinematicPressure& left,
    const DynamicKinematicPressure& right) noexcept {
  return left.Value() >= right.Value();
}

inline std::ostream& operator<<(
    std::ostream& stream,
    const DynamicKinematicPressure& dynamic_kinematic_pressure) {
  stream << dynamic_kinematic_pressure.Print();
  return stream;
}

inline constexpr DynamicKinematicPressure operator*(
    const double number,
    const DynamicKinematicPressure& dynamic_kinematic_pressure) {
  return dynamic_kinematic_pressure * number;
}

inline Speed::Speed(const DynamicKinematicPressure& dynamic_kinematic_pressure)
  : Speed(std::sqrt(2.0 * dynamic_kinematic_pressure.Value())) {}

inline constexpr DynamicPressure::DynamicPressure(
    const DynamicKinematicPressure& dynamic_kinematic_pressure,
    const MassDensity& mass_density)
  : DynamicPressure(dynamic_kinematic_pressure.Value() * mass_density.Value()) {
}

}  // namespace PhQ

namespace std {

template <>
struct hash<PhQ::DynamicKinematicPressure> {
  inline size_t operator()(
      const PhQ::DynamicKinematicPressure& dynamic_kinematic_pressure) const {
    return hash<double>()(dynamic_kinematic_pressure.Value());
  }
};

}  // namespace std

#endif  // PHYSICAL_QUANTITIES_INCLUDE_PHQ_DYNAMIC_KINEMATIC_PRESSURE_HPP
