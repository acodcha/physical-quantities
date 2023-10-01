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

#ifndef PHYSICAL_QUANTITIES_INCLUDE_PHQ_THERMAL_DIFFUSIVITY_HPP
#define PHYSICAL_QUANTITIES_INCLUDE_PHQ_THERMAL_DIFFUSIVITY_HPP

#include "MassDensity.hpp"
#include "SpecificIsobaricHeatCapacity.hpp"
#include "ThermalConductivityScalar.hpp"
#include "Unit/Diffusivity.hpp"

namespace PhQ {

// Forward declaration for class ThermalDiffusivity.
class PrandtlNumber;

// Thermal diffusivity.
class ThermalDiffusivity : public DimensionalScalarQuantity<Unit::Diffusivity> {
public:
  // Default constructor. Constructs a thermal diffusivity with an uninitialized
  // value.
  ThermalDiffusivity() = default;

  // Constructor. Constructs a thermal diffusivity with a given value expressed
  // in a given diffusivity unit.
  ThermalDiffusivity(const double value, const Unit::Diffusivity unit)
    : DimensionalScalarQuantity<Unit::Diffusivity>(value, unit) {}

  // Constructor. Constructs a thermal diffusivity from a given thermal
  // conductivity scalar, specific isobaric heat capacity, and mass density
  // using the definition of the thermal diffusivity.
  constexpr ThermalDiffusivity(
      const ThermalConductivityScalar& thermal_conductivity_scalar,
      const SpecificIsobaricHeatCapacity& specific_isobaric_heat_capacity,
      const MassDensity& mass_density)
    : ThermalDiffusivity(
        thermal_conductivity_scalar.Value()
        / (mass_density.Value() * specific_isobaric_heat_capacity.Value())) {}

  // Constructor. Constructs a thermal diffusivity from a given Prandtl number
  // and kinematic viscosity using the definition of the Prandtl number.
  constexpr ThermalDiffusivity(const PrandtlNumber& prandtl_number,
                               const KinematicViscosity& kinematic_viscosity);

  // Destructor. Destroys this thermal diffusivity.
  ~ThermalDiffusivity() noexcept = default;

  // Copy constructor. Constructs a thermal diffusivity by copying another one.
  constexpr ThermalDiffusivity(const ThermalDiffusivity& other) = default;

  // Move constructor. Constructs a thermal diffusivity by moving another one.
  constexpr ThermalDiffusivity(ThermalDiffusivity&& other) noexcept = default;

  // Copy assignment operator. Assigns this thermal diffusivity by copying
  // another one.
  constexpr ThermalDiffusivity& operator=(
      const ThermalDiffusivity& other) = default;

  // Move assignment operator. Assigns this thermal diffusivity by moving
  // another one.
  constexpr ThermalDiffusivity& operator=(
      ThermalDiffusivity&& other) noexcept = default;

  // Statically creates a thermal diffusivity of zero.
  static constexpr ThermalDiffusivity Zero() {
    return ThermalDiffusivity{0.0};
  }

  // Statically creates a thermal diffusivity with a given value expressed in a
  // given diffusivity unit.
  template <Unit::Diffusivity Unit>
  static constexpr ThermalDiffusivity Create(const double value) {
    return ThermalDiffusivity{
        StaticConvertCopy<Unit::Diffusivity, Unit, Standard<Unit::Diffusivity>>(
            value)};
  }

  constexpr ThermalDiffusivity operator+(
      const ThermalDiffusivity& thermal_diffusivity) const {
    return ThermalDiffusivity{value_ + thermal_diffusivity.value_};
  }

  constexpr ThermalDiffusivity operator-(
      const ThermalDiffusivity& thermal_diffusivity) const {
    return ThermalDiffusivity{value_ - thermal_diffusivity.value_};
  }

  constexpr ThermalDiffusivity operator*(const double number) const {
    return ThermalDiffusivity{value_ * number};
  }

  constexpr ThermalDiffusivity operator/(const double number) const {
    return ThermalDiffusivity{value_ / number};
  }

