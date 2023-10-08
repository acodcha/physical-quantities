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

#include "../include/PhQ/HeatFlux.hpp"

#include <gtest/gtest.h>

namespace PhQ {

namespace {

TEST(HeatFlux, Angle) {
  EXPECT_EQ(HeatFlux({0.0, -2.22, 0.0}, Unit::EnergyFlux::WattPerSquareMetre)
                .Angle(HeatFlux(
                    {0.0, 0.0, 3.33}, Unit::EnergyFlux::WattPerSquareMetre)),
            Angle(90.0, Unit::Angle::Degree));
}

TEST(HeatFlux, ArithmeticAddition) {
  EXPECT_EQ(
      HeatFlux({1.0, -2.0, 3.0}, Unit::EnergyFlux::WattPerSquareMetre)
          + HeatFlux({2.0, -4.0, 6.0}, Unit::EnergyFlux::WattPerSquareMetre),
      HeatFlux({3.0, -6.0, 9.0}, Unit::EnergyFlux::WattPerSquareMetre));

  HeatFlux quantity({1.0, -2.0, 3.0}, Unit::EnergyFlux::WattPerSquareMetre);
  quantity += HeatFlux({2.0, -4.0, 6.0}, Unit::EnergyFlux::WattPerSquareMetre);
  EXPECT_EQ(quantity,
            HeatFlux({3.0, -6.0, 9.0}, Unit::EnergyFlux::WattPerSquareMetre));
}

TEST(HeatFlux, ArithmeticDivision) {
  EXPECT_EQ(
      HeatFlux({2.0, -4.0, 6.0}, Unit::EnergyFlux::WattPerSquareMetre) / 2.0,
      HeatFlux({1.0, -2.0, 3.0}, Unit::EnergyFlux::WattPerSquareMetre));

  HeatFlux quantity({2.0, -4.0, 6.0}, Unit::EnergyFlux::WattPerSquareMetre);
  quantity /= 2.0;
  EXPECT_EQ(quantity,
            HeatFlux({1.0, -2.0, 3.0}, Unit::EnergyFlux::WattPerSquareMetre));
}

TEST(HeatFlux, ArithmeticMultiplication) {
  EXPECT_EQ(
      HeatFlux({1.0, -2.0, 3.0}, Unit::EnergyFlux::WattPerSquareMetre) * 2.0,
      HeatFlux({2.0, -4.0, 6.0}, Unit::EnergyFlux::WattPerSquareMetre));

  EXPECT_EQ(
      2.0 * HeatFlux({1.0, -2.0, 3.0}, Unit::EnergyFlux::WattPerSquareMetre),
      HeatFlux({2.0, -4.0, 6.0}, Unit::EnergyFlux::WattPerSquareMetre));

  EXPECT_EQ(Direction(2.0, -3.0, 6.0)
                * HeatFluxMagnitude(7.0, Unit::EnergyFlux::WattPerSquareMetre),
            HeatFlux({2.0, -3.0, 6.0}, Unit::EnergyFlux::WattPerSquareMetre));

  EXPECT_EQ(HeatFluxMagnitude(7.0, Unit::EnergyFlux::WattPerSquareMetre)
                * Direction(2.0, -3.0, 6.0),
            HeatFlux({2.0, -3.0, 6.0}, Unit::EnergyFlux::WattPerSquareMetre));

  HeatFlux quantity({1.0, -2.0, 3.0}, Unit::EnergyFlux::WattPerSquareMetre);
  quantity *= 2.0;
  EXPECT_EQ(quantity,
            HeatFlux({2.0, -4.0, 6.0}, Unit::EnergyFlux::WattPerSquareMetre));
}

TEST(HeatFlux, ArithmeticSubtraction) {
  EXPECT_EQ(
      HeatFlux({3.0, -6.0, 9.0}, Unit::EnergyFlux::WattPerSquareMetre)
          - HeatFlux({2.0, -4.0, 6.0}, Unit::EnergyFlux::WattPerSquareMetre),
      HeatFlux({1.0, -2.0, 3.0}, Unit::EnergyFlux::WattPerSquareMetre));

  HeatFlux quantity({3.0, -6.0, 9.0}, Unit::EnergyFlux::WattPerSquareMetre);
  quantity -= HeatFlux({2.0, -4.0, 6.0}, Unit::EnergyFlux::WattPerSquareMetre);
  EXPECT_EQ(quantity,
            HeatFlux({1.0, -2.0, 3.0}, Unit::EnergyFlux::WattPerSquareMetre));
}

TEST(HeatFlux, Comparisons) {
  const HeatFlux first(
      {1.11, -2.22, 3.33}, Unit::EnergyFlux::WattPerSquareMetre);
  const HeatFlux second(
      {1.11, -2.22, 3.330001}, Unit::EnergyFlux::WattPerSquareMetre);
  EXPECT_EQ(first, first);
  EXPECT_NE(first, second);
  EXPECT_LT(first, second);
  EXPECT_GT(second, first);
  EXPECT_LE(first, first);
  EXPECT_LE(first, second);
  EXPECT_GE(first, first);
  EXPECT_GE(second, first);
}

TEST(HeatFlux, CopyAssignment) {
  const HeatFlux first(
      {1.11, -2.22, 3.33}, Unit::EnergyFlux::WattPerSquareMetre);
  HeatFlux second = HeatFlux::Zero();
  second = first;
  EXPECT_EQ(second, first);
}

TEST(HeatFlux, CopyConstructor) {
  const HeatFlux first(
      {1.11, -2.22, 3.33}, Unit::EnergyFlux::WattPerSquareMetre);
  const HeatFlux second{first};
  EXPECT_EQ(second, first);
}

TEST(HeatFlux, Create) {
  constexpr HeatFlux quantity =
      HeatFlux::Create<Unit::EnergyFlux::WattPerSquareMetre>(
          {1.11, -2.22, 3.33});
  EXPECT_EQ(quantity, HeatFlux({1.11, -2.22, 3.33},
                               Unit::EnergyFlux::WattPerSquareMetre));
}

TEST(HeatFlux, DefaultConstructor) {
  EXPECT_NO_THROW(HeatFlux{});
}

TEST(HeatFlux, Dimensions) {
  EXPECT_EQ(HeatFlux::Dimensions(), RelatedDimensions<Unit::EnergyFlux>);
}

TEST(HeatFlux, Hash) {
  const HeatFlux first(
      {1.11, -2.22, 3.33}, Unit::EnergyFlux::NanowattPerSquareMillimetre);
  const HeatFlux second(
      {1.11, -2.22, 3.330001}, Unit::EnergyFlux::NanowattPerSquareMillimetre);
  const HeatFlux third(
      {1.11, 2.22, 3.33}, Unit::EnergyFlux::NanowattPerSquareMillimetre);
  const std::hash<HeatFlux> hash;
  EXPECT_NE(hash(first), hash(second));
  EXPECT_NE(hash(first), hash(third));
  EXPECT_NE(hash(second), hash(third));
}

TEST(HeatFlux, JSON) {
  EXPECT_EQ(HeatFlux({1.11, -2.22, 3.33}, Unit::EnergyFlux::WattPerSquareMetre)
                .JSON(),
            "{\"value\":{\"x\":1.110000000000000,\"y\":-2.220000000000000,"
            "\"z\":"
            "3.330000000000000},\"unit\":\"W/m^2\"}");
  EXPECT_EQ(
      HeatFlux({0.0, -2.22, 0.0}, Unit::EnergyFlux::NanowattPerSquareMillimetre)
          .JSON(Unit::EnergyFlux::NanowattPerSquareMillimetre),
      "{\"value\":{\"x\":0,\"y\":-2.220000000000000,\"z\":0},\"unit\":\"nW/"
      "mm^2\"}");
}

TEST(HeatFlux, Magnitude) {
  EXPECT_EQ(HeatFlux({2.0, -3.0, 6.0}, Unit::EnergyFlux::WattPerSquareMetre)
                .Magnitude(),
            HeatFluxMagnitude(7.0, Unit::EnergyFlux::WattPerSquareMetre));
}

TEST(HeatFlux, MiscellaneousConstructors) {
  EXPECT_EQ(Direction(HeatFlux(
                {1.11, -2.22, 3.33}, Unit::EnergyFlux::WattPerSquareMetre)),
            Direction(1.11, -2.22, 3.33));

  EXPECT_EQ(
      Angle(HeatFlux({0.0, -2.22, 0.0}, Unit::EnergyFlux::WattPerSquareMetre),
            HeatFlux({0.0, 0.0, 3.33}, Unit::EnergyFlux::WattPerSquareMetre)),
      Angle(90.0, Unit::Angle::Degree));

  EXPECT_EQ(HeatFluxMagnitude(HeatFlux(
                {2.0, -3.0, 6.0}, Unit::EnergyFlux::WattPerSquareMetre)),
            HeatFluxMagnitude(7.0, Unit::EnergyFlux::WattPerSquareMetre));

  EXPECT_EQ(
      HeatFlux(ThermalConductivityScalar(
                   2.0, Unit::ThermalConductivity::WattPerMetrePerKelvin),
               TemperatureGradient({1.0, -2.0, 3.0},
                                   Unit::TemperatureGradient::KelvinPerMetre)),
      HeatFlux({-2.0, 4.0, -6.0}, Unit::EnergyFlux::WattPerSquareMetre));

  EXPECT_EQ(
      HeatFlux(
          ThermalConductivity({1.0, -2.0, 3.0, -4.0, 5.0, -6.0},
                              Unit::ThermalConductivity::WattPerMetrePerKelvin),
          TemperatureGradient(
              {1.0, -2.0, 3.0}, Unit::TemperatureGradient::KelvinPerMetre)),
      HeatFlux({-14.0, -21.0, 25.0}, Unit::EnergyFlux::WattPerSquareMetre));
}

TEST(HeatFlux, MoveAssignment) {
  const HeatFlux first(
      {1.11, -2.22, 3.33}, Unit::EnergyFlux::WattPerSquareMetre);
  HeatFlux second({1.11, -2.22, 3.33}, Unit::EnergyFlux::WattPerSquareMetre);
  HeatFlux third = HeatFlux::Zero();
  third = std::move(second);
  EXPECT_EQ(third, first);
}

TEST(HeatFlux, MoveConstructor) {
  const HeatFlux first(
      {1.11, -2.22, 3.33}, Unit::EnergyFlux::WattPerSquareMetre);
  HeatFlux second({1.11, -2.22, 3.33}, Unit::EnergyFlux::WattPerSquareMetre);
  HeatFlux third{std::move(second)};
  EXPECT_EQ(third, first);
}

TEST(HeatFlux, MutableValue) {
  HeatFlux quantity({1.11, -2.22, 3.33}, Unit::EnergyFlux::WattPerSquareMetre);
  Value::Vector& value = quantity.MutableValue();
  value = Value::Vector{-4.44, 5.55, -6.66};
  EXPECT_EQ(quantity.Value(), Value::Vector(-4.44, 5.55, -6.66));
}

TEST(HeatFlux, Print) {
  EXPECT_EQ(HeatFlux({1.11, -2.22, 3.33}, Unit::EnergyFlux::WattPerSquareMetre)
                .Print(),
            "(1.110000000000000, -2.220000000000000, 3.330000000000000) W/m^2");
  EXPECT_EQ(
      HeatFlux({0.0, -2.22, 0.0}, Unit::EnergyFlux::NanowattPerSquareMillimetre)
          .Print(Unit::EnergyFlux::NanowattPerSquareMillimetre),
      "(0, -2.220000000000000, 0) nW/mm^2");
}

TEST(HeatFlux, SetValue) {
  HeatFlux quantity({1.11, -2.22, 3.33}, Unit::EnergyFlux::WattPerSquareMetre);
  quantity.SetValue({-4.44, 5.55, -6.66});
  EXPECT_EQ(quantity.Value(), Value::Vector(-4.44, 5.55, -6.66));
}

TEST(HeatFlux, SizeOf) {
  EXPECT_EQ(sizeof(HeatFlux{}), 3 * sizeof(double));
}

TEST(HeatFlux, StandardConstructor) {
  EXPECT_NO_THROW(HeatFlux(
      {1.11, -2.22, 3.33}, Unit::EnergyFlux::NanowattPerSquareMillimetre));
}

TEST(HeatFlux, StaticValue) {
  constexpr HeatFlux quantity =
      HeatFlux::Create<Unit::EnergyFlux::NanowattPerSquareMillimetre>(
          {1.11, -2.22, 3.33});
  constexpr Value::Vector value =
      quantity.StaticValue<Unit::EnergyFlux::NanowattPerSquareMillimetre>();
  EXPECT_EQ(value, Value::Vector(1.11, -2.22, 3.33));
}

TEST(HeatFlux, Stream) {
  std::ostringstream stream;
  stream << HeatFlux({1.11, -2.22, 3.33}, Unit::EnergyFlux::WattPerSquareMetre);
  EXPECT_EQ(stream.str(),
            HeatFlux({1.11, -2.22, 3.33}, Unit::EnergyFlux::WattPerSquareMetre)
                .Print());
}

TEST(HeatFlux, Unit) {
  EXPECT_EQ(HeatFlux::Unit(), Standard<Unit::EnergyFlux>);
}

TEST(HeatFlux, Value) {
  EXPECT_EQ(HeatFlux({1.11, -2.22, 3.33}, Unit::EnergyFlux::WattPerSquareMetre)
                .Value(),
            Value::Vector(1.11, -2.22, 3.33));
  EXPECT_EQ(HeatFlux({1.11, -2.22, 3.33},
                     Unit::EnergyFlux::NanowattPerSquareMillimetre)
                .Value(Unit::EnergyFlux::NanowattPerSquareMillimetre),
            Value::Vector(1.11, -2.22, 3.33));
}

TEST(HeatFlux, XML) {
  EXPECT_EQ(
      HeatFlux({1.11, -2.22, 3.33}, Unit::EnergyFlux::WattPerSquareMetre).XML(),
      "<value><x>1.110000000000000</x><y>-2.220000000000000</"
      "y><z>3.330000000000000</z></value><unit>W/m^2</unit>");
  EXPECT_EQ(
      HeatFlux({0.0, -2.22, 0.0}, Unit::EnergyFlux::NanowattPerSquareMillimetre)
          .XML(Unit::EnergyFlux::NanowattPerSquareMillimetre),
      "<value><x>0</x><y>-2.220000000000000</y><z>0</z></value><unit>nW/mm^2</"
      "unit>");
}

TEST(HeatFlux, YAML) {
  EXPECT_EQ(HeatFlux({1.11, -2.22, 3.33}, Unit::EnergyFlux::WattPerSquareMetre)
                .YAML(),
            "{value:{x:1.110000000000000,y:-2.220000000000000,z:3."
            "330000000000000},unit:\"W/m^2\"}");
  EXPECT_EQ(
      HeatFlux({0.0, -2.22, 0.0}, Unit::EnergyFlux::NanowattPerSquareMillimetre)
          .YAML(Unit::EnergyFlux::NanowattPerSquareMillimetre),
      "{value:{x:0,y:-2.220000000000000,z:0},unit:\"nW/mm^2\"}");
}

TEST(HeatFlux, Zero) {
  EXPECT_EQ(HeatFlux::Zero(),
            HeatFlux({0.0, 0.0, 0.0}, Unit::EnergyFlux::WattPerSquareMetre));
}

}  // namespace

}  // namespace PhQ
