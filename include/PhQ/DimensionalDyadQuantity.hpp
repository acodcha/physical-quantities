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

#ifndef PHYSICAL_QUANTITIES_INCLUDE_PHQ_DIMENSIONAL_DYAD_QUANTITY_HPP
#define PHYSICAL_QUANTITIES_INCLUDE_PHQ_DIMENSIONAL_DYAD_QUANTITY_HPP

#include "Unit.hpp"
#include "Value/Dyad.hpp"

namespace PhQ {

// Abstract base class that represents any dimensional dyadic tensor physical
// quantity. Such a physical quantity is composed of a value and a unit of
// measure where the value is a tensor of rank two and dimension three. The
// tensor may be non-symmetric.
template<typename U> class DimensionalDyadQuantity {
public:
  static constexpr const PhQ::Dimensions& Dimensions() noexcept {
    return RelatedDimensions<U>;
  }

  static constexpr U Unit() noexcept { return Standard<U>; }

  constexpr const Value::Dyad& Value() const noexcept { return value_; }

  Value::Dyad Value(const U unit) const noexcept {
    Value::Dyad result{value_};
    Convert(result, Standard<U>, unit);
    return result;
  }

  template<U NewUnit> constexpr Value::Dyad StaticValue() const noexcept {
    return StaticConvertCopy<U, Standard<U>, NewUnit>(value_);
  }

  constexpr Value::Dyad& MutableValue() noexcept { return value_; }

  constexpr void SetValue(const Value::Dyad& value) noexcept { value_ = value; }

  std::string Print() const noexcept {
    return value_.Print().append(" ").append(Abbreviation(Standard<U>));
  }

  std::string Print(const Precision precision) const noexcept {
    return value_.Print(precision).append(" ").append(
        Abbreviation(Standard<U>));
  }

  std::string Print(const U unit) const noexcept {
    return Value(unit).Print().append(" ").append(Abbreviation(unit));
  }

  std::string Print(const U unit, const Precision precision) const noexcept {
    return Value(unit).Print(precision).append(" ").append(Abbreviation(unit));
  }

  std::string JSON() const noexcept {
    return std::string{"{\"value\":"}
        .append(value_.JSON())
        .append(",\"unit\":\"")
        .append(Abbreviation(Standard<U>))
        .append("\"}");
  }

  std::string JSON(const U unit) const noexcept {
    return std::string{"{\"value\":"}
        .append(Value(unit).JSON())
        .append(",\"unit\":\"")
        .append(Abbreviation(unit))
        .append("\"}");
  }

  std::string XML() const noexcept {
    return std::string{"<value>"}
        .append(value_.XML())
        .append("</value><unit>")
        .append(Abbreviation(Standard<U>))
        .append("</unit>");
  }

  std::string XML(const U unit) const noexcept {
    return std::string{"<value>"}
        .append(Value(unit).XML())
        .append("</value><unit>")
        .append(Abbreviation(unit))
        .append("</unit>");
  }

  std::string YAML() const noexcept {
    return std::string{"{value:"}
        .append(value_.YAML())
        .append(",unit:\"")
        .append(Abbreviation(Standard<U>))
        .append("\"}");
  }

  std::string YAML(const U unit) const noexcept {
    return std::string{"{value:"}
        .append(Value(unit).YAML())
        .append(",unit:\"")
        .append(Abbreviation(unit))
        .append("\"}");
  }

protected:
  constexpr DimensionalDyadQuantity() noexcept : value_() {}

  constexpr DimensionalDyadQuantity(const Value::Dyad& value) noexcept
    : value_(value) {}

  constexpr DimensionalDyadQuantity(Value::Dyad&& value) noexcept
    : value_(std::move(value)) {}

  DimensionalDyadQuantity(const Value::Dyad& value, const U unit) noexcept
    : value_(value) {
    Convert(value_, unit, Standard<U>);
  }

  DimensionalDyadQuantity(Value::Dyad&& value, const U unit) noexcept
    : value_(std::move(value)) {
    Convert(value_, unit, Standard<U>);
  }

  virtual ~DimensionalDyadQuantity() noexcept = default;

  constexpr void operator=(const Value::Dyad& value) noexcept {
    value_ = value;
  }

  constexpr void operator=(Value::Dyad&& value) noexcept {
    value_ = std::move(value);
  }

  Value::Dyad value_;
};

template<typename U> inline std::ostream& operator<<(
    std::ostream& stream, const DimensionalDyadQuantity<U>& quantity) noexcept {
  stream << quantity.Print();
  return stream;
}

}  // namespace PhQ

namespace std {

template<typename U> struct hash<PhQ::DimensionalDyadQuantity<U>> {
  inline size_t operator()(
      const PhQ::DimensionalDyadQuantity<U>& quantity) const {
    return hash<PhQ::Value::Dyad>()(quantity.Value());
  }
};

}  // namespace std

#endif  // PHYSICAL_QUANTITIES_INCLUDE_PHQ_DIMENSIONAL_DYAD_QUANTITY_HPP
