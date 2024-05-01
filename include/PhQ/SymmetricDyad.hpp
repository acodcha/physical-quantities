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

#ifndef PHQ_SYMMETRIC_DYAD_HPP
#define PHQ_SYMMETRIC_DYAD_HPP

#include <array>
#include <cstddef>
#include <functional>
#include <optional>
#include <ostream>
#include <string>
#include <type_traits>

#include "Base.hpp"
#include "Vector.hpp"

namespace PhQ {

// Three-dimensional symmetric dyadic tensor in Cartesian coordinates. Contains six components: xx,
// xy = yx, xz = zx, yy, yz = zy, and zz.
template <typename NumberType = double>
class SymmetricDyad {
  static_assert(std::is_floating_point<NumberType>::value,
                "NumberType must be a floating-point number type.");

public:
  // Default constructor. Constructs a three-dimensional symmetric dyadic tensor with uninitialized
  // xx, xy, xz, yy, yz, and zz Cartesian components.
  SymmetricDyad() = default;

  // Constructor. Constructs a three-dimensional symmetric dyadic tensor from the given xx, xy, xz,
  // yy, yz, and zz Cartesian components.
  constexpr SymmetricDyad(const NumberType xx, const NumberType xy, const NumberType xz,
                          const NumberType yy, const NumberType yz, const NumberType zz)
    : xx_xy_xz_yy_yz_zz_({xx, xy, xz, yy, yz, zz}) {}

  // Constructor. Constructs a three-dimensional symmetric dyadic tensor from a given array
  // representing its xx, xy, xz, yy, yz, and zz Cartesian components.
  explicit constexpr SymmetricDyad(const std::array<NumberType, 6>& xx_xy_xz_yy_yz_zz)
    : xx_xy_xz_yy_yz_zz_(xx_xy_xz_yy_yz_zz) {}

  // Destructor. Destroys this three-dimensional symmetric dyadic tensor.
  ~SymmetricDyad() noexcept = default;

  // Copy constructor. Constructs a three-dimensional symmetric dyadic tensor by copying another
  // one.
  constexpr SymmetricDyad(const SymmetricDyad& other) = default;

  // Copy constructor. Constructs a three-dimensional symmetric dyadic tensor by copying another
  // one.
  template <typename OtherNumberType>
  constexpr SymmetricDyad(const SymmetricDyad<OtherNumberType>& other)
    : xx_xy_xz_yy_yz_zz_(other.xx_xy_xz_yy_yz_zz_) {}

  // Move constructor. Constructs a three-dimensional symmetric dyadic tensor by moving another one.
  constexpr SymmetricDyad(SymmetricDyad&& other) noexcept = default;

  // Copy assignment operator. Assigns this three-dimensional symmetric dyadic tensor by copying
  // another one.
  constexpr SymmetricDyad& operator=(const SymmetricDyad& other) = default;

  // Copy assignment operator. Assigns this three-dimensional symmetric dyadic tensor by copying
  // another one.
  template <typename OtherNumberType>
  constexpr SymmetricDyad& operator=(const SymmetricDyad<OtherNumberType>& other) {
    xx_xy_xz_yy_yz_zz_ = other.xx_xy_xz_yy_yz_zz_;
    return *this;
  }

  // Move assignment operator. Assigns this three-dimensional symmetric dyadic tensor by moving
  // another one.
  constexpr SymmetricDyad& operator=(SymmetricDyad&& other) noexcept = default;

  // Assignment operator. Assigns this three-dimensional symmetric dyadic tensor by copying a given
  // array representing its xx, xy, xz, yy, yz, and zz Cartesian components.
  constexpr SymmetricDyad& operator=(const std::array<NumberType, 6>& xx_xy_xz_yy_yz_zz) {
    xx_xy_xz_yy_yz_zz_ = xx_xy_xz_yy_yz_zz;
    return *this;
  }

