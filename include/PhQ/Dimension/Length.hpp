// Copyright 2020-2023 Alexandre Coderre-Chabot
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

#ifndef PHYSICAL_QUANTITIES_INCLUDE_PHQ_DIMENSION_LENGTH_HPP
#define PHYSICAL_QUANTITIES_INCLUDE_PHQ_DIMENSION_LENGTH_HPP

#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <string_view>

namespace PhQ::Dimension {

// Base physical dimension of length. Typically denoted "L". One of seven independent base physical
// dimensions that form the physical dimension set of any unit of measure or physical quantity.
class Length {
public:
  // Default constructor. Constructs a base physical dimension of length with a value of zero.
  constexpr Length() : value_(0) {}

  // Constructor. Constructs a base physical dimension of length with a given value.
  explicit constexpr Length(const int8_t value) : value_(value) {}

  // Destructor. Destroys this base physical dimension of length.
  ~Length() noexcept = default;

  // Copy constructor. Constructs a base physical dimension of length by copying another one.
  constexpr Length(const Length& other) = default;

  // Copy assignment operator. Assigns the value of this base physical dimension of length by
  // copying from another one.
  constexpr Length& operator=(const Length& other) = default;

  // Move constructor. Constructs a base physical dimension of length by moving another one.
  constexpr Length(Length&& other) noexcept = default;

  // Move assignment operator. Assigns the value of this base physical dimension of length by moving
  // another one.
  constexpr Length& operator=(Length&& other) noexcept = default;

  // Value of this base physical dimension.
  [[nodiscard]] constexpr int8_t Value() const noexcept {
    return value_;
  }

  // Abbreviation of this base physical dimension.
  static std::string_view Abbreviation() noexcept {
    return "L";
  }

  // Label of this base physical dimension.
  static std::string_view Label() noexcept {
    return "Length";
  }

  // Prints this base physical dimension as a string.
  [[nodiscard]] std::string Print() const noexcept {
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
  // Value of this base physical dimension.
  int8_t value_;
};

inline constexpr bool operator==(const Length& left, const Length& right) noexcept {
  return left.Value() == right.Value();
}

inline constexpr bool operator!=(const Length& left, const Length& right) noexcept {
  return left.Value() != right.Value();
}

inline constexpr bool operator<(const Length& left, const Length& right) noexcept {
  return left.Value() < right.Value();
}

inline constexpr bool operator>(const Length& left, const Length& right) noexcept {
  return left.Value() > right.Value();
}

inline constexpr bool operator<=(const Length& left, const Length& right) noexcept {
  return left.Value() <= right.Value();
}

inline constexpr bool operator>=(const Length& left, const Length& right) noexcept {
  return left.Value() >= right.Value();
}

inline std::ostream& operator<<(std::ostream& stream, const Length& length) {
  stream << length.Print();
  return stream;
}

}  // namespace PhQ::Dimension

namespace std {

template <>
struct hash<PhQ::Dimension::Length> {
  inline size_t operator()(const PhQ::Dimension::Length& length) const {
    return hash<int8_t>()(length.Value());
  }
};

}  // namespace std

#endif  // PHYSICAL_QUANTITIES_INCLUDE_PHQ_DIMENSION_LENGTH_HPP
