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

#include "../../include/PhQ/ConstitutiveModel/ElasticIsotropicSolid.hpp"

#include <functional>
#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <utility>

#include "../../include/PhQ/ConstitutiveModel.hpp"
#include "../../include/PhQ/IsentropicBulkModulus.hpp"
#include "../../include/PhQ/IsothermalBulkModulus.hpp"
#include "../../include/PhQ/LameFirstModulus.hpp"
#include "../../include/PhQ/PoissonRatio.hpp"
#include "../../include/PhQ/PWaveModulus.hpp"
#include "../../include/PhQ/ShearModulus.hpp"
#include "../../include/PhQ/Strain.hpp"
#include "../../include/PhQ/StrainRate.hpp"
#include "../../include/PhQ/Stress.hpp"
#include "../../include/PhQ/Unit/Frequency.hpp"
#include "../../include/PhQ/Unit/Pressure.hpp"
#include "../../include/PhQ/YoungModulus.hpp"

namespace PhQ {

namespace {

TEST(ConstitutiveModelElasticIsotropicSolid, ComparisonOperators) {
  const ConstitutiveModel<>::ElasticIsotropicSolid first{
      ShearModulus(4.0, Unit::Pressure::Pascal), LameFirstModulus(-2.0, Unit::Pressure::Pascal)};
  const ConstitutiveModel<>::ElasticIsotropicSolid second{
      ShearModulus(4.0, Unit::Pressure::Pascal), LameFirstModulus(-1.0, Unit::Pressure::Pascal)};
  EXPECT_EQ(first, first);
  EXPECT_NE(first, second);
  EXPECT_LT(first, second);
  EXPECT_GT(second, first);
  EXPECT_LE(first, first);
  EXPECT_LE(first, second);
  EXPECT_GE(first, first);
  EXPECT_GE(second, first);
}

TEST(ConstitutiveModelElasticIsotropicSolid, CopyAssignmentOperator) {
  const ConstitutiveModel<>::ElasticIsotropicSolid first{
      ShearModulus(4.0, Unit::Pressure::Pascal), LameFirstModulus(-2.0, Unit::Pressure::Pascal)};
  ConstitutiveModel<>::ElasticIsotropicSolid second{
      ShearModulus(16.0, Unit::Pressure::Pascal), LameFirstModulus(-8.0, Unit::Pressure::Pascal)};
  second = first;
  EXPECT_EQ(second, first);
}

TEST(ConstitutiveModelElasticIsotropicSolid, CopyConstructor) {
  const ConstitutiveModel<>::ElasticIsotropicSolid first{
      ShearModulus(4.0, Unit::Pressure::Pascal), LameFirstModulus(-2.0, Unit::Pressure::Pascal)};
  const ConstitutiveModel<>::ElasticIsotropicSolid second{first};
  EXPECT_EQ(second, first);
}

TEST(ConstitutiveModelElasticIsotropicSolid, DefaultConstructor) {
  EXPECT_NO_THROW(ConstitutiveModel<>::ElasticIsotropicSolid{});
}

TEST(ConstitutiveModelElasticIsotropicSolid, Hash) {
  const ConstitutiveModel<>::ElasticIsotropicSolid first{
      ShearModulus(4.0, Unit::Pressure::Pascal), LameFirstModulus(-2.0, Unit::Pressure::Pascal)};
  const ConstitutiveModel<>::ElasticIsotropicSolid second{
      ShearModulus{4.000001, Unit::Pressure::Pascal},
      LameFirstModulus{-2.0,     Unit::Pressure::Pascal}
  };
  const ConstitutiveModel<>::ElasticIsotropicSolid third{
      ShearModulus{4.0,       Unit::Pressure::Pascal},
      LameFirstModulus{-2.000001, Unit::Pressure::Pascal}
  };
  const std::hash<ConstitutiveModel<>::ElasticIsotropicSolid> hash;
  EXPECT_NE(hash(first), hash(second));
  EXPECT_NE(hash(first), hash(third));
  EXPECT_NE(hash(second), hash(third));
}

TEST(ConstitutiveModelElasticIsotropicSolid, JSON) {
  const std::unique_ptr<ConstitutiveModel<>> model =
      std::make_unique<ConstitutiveModel<>::ElasticIsotropicSolid>(
          ShearModulus(4.0, Unit::Pressure::Pascal),
          LameFirstModulus(-2.0, Unit::Pressure::Pascal));
  ASSERT_NE(model, nullptr);
  EXPECT_EQ(model->JSON(),
            "{\"type\":\"elastic_isotropic_solid\",\"shear_modulus\":"
                + ShearModulus(4.0, Unit::Pressure::Pascal).JSON() + ",\"lame_first_modulus\":"
                + LameFirstModulus(-2.0, Unit::Pressure::Pascal).JSON() + "}");
}

TEST(ConstitutiveModelElasticIsotropicSolid, MoveAssignmentOperator) {
  ConstitutiveModel<>::ElasticIsotropicSolid first{
      ShearModulus(4.0, Unit::Pressure::Pascal), LameFirstModulus(-2.0, Unit::Pressure::Pascal)};
  ConstitutiveModel<>::ElasticIsotropicSolid second{
      ShearModulus(16.0, Unit::Pressure::Pascal), LameFirstModulus(-8.0, Unit::Pressure::Pascal)};
  second = std::move(first);
  EXPECT_EQ(second, ConstitutiveModel<>::ElasticIsotropicSolid(
                        ShearModulus(4.0, Unit::Pressure::Pascal),
                        LameFirstModulus(-2.0, Unit::Pressure::Pascal)));
}

TEST(ConstitutiveModelElasticIsotropicSolid, MoveConstructor) {
  ConstitutiveModel<>::ElasticIsotropicSolid first{
      ShearModulus(4.0, Unit::Pressure::Pascal), LameFirstModulus(-2.0, Unit::Pressure::Pascal)};
  const ConstitutiveModel<>::ElasticIsotropicSolid second{std::move(first)};
  EXPECT_EQ(second, ConstitutiveModel<>::ElasticIsotropicSolid(
                        ShearModulus(4.0, Unit::Pressure::Pascal),
                        LameFirstModulus(-2.0, Unit::Pressure::Pascal)));
}

TEST(ConstitutiveModelElasticIsotropicSolid, Print) {
  const std::unique_ptr<ConstitutiveModel<>> model =
      std::make_unique<ConstitutiveModel<>::ElasticIsotropicSolid>(
          ShearModulus(4.0, Unit::Pressure::Pascal),
          LameFirstModulus(-2.0, Unit::Pressure::Pascal));
  ASSERT_NE(model, nullptr);
  EXPECT_EQ(model->Print(),
            "Type = Elastic Isotropic Solid, Shear Modulus = "
                + ShearModulus(4.0, Unit::Pressure::Pascal).Print() + ", Lamé's First Modulus = "
                + LameFirstModulus(-2.0, Unit::Pressure::Pascal).Print());
}

TEST(ConstitutiveModelElasticIsotropicSolid, StandardConstructors) {
  const YoungModulus young_modulus{4.0, Unit::Pressure::Pascal};
  const ShearModulus shear_modulus{4.0, Unit::Pressure::Pascal};
  const IsentropicBulkModulus isentropic_bulk_modulus{4.0, Unit::Pressure::Pascal};
  const IsothermalBulkModulus isothermal_bulk_modulus{4.0, Unit::Pressure::Pascal};
  const LameFirstModulus lame_first_modulus{-2.0, Unit::Pressure::Pascal};
  const PWaveModulus p_wave_modulus{4.0, Unit::Pressure::Pascal};
  const PoissonRatio poisson_ratio{0.25};

  const ConstitutiveModel<>::ElasticIsotropicSolid model01{young_modulus, shear_modulus};
  EXPECT_EQ(model01.YoungModulus(), young_modulus);
  EXPECT_EQ(model01.ShearModulus(), shear_modulus);

  const ConstitutiveModel<>::ElasticIsotropicSolid model02{young_modulus, isentropic_bulk_modulus};
  EXPECT_EQ(model02.YoungModulus(), young_modulus);
  EXPECT_EQ(model02.IsentropicBulkModulus(), isentropic_bulk_modulus);

  const ConstitutiveModel<>::ElasticIsotropicSolid model03{young_modulus, lame_first_modulus};
  EXPECT_EQ(model03.YoungModulus(), young_modulus);
  EXPECT_EQ(model03.LameFirstModulus(), lame_first_modulus);

  const ConstitutiveModel<>::ElasticIsotropicSolid model04{young_modulus, p_wave_modulus};
  EXPECT_EQ(model04.YoungModulus(), young_modulus);
  EXPECT_EQ(model04.PWaveModulus(), p_wave_modulus);

  const ConstitutiveModel<>::ElasticIsotropicSolid model05{young_modulus, poisson_ratio};
  EXPECT_EQ(model05.YoungModulus(), young_modulus);
  EXPECT_EQ(model05.PoissonRatio(), poisson_ratio);

  const ConstitutiveModel<>::ElasticIsotropicSolid model06{shear_modulus, isentropic_bulk_modulus};
  EXPECT_EQ(model06.ShearModulus(), shear_modulus);
  EXPECT_EQ(model06.IsentropicBulkModulus(), isentropic_bulk_modulus);

  const ConstitutiveModel<>::ElasticIsotropicSolid model07{shear_modulus, lame_first_modulus};
  EXPECT_EQ(model07.ShearModulus(), shear_modulus);
  EXPECT_EQ(model07.LameFirstModulus(), lame_first_modulus);

  const ConstitutiveModel<>::ElasticIsotropicSolid model08{shear_modulus, p_wave_modulus};
  EXPECT_EQ(model08.ShearModulus(), shear_modulus);
  EXPECT_EQ(model08.PWaveModulus(), p_wave_modulus);

  const ConstitutiveModel<>::ElasticIsotropicSolid model09{shear_modulus, poisson_ratio};
  EXPECT_EQ(model09.ShearModulus(), shear_modulus);
  EXPECT_EQ(model09.PoissonRatio(), poisson_ratio);

  const ConstitutiveModel<>::ElasticIsotropicSolid model10{
      isentropic_bulk_modulus, lame_first_modulus};
  EXPECT_EQ(model10.IsentropicBulkModulus(), isentropic_bulk_modulus);
  EXPECT_EQ(model10.LameFirstModulus(), lame_first_modulus);

  const ConstitutiveModel<>::ElasticIsotropicSolid model11{isentropic_bulk_modulus, p_wave_modulus};
  EXPECT_EQ(model11.IsentropicBulkModulus(), isentropic_bulk_modulus);
  EXPECT_EQ(model11.PWaveModulus(), p_wave_modulus);

  const ConstitutiveModel<>::ElasticIsotropicSolid model12{isentropic_bulk_modulus, poisson_ratio};
  EXPECT_EQ(model12.IsentropicBulkModulus(), isentropic_bulk_modulus);
  EXPECT_DOUBLE_EQ(model12.PoissonRatio().Value(), poisson_ratio.Value());

  const ConstitutiveModel<>::ElasticIsotropicSolid model13{lame_first_modulus, p_wave_modulus};
  EXPECT_EQ(model13.LameFirstModulus(), lame_first_modulus);
  EXPECT_EQ(model13.PWaveModulus(), p_wave_modulus);

  const ConstitutiveModel<>::ElasticIsotropicSolid model14{lame_first_modulus, poisson_ratio};
  EXPECT_EQ(model14.LameFirstModulus(), lame_first_modulus);
  EXPECT_EQ(model14.PoissonRatio(), poisson_ratio);

  const ConstitutiveModel<>::ElasticIsotropicSolid model15{p_wave_modulus, poisson_ratio};
  EXPECT_EQ(model15.PWaveModulus(), p_wave_modulus);
  EXPECT_EQ(model15.PoissonRatio(), poisson_ratio);
}

TEST(ConstitutiveModelElasticIsotropicSolid, Stream) {
  const ConstitutiveModel<>::ElasticIsotropicSolid first_model{
      ShearModulus(4.0, Unit::Pressure::Pascal), LameFirstModulus(-2.0, Unit::Pressure::Pascal)};
  std::ostringstream first_stream;
  first_stream << first_model;
  EXPECT_EQ(first_stream.str(), first_model.Print());

  const std::unique_ptr<ConstitutiveModel<>> second_model =
      std::make_unique<ConstitutiveModel<>::ElasticIsotropicSolid>(
          ShearModulus(4.0, Unit::Pressure::Pascal),
          LameFirstModulus(-2.0, Unit::Pressure::Pascal));
  ASSERT_NE(second_model, nullptr);
  std::ostringstream second_stream;
  second_stream << *second_model;
  EXPECT_EQ(second_stream.str(), second_model->Print());
}

TEST(ConstitutiveModelElasticIsotropicSolid, StressAndStrain) {
  const std::unique_ptr<ConstitutiveModel<>> model =
      std::make_unique<ConstitutiveModel<>::ElasticIsotropicSolid>(
          ShearModulus(4.0, Unit::Pressure::Pascal),
          LameFirstModulus(-2.0, Unit::Pressure::Pascal));
  ASSERT_NE(model, nullptr);
  const Strain strain{32.0, -4.0, -2.0, 16.0, -1.0, 8.0};
  const StrainRate strain_rate{
      {32.0, -4.0, -2.0, 16.0, -1.0, 8.0},
      Unit::Frequency::Hertz
  };
  const Stress stress = model->Stress(strain);
  EXPECT_EQ(model->Strain(stress), strain);
  EXPECT_EQ(model->Strain(Stress<>::Zero()), Strain<>::Zero());
  EXPECT_EQ(model->StrainRate(stress), StrainRate<>::Zero());
  EXPECT_EQ(model->Stress(strain), stress);
  EXPECT_EQ(model->Stress(strain_rate), Stress<>::Zero());
  EXPECT_EQ(model->Stress(strain, strain_rate), stress);
}

TEST(ConstitutiveModelElasticIsotropicSolid, Type) {
  const std::unique_ptr<ConstitutiveModel<>> model =
      std::make_unique<ConstitutiveModel<>::ElasticIsotropicSolid>(
          ShearModulus{4.0, Unit::Pressure::Pascal},
          LameFirstModulus(-2.0, Unit::Pressure::Pascal));
  ASSERT_NE(model, nullptr);
  EXPECT_EQ(model->Type(), ConstitutiveModelType::ElasticIsotropicSolid);
}

TEST(ConstitutiveModelElasticIsotropicSolid, XML) {
  const std::unique_ptr<ConstitutiveModel<>> model =
      std::make_unique<ConstitutiveModel<>::ElasticIsotropicSolid>(
          ShearModulus(4.0, Unit::Pressure::Pascal),
          LameFirstModulus(-2.0, Unit::Pressure::Pascal));
  ASSERT_NE(model, nullptr);
  EXPECT_EQ(
      model->XML(),
      "<type>elastic_isotropic_solid</type><shear_modulus>"
          + ShearModulus(4.0, Unit::Pressure::Pascal).XML() + "</shear_modulus><lame_first_modulus>"
          + LameFirstModulus(-2.0, Unit::Pressure::Pascal).XML() + "</lame_first_modulus>");
}

TEST(ConstitutiveModelElasticIsotropicSolid, YAML) {
  const std::unique_ptr<ConstitutiveModel<>> model =
      std::make_unique<ConstitutiveModel<>::ElasticIsotropicSolid>(
          ShearModulus(4.0, Unit::Pressure::Pascal),
          LameFirstModulus(-2.0, Unit::Pressure::Pascal));
  ASSERT_NE(model, nullptr);
  EXPECT_EQ(model->YAML(),
            "{type:\"elastic_isotropic_solid\",shear_modulus:"
                + ShearModulus(4.0, Unit::Pressure::Pascal).YAML() + ",lame_first_modulus:"
                + LameFirstModulus(-2.0, Unit::Pressure::Pascal).YAML() + "}");
}

}  // namespace

}  // namespace PhQ
