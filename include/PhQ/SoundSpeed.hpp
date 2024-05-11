// Copyright 2020-2024 Alexandre Coderre-Chabot
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

#ifndef PHQ_SOUND_SPEED_HPP
#define PHQ_SOUND_SPEED_HPP

#include <cstddef>
#include <functional>
#include <ostream>

#include "DimensionalScalar.hpp"
#include "HeatCapacityRatio.hpp"
#include "IsentropicBulkModulus.hpp"
#include "MassDensity.hpp"
#include "SpecificGasConstant.hpp"
#include "Speed.hpp"
#include "StaticPressure.hpp"
#include "Temperature.hpp"

namespace PhQ {

// Forward declaration for class PhQ::SoundSpeed.
template <typename Number>
class MachNumber;

// Forward declaration for class PhQ::SoundSpeed.
template <typename Number>
class Speed;

// Speed of sound. Applies to any deformable medium, including fluids and elastic solids.
template <typename Number = double>
class SoundSpeed : public DimensionalScalar<Unit::Speed, Number> {
public:
  // Default constructor. Constructs a sound speed with an uninitialized value.
  SoundSpeed() = default;

  // Constructs a sound speed from a given value and speed unit.
  SoundSpeed(const Number value, const Unit::Speed unit)
    : DimensionalScalar<Unit::Speed, Number>(value, unit) {}

  // Constructs a sound speed from an isentropic bulk modulus and a mass density. This is the
  // definition of the sound speed; this relation always holds true.
  SoundSpeed(const IsentropicBulkModulus<Number>& isentropic_bulk_modulus,
             const MassDensity<Number>& mass_density)
    : SoundSpeed<Number>(std::sqrt(isentropic_bulk_modulus.Value() / mass_density.Value())) {}

  // Constructs a sound speed from a heat capacity ratio, a static pressure, and a mass density.
  // This relation applies only to an ideal gas.
  SoundSpeed(const HeatCapacityRatio<Number>& heat_capacity_ratio,
             const StaticPressure<Number>& static_pressure, const MassDensity<Number>& mass_density)
    : SoundSpeed<Number>(
        std::sqrt(heat_capacity_ratio.Value() * static_pressure.Value() / mass_density.Value())) {}

  // Constructs a sound speed from a heat capacity ratio, a specific gas constant, and a
  // temperature. This relation applies only to an ideal gas.
  SoundSpeed(const HeatCapacityRatio<Number>& heat_capacity_ratio,
             const SpecificGasConstant<Number>& specific_gas_constant,
             const Temperature<Number>& temperature)
    : SoundSpeed<Number>(std::sqrt(
        heat_capacity_ratio.Value() * specific_gas_constant.Value() * temperature.Value())) {}

  // Constructs a sound speed from a speed and a Mach number. This uses the definition of the Mach
  // number; this relation always holds true.
  constexpr SoundSpeed(const Speed<Number>& speed, const MachNumber<Number>& mach_number);

  // Destructor. Destroys this sound speed.
  ~SoundSpeed() noexcept = default;

  // Copy constructor. Constructs a sound speed by copying another one.
  constexpr SoundSpeed(const SoundSpeed<Number>& other) = default;

  // Copy constructor. Constructs a sound speed by copying another one.
  template <typename OtherNumber>
  explicit constexpr SoundSpeed(const SoundSpeed<OtherNumber>& other)
    : SoundSpeed(static_cast<Number>(other.Value())) {}

  // Move constructor. Constructs a sound speed by moving another one.
  constexpr SoundSpeed(SoundSpeed<Number>&& other) noexcept = default;

  // Copy assignment operator. Assigns this sound speed by copying another one.
  constexpr SoundSpeed<Number>& operator=(const SoundSpeed<Number>& other) = default;

  // Copy assignment operator. Assigns this sound speed by copying another one.
  template <typename OtherNumber>
  constexpr SoundSpeed<Number>& operator=(const SoundSpeed<OtherNumber>& other) {
    this->value = static_cast<Number>(other.Value());
    return *this;
  }

  // Move assignment operator. Assigns this sound speed by moving another one.
  constexpr SoundSpeed<Number>& operator=(SoundSpeed<Number>&& other) noexcept = default;

  static constexpr SoundSpeed<Number> Zero() {
    return SoundSpeed<Number>{static_cast<Number>(0)};
  }

  // Creates a sound speed from a given value and speed unit.
  template <Unit::Speed Unit>
  static constexpr SoundSpeed<Number> Create(const Number value) {
    return SoundSpeed<Number>{StaticConvertCopy<Unit::Speed, Unit, Standard<Unit::Speed>>(value)};
  }

  constexpr SoundSpeed<Number> operator+(const SoundSpeed<Number>& speed) const {
    return SoundSpeed<Number>{this->value + speed.value};
  }

  constexpr Speed<Number> operator+(const Speed<Number>& speed) const {
    return Speed<Number>{this->value + speed.value};
  }