  constexpr double operator/(
      const ThermalDiffusivity& thermal_diffusivity) const noexcept {
    return value_ / thermal_diffusivity.value_;
  }

  constexpr void operator+=(
      const ThermalDiffusivity& thermal_diffusivity) noexcept {
    value_ += thermal_diffusivity.value_;
  }

  constexpr void operator-=(
      const ThermalDiffusivity& thermal_diffusivity) noexcept {
    value_ -= thermal_diffusivity.value_;
  }

  constexpr void operator*=(const double number) noexcept {
    value_ *= number;
  }

  constexpr void operator/=(const double number) noexcept {
    value_ /= number;
  }

private:
  // Constructor. Constructs a thermal diffusivity with a given value expressed
  // in the standard diffusivity unit.
  explicit constexpr ThermalDiffusivity(const double value)
    : DimensionalScalarQuantity<Unit::Diffusivity>(value) {}
};

inline constexpr bool operator==(
    const ThermalDiffusivity& left, const ThermalDiffusivity& right) noexcept {
  return left.Value() == right.Value();
}

inline constexpr bool operator!=(
    const ThermalDiffusivity& left, const ThermalDiffusivity& right) noexcept {
  return left.Value() != right.Value();
}

inline constexpr bool operator<(
    const ThermalDiffusivity& left, const ThermalDiffusivity& right) noexcept {
  return left.Value() < right.Value();
}

inline constexpr bool operator>(
    const ThermalDiffusivity& left, const ThermalDiffusivity& right) noexcept {
  return left.Value() > right.Value();
}

inline constexpr bool operator<=(
    const ThermalDiffusivity& left, const ThermalDiffusivity& right) noexcept {
  return left.Value() <= right.Value();
}

inline constexpr bool operator>=(
    const ThermalDiffusivity& left, const ThermalDiffusivity& right) noexcept {
  return left.Value() >= right.Value();
}

inline std::ostream& operator<<(
    std::ostream& stream, const ThermalDiffusivity& thermal_diffusivity) {
  stream << thermal_diffusivity.Print();
  return stream;
}

inline constexpr ThermalDiffusivity operator*(
    const double number, const ThermalDiffusivity& thermal_diffusivity) {
  return thermal_diffusivity * number;
}

inline constexpr ThermalConductivityScalar::ThermalConductivityScalar(
    const ThermalDiffusivity& thermal_diffusivity,
    const SpecificIsobaricHeatCapacity& specific_isobaric_heat_capacity,
    const MassDensity& mass_density)
  : ThermalConductivityScalar(
      thermal_diffusivity.Value() * specific_isobaric_heat_capacity.Value()
      * mass_density.Value()) {}

inline constexpr MassDensity::MassDensity(
    const ThermalDiffusivity& thermal_diffusivity,
    const ThermalConductivityScalar& thermal_conductivity_scalar,
    const SpecificIsobaricHeatCapacity& specific_isobaric_heat_capacity)
  : MassDensity(thermal_conductivity_scalar.Value()
                / (thermal_diffusivity.Value()
                   * specific_isobaric_heat_capacity.Value())) {}

inline constexpr SpecificIsobaricHeatCapacity::SpecificIsobaricHeatCapacity(
    const ThermalDiffusivity& thermal_diffusivity,
    const ThermalConductivityScalar& thermal_conductivity_scalar,
    const MassDensity& mass_density)
  : SpecificIsobaricHeatCapacity(
      thermal_conductivity_scalar.Value()
      / (thermal_diffusivity.Value() * mass_density.Value())) {}

}  // namespace PhQ

namespace std {

template <>
struct hash<PhQ::ThermalDiffusivity> {
  inline size_t operator()(
      const PhQ::ThermalDiffusivity& thermal_diffusivity) const {
    return hash<double>()(thermal_diffusivity.Value());
  }
};

}  // namespace std

#endif  // PHYSICAL_QUANTITIES_INCLUDE_PHQ_THERMAL_DIFFUSIVITY_HPP
