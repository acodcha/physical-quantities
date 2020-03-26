#pragma once

#include "Length.hpp"
#include "Unit/Time.hpp"

namespace PhQ {

class Time : public DimensionalScalarQuantity<Unit::Time> {

public:

  constexpr Time() noexcept : DimensionalScalarQuantity<Unit::Time>() {}

  constexpr Time(const DimensionalScalarQuantity<Unit::Time>& quantity) noexcept : DimensionalScalarQuantity<Unit::Time>(quantity) {}

  constexpr Time(double value, Unit::Time unit) noexcept : DimensionalScalarQuantity<Unit::Time>(value, unit) {}

  friend class Length;

  friend class Speed;

  friend class AccelerationMagnitude;

};

} // namespace PhQ