  constexpr SoundSpeed<Number> operator-(const SoundSpeed<Number>& speed) const {
    return SoundSpeed<Number>{this->value - speed.value};
  }

  constexpr Speed<Number> operator-(const Speed<Number>& speed) const {
    return Speed<Number>{this->value - speed.value};
  }

  constexpr SoundSpeed<Number> operator*(const Number number) const {
    return SoundSpeed<Number>{this->value * number};
  }

  constexpr Speed<Number> operator*(const MachNumber<Number>& mach_number) const;

  constexpr SoundSpeed<Number> operator/(const Number number) const {
    return SoundSpeed<Number>{this->value / number};
  }

  constexpr Number operator/(const SoundSpeed<Number>& sound_speed) const noexcept {
    return this->value / sound_speed.value;
  }

  constexpr void operator+=(const SoundSpeed<Number>& sound_speed) noexcept {
    this->value += sound_speed.value;
  }

  constexpr void operator+=(const Speed<Number>& speed) noexcept {
    this->value += speed.value;
  }

  constexpr void operator-=(const SoundSpeed<Number>& sound_speed) noexcept {
    this->value -= sound_speed.value;
  }

  constexpr void operator-=(const Speed<Number>& speed) noexcept {
    this->value -= speed.value;
  }

  constexpr void operator*=(const Number number) noexcept {
    this->value *= number;
  }

  constexpr void operator/=(const Number number) noexcept {
    this->value /= number;
  }

private:
  // Constructor. Constructs a sound speed with a given value expressed in the standard speed unit.
  explicit constexpr SoundSpeed(const Number value)
    : DimensionalScalar<Unit::Speed, Number>(value) {}
};

template <typename Number>
inline constexpr bool operator==(
    const SoundSpeed<Number>& left, const SoundSpeed<Number>& right) noexcept {
  return left.Value() == right.Value();
}

template <typename Number>
inline constexpr bool operator!=(
    const SoundSpeed<Number>& left, const SoundSpeed<Number>& right) noexcept {
  return left.Value() != right.Value();
}

template <typename Number>
inline constexpr bool operator<(
    const SoundSpeed<Number>& left, const SoundSpeed<Number>& right) noexcept {
  return left.Value() < right.Value();
}

template <typename Number>
inline constexpr bool operator>(
    const SoundSpeed<Number>& left, const SoundSpeed<Number>& right) noexcept {
  return left.Value() > right.Value();
}

template <typename Number>
inline constexpr bool operator<=(
    const SoundSpeed<Number>& left, const SoundSpeed<Number>& right) noexcept {
  return left.Value() <= right.Value();
}

template <typename Number>
inline constexpr bool operator>=(
    const SoundSpeed<Number>& left, const SoundSpeed<Number>& right) noexcept {
  return left.Value() >= right.Value();
}

template <typename Number>
inline std::ostream& operator<<(std::ostream& stream, const SoundSpeed<Number>& sound_speed) {
  stream << sound_speed.Print();
  return stream;
}

template <typename Number>
inline constexpr SoundSpeed<Number> operator*(
    const Number number, const SoundSpeed<Number>& sound_speed) {
  return sound_speed * number;
}

template <typename Number>
inline constexpr Speed<Number> Speed<Number>::operator+(
    const SoundSpeed<Number>& sound_speed) const {
  return Speed<Number>{value + sound_speed.Value()};
}

template <typename Number>
inline constexpr Speed<Number> Speed<Number>::operator-(
    const SoundSpeed<Number>& sound_speed) const {
  return Speed<Number>{value - sound_speed.Value()};
}

template <typename Number>
inline constexpr void Speed<Number>::operator+=(const SoundSpeed<Number>& speed) noexcept {
  value += speed.Value();
}

template <typename Number>
inline constexpr void Speed<Number>::operator-=(const SoundSpeed<Number>& speed) noexcept {
  value -= speed.Value();
}

template <typename Number>
constexpr MassDensity<Number>::MassDensity(
    const IsentropicBulkModulus<Number>& isentropic_bulk_modulus,
    const SoundSpeed<Number>& sound_speed)
  : MassDensity<Number>(isentropic_bulk_modulus.Value() / std::pow(sound_speed.Value(), 2)) {}

template <typename Number>
constexpr IsentropicBulkModulus<Number>::IsentropicBulkModulus(
    const MassDensity<Number>& mass_density, const SoundSpeed<Number>& sound_speed)
  : IsentropicBulkModulus<Number>(mass_density.Value() * std::pow(sound_speed.Value(), 2)) {}

}  // namespace PhQ

namespace std {

template <typename Number>
struct hash<PhQ::SoundSpeed<Number>> {
  inline size_t operator()(const PhQ::SoundSpeed<Number>& sound_speed) const {
    return hash<Number>()(sound_speed.Value());
  }
};

}  // namespace std

#endif  // PHQ_SOUND_SPEED_HPP
