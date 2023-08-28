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

#ifndef PHYSICAL_QUANTITIES_INCLUDE_PHQ_DIMENSIONAL_SCALAR_QUANTITY_HPP
#define PHYSICAL_QUANTITIES_INCLUDE_PHQ_DIMENSIONAL_SCALAR_QUANTITY_HPP

#include "Unit.hpp"

namespace PhQ {

// Abstract base class that represents any dimensional scalar physical quantity.
// Such a physical quantity is composed of a value and a unit of measure where
// the value is a scalar number.
template<typename U> class DimensionalScalarQuantity {
public:
  static constexpr const PhQ::Dimensions& Dimensions() noexcept {
    return RelatedDimensions<U>;
  }

  static constexpr U Unit() noexcept { return Standard<U>; }

  constexpr double Value() const noexcept { return value_; }

  double Value(const U unit) const noexcept {
    double result{value_};
    Convert(result, Standard<U>, unit);
    return result;
  }

  template<U NewUnit> constexpr double StaticValue() const noexcept {
    return StaticConvertCopy<U, Standard<U>, NewUnit>(value_);
  }

  constexpr double& MutableValue() noexcept { return value_; }

  constexpr void SetValue(const double value) noexcept { value_ = value; }

  std::string Print() const noexcept {
    return PhQ::Print(value_).append(" ").append(Abbreviation(Standard<U>));
  }

  std::string Print(const Precision precision) const noexcept {
    return PhQ::Print(value_, precision)
        .append(" ")
        .append(Abbreviation(Standard<U>));
  }

  std::string Print(const U unit) const noexcept {
    return PhQ::Print(Value(unit)).append(" ").append(Abbreviation(unit));
  }

  std::string Print(const U unit, const Precision precision) const noexcept {
    return PhQ::Print(Value(unit), precision)
        .append(" ")
        .append(Abbreviation(unit));
  }

  std::string JSON() const noexcept {
    return std::string{"{\"value\":"}
        .append(PhQ::Print(value_))
        .append(",\"unit\":\"")
        .append(Abbreviation(Standard<U>))
        .append("\"}");
  }

  std::string JSON(const U unit) const noexcept {
    return std::string{"{\"value\":"}
        .append(PhQ::Print(Value(unit)))
        .append(",\"unit\":\"")
        .append(Abbreviation(unit))
        .append("\"}");
  }

  std::string XML() const noexcept {
    return std::string{"<value>"}
        .append(PhQ::Print(value_))
        .append("</value><unit>")
        .append(Abbreviation(Standard<U>))
        .append("</unit>");
  }

  std::string XML(const U unit) const noexcept {
    return std::string{"<value>"}
        .append(PhQ::Print(Value(unit)))
        .append("</value><unit>")
        .append(Abbreviation(unit))
        .append("</unit>");
  }

  std::string YAML() const noexcept {
    return std::string{"{value:"}
        .append(PhQ::Print(value_))
        .append(",unit:\"")
        .append(Abbreviation(Standard<U>))
        .append("\"}");
  }

  std::string YAML(const U unit) const noexcept {
    return std::string{"{value:"}
        .append(PhQ::Print(Value(unit)))
        .append(",unit:\"")
        .append(Abbreviation(unit))
        .append("\"}");
  }

protected:
  constexpr DimensionalScalarQuantity() noexcept : value_() {}

  constexpr DimensionalScalarQuantity(const double value) noexcept
    : value_(value) {}

  DimensionalScalarQuantity(const double value, const U unit) noexcept
    : value_(value) {
    Convert(value_, unit, Standard<U>);
  }

  ~DimensionalScalarQuantity() noexcept = default;

  constexpr void operator=(const double value) noexcept { value_ = value; }

  double value_;
};

template<typename U> inline std::ostream& operator<<(
    std::ostream& stream,
    const DimensionalScalarQuantity<U>& quantity) noexcept {
  stream << quantity.Print();
  return stream;
}

}  // namespace PhQ

namespace std {

template<typename U> struct hash<PhQ::DimensionalScalarQuantity<U>> {
  inline size_t operator()(
      const PhQ::DimensionalScalarQuantity<U>& quantity) const {
    return hash<double>()(quantity.Value());
  }
};

}  // namespace std

#endif  // PHYSICAL_QUANTITIES_INCLUDE_PHQ_DIMENSIONAL_SCALAR_QUANTITY_HPP
