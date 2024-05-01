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

#ifndef PHQ_DYAD_HPP
#define PHQ_DYAD_HPP

#include <array>
#include <cstddef>
#include <functional>
#include <optional>
#include <ostream>
#include <string>
#include <type_traits>

#include "Base.hpp"
#include "SymmetricDyad.hpp"
#include "Vector.hpp"

namespace PhQ {

// Three-dimensional dyadic tensor in Cartesian coordinates. May be non-symmetric. Contains nine
// components: xx, xy, xz, yx, yy, yz, zx, zy, and zz.
template <typename NumberType = double>
class Dyad {
  static_assert(std::is_floating_point<NumberType>::value,
                "NumberType must be a floating-point number type.");

public:
  // Default constructor. Constructs a three-dimensional dyadic tensor with uninitialized xx, xy,
  // xz, yx, yy, yz, zx, zy, and zz Cartesian components.
  Dyad() = default;

  // Constructor. Constructs a three-dimensional dyadic tensor from the given xx, xy, xz, yx, yy,
  // yz, zx, zy, and zz Cartesian components.
  constexpr Dyad(const NumberType xx, const NumberType xy, const NumberType xz, const NumberType yx,
                 const NumberType yy, const NumberType yz, const NumberType zx, const NumberType zy,
                 const NumberType zz)
    : xx_xy_xz_yx_yy_yz_zx_zy_zz_({xx, xy, xz, yx, yy, yz, zx, zy, zz}) {}

  // Constructor. Constructs a three-dimensional dyadic tensor from a given array representing its
  // xx, xy, xz, yx, yy, yz, zx, zy, and zz Cartesian components.
  explicit constexpr Dyad(const std::array<NumberType, 9>& xx_xy_xz_yx_yy_yz_zx_zy_zz)
    : xx_xy_xz_yx_yy_yz_zx_zy_zz_(xx_xy_xz_yx_yy_yz_zx_zy_zz) {}

  // Constructor. Constructs a three-dimensional dyadic tensor from a given three-dimensional
  // symmetric dyadic tensor.
  explicit constexpr Dyad(const SymmetricDyad<NumberType>& symmetric_dyad)
    : xx_xy_xz_yx_yy_yz_zx_zy_zz_(
        {symmetric_dyad.xx(), symmetric_dyad.xy(), symmetric_dyad.xz(), symmetric_dyad.yx(),
         symmetric_dyad.yy(), symmetric_dyad.yz(), symmetric_dyad.zx(), symmetric_dyad.zy(),
         symmetric_dyad.zz()}) {}

  // Destructor. Destroys this three-dimensional dyadic tensor.
  ~Dyad() noexcept = default;

  // Copy constructor. Constructs a three-dimensional dyadic tensor by copying another one.
  constexpr Dyad(const Dyad& other) = default;

  // Copy constructor. Constructs a three-dimensional dyadic tensor by copying another one.
  template <typename OtherNumberType>
  constexpr Dyad(const Dyad<OtherNumberType>& other)
    : xx_xy_xz_yx_yy_yz_zx_zy_zz_(other.xx_xy_xz_yx_yy_yz_zx_zy_zz_) {}

  // Move constructor. Constructs a three-dimensional dyadic tensor by moving another one.
  constexpr Dyad(Dyad&& other) noexcept = default;

  // Copy assignment operator. Assigns this three-dimensional dyadic tensor by copying another
  // one.
  constexpr Dyad& operator=(const Dyad& other) = default;

  // Copy assignment operator. Assigns this three-dimensional dyadic tensor by copying another
  // one.
  template <typename OtherNumberType>
  constexpr Dyad& operator=(const Dyad<OtherNumberType>& other) {
    xx_xy_xz_yx_yy_yz_zx_zy_zz_ = other.xx_xy_xz_yx_yy_yz_zx_zy_zz_;
    return *this;
  }

  // Move assignment operator. Assigns this three-dimensional dyadic tensor by moving another
  // one.
  constexpr Dyad& operator=(Dyad&& other) noexcept = default;

