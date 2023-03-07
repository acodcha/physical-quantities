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

#ifndef PHYSICAL_QUANTITIES_INCLUDE_PHQ_YOUNG_MODULUS_HPP
#define PHYSICAL_QUANTITIES_INCLUDE_PHQ_YOUNG_MODULUS_HPP

#include "Quantity/DimensionalScalar.hpp"
#include "Unit/Pressure.hpp"

namespace PhQ {

class YoungModulus : public DimensionalScalarQuantity<Unit::Pressure> {
public:
  constexpr YoungModulus() noexcept
      : DimensionalScalarQuantity<Unit::Pressure>() {}

  YoungModulus(const double value, const Unit::Pressure unit) noexcept
      : DimensionalScalarQuantity<Unit::Pressure>(value, unit) {}

  inline YoungModulus operator+(
      const YoungModulus& young_modulus) const noexcept {
    return YoungModulus{value_ + young_modulus.value_};
  }

  inline YoungModulus operator-(
      const YoungModulus& young_modulus) const noexcept {
    return YoungModulus{value_ - young_modulus.value_};
  }

  inline YoungModulus operator*(const double number) const noexcept {
    return YoungModulus{value_ * number};
  }

  inline YoungModulus operator/(const double number) const noexcept {
    return YoungModulus{value_ / number};
  }

  inline constexpr void operator+=(const YoungModulus& young_modulus) noexcept {
    value_ += young_modulus.value_;
  }

  inline constexpr void operator-=(const YoungModulus& young_modulus) noexcept {
    value_ -= young_modulus.value_;
  }

  inline constexpr void operator*=(const double number) noexcept {
    value_ *= number;
  }

  inline constexpr void operator/=(const double number) noexcept {
    value_ /= number;
  }

private:
  explicit constexpr YoungModulus(const double value) noexcept
      : DimensionalScalarQuantity<Unit::Pressure>(value) {}
};

inline constexpr bool operator==(const YoungModulus& left,
                                 const YoungModulus& right) noexcept {
  return left.Value() == right.Value();
}

inline constexpr bool operator!=(const YoungModulus& left,
                                 const YoungModulus& right) noexcept {
  return left.Value() != right.Value();
}

inline constexpr bool operator<(const YoungModulus& left,
                                const YoungModulus& right) noexcept {
  return left.Value() < right.Value();
}

inline constexpr bool operator>(const YoungModulus& left,
                                const YoungModulus& right) noexcept {
  return left.Value() > right.Value();
}

inline constexpr bool operator<=(const YoungModulus& left,
                                 const YoungModulus& right) noexcept {
  return left.Value() <= right.Value();
}

inline constexpr bool operator>=(const YoungModulus& left,
                                 const YoungModulus& right) noexcept {
  return left.Value() >= right.Value();
}

inline std::ostream& operator<<(std::ostream& stream,
                                const YoungModulus& young_modulus) noexcept {
  stream << young_modulus.Print();
  return stream;
}

inline YoungModulus operator*(const double number,
                              const YoungModulus& young_modulus) noexcept {
  return young_modulus * number;
}

}  // namespace PhQ

namespace std {

template <>
struct hash<PhQ::YoungModulus> {
  size_t operator()(const PhQ::YoungModulus& young_modulus) const {
    return hash<double>()(young_modulus.Value());
  }
};

}  // namespace std

#endif  // PHYSICAL_QUANTITIES_INCLUDE_PHQ_YOUNG_MODULUS_HPP
