#pragma once

#include "Base.hpp"

namespace PhQ {

class ReynoldsNumber : public DimensionlessScalarQuantity {

public:

  ReynoldsNumber() noexcept : DimensionlessScalarQuantity() {}

  constexpr ReynoldsNumber(double value) noexcept : DimensionlessScalarQuantity(value) {}

};

} // namespace PhQ