  // Assignment operator. Assigns this three-dimensional dyadic tensor by copying a
  // three-dimensional symmetric dyadic tensor.
  constexpr Dyad& operator=(const SymmetricDyad<NumberType>& other) {
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[0] = other.xx();
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[1] = other.xy();
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[2] = other.xz();
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[3] = other.yx();
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[4] = other.yy();
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[5] = other.yz();
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[6] = other.zx();
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[7] = other.zy();
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[8] = other.zz();
    return *this;
  }

  // Assignment operator. Assigns this three-dimensional dyadic tensor by copying a given array
  // representing its xx, xy, xz, yx, yy, yz, zx, zy, and zz Cartesian components.
  constexpr Dyad& operator=(const std::array<NumberType, 9>& xx_xy_xz_yx_yy_yz_zx_zy_zz) {
    xx_xy_xz_yx_yy_yz_zx_zy_zz_ = xx_xy_xz_yx_yy_yz_zx_zy_zz;
    return *this;
  }

  // Statically creates a three-dimensional dyadic tensor with its xx, xy, xz, yx, yy, yz, zx, zy,
  // and zz Cartesian components initialized to zero.
  static constexpr Dyad Zero() {
    return Dyad{
        std::array<NumberType, 9>{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
    };
  }

  // Returns this three-dimensional symmetric dyadic tensor's xx, xy, xz, yx, yy, yz, zx, zy, and zz
  // Cartesian components as an array.
  [[nodiscard]] constexpr const std::array<NumberType, 9>&
  xx_xy_xz_yx_yy_yz_zx_zy_zz() const noexcept {
    return xx_xy_xz_yx_yy_yz_zx_zy_zz_;
  }

  // Returns this three-dimensional dyadic tensor's xx Cartesian component.
  [[nodiscard]] constexpr NumberType xx() const noexcept {
    return xx_xy_xz_yx_yy_yz_zx_zy_zz_[0];
  }

  // Returns this three-dimensional dyadic tensor's xy Cartesian component.
  [[nodiscard]] constexpr NumberType xy() const noexcept {
    return xx_xy_xz_yx_yy_yz_zx_zy_zz_[1];
  }

  // Returns this three-dimensional dyadic tensor's xz Cartesian component.
  [[nodiscard]] constexpr NumberType xz() const noexcept {
    return xx_xy_xz_yx_yy_yz_zx_zy_zz_[2];
  }

  // Returns this three-dimensional dyadic tensor's yx Cartesian component.
  [[nodiscard]] constexpr NumberType yx() const noexcept {
    return xx_xy_xz_yx_yy_yz_zx_zy_zz_[3];
  }

  // Returns this three-dimensional dyadic tensor's yy Cartesian component.
  [[nodiscard]] constexpr NumberType yy() const noexcept {
    return xx_xy_xz_yx_yy_yz_zx_zy_zz_[4];
  }

  // Returns this three-dimensional dyadic tensor's yz Cartesian component.
  [[nodiscard]] constexpr NumberType yz() const noexcept {
    return xx_xy_xz_yx_yy_yz_zx_zy_zz_[5];
  }

  // Returns this three-dimensional dyadic tensor's zx Cartesian component.
  [[nodiscard]] constexpr NumberType zx() const noexcept {
    return xx_xy_xz_yx_yy_yz_zx_zy_zz_[6];
  }

  // Returns this three-dimensional dyadic tensor's zy Cartesian component.
  [[nodiscard]] constexpr NumberType zy() const noexcept {
    return xx_xy_xz_yx_yy_yz_zx_zy_zz_[7];
  }

  // Returns this three-dimensional dyadic tensor's zz Cartesian component.
  [[nodiscard]] constexpr NumberType zz() const noexcept {
    return xx_xy_xz_yx_yy_yz_zx_zy_zz_[8];
  }

  // Returns this three-dimensional symmetric dyadic tensor's xx, xy, xz, yx, yy, yz, zx, zy, and zz
  // Cartesian components as a mutable array.
  constexpr std::array<NumberType, 9>& Mutable_xx_xy_xz_yx_yy_yz_zx_zy_zz() noexcept {
    return xx_xy_xz_yx_yy_yz_zx_zy_zz_;
  }

  // Returns this three-dimensional dyadic tensor's xx Cartesian component as a mutable value.
  constexpr NumberType& Mutable_xx() noexcept {
    return xx_xy_xz_yx_yy_yz_zx_zy_zz_[0];
  }

  // Returns this three-dimensional dyadic tensor's xy Cartesian component as a mutable value.
  constexpr NumberType& Mutable_xy() noexcept {
    return xx_xy_xz_yx_yy_yz_zx_zy_zz_[1];
  }

  // Returns this three-dimensional dyadic tensor's xz Cartesian component as a mutable value.
  constexpr NumberType& Mutable_xz() noexcept {
    return xx_xy_xz_yx_yy_yz_zx_zy_zz_[2];
  }

  // Returns this three-dimensional dyadic tensor's yx Cartesian component as a mutable value.
  constexpr NumberType& Mutable_yx() noexcept {
    return xx_xy_xz_yx_yy_yz_zx_zy_zz_[3];
  }

  // Returns this three-dimensional dyadic tensor's yy Cartesian component as a mutable value.
  constexpr NumberType& Mutable_yy() noexcept {
    return xx_xy_xz_yx_yy_yz_zx_zy_zz_[4];
  }

  // Returns this three-dimensional dyadic tensor's yz Cartesian component as a mutable value.
  constexpr NumberType& Mutable_yz() noexcept {
    return xx_xy_xz_yx_yy_yz_zx_zy_zz_[5];
  }

  // Returns this three-dimensional dyadic tensor's zx Cartesian component as a mutable value.
  constexpr NumberType& Mutable_zx() noexcept {
    return xx_xy_xz_yx_yy_yz_zx_zy_zz_[6];
  }

  // Returns this three-dimensional dyadic tensor's zy Cartesian component as a mutable value.
  constexpr NumberType& Mutable_zy() noexcept {
    return xx_xy_xz_yx_yy_yz_zx_zy_zz_[7];
  }

  // Returns this three-dimensional dyadic tensor's zz Cartesian component as a mutable value.
  constexpr NumberType& Mutable_zz() noexcept {
    return xx_xy_xz_yx_yy_yz_zx_zy_zz_[8];
  }

  // Sets this three-dimensional dyadic tensor's xx, xy, xz, yx, yy, yz, zx, zy, and zz Cartesian
  // components to the given values.
  constexpr void Set_xx_xy_xz_yx_yy_yz_zx_zy_zz(
      const std::array<NumberType, 9>& xx_xy_xz_yx_yy_yz_zx_zy_zz) noexcept {
    xx_xy_xz_yx_yy_yz_zx_zy_zz_ = xx_xy_xz_yx_yy_yz_zx_zy_zz;
  }

  // Sets this three-dimensional dyadic tensor's xx, xy, xz, yx, yy, yz, zx, zy, and zz Cartesian
  // components to the given values.
  constexpr void Set_xx_xy_xz_yx_yy_yz_zx_zy_zz(
      const NumberType xx, const NumberType xy, const NumberType xz, const NumberType yx,
      const NumberType yy, const NumberType yz, const NumberType zx, const NumberType zy,
      const NumberType zz) noexcept {
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[0] = xx;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[1] = xy;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[2] = xz;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[3] = yx;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[4] = yy;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[5] = yz;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[6] = zx;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[7] = zy;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[8] = zz;
  }

  // Sets this three-dimensional dyadic tensor's xx Cartesian component to a given value.
  constexpr void Set_xx(const NumberType xx) noexcept {
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[0] = xx;
  }

  // Sets this three-dimensional dyadic tensor's xy Cartesian component to a given value.
  constexpr void Set_xy(const NumberType xy) noexcept {
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[1] = xy;
  }

  // Sets this three-dimensional dyadic tensor's xz Cartesian component to a given value.
  constexpr void Set_xz(const NumberType xz) noexcept {
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[2] = xz;
  }

  // Sets this three-dimensional dyadic tensor's yx Cartesian component to a given value.
  constexpr void Set_yx(const NumberType yx) noexcept {
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[3] = yx;
  }

  // Sets this three-dimensional dyadic tensor's yy Cartesian component to a given value.
  constexpr void Set_yy(const NumberType yy) noexcept {
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[4] = yy;
  }

  // Sets this three-dimensional dyadic tensor's yz Cartesian component to a given value.
  constexpr void Set_yz(const NumberType yz) noexcept {
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[5] = yz;
  }

  // Sets this three-dimensional dyadic tensor's zx Cartesian component to a given value.
  constexpr void Set_zx(const NumberType zx) noexcept {
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[6] = zx;
  }

  // Sets this three-dimensional dyadic tensor's zy Cartesian component to a given value.
  constexpr void Set_zy(const NumberType zy) noexcept {
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[7] = zy;
  }

  // Sets this three-dimensional dyadic tensor's zz Cartesian component to a given value.
  constexpr void Set_zz(const NumberType zz) noexcept {
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[8] = zz;
  }

  // Returns whether this three-dimensional dyadic tensor is symmetric.
  [[nodiscard]] constexpr bool IsSymmetric() const noexcept {
    return xy() == yx() && xz() == zx() && yz() == zy();
  }

  // Returns the trace of this three-dimensional dyadic tensor.
  [[nodiscard]] constexpr NumberType Trace() const noexcept {
    return xx() + yy() + zz();
  }

  // Returns the determinant of this three-dimensional dyadic tensor.
  [[nodiscard]] constexpr NumberType Determinant() const noexcept {
    return (xx() * (yy() * zz() - yz() * zy()) + xy() * (yz() * zx() - yx() * zz())
            + xz() * (yx() * zy() - yy() * zx()));
  }

  // Returns the transpose of this three-dimensional dyadic tensor.
  [[nodiscard]] constexpr Dyad Transpose() const {
    return {xx(), yx(), zx(), xy(), yy(), zy(), xz(), yz(), zz()};
  }

  // Returns the cofactors of this three-dimensional dyadic tensor.
  [[nodiscard]] constexpr Dyad Cofactors() const {
    const NumberType cofactor_xx{yy() * zz() - yz() * zy()};
    const NumberType cofactor_xy{yz() * zx() - yx() * zz()};
    const NumberType cofactor_xz{yx() * zy() - yy() * zx()};
    const NumberType cofactor_yx{xz() * zy() - xy() * zz()};
    const NumberType cofactor_yy{xx() * zz() - xz() * zx()};
    const NumberType cofactor_yz{xy() * zx() - xx() * zy()};
    const NumberType cofactor_zx{xy() * yz() - xz() * yy()};
    const NumberType cofactor_zy{xz() * yx() - xx() * yz()};
    const NumberType cofactor_zz{xx() * yy() - xy() * yx()};
    return {cofactor_xx, cofactor_xy, cofactor_xz, cofactor_yx, cofactor_yy,
            cofactor_yz, cofactor_zx, cofactor_zy, cofactor_zz};
  }

  // Returns the adjugate of this three-dimensional dyadic tensor.
  [[nodiscard]] constexpr Dyad Adjugate() const {
    return Cofactors().Transpose();
  }

  // Returns the inverse of this three-dimensional dyadic tensor if it exists, or std::nullopt
  // otherwise.
  [[nodiscard]] constexpr std::optional<Dyad> Inverse() const;

  // Prints this three-dimensional dyadic tensor as a string.
  [[nodiscard]] std::string Print() const {
    return "(" + PhQ::Print(xx()) + ", " + PhQ::Print(xy()) + ", " + PhQ::Print(xz()) + "; "
           + PhQ::Print(yx()) + ", " + PhQ::Print(yy()) + ", " + PhQ::Print(yz()) + "; "
           + PhQ::Print(zx()) + ", " + PhQ::Print(zy()) + ", " + PhQ::Print(zz()) + ")";
  }

  // Serializes this three-dimensional dyadic tensor as a JSON message.
  [[nodiscard]] std::string JSON() const {
    return "{\"xx\":" + PhQ::Print(xx()) + ",\"xy\":" + PhQ::Print(xy()) + ",\"xz\":"
           + PhQ::Print(xz()) + ",\"yx\":" + PhQ::Print(yx()) + ",\"yy\":" + PhQ::Print(yy())
           + ",\"yz\":" + PhQ::Print(yz()) + ",\"zx\":" + PhQ::Print(zx())
           + ",\"zy\":" + PhQ::Print(zy()) + ",\"zz\":" + PhQ::Print(zz()) + "}";
  }

  // Serializes this three-dimensional dyadic tensor as an XML message.
  [[nodiscard]] std::string XML() const {
    return "<xx>" + PhQ::Print(xx()) + "</xx><xy>" + PhQ::Print(xy()) + "</xy><xz>"
           + PhQ::Print(xz()) + "</xz><yx>" + PhQ::Print(yx()) + "</yx><yy>" + PhQ::Print(yy())
           + "</yy><yz>" + PhQ::Print(yz()) + "</yz><zx>" + PhQ::Print(zx()) + "</zx><zy>"
           + PhQ::Print(zy()) + "</zy><zz>" + PhQ::Print(zz()) + "</zz>";
  }

  // Serializes this three-dimensional dyadic tensor as a YAML message.
  [[nodiscard]] std::string YAML() const {
    return "{xx:" + PhQ::Print(xx()) + ",xy:" + PhQ::Print(xy()) + ",xz:" + PhQ::Print(xz())
           + ",yx:" + PhQ::Print(yx()) + ",yy:" + PhQ::Print(yy()) + ",yz:" + PhQ::Print(yz())
           + ",zx:" + PhQ::Print(zx()) + ",zy:" + PhQ::Print(zy()) + ",zz:" + PhQ::Print(zz())
           + "}";
  }

  constexpr void operator+=(const Dyad& dyad) noexcept {
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[0] += dyad.xx_xy_xz_yx_yy_yz_zx_zy_zz_[0];
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[1] += dyad.xx_xy_xz_yx_yy_yz_zx_zy_zz_[1];
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[2] += dyad.xx_xy_xz_yx_yy_yz_zx_zy_zz_[2];
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[3] += dyad.xx_xy_xz_yx_yy_yz_zx_zy_zz_[3];
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[4] += dyad.xx_xy_xz_yx_yy_yz_zx_zy_zz_[4];
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[5] += dyad.xx_xy_xz_yx_yy_yz_zx_zy_zz_[5];
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[6] += dyad.xx_xy_xz_yx_yy_yz_zx_zy_zz_[6];
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[7] += dyad.xx_xy_xz_yx_yy_yz_zx_zy_zz_[7];
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[8] += dyad.xx_xy_xz_yx_yy_yz_zx_zy_zz_[8];
  }

  constexpr void operator-=(const Dyad& dyad) noexcept {
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[0] -= dyad.xx_xy_xz_yx_yy_yz_zx_zy_zz_[0];
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[1] -= dyad.xx_xy_xz_yx_yy_yz_zx_zy_zz_[1];
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[2] -= dyad.xx_xy_xz_yx_yy_yz_zx_zy_zz_[2];
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[3] -= dyad.xx_xy_xz_yx_yy_yz_zx_zy_zz_[3];
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[4] -= dyad.xx_xy_xz_yx_yy_yz_zx_zy_zz_[4];
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[5] -= dyad.xx_xy_xz_yx_yy_yz_zx_zy_zz_[5];
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[6] -= dyad.xx_xy_xz_yx_yy_yz_zx_zy_zz_[6];
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[7] -= dyad.xx_xy_xz_yx_yy_yz_zx_zy_zz_[7];
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[8] -= dyad.xx_xy_xz_yx_yy_yz_zx_zy_zz_[8];
  }

  template <typename OtherNumberType>
  constexpr void operator*=(const OtherNumberType number) noexcept {
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[0] *= number;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[1] *= number;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[2] *= number;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[3] *= number;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[4] *= number;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[5] *= number;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[6] *= number;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[7] *= number;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[8] *= number;
  }

  template <typename OtherNumberType>
  constexpr void operator/=(const OtherNumberType number) noexcept {
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[0] /= number;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[1] /= number;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[2] /= number;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[3] /= number;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[4] /= number;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[5] /= number;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[6] /= number;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[7] /= number;
    xx_xy_xz_yx_yy_yz_zx_zy_zz_[8] /= number;
  }

private:
  // Cartesian components of this three-dimensional dyadic tensor.
  std::array<NumberType, 9> xx_xy_xz_yx_yy_yz_zx_zy_zz_;
};

template <typename NumberType>
inline constexpr bool operator==(
    const Dyad<NumberType>& left, const Dyad<NumberType>& right) noexcept {
  return (left.xx() == right.xx() && left.xy() == right.xy() && left.xz() == right.xz()
          && left.yx() == right.yx() && left.yy() == right.yy() && left.yz() == right.yz()
          && left.zx() == right.zx() && left.zy() == right.zy() && left.zz() == right.zz());
}

template <typename NumberType>
inline constexpr bool operator!=(
    const Dyad<NumberType>& left, const Dyad<NumberType>& right) noexcept {
  return (left.xx() != right.xx() || left.xy() != right.xy() || left.xz() != right.xz()
          || left.yx() != right.yx() || left.yy() != right.yy() || left.yz() != right.yz()
          || left.zx() != right.zx() || left.zy() != right.zy() || left.zz() != right.zz());
}

template <typename NumberType>
inline constexpr bool operator<(
    const Dyad<NumberType>& left, const Dyad<NumberType>& right) noexcept {
  if (left.xx() != right.xx()) {
    return left.xx() < right.xx();
  }
  if (left.xy() != right.xy()) {
    return left.xy() < right.xy();
  }
  if (left.xz() != right.xz()) {
    return left.xz() < right.xz();
  }
  if (left.yx() != right.yx()) {
    return left.yx() < right.yx();
  }
  if (left.yy() != right.yy()) {
    return left.yy() < right.yy();
  }
  if (left.yz() != right.yz()) {
    return left.yz() < right.yz();
  }
  if (left.zx() != right.zx()) {
    return left.zx() < right.zx();
  }
  if (left.zy() != right.zy()) {
    return left.zy() < right.zy();
  }
  return left.zz() < right.zz();
}

template <typename NumberType>
inline constexpr bool operator>(
    const Dyad<NumberType>& left, const Dyad<NumberType>& right) noexcept {
  if (left.xx() != right.xx()) {
    return left.xx() > right.xx();
  }
  if (left.xy() != right.xy()) {
    return left.xy() > right.xy();
  }
  if (left.xz() != right.xz()) {
    return left.xz() > right.xz();
  }
  if (left.yx() != right.yx()) {
    return left.yx() > right.yx();
  }
  if (left.yy() != right.yy()) {
    return left.yy() > right.yy();
  }
  if (left.yz() != right.yz()) {
    return left.yz() > right.yz();
  }
  if (left.zx() != right.zx()) {
    return left.zx() > right.zx();
  }
  if (left.zy() != right.zy()) {
    return left.zy() > right.zy();
  }
  return left.zz() > right.zz();
}

template <typename NumberType>
inline constexpr bool operator<=(
    const Dyad<NumberType>& left, const Dyad<NumberType>& right) noexcept {
  return !(left > right);
}

template <typename NumberType>
inline constexpr bool operator>=(
    const Dyad<NumberType>& left, const Dyad<NumberType>& right) noexcept {
  return !(left < right);
}

template <typename NumberType>
inline constexpr Dyad<NumberType> operator+(
    const Dyad<NumberType>& left, const Dyad<NumberType>& right) {
  return {left.xx() + right.xx(), left.xy() + right.xy(), left.xz() + right.xz(),
          left.yx() + right.yx(), left.yy() + right.yy(), left.yz() + right.yz(),
          left.zx() + right.zx(), left.zy() + right.zy(), left.zz() + right.zz()};
}

template <typename NumberType>
inline constexpr Dyad<NumberType> operator-(
    const Dyad<NumberType>& left, const Dyad<NumberType>& right) {
  return {left.xx() - right.xx(), left.xy() - right.xy(), left.xz() - right.xz(),
          left.yx() - right.yx(), left.yy() - right.yy(), left.yz() - right.yz(),
          left.zx() - right.zx(), left.zy() - right.zy(), left.zz() - right.zz()};
}

template <typename NumberType, typename OtherNumberType>
inline constexpr Dyad<NumberType> operator*(
    const Dyad<NumberType>& dyad, const OtherNumberType number) {
  return {dyad.xx() * number, dyad.xy() * number, dyad.xz() * number,
          dyad.yx() * number, dyad.yy() * number, dyad.yz() * number,
          dyad.zx() * number, dyad.zy() * number, dyad.zz() * number};
}

template <typename NumberType, typename OtherNumberType>
inline constexpr Dyad<NumberType> operator*(
    const OtherNumberType number, const Dyad<NumberType>& dyad) {
  return {dyad * number};
}

template <typename NumberType>
inline constexpr Vector<NumberType> operator*(
    const Dyad<NumberType>& dyad, const Vector<NumberType>& vector) {
  return {dyad.xx() * vector.x() + dyad.xy() * vector.y() + dyad.xz() * vector.z(),
          dyad.yx() * vector.x() + dyad.yy() * vector.y() + dyad.yz() * vector.z(),
          dyad.zx() * vector.x() + dyad.zy() * vector.y() + dyad.zz() * vector.z()};
}

template <typename NumberType>
inline constexpr Dyad<NumberType> operator*(
    const SymmetricDyad<NumberType>& left, const SymmetricDyad<NumberType>& right) {
  return {left.xx() * right.xx() + left.xy() * right.xy() + left.xz() * right.xz(),
          left.xx() * right.xy() + left.xy() * right.yy() + left.xz() * right.yz(),
          left.xx() * right.xz() + left.xy() * right.yz() + left.xz() * right.zz(),
          left.xy() * right.xx() + left.yy() * right.xy() + left.yz() * right.xz(),
          left.xy() * right.xy() + left.yy() * right.yy() + left.yz() * right.yz(),
          left.xy() * right.xz() + left.yy() * right.yz() + left.yz() * right.zz(),
          left.xz() * right.xx() + left.yz() * right.xy() + left.zz() * right.xz(),
          left.xz() * right.xy() + left.yz() * right.yy() + left.zz() * right.yz(),
          left.xz() * right.xz() + left.yz() * right.yz() + left.zz() * right.zz()};
}

template <typename NumberType>
inline constexpr Dyad<NumberType> operator*(
    const SymmetricDyad<NumberType>& symmetric_dyad, const Dyad<NumberType>& dyad) {
  return {
      symmetric_dyad.xx() * dyad.xx() + symmetric_dyad.xy() * dyad.yx()
          + symmetric_dyad.xz() * dyad.zx(),
      symmetric_dyad.xx() * dyad.xy() + symmetric_dyad.xy() * dyad.yy()
          + symmetric_dyad.xz() * dyad.zy(),
      symmetric_dyad.xx() * dyad.xz() + symmetric_dyad.xy() * dyad.yz()
          + symmetric_dyad.xz() * dyad.zz(),
      symmetric_dyad.xy() * dyad.xx() + symmetric_dyad.yy() * dyad.yx()
          + symmetric_dyad.yz() * dyad.zx(),
      symmetric_dyad.xy() * dyad.xy() + symmetric_dyad.yy() * dyad.yy()
          + symmetric_dyad.yz() * dyad.zy(),
      symmetric_dyad.xy() * dyad.xz() + symmetric_dyad.yy() * dyad.yz()
          + symmetric_dyad.yz() * dyad.zz(),
      symmetric_dyad.xz() * dyad.xx() + symmetric_dyad.yz() * dyad.yx()
          + symmetric_dyad.zz() * dyad.zx(),
      symmetric_dyad.xz() * dyad.xy() + symmetric_dyad.yz() * dyad.yy()
          + symmetric_dyad.zz() * dyad.zy(),
      symmetric_dyad.xz() * dyad.xz() + symmetric_dyad.yz() * dyad.yz()
          + symmetric_dyad.zz() * dyad.zz()};
}

template <typename NumberType>
inline constexpr Dyad<NumberType> operator*(
    const Dyad<NumberType>& dyad, const SymmetricDyad<NumberType>& symmetric_dyad) {
  return {
      dyad.xx() * symmetric_dyad.xx() + dyad.xy() * symmetric_dyad.yx()
          + dyad.xz() * symmetric_dyad.zx(),
      dyad.xx() * symmetric_dyad.xy() + dyad.xy() * symmetric_dyad.yy()
          + dyad.xz() * symmetric_dyad.zy(),
      dyad.xx() * symmetric_dyad.xz() + dyad.xy() * symmetric_dyad.yz()
          + dyad.xz() * symmetric_dyad.zz(),
      dyad.yx() * symmetric_dyad.xx() + dyad.yy() * symmetric_dyad.yx()
          + dyad.yz() * symmetric_dyad.zx(),
      dyad.yx() * symmetric_dyad.xy() + dyad.yy() * symmetric_dyad.yy()
          + dyad.yz() * symmetric_dyad.zy(),
      dyad.yx() * symmetric_dyad.xz() + dyad.yy() * symmetric_dyad.yz()
          + dyad.yz() * symmetric_dyad.zz(),
      dyad.zx() * symmetric_dyad.xx() + dyad.zy() * symmetric_dyad.yx()
          + dyad.zz() * symmetric_dyad.zx(),
      dyad.zx() * symmetric_dyad.xy() + dyad.zy() * symmetric_dyad.yy()
          + dyad.zz() * symmetric_dyad.zy(),
      dyad.zx() * symmetric_dyad.xz() + dyad.zy() * symmetric_dyad.yz()
          + dyad.zz() * symmetric_dyad.zz()};
}

template <typename NumberType>
inline constexpr Dyad<NumberType> operator*(
    const Dyad<NumberType>& left, const Dyad<NumberType>& right) {
  return {left.xx() * right.xx() + left.xy() * right.yx() + left.xz() * right.zx(),
          left.xx() * right.xy() + left.xy() * right.yy() + left.xz() * right.zy(),
          left.xx() * right.xz() + left.xy() * right.yz() + left.xz() * right.zz(),
          left.yx() * right.xx() + left.yy() * right.yx() + left.yz() * right.zx(),
          left.yx() * right.xy() + left.yy() * right.yy() + left.yz() * right.zy(),
          left.yx() * right.xz() + left.yy() * right.yz() + left.yz() * right.zz(),
          left.zx() * right.xx() + left.zy() * right.yx() + left.zz() * right.zx(),
          left.zx() * right.xy() + left.zy() * right.yy() + left.zz() * right.zy(),
          left.zx() * right.xz() + left.zy() * right.yz() + left.zz() * right.zz()};
}

template <typename NumberType, typename OtherNumberType>
inline constexpr Dyad<NumberType> operator/(
    const Dyad<NumberType>& dyad, const OtherNumberType number) {
  return {dyad.xx() / number, dyad.xy() / number, dyad.xz() / number,
          dyad.yx() / number, dyad.yy() / number, dyad.yz() / number,
          dyad.zx() / number, dyad.zy() / number, dyad.zz() / number};
}

template <typename NumberType>
inline std::ostream& operator<<(std::ostream& stream, const Dyad<NumberType>& dyad) {
  stream << dyad.Print();
  return stream;
}

template <typename NumberType>
inline constexpr std::optional<Dyad<NumberType>> Dyad<NumberType>::Inverse() const {
  const NumberType determinant_{Determinant()};
  if (determinant_ != 0.0) {
    return std::optional<Dyad<NumberType>>{Adjugate() / determinant_};
  }
  return std::nullopt;
}

template <typename NumberType>
inline constexpr Dyad<NumberType> Vector<NumberType>::Dyadic(
    const Vector<NumberType>& vector) const {
  return {x_y_z_[0] * vector.x_y_z_[0], x_y_z_[0] * vector.x_y_z_[1], x_y_z_[0] * vector.x_y_z_[2],
          x_y_z_[1] * vector.x_y_z_[0], x_y_z_[1] * vector.x_y_z_[1], x_y_z_[1] * vector.x_y_z_[2],
          x_y_z_[2] * vector.x_y_z_[0], x_y_z_[2] * vector.x_y_z_[1], x_y_z_[2] * vector.x_y_z_[2]};
}

}  // namespace PhQ

namespace std {

template <typename NumberType>
struct hash<PhQ::Dyad<NumberType>> {
  inline size_t operator()(const PhQ::Dyad<NumberType>& dyad) const {
    size_t result{17};
    result = 31 * result + hash<NumberType>()(dyad.xx());
    result = 31 * result + hash<NumberType>()(dyad.xy());
    result = 31 * result + hash<NumberType>()(dyad.xz());
    result = 31 * result + hash<NumberType>()(dyad.yx());
    result = 31 * result + hash<NumberType>()(dyad.yy());
    result = 31 * result + hash<NumberType>()(dyad.yz());
    result = 31 * result + hash<NumberType>()(dyad.zx());
    result = 31 * result + hash<NumberType>()(dyad.zy());
    result = 31 * result + hash<NumberType>()(dyad.zz());
    return result;
  }
};

}  // namespace std

#endif  // PHQ_DYAD_HPP
