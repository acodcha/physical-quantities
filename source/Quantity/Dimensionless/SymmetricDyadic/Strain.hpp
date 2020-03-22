#pragma once

#include "Base.hpp"

namespace PhQ {

class Strain : public DimensionlessSymmetricDyadicQuantity {

public:

  Strain() noexcept : DimensionlessSymmetricDyadicQuantity() {}

  constexpr Strain(const Value::SymmetricDyadic& value) noexcept : DimensionlessSymmetricDyadicQuantity(value) {}

};

} // namespace PhQ