  // Statically creates a three-dimensional symmetric dyadic tensor with its xx, xy, xz, yy, yz, and
  // zz Cartesian components initialized to zero.
  static constexpr SymmetricDyad Zero() {
    return SymmetricDyad{
        std::array<NumberType, 6>{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
    };
  }

  // Returns this three-dimensional symmetric dyadic tensor's xx, xy, xz, yy, yz, and zz Cartesian
  // components as an array.
  [[nodiscard]] constexpr const std::array<NumberType, 6>& xx_xy_xz_yy_yz_zz() const noexcept {
    return xx_xy_xz_yy_yz_zz_;
  }

  // Returns this three-dimensional symmetric dyadic tensor's xx Cartesian component.
  [[nodiscard]] constexpr NumberType xx() const noexcept {
    return xx_xy_xz_yy_yz_zz_[0];
  }

  // Returns this three-dimensional symmetric dyadic tensor's xy = yx Cartesian component.
  [[nodiscard]] constexpr NumberType xy() const noexcept {
    return xx_xy_xz_yy_yz_zz_[1];
  }

  // Returns this three-dimensional symmetric dyadic tensor's xz = zx Cartesian component.
  [[nodiscard]] constexpr NumberType xz() const noexcept {
    return xx_xy_xz_yy_yz_zz_[2];
  }

  // Returns this three-dimensional symmetric dyadic tensor's yx = xy Cartesian component.
  [[nodiscard]] constexpr NumberType yx() const noexcept {
    return xx_xy_xz_yy_yz_zz_[1];
  }

  // Returns this three-dimensional symmetric dyadic tensor's yy Cartesian component.
  [[nodiscard]] constexpr NumberType yy() const noexcept {
    return xx_xy_xz_yy_yz_zz_[3];
  }

  // Returns this three-dimensional symmetric dyadic tensor's yz = zy Cartesian component.
  [[nodiscard]] constexpr NumberType yz() const noexcept {
    return xx_xy_xz_yy_yz_zz_[4];
  }

  // Returns this three-dimensional symmetric dyadic tensor's zx = xz Cartesian component.
  [[nodiscard]] constexpr NumberType zx() const noexcept {
    return xx_xy_xz_yy_yz_zz_[2];
  }

  // Returns this three-dimensional symmetric dyadic tensor's zy = yz Cartesian component.
  [[nodiscard]] constexpr NumberType zy() const noexcept {
    return xx_xy_xz_yy_yz_zz_[4];
  }

  // Returns this three-dimensional symmetric dyadic tensor's zz Cartesian component.
  [[nodiscard]] constexpr NumberType zz() const noexcept {
    return xx_xy_xz_yy_yz_zz_[5];
  }

  // Returns this three-dimensional symmetric dyadic tensor's xx, xy, xz, yy, yz, and zz Cartesian
  // components as a mutable array.
  constexpr std::array<NumberType, 6>& Mutable_xx_xy_xz_yy_yz_zz() noexcept {
    return xx_xy_xz_yy_yz_zz_;
  }

  // Returns this three-dimensional symmetric dyadic tensor's xx Cartesian component as a mutable
  // value.
  constexpr NumberType& Mutable_xx() noexcept {
    return xx_xy_xz_yy_yz_zz_[0];
  }

  // Returns this three-dimensional symmetric dyadic tensor's xy = yx Cartesian component as a
  // mutable value.
  constexpr NumberType& Mutable_xy() noexcept {
    return xx_xy_xz_yy_yz_zz_[1];
  }

  // Returns this three-dimensional symmetric dyadic tensor's xz = zx Cartesian component as a
  // mutable value.
  constexpr NumberType& Mutable_xz() noexcept {
    return xx_xy_xz_yy_yz_zz_[2];
  }

  // Returns this three-dimensional symmetric dyadic tensor's yx = xy Cartesian component as a
  // mutable value.
  constexpr NumberType& Mutable_yx() noexcept {
    return xx_xy_xz_yy_yz_zz_[1];
  }

  // Returns this three-dimensional symmetric dyadic tensor's yy Cartesian component as a mutable
  // value.
  constexpr NumberType& Mutable_yy() noexcept {
    return xx_xy_xz_yy_yz_zz_[3];
  }

  // Returns this three-dimensional symmetric dyadic tensor's yz = zy Cartesian component as a
  // mutable value.
  constexpr NumberType& Mutable_yz() noexcept {
    return xx_xy_xz_yy_yz_zz_[4];
  }

  // Returns this three-dimensional symmetric dyadic tensor's zx = xz Cartesian component as a
  // mutable value.
  constexpr NumberType& Mutable_zx() noexcept {
    return xx_xy_xz_yy_yz_zz_[2];
  }

  // Returns this three-dimensional symmetric dyadic tensor's zy = yz Cartesian component as a
  // mutable value.
  constexpr NumberType& Mutable_zy() noexcept {
    return xx_xy_xz_yy_yz_zz_[4];
  }

  // Returns this three-dimensional symmetric dyadic tensor's zz Cartesian component as a mutable
  // value.
  constexpr NumberType& Mutable_zz() noexcept {
    return xx_xy_xz_yy_yz_zz_[5];
  }

  // Sets this three-dimensional symmetric dyadic tensor's xx, xy, xz, yy, yz, and zz Cartesian
  // components to the given values.
  constexpr void Set_xx_xy_xz_yy_yz_zz(
      const std::array<NumberType, 6>& xx_xy_xz_yy_yz_zz) noexcept {
    xx_xy_xz_yy_yz_zz_ = xx_xy_xz_yy_yz_zz;
  }

  // Sets this three-dimensional symmetric dyadic tensor's xx, xy, xz, yy, yz, and zz Cartesian
  // components to the given values.
  constexpr void Set_xx_xy_xz_yy_yz_zz(
      const NumberType xx, const NumberType xy, const NumberType xz, const NumberType yy,
      const NumberType yz, const NumberType zz) noexcept {
    xx_xy_xz_yy_yz_zz_[0] = xx;
    xx_xy_xz_yy_yz_zz_[1] = xy;
    xx_xy_xz_yy_yz_zz_[2] = xz;
    xx_xy_xz_yy_yz_zz_[3] = yy;
    xx_xy_xz_yy_yz_zz_[4] = yz;
    xx_xy_xz_yy_yz_zz_[5] = zz;
  }

  // Sets this three-dimensional symmetric dyadic tensor's xx Cartesian component to a given value.
  constexpr void Set_xx(const NumberType xx) noexcept {
    xx_xy_xz_yy_yz_zz_[0] = xx;
  }

  // Sets this three-dimensional symmetric dyadic tensor's xy = yx Cartesian component to a given
  // value.
  constexpr void Set_xy(const NumberType xy) noexcept {
    xx_xy_xz_yy_yz_zz_[1] = xy;
  }

  // Sets this three-dimensional symmetric dyadic tensor's xz = zx Cartesian component to a given
  // value.
  constexpr void Set_xz(const NumberType xz) noexcept {
    xx_xy_xz_yy_yz_zz_[2] = xz;
  }

  // Sets this three-dimensional symmetric dyadic tensor's yx = xy Cartesian component to a given
  // value.
  constexpr void Set_yx(const NumberType yx) noexcept {
    xx_xy_xz_yy_yz_zz_[1] = yx;
  }

  // Sets this three-dimensional symmetric dyadic tensor's yy Cartesian component to a given value.
  constexpr void Set_yy(const NumberType yy) noexcept {
    xx_xy_xz_yy_yz_zz_[3] = yy;
  }

  // Sets this three-dimensional symmetric dyadic tensor's yz = zy Cartesian component to a given
  // value.
  constexpr void Set_yz(const NumberType yz) noexcept {
    xx_xy_xz_yy_yz_zz_[4] = yz;
  }

  // Sets this three-dimensional symmetric dyadic tensor's zx = xz Cartesian component to a given
  // value.
  constexpr void Set_zx(const NumberType zx) noexcept {
    xx_xy_xz_yy_yz_zz_[2] = zx;
  }

  // Sets this three-dimensional symmetric dyadic tensor's zy = yz Cartesian component to a given
  // value.
  constexpr void Set_zy(const NumberType zy) noexcept {
    xx_xy_xz_yy_yz_zz_[4] = zy;
  }

  // Sets this three-dimensional symmetric dyadic tensor's zz Cartesian component to a given value.
  constexpr void Set_zz(const NumberType zz) noexcept {
    xx_xy_xz_yy_yz_zz_[5] = zz;
  }

  // Returns the trace of this three-dimensional symmetric dyadic tensor.
  [[nodiscard]] constexpr NumberType Trace() const noexcept {
    return xx() + yy() + zz();
  }

  // Returns the determinant of this three-dimensional symmetric dyadic tensor.
  [[nodiscard]] constexpr NumberType Determinant() const noexcept {
    return xx() * (yy() * zz() - yz() * zy()) + xy() * (yz() * zx() - yx() * zz())
           + xz() * (yx() * zy() - yy() * zx());
  }

  // Returns the transpose of this three-dimensional symmetric dyadic tensor.
  [[nodiscard]] constexpr const SymmetricDyad& Transpose() const noexcept {
    return *this;
  }

  // Returns the cofactors of this three-dimensional symmetric dyadic tensor.
  [[nodiscard]] constexpr SymmetricDyad Cofactors() const {
    const NumberType cofactor_xx{yy() * zz() - yz() * yz()};
    const NumberType cofactor_xy{xz() * yz() - xy() * zz()};
    const NumberType cofactor_xz{xy() * yz() - xz() * yy()};
    const NumberType cofactor_yy{xx() * zz() - xz() * xz()};
    const NumberType cofactor_yz{xy() * xz() - xx() * yz()};
    const NumberType cofactor_zz{xx() * yy() - xy() * xy()};
    return {cofactor_xx, cofactor_xy, cofactor_xz, cofactor_yy, cofactor_yz, cofactor_zz};
  }

  // Returns the adjugate of this three-dimensional symmetric dyadic tensor.
  [[nodiscard]] constexpr SymmetricDyad Adjugate() const {
    // In general, for a dyadic tensor, this is cofactors().transpose(), but since this is a
    // symmetric dyadic tensor, the transpose is redundant.
    return Cofactors();
  }

  // Returns the inverse of this three-dimensional symmetric dyadic tensor if it exists, or
  // std::nullopt otherwise.
  [[nodiscard]] std::optional<SymmetricDyad> Inverse() const;

  // Prints this three-dimensional symmetric dyadic tensor as a string.
  [[nodiscard]] std::string Print() const {
    return "(" + PhQ::Print(xx_xy_xz_yy_yz_zz_[0]) + ", " + PhQ::Print(xx_xy_xz_yy_yz_zz_[1]) + ", "
           + PhQ::Print(xx_xy_xz_yy_yz_zz_[2]) + "; " + PhQ::Print(xx_xy_xz_yy_yz_zz_[3]) + ", "
           + PhQ::Print(xx_xy_xz_yy_yz_zz_[4]) + "; " + PhQ::Print(xx_xy_xz_yy_yz_zz_[5]) + ")";
  }

  // Serializes this three-dimensional symmetric dyadic tensor as a JSON message.
  [[nodiscard]] std::string JSON() const {
    return "{\"xx\":" + PhQ::Print(xx_xy_xz_yy_yz_zz_[0]) + ",\"xy\":"
           + PhQ::Print(xx_xy_xz_yy_yz_zz_[1]) + ",\"xz\":" + PhQ::Print(xx_xy_xz_yy_yz_zz_[2])
           + ",\"yy\":" + PhQ::Print(xx_xy_xz_yy_yz_zz_[3])
           + ",\"yz\":" + PhQ::Print(xx_xy_xz_yy_yz_zz_[4])
           + ",\"zz\":" + PhQ::Print(xx_xy_xz_yy_yz_zz_[5]) + "}";
  }

  // Serializes this three-dimensional symmetric dyadic tensor as an XML message.
  [[nodiscard]] std::string XML() const {
    return "<xx>" + PhQ::Print(xx_xy_xz_yy_yz_zz_[0]) + "</xx><xy>"
           + PhQ::Print(xx_xy_xz_yy_yz_zz_[1]) + "</xy><xz>" + PhQ::Print(xx_xy_xz_yy_yz_zz_[2])
           + "</xz><yy>" + PhQ::Print(xx_xy_xz_yy_yz_zz_[3]) + "</yy><yz>"
           + PhQ::Print(xx_xy_xz_yy_yz_zz_[4]) + "</yz><zz>" + PhQ::Print(xx_xy_xz_yy_yz_zz_[5])
           + "</zz>";
  }

  // Serializes this three-dimensional symmetric dyadic tensor as a YAML message.
  [[nodiscard]] std::string YAML() const {
    return "{xx:" + PhQ::Print(xx_xy_xz_yy_yz_zz_[0]) + ",xy:" + PhQ::Print(xx_xy_xz_yy_yz_zz_[1])
           + ",xz:" + PhQ::Print(xx_xy_xz_yy_yz_zz_[2]) + ",yy:" + PhQ::Print(xx_xy_xz_yy_yz_zz_[3])
           + ",yz:" + PhQ::Print(xx_xy_xz_yy_yz_zz_[4]) + ",zz:" + PhQ::Print(xx_xy_xz_yy_yz_zz_[5])
           + "}";
  }

  constexpr void operator+=(const SymmetricDyad& symmetric_dyad) noexcept {
    xx_xy_xz_yy_yz_zz_[0] += symmetric_dyad.xx_xy_xz_yy_yz_zz_[0];
    xx_xy_xz_yy_yz_zz_[1] += symmetric_dyad.xx_xy_xz_yy_yz_zz_[1];
    xx_xy_xz_yy_yz_zz_[2] += symmetric_dyad.xx_xy_xz_yy_yz_zz_[2];
    xx_xy_xz_yy_yz_zz_[3] += symmetric_dyad.xx_xy_xz_yy_yz_zz_[3];
    xx_xy_xz_yy_yz_zz_[4] += symmetric_dyad.xx_xy_xz_yy_yz_zz_[4];
    xx_xy_xz_yy_yz_zz_[5] += symmetric_dyad.xx_xy_xz_yy_yz_zz_[5];
  }

  constexpr void operator-=(const SymmetricDyad& symmetric_dyad) noexcept {
    xx_xy_xz_yy_yz_zz_[0] -= symmetric_dyad.xx_xy_xz_yy_yz_zz_[0];
    xx_xy_xz_yy_yz_zz_[1] -= symmetric_dyad.xx_xy_xz_yy_yz_zz_[1];
    xx_xy_xz_yy_yz_zz_[2] -= symmetric_dyad.xx_xy_xz_yy_yz_zz_[2];
    xx_xy_xz_yy_yz_zz_[3] -= symmetric_dyad.xx_xy_xz_yy_yz_zz_[3];
    xx_xy_xz_yy_yz_zz_[4] -= symmetric_dyad.xx_xy_xz_yy_yz_zz_[4];
    xx_xy_xz_yy_yz_zz_[5] -= symmetric_dyad.xx_xy_xz_yy_yz_zz_[5];
  }

  template <typename OtherNumberType>
  constexpr void operator*=(const OtherNumberType number) noexcept {
    xx_xy_xz_yy_yz_zz_[0] *= number;
    xx_xy_xz_yy_yz_zz_[1] *= number;
    xx_xy_xz_yy_yz_zz_[2] *= number;
    xx_xy_xz_yy_yz_zz_[3] *= number;
    xx_xy_xz_yy_yz_zz_[4] *= number;
    xx_xy_xz_yy_yz_zz_[5] *= number;
  }

  template <typename OtherNumberType>
  constexpr void operator/=(const OtherNumberType number) noexcept {
    xx_xy_xz_yy_yz_zz_[0] /= number;
    xx_xy_xz_yy_yz_zz_[1] /= number;
    xx_xy_xz_yy_yz_zz_[2] /= number;
    xx_xy_xz_yy_yz_zz_[3] /= number;
    xx_xy_xz_yy_yz_zz_[4] /= number;
    xx_xy_xz_yy_yz_zz_[5] /= number;
  }

private:
  // Cartesian components of this three-dimensional symmetric dyadic tensor.
  std::array<NumberType, 6> xx_xy_xz_yy_yz_zz_;

  friend class Dyad<NumberType>;
};

template <typename NumberType>
inline constexpr bool operator==(
    const SymmetricDyad<NumberType>& left, const SymmetricDyad<NumberType>& right) noexcept {
  return (left.xx() == right.xx() && left.xy() == right.xy() && left.xz() == right.xz()
          && left.yy() == right.yy() && left.yz() == right.yz() && left.zz() == right.zz());
}

template <typename NumberType>
inline constexpr bool operator!=(
    const SymmetricDyad<NumberType>& left, const SymmetricDyad<NumberType>& right) noexcept {
  return (left.xx() != right.xx() || left.xy() != right.xy() || left.xz() != right.xz()
          || left.yy() != right.yy() || left.yz() != right.yz() || left.zz() != right.zz());
}

template <typename NumberType>
inline constexpr bool operator<(
    const SymmetricDyad<NumberType>& left, const SymmetricDyad<NumberType>& right) noexcept {
  if (left.xx() != right.xx()) {
    return left.xx() < right.xx();
  }
  if (left.xy() != right.xy()) {
    return left.xy() < right.xy();
  }
  if (left.xz() != right.xz()) {
    return left.xz() < right.xz();
  }
  if (left.yy() != right.yy()) {
    return left.yy() < right.yy();
  }
  if (left.yz() != right.yz()) {
    return left.yz() < right.yz();
  }
  return left.zz() < right.zz();
}

template <typename NumberType>
inline constexpr bool operator>(
    const SymmetricDyad<NumberType>& left, const SymmetricDyad<NumberType>& right) noexcept {
  if (left.xx() != right.xx()) {
    return left.xx() > right.xx();
  }
  if (left.xy() != right.xy()) {
    return left.xy() > right.xy();
  }
  if (left.xz() != right.xz()) {
    return left.xz() > right.xz();
  }
  if (left.yy() != right.yy()) {
    return left.yy() > right.yy();
  }
  if (left.yz() != right.yz()) {
    return left.yz() > right.yz();
  }
  return left.zz() > right.zz();
}

template <typename NumberType>
inline constexpr bool operator<=(
    const SymmetricDyad<NumberType>& left, const SymmetricDyad<NumberType>& right) noexcept {
  return !(left > right);
}

template <typename NumberType>
inline constexpr bool operator>=(
    const SymmetricDyad<NumberType>& left, const SymmetricDyad<NumberType>& right) noexcept {
  return !(left < right);
}

template <typename NumberType>
inline constexpr SymmetricDyad<NumberType> operator+(
    const SymmetricDyad<NumberType>& left, const SymmetricDyad<NumberType>& right) {
  return {left.xx() + right.xx(), left.xy() + right.xy(), left.xz() + right.xz(),
          left.yy() + right.yy(), left.yz() + right.yz(), left.zz() + right.zz()};
}

template <typename NumberType>
inline constexpr SymmetricDyad<NumberType> operator-(
    const SymmetricDyad<NumberType>& left, const SymmetricDyad<NumberType>& right) {
  return {left.xx() - right.xx(), left.xy() - right.xy(), left.xz() - right.xz(),
          left.yy() - right.yy(), left.yz() - right.yz(), left.zz() - right.zz()};
}

template <typename NumberType, typename OtherNumberType>
inline constexpr SymmetricDyad<NumberType> operator*(
    const SymmetricDyad<NumberType>& symmetric_dyad, const OtherNumberType number) {
  return {symmetric_dyad.xx() * number, symmetric_dyad.xy() * number, symmetric_dyad.xz() * number,
          symmetric_dyad.yy() * number, symmetric_dyad.yz() * number, symmetric_dyad.zz() * number};
}

template <typename NumberType, typename OtherNumberType>
inline constexpr SymmetricDyad<NumberType> operator*(
    const OtherNumberType number, const SymmetricDyad<NumberType>& symmetric_dyad) {
  return {symmetric_dyad * number};
}

template <typename NumberType>
inline constexpr Vector<NumberType> operator*(
    const SymmetricDyad<NumberType>& symmetric_dyad, const Vector<NumberType>& vector) {
  return {symmetric_dyad.xx() * vector.x() + symmetric_dyad.xy() * vector.y()
              + symmetric_dyad.xz() * vector.z(),
          symmetric_dyad.xy() * vector.x() + symmetric_dyad.yy() * vector.y()
              + symmetric_dyad.yz() * vector.z(),
          symmetric_dyad.xz() * vector.x() + symmetric_dyad.yz() * vector.y()
              + symmetric_dyad.zz() * vector.z()};
}

template <typename NumberType>
inline constexpr Dyad<NumberType> operator*(
    const SymmetricDyad<NumberType>& left, const SymmetricDyad<NumberType>& right);

template <typename NumberType>
inline constexpr Dyad<NumberType> operator*(
    const SymmetricDyad<NumberType>& symmetric_dyad, const Dyad<NumberType>& dyad);

template <typename NumberType, typename OtherNumberType>
inline constexpr SymmetricDyad<NumberType> operator/(
    const SymmetricDyad<NumberType>& symmetric_dyad, const OtherNumberType number) {
  return {symmetric_dyad.xx() / number, symmetric_dyad.xy() / number, symmetric_dyad.xz() / number,
          symmetric_dyad.yy() / number, symmetric_dyad.yz() / number, symmetric_dyad.zz() / number};
}

template <typename NumberType>
inline std::optional<SymmetricDyad<NumberType>> SymmetricDyad<NumberType>::Inverse() const {
  const NumberType determinant_{Determinant()};
  if (determinant_ != 0.0) {
    return std::optional<SymmetricDyad>{Adjugate() / determinant_};
  }
  return std::nullopt;
}

template <typename NumberType>
inline std::ostream& operator<<(std::ostream& stream, const SymmetricDyad<NumberType>& symmetric) {
  stream << symmetric.Print();
  return stream;
}

}  // namespace PhQ

namespace std {

template <typename NumberType>
struct hash<PhQ::SymmetricDyad<NumberType>> {
  inline size_t operator()(const PhQ::SymmetricDyad<NumberType>& symmetric) const {
    size_t result{17};
    result = 31 * result + hash<NumberType>()(symmetric.xx());
    result = 31 * result + hash<NumberType>()(symmetric.xy());
    result = 31 * result + hash<NumberType>()(symmetric.xz());
    result = 31 * result + hash<NumberType>()(symmetric.yy());
    result = 31 * result + hash<NumberType>()(symmetric.yz());
    result = 31 * result + hash<NumberType>()(symmetric.zz());
    return result;
  }
};

}  // namespace std

#endif  // PHQ_SYMMETRIC_DYAD_HPP
