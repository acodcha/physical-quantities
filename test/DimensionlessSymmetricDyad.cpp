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

#include <functional>
#include <gtest/gtest.h>
#include <sstream>

#include "../include/PhQ/Dimensions.hpp"
#include "../include/PhQ/Strain.hpp"
#include "../include/PhQ/SymmetricDyad.hpp"

namespace PhQ {

namespace {

// Since PhQ::DimensionlessSymmetricDyad is an abstract base class, tests use PhQ::Strain, which is
// one of its derived classes.

TEST(DimensionlessSymmetricDyad, Dimensions) {
  EXPECT_EQ(Strain::Dimensions(), Dimensionless);
}

TEST(DimensionlessSymmetricDyad, Hash) {
  constexpr Strain first(1.0, -2.0, 3.0, -4.0, 5.0, -6.0);
  constexpr Strain second(1.0, -2.0, 3.0, -4.0, 5.0, -6.000001);
  constexpr Strain third(1.0, -2.0, 3.0, 4.0, 5.0, -6.0);
  const std::hash<Strain> hash;
  EXPECT_NE(hash(first), hash(second));
  EXPECT_NE(hash(first), hash(third));
  EXPECT_NE(hash(second), hash(third));
}

TEST(DimensionlessSymmetricDyad, JSON) {
  EXPECT_EQ(
      Strain(1.0, -2.0, 3.0, -4.0, 5.0, -6.0).JSON(),
      "{\"xx\":" + Print(1.0) + ",\"xy\":" + Print(-2.0) + ",\"xz\":" + Print(3.0)
          + ",\"yy\":" + Print(-4.0) + ",\"yz\":" + Print(5.0) + ",\"zz\":" + Print(-6.0) + "}");
}

TEST(DimensionlessSymmetricDyad, MutableValue) {
  Strain strain{1.0, -2.0, 3.0, -4.0, 5.0, -6.0};
  SymmetricDyad<>& value = strain.MutableValue();
  value = SymmetricDyad{-7.0, 8.0, -9.0, 10.0, -11.0, 12.0};
  EXPECT_EQ(strain.Value(), SymmetricDyad(-7.0, 8.0, -9.0, 10.0, -11.0, 12.0));
}

TEST(DimensionlessSymmetricDyad, Print) {
  EXPECT_EQ(Strain(1.0, -2.0, 3.0, -4.0, 5.0, -6.0).Print(),
            "(" + Print(1.0) + ", " + Print(-2.0) + ", " + Print(3.0) + "; " + Print(-4.0) + ", "
                + Print(5.0) + "; " + Print(-6.0) + ")");
}

TEST(DimensionlessSymmetricDyad, SetValue) {
  Strain strain{1.0, -2.0, 3.0, -4.0, 5.0, -6.0};
  strain.SetValue(SymmetricDyad{-7.0, 8.0, -9.0, 10.0, -11.0, 12.0});
  EXPECT_EQ(strain.Value(), SymmetricDyad(-7.0, 8.0, -9.0, 10.0, -11.0, 12.0));
}

TEST(DimensionlessSymmetricDyad, SizeOf) {
  EXPECT_EQ(sizeof(Strain{}), 6 * sizeof(double));
}

TEST(DimensionlessSymmetricDyad, Stream) {
  std::ostringstream stream;
  stream << Strain{1.0, -2.0, 3.0, -4.0, 5.0, -6.0};
  EXPECT_EQ(stream.str(), Strain(1.0, -2.0, 3.0, -4.0, 5.0, -6.0).Print());
}

TEST(DimensionlessSymmetricDyad, Value) {
  EXPECT_EQ(Strain(1.0, -2.0, 3.0, -4.0, 5.0, -6.0).Value(),
            SymmetricDyad(1.0, -2.0, 3.0, -4.0, 5.0, -6.0));
}

TEST(DimensionlessSymmetricDyad, XML) {
  EXPECT_EQ(Strain(1.0, -2.0, 3.0, -4.0, 5.0, -6.0).XML(),
            "<xx>" + Print(1.0) + "</xx><xy>" + Print(-2.0) + "</xy><xz>" + Print(3.0) + "</xz><yy>"
                + Print(-4.0) + "</yy><yz>" + Print(5.0) + "</yz><zz>" + Print(-6.0) + "</zz>");
}

TEST(DimensionlessSymmetricDyad, YAML) {
  EXPECT_EQ(Strain(1.0, -2.0, 3.0, -4.0, 5.0, -6.0).YAML(),
            "{xx:" + Print(1.0) + ",xy:" + Print(-2.0) + ",xz:" + Print(3.0) + ",yy:" + Print(-4.0)
                + ",yz:" + Print(5.0) + ",zz:" + Print(-6.0) + "}");
}

}  // namespace

}  // namespace PhQ