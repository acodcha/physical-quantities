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

#ifndef PHYSICAL_QUANTITIES_INCLUDE_PHQ_QUANTITY_DIMENSIONLESS_SYMMETRIC_DYAD_HPP
#define PHYSICAL_QUANTITIES_INCLUDE_PHQ_QUANTITY_DIMENSIONLESS_SYMMETRIC_DYAD_HPP

#include <utility>

#include "../Value/SymmetricDyad.hpp"
#include "Dimensionless.hpp"

namespace PhQ {

class DimensionlessSymmetricDyadQuantity : public DimensionlessQuantity {
public:
  virtual ~DimensionlessSymmetricDyadQuantity() noexcept = default;

  constexpr const Value::SymmetricDyad& Value() const noexcept {
    return value_;
  }

  std::string Print() const noexcept override { return value_.Print(); }

  std::string Json() const noexcept override { return value_.Json(); }

  std::string Xml() const noexcept override { return value_.Xml(); }

  std::string Yaml() const noexcept override { return value_.Yaml(); }

protected:
  constexpr DimensionlessSymmetricDyadQuantity() noexcept
      : DimensionlessQuantity(), value_() {}

  constexpr DimensionlessSymmetricDyadQuantity(
      const Value::SymmetricDyad& value) noexcept
      : DimensionlessQuantity(), value_(value) {}

  constexpr DimensionlessSymmetricDyadQuantity(
      Value::SymmetricDyad&& value) noexcept
      : DimensionlessQuantity(), value_(std::move(value)) {}

  void operator=(const Value::SymmetricDyad& value) noexcept { value_ = value; }

  void operator=(Value::SymmetricDyad&& value) noexcept {
    value_ = std::move(value);
  }

  Value::SymmetricDyad value_;
};

}  // namespace PhQ

namespace std {

template <>
struct hash<PhQ::DimensionlessSymmetricDyadQuantity> {
  size_t operator()(
      const PhQ::DimensionlessSymmetricDyadQuantity& quantity) const {
    return hash<PhQ::Value::SymmetricDyad>()(quantity.Value());
  }
};

}  // namespace std

#endif  // PHYSICAL_QUANTITIES_INCLUDE_PHQ_QUANTITY_DIMENSIONLESS_SYMMETRIC_DYAD_HPP