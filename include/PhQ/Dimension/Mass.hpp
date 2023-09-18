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

#ifndef PHYSICAL_QUANTITIES_INCLUDE_PHQ_DIMENSION_MASS_HPP
#define PHYSICAL_QUANTITIES_INCLUDE_PHQ_DIMENSION_MASS_HPP

#include <iostream>
#include <string>
#include <string_view>

#include "../Base.hpp"

namespace PhQ::Dimension {

// Base physical dimension of mass. Typically denoted "M". One of seven
// independent base physical dimensions that form the physical dimension set of
// any unit of measure or physical quantity.
class Mass {
public:
  // Default constructor. Constructs a base physical dimension of mass with a
  // value of zero.
  constexpr Mass() noexcept : value_(0) {}

  // Constructor. Constructs a base physical dimension of mass with a given
  // value.
  explicit constexpr Mass(const int8_t value) noexcept : value_(value) {}

  // Destructor. Destroys this base physical dimension.
  ~Mass() noexcept = default;

  // Copy constructor. Constructs a base physical dimension of mass by copying
  // another one.
  constexpr Mass(const Mass& other) noexcept = default;

  // Copy assignment operator. Assigns the value of this base physical dimension
  // of mass by copying from another one.
  constexpr Mass& operator=(const Mass& other) noexcept = default;

  // Move constructor. Constructs a base physical dimension of mass by moving
  // another one.
  constexpr Mass(Mass&& other) noexcept = default;

  // Move assignment operator. Assigns the value of this base physical dimension
  // of mass by moving another one.
  constexpr Mass& operator=(Mass&& other) noexcept = default;

  // Value of this base physical dimension.
  constexpr int8_t Value() const noexcept {
    return value_;
  }

  // Abbreviation of this base physical dimension.
  static std::string_view Abbreviation() noexcept {
    return "M";
  }

  // Label of this base physical dimension.
  static std::string_view Label() noexcept {
    return "Mass";
  }

  // Prints this base physical dimension as a string.
  std::string Print() const noexcept {
    if (value_ == 0) {
      return {};
    }
    std::string text{Abbreviation()};
    if (value_ >= 2) {
      text.append("^" + std::to_string(value_));
    } else if (value_ <= -1) {
      text.append("^(" + std::to_string(value_) + ")");
    }
    return text;
  }

private:
  int8_t value_;
};

inline constexpr bool operator==(const Mass& left, const Mass& right) noexcept {
  return left.Value() == right.Value();
}

inline constexpr bool operator!=(const Mass& left, const Mass& right) noexcept {
  return left.Value() != right.Value();
}

inline constexpr bool operator<(const Mass& left, const Mass& right) noexcept {
  return left.Value() < right.Value();
}

inline constexpr bool operator>(const Mass& left, const Mass& right) noexcept {
  return left.Value() > right.Value();
}

inline constexpr bool operator<=(const Mass& left, const Mass& right) noexcept {
  return left.Value() <= right.Value();
}

inline constexpr bool operator>=(const Mass& left, const Mass& right) noexcept {
  return left.Value() >= right.Value();
}

inline std::ostream& operator<<(
    std::ostream& stream, const Mass& mass) noexcept {
  stream << mass.Print();
  return stream;
}

}  // namespace PhQ::Dimension

namespace std {

template <>
struct hash<PhQ::Dimension::Mass> {
  inline size_t operator()(const PhQ::Dimension::Mass& mass) const {
    return hash<int8_t>()(mass.Value());
  }
};

}  // namespace std

#endif  // PHYSICAL_QUANTITIES_INCLUDE_PHQ_DIMENSION_MASS_HPP
