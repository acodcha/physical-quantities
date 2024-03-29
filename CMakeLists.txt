cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Define the global settings.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math -O3 -Wall -Wextra -Wno-return-type -Wpedantic")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Release)

# Define the PhQ project and its options.
project(
  "PhQ"
  VERSION 1.0.0
  LANGUAGES CXX
  DESCRIPTION "C++ library of physical quantities, physical models, and units of measure for scientific computation."
  HOMEPAGE_URL "https://github.com/acodcha/physical-quantities"
)
option(
  TEST_PHQ_LIBRARY
  "Configure the Physical Quantities (PhQ) library tests."
  OFF
)

# Define the PhQ library.
add_library(
  ${PROJECT_NAME}
  INTERFACE
)
target_include_directories(
  ${PROJECT_NAME}
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Configure the PhQ library tests.
if(TEST_PHQ_LIBRARY)
  # Search for the GoogleTest library.
  find_package(GTest QUIET)

  if(GTest_FOUND)
    message(STATUS "The GoogleTest library was found at: ${GTest_CONFIG}")
  else()
    # In this case, the GoogleTest library is not found, so fetch it instead.
    include(FetchContent)
    FetchContent_Declare(
      GoogleTest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG main
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(GoogleTest)
    message(STATUS "The GoogleTest library was fetched from: https://github.com/google/googletest.git")
  endif()

  # Include the GoogleTest library and enable testing.
  include(GoogleTest)
  enable_testing()

  # Define the test executables.

  add_executable(acceleration ${PROJECT_SOURCE_DIR}/test/Acceleration.cpp)
  target_link_libraries(acceleration GTest::gtest_main)
  gtest_discover_tests(acceleration)

  add_executable(angle ${PROJECT_SOURCE_DIR}/test/Angle.cpp)
  target_link_libraries(angle GTest::gtest_main)
  gtest_discover_tests(angle)

  add_executable(angular_speed ${PROJECT_SOURCE_DIR}/test/AngularSpeed.cpp)
  target_link_libraries(angular_speed GTest::gtest_main)
  gtest_discover_tests(angular_speed)

  add_executable(area ${PROJECT_SOURCE_DIR}/test/Area.cpp)
  target_link_libraries(area GTest::gtest_main)
  gtest_discover_tests(area)

  add_executable(base ${PROJECT_SOURCE_DIR}/test/Base.cpp)
  target_link_libraries(base GTest::gtest_main)
  gtest_discover_tests(base)

  add_executable(bulk_dynamic_viscosity ${PROJECT_SOURCE_DIR}/test/BulkDynamicViscosity.cpp)
  target_link_libraries(bulk_dynamic_viscosity GTest::gtest_main)
  gtest_discover_tests(bulk_dynamic_viscosity)

  add_executable(constitutive_model__compressible_newtonian_fluid ${PROJECT_SOURCE_DIR}/test/ConstitutiveModel/CompressibleNewtonianFluid.cpp)
  target_link_libraries(constitutive_model__compressible_newtonian_fluid GTest::gtest_main)
  gtest_discover_tests(constitutive_model__compressible_newtonian_fluid)

  add_executable(constitutive_model__elastic_isotropic_solid ${PROJECT_SOURCE_DIR}/test/ConstitutiveModel/ElasticIsotropicSolid.cpp)
  target_link_libraries(constitutive_model__elastic_isotropic_solid GTest::gtest_main)
  gtest_discover_tests(constitutive_model__elastic_isotropic_solid)

  add_executable(constitutive_model__incompressible_newtonian_fluid ${PROJECT_SOURCE_DIR}/test/ConstitutiveModel/IncompressibleNewtonianFluid.cpp)
  target_link_libraries(constitutive_model__incompressible_newtonian_fluid GTest::gtest_main)
  gtest_discover_tests(constitutive_model__incompressible_newtonian_fluid)

  add_executable(dimension__electric_current ${PROJECT_SOURCE_DIR}/test/Dimension/ElectricCurrent.cpp)
  target_link_libraries(dimension__electric_current GTest::gtest_main)
  gtest_discover_tests(dimension__electric_current)

  add_executable(dimension__length ${PROJECT_SOURCE_DIR}/test/Dimension/Length.cpp)
  target_link_libraries(dimension__length GTest::gtest_main)
  gtest_discover_tests(dimension__length)

  add_executable(dimension__luminous_intensity ${PROJECT_SOURCE_DIR}/test/Dimension/LuminousIntensity.cpp)
  target_link_libraries(dimension__luminous_intensity GTest::gtest_main)
  gtest_discover_tests(dimension__luminous_intensity)

  add_executable(dimension__mass ${PROJECT_SOURCE_DIR}/test/Dimension/Mass.cpp)
  target_link_libraries(dimension__mass GTest::gtest_main)
  gtest_discover_tests(dimension__mass)

  add_executable(dimension__substance_amount ${PROJECT_SOURCE_DIR}/test/Dimension/SubstanceAmount.cpp)
  target_link_libraries(dimension__substance_amount GTest::gtest_main)
  gtest_discover_tests(dimension__substance_amount)

  add_executable(dimension__temperature ${PROJECT_SOURCE_DIR}/test/Dimension/Temperature.cpp)
  target_link_libraries(dimension__temperature GTest::gtest_main)
  gtest_discover_tests(dimension__temperature)

  add_executable(dimension__time ${PROJECT_SOURCE_DIR}/test/Dimension/Time.cpp)
  target_link_libraries(dimension__time GTest::gtest_main)
  gtest_discover_tests(dimension__time)

  add_executable(dimensions ${PROJECT_SOURCE_DIR}/test/Dimensions.cpp)
  target_link_libraries(dimensions GTest::gtest_main)
  gtest_discover_tests(dimensions)

  add_executable(direction ${PROJECT_SOURCE_DIR}/test/Direction.cpp)
  target_link_libraries(direction GTest::gtest_main)
  gtest_discover_tests(direction)

  add_executable(displacement ${PROJECT_SOURCE_DIR}/test/Displacement.cpp)
  target_link_libraries(displacement GTest::gtest_main)
  gtest_discover_tests(displacement)

  add_executable(displacement_gradient ${PROJECT_SOURCE_DIR}/test/DisplacementGradient.cpp)
  target_link_libraries(displacement_gradient GTest::gtest_main)
  gtest_discover_tests(displacement_gradient)

  add_executable(dyad ${PROJECT_SOURCE_DIR}/test/Dyad.cpp)
  target_link_libraries(dyad GTest::gtest_main)
  gtest_discover_tests(dyad)

  add_executable(dynamic_kinematic_pressure ${PROJECT_SOURCE_DIR}/test/DynamicKinematicPressure.cpp)
  target_link_libraries(dynamic_kinematic_pressure GTest::gtest_main)
  gtest_discover_tests(dynamic_kinematic_pressure)

  add_executable(dynamic_pressure ${PROJECT_SOURCE_DIR}/test/DynamicPressure.cpp)
  target_link_libraries(dynamic_pressure GTest::gtest_main)
  gtest_discover_tests(dynamic_pressure)

  add_executable(dynamic_viscosity ${PROJECT_SOURCE_DIR}/test/DynamicViscosity.cpp)
  target_link_libraries(dynamic_viscosity GTest::gtest_main)
  gtest_discover_tests(dynamic_viscosity)

  add_executable(energy ${PROJECT_SOURCE_DIR}/test/Energy.cpp)
  target_link_libraries(energy GTest::gtest_main)
  gtest_discover_tests(energy)

  add_executable(force ${PROJECT_SOURCE_DIR}/test/Force.cpp)
  target_link_libraries(force GTest::gtest_main)
  gtest_discover_tests(force)

  add_executable(frequency ${PROJECT_SOURCE_DIR}/test/Frequency.cpp)
  target_link_libraries(frequency GTest::gtest_main)
  gtest_discover_tests(frequency)

  add_executable(gas_constant ${PROJECT_SOURCE_DIR}/test/GasConstant.cpp)
  target_link_libraries(gas_constant GTest::gtest_main)
  gtest_discover_tests(gas_constant)

  add_executable(heat_capacity_ratio ${PROJECT_SOURCE_DIR}/test/HeatCapacityRatio.cpp)
  target_link_libraries(heat_capacity_ratio GTest::gtest_main)
  gtest_discover_tests(heat_capacity_ratio)

  add_executable(heat_flux ${PROJECT_SOURCE_DIR}/test/HeatFlux.cpp)
  target_link_libraries(heat_flux GTest::gtest_main)
  gtest_discover_tests(heat_flux)

  add_executable(isentropic_bulk_modulus ${PROJECT_SOURCE_DIR}/test/IsentropicBulkModulus.cpp)
  target_link_libraries(isentropic_bulk_modulus GTest::gtest_main)
  gtest_discover_tests(isentropic_bulk_modulus)

  add_executable(isobaric_heat_capacity ${PROJECT_SOURCE_DIR}/test/IsobaricHeatCapacity.cpp)
  target_link_libraries(isobaric_heat_capacity GTest::gtest_main)
  gtest_discover_tests(isobaric_heat_capacity)

  add_executable(isochoric_heat_capacity ${PROJECT_SOURCE_DIR}/test/IsochoricHeatCapacity.cpp)
  target_link_libraries(isochoric_heat_capacity GTest::gtest_main)
  gtest_discover_tests(isochoric_heat_capacity)

  add_executable(isothermal_bulk_modulus ${PROJECT_SOURCE_DIR}/test/IsothermalBulkModulus.cpp)
  target_link_libraries(isothermal_bulk_modulus GTest::gtest_main)
  gtest_discover_tests(isothermal_bulk_modulus)

  add_executable(kinematic_viscosity ${PROJECT_SOURCE_DIR}/test/KinematicViscosity.cpp)
  target_link_libraries(kinematic_viscosity GTest::gtest_main)
  gtest_discover_tests(kinematic_viscosity)

  add_executable(lame_first_modulus ${PROJECT_SOURCE_DIR}/test/LameFirstModulus.cpp)
  target_link_libraries(lame_first_modulus GTest::gtest_main)
  gtest_discover_tests(lame_first_modulus)

  add_executable(length ${PROJECT_SOURCE_DIR}/test/Length.cpp)
  target_link_libraries(length GTest::gtest_main)
  gtest_discover_tests(length)

  add_executable(linear_thermal_expansion_coefficient ${PROJECT_SOURCE_DIR}/test/LinearThermalExpansionCoefficient.cpp)
  target_link_libraries(linear_thermal_expansion_coefficient GTest::gtest_main)
  gtest_discover_tests(linear_thermal_expansion_coefficient)

  add_executable(mach_number ${PROJECT_SOURCE_DIR}/test/MachNumber.cpp)
  target_link_libraries(mach_number GTest::gtest_main)
  gtest_discover_tests(mach_number)

  add_executable(mass ${PROJECT_SOURCE_DIR}/test/Mass.cpp)
  target_link_libraries(mass GTest::gtest_main)
  gtest_discover_tests(mass)

  add_executable(mass_density ${PROJECT_SOURCE_DIR}/test/MassDensity.cpp)
  target_link_libraries(mass_density GTest::gtest_main)
  gtest_discover_tests(mass_density)

  add_executable(mass_rate ${PROJECT_SOURCE_DIR}/test/MassRate.cpp)
  target_link_libraries(mass_rate GTest::gtest_main)
  gtest_discover_tests(mass_rate)

  add_executable(memory ${PROJECT_SOURCE_DIR}/test/Memory.cpp)
  target_link_libraries(memory GTest::gtest_main)
  gtest_discover_tests(memory)

  add_executable(memory_rate ${PROJECT_SOURCE_DIR}/test/MemoryRate.cpp)
  target_link_libraries(memory_rate GTest::gtest_main)
  gtest_discover_tests(memory_rate)

  add_executable(poisson_ratio ${PROJECT_SOURCE_DIR}/test/PoissonRatio.cpp)
  target_link_libraries(poisson_ratio GTest::gtest_main)
  gtest_discover_tests(poisson_ratio)

  add_executable(position ${PROJECT_SOURCE_DIR}/test/Position.cpp)
  target_link_libraries(position GTest::gtest_main)
  gtest_discover_tests(position)

  add_executable(power ${PROJECT_SOURCE_DIR}/test/Power.cpp)
  target_link_libraries(power GTest::gtest_main)
  gtest_discover_tests(power)

  add_executable(prandtl_number ${PROJECT_SOURCE_DIR}/test/PrandtlNumber.cpp)
  target_link_libraries(prandtl_number GTest::gtest_main)
  gtest_discover_tests(prandtl_number)

  add_executable(p_wave_modulus ${PROJECT_SOURCE_DIR}/test/PWaveModulus.cpp)
  target_link_libraries(p_wave_modulus GTest::gtest_main)
  gtest_discover_tests(p_wave_modulus)

  add_executable(reynolds_number ${PROJECT_SOURCE_DIR}/test/ReynoldsNumber.cpp)
  target_link_libraries(reynolds_number GTest::gtest_main)
  gtest_discover_tests(reynolds_number)

  add_executable(scalar_acceleration ${PROJECT_SOURCE_DIR}/test/ScalarAcceleration.cpp)
  target_link_libraries(scalar_acceleration GTest::gtest_main)
  gtest_discover_tests(scalar_acceleration)

  add_executable(scalar_angular_acceleration ${PROJECT_SOURCE_DIR}/test/ScalarAngularAcceleration.cpp)
  target_link_libraries(scalar_angular_acceleration GTest::gtest_main)
  gtest_discover_tests(scalar_angular_acceleration)

  add_executable(scalar_displacement_gradient ${PROJECT_SOURCE_DIR}/test/ScalarDisplacementGradient.cpp)
  target_link_libraries(scalar_displacement_gradient GTest::gtest_main)
  gtest_discover_tests(scalar_displacement_gradient)

  add_executable(scalar_force ${PROJECT_SOURCE_DIR}/test/ScalarForce.cpp)
  target_link_libraries(scalar_force GTest::gtest_main)
  gtest_discover_tests(scalar_force)

  add_executable(scalar_heat_flux ${PROJECT_SOURCE_DIR}/test/ScalarHeatFlux.cpp)
  target_link_libraries(scalar_heat_flux GTest::gtest_main)
  gtest_discover_tests(scalar_heat_flux)

  add_executable(scalar_strain ${PROJECT_SOURCE_DIR}/test/ScalarStrain.cpp)
  target_link_libraries(scalar_strain GTest::gtest_main)
  gtest_discover_tests(scalar_strain)

  add_executable(scalar_strain_rate ${PROJECT_SOURCE_DIR}/test/ScalarStrainRate.cpp)
  target_link_libraries(scalar_strain_rate GTest::gtest_main)
  gtest_discover_tests(scalar_strain_rate)

  add_executable(scalar_stress ${PROJECT_SOURCE_DIR}/test/ScalarStress.cpp)
  target_link_libraries(scalar_stress GTest::gtest_main)
  gtest_discover_tests(scalar_stress)

  add_executable(scalar_temperature_gradient ${PROJECT_SOURCE_DIR}/test/ScalarTemperatureGradient.cpp)
  target_link_libraries(scalar_temperature_gradient GTest::gtest_main)
  gtest_discover_tests(scalar_temperature_gradient)

  add_executable(scalar_thermal_conductivity ${PROJECT_SOURCE_DIR}/test/ScalarThermalConductivity.cpp)
  target_link_libraries(scalar_thermal_conductivity GTest::gtest_main)
  gtest_discover_tests(scalar_thermal_conductivity)

  add_executable(scalar_velocity_gradient ${PROJECT_SOURCE_DIR}/test/ScalarVelocityGradient.cpp)
  target_link_libraries(scalar_velocity_gradient GTest::gtest_main)
  gtest_discover_tests(scalar_velocity_gradient)

  add_executable(shear_modulus ${PROJECT_SOURCE_DIR}/test/ShearModulus.cpp)
  target_link_libraries(shear_modulus GTest::gtest_main)
  gtest_discover_tests(shear_modulus)

  add_executable(sound_speed ${PROJECT_SOURCE_DIR}/test/SoundSpeed.cpp)
  target_link_libraries(sound_speed GTest::gtest_main)
  gtest_discover_tests(sound_speed)

  add_executable(specific_energy ${PROJECT_SOURCE_DIR}/test/SpecificEnergy.cpp)
  target_link_libraries(specific_energy GTest::gtest_main)
  gtest_discover_tests(specific_energy)

  add_executable(specific_gas_constant ${PROJECT_SOURCE_DIR}/test/SpecificGasConstant.cpp)
  target_link_libraries(specific_gas_constant GTest::gtest_main)
  gtest_discover_tests(specific_gas_constant)

  add_executable(specific_isobaric_heat_capacity ${PROJECT_SOURCE_DIR}/test/SpecificIsobaricHeatCapacity.cpp)
  target_link_libraries(specific_isobaric_heat_capacity GTest::gtest_main)
  gtest_discover_tests(specific_isobaric_heat_capacity)

  add_executable(specific_isochoric_heat_capacity ${PROJECT_SOURCE_DIR}/test/SpecificIsochoricHeatCapacity.cpp)
  target_link_libraries(specific_isochoric_heat_capacity GTest::gtest_main)
  gtest_discover_tests(specific_isochoric_heat_capacity)

  add_executable(specific_power ${PROJECT_SOURCE_DIR}/test/SpecificPower.cpp)
  target_link_libraries(specific_power GTest::gtest_main)
  gtest_discover_tests(specific_power)

  add_executable(speed ${PROJECT_SOURCE_DIR}/test/Speed.cpp)
  target_link_libraries(speed GTest::gtest_main)
  gtest_discover_tests(speed)

  add_executable(static_kinematic_pressure ${PROJECT_SOURCE_DIR}/test/StaticKinematicPressure.cpp)
  target_link_libraries(static_kinematic_pressure GTest::gtest_main)
  gtest_discover_tests(static_kinematic_pressure)

  add_executable(static_pressure ${PROJECT_SOURCE_DIR}/test/StaticPressure.cpp)
  target_link_libraries(static_pressure GTest::gtest_main)
  gtest_discover_tests(static_pressure)

  add_executable(strain ${PROJECT_SOURCE_DIR}/test/Strain.cpp)
  target_link_libraries(strain GTest::gtest_main)
  gtest_discover_tests(strain)

  add_executable(strain_rate ${PROJECT_SOURCE_DIR}/test/StrainRate.cpp)
  target_link_libraries(strain_rate GTest::gtest_main)
  gtest_discover_tests(strain_rate)

  add_executable(stress ${PROJECT_SOURCE_DIR}/test/Stress.cpp)
  target_link_libraries(stress GTest::gtest_main)
  gtest_discover_tests(stress)

  add_executable(substance_amount ${PROJECT_SOURCE_DIR}/test/SubstanceAmount.cpp)
  target_link_libraries(substance_amount GTest::gtest_main)
  gtest_discover_tests(substance_amount)

  add_executable(symmetric_dyad ${PROJECT_SOURCE_DIR}/test/SymmetricDyad.cpp)
  target_link_libraries(symmetric_dyad GTest::gtest_main)
  gtest_discover_tests(symmetric_dyad)

  add_executable(temperature ${PROJECT_SOURCE_DIR}/test/Temperature.cpp)
  target_link_libraries(temperature GTest::gtest_main)
  gtest_discover_tests(temperature)

  add_executable(temperature_difference ${PROJECT_SOURCE_DIR}/test/TemperatureDifference.cpp)
  target_link_libraries(temperature_difference GTest::gtest_main)
  gtest_discover_tests(temperature_difference)

  add_executable(temperature_gradient ${PROJECT_SOURCE_DIR}/test/TemperatureGradient.cpp)
  target_link_libraries(temperature_gradient GTest::gtest_main)
  gtest_discover_tests(temperature_gradient)

  add_executable(thermal_conductivity ${PROJECT_SOURCE_DIR}/test/ThermalConductivity.cpp)
  target_link_libraries(thermal_conductivity GTest::gtest_main)
  gtest_discover_tests(thermal_conductivity)

  add_executable(thermal_diffusivity ${PROJECT_SOURCE_DIR}/test/ThermalDiffusivity.cpp)
  target_link_libraries(thermal_diffusivity GTest::gtest_main)
  gtest_discover_tests(thermal_diffusivity)

  add_executable(time ${PROJECT_SOURCE_DIR}/test/Time.cpp)
  target_link_libraries(time GTest::gtest_main)
  gtest_discover_tests(time)

  add_executable(total_kinematic_pressure ${PROJECT_SOURCE_DIR}/test/TotalKinematicPressure.cpp)
  target_link_libraries(total_kinematic_pressure GTest::gtest_main)
  gtest_discover_tests(total_kinematic_pressure)

  add_executable(total_pressure ${PROJECT_SOURCE_DIR}/test/TotalPressure.cpp)
  target_link_libraries(total_pressure GTest::gtest_main)
  gtest_discover_tests(total_pressure)

  add_executable(traction ${PROJECT_SOURCE_DIR}/test/Traction.cpp)
  target_link_libraries(traction GTest::gtest_main)
  gtest_discover_tests(traction)

  add_executable(transport_energy_consumption ${PROJECT_SOURCE_DIR}/test/TransportEnergyConsumption.cpp)
  target_link_libraries(transport_energy_consumption GTest::gtest_main)
  gtest_discover_tests(transport_energy_consumption)

  add_executable(unit__acceleration ${PROJECT_SOURCE_DIR}/test/Unit/Acceleration.cpp)
  target_link_libraries(unit__acceleration GTest::gtest_main)
  gtest_discover_tests(unit__acceleration)

  add_executable(unit__angle ${PROJECT_SOURCE_DIR}/test/Unit/Angle.cpp)
  target_link_libraries(unit__angle GTest::gtest_main)
  gtest_discover_tests(unit__angle)

  add_executable(unit__angular_acceleration ${PROJECT_SOURCE_DIR}/test/Unit/AngularAcceleration.cpp)
  target_link_libraries(unit__angular_acceleration GTest::gtest_main)
  gtest_discover_tests(unit__angular_acceleration)

  add_executable(unit__angular_speed ${PROJECT_SOURCE_DIR}/test/Unit/AngularSpeed.cpp)
  target_link_libraries(unit__angular_speed GTest::gtest_main)
  gtest_discover_tests(unit__angular_speed)

  add_executable(unit__area ${PROJECT_SOURCE_DIR}/test/Unit/Area.cpp)
  target_link_libraries(unit__area GTest::gtest_main)
  gtest_discover_tests(unit__area)

  add_executable(unit__diffusivity ${PROJECT_SOURCE_DIR}/test/Unit/Diffusivity.cpp)
  target_link_libraries(unit__diffusivity GTest::gtest_main)
  gtest_discover_tests(unit__diffusivity)

  add_executable(unit__dynamic_viscosity ${PROJECT_SOURCE_DIR}/test/Unit/DynamicViscosity.cpp)
  target_link_libraries(unit__dynamic_viscosity GTest::gtest_main)
  gtest_discover_tests(unit__dynamic_viscosity)

  add_executable(unit__energy ${PROJECT_SOURCE_DIR}/test/Unit/Energy.cpp)
  target_link_libraries(unit__energy GTest::gtest_main)
  gtest_discover_tests(unit__energy)

  add_executable(unit__energy_flux ${PROJECT_SOURCE_DIR}/test/Unit/EnergyFlux.cpp)
  target_link_libraries(unit__energy_flux GTest::gtest_main)
  gtest_discover_tests(unit__energy_flux)

  add_executable(unit__force ${PROJECT_SOURCE_DIR}/test/Unit/Force.cpp)
  target_link_libraries(unit__force GTest::gtest_main)
  gtest_discover_tests(unit__force)

  add_executable(unit__frequency ${PROJECT_SOURCE_DIR}/test/Unit/Frequency.cpp)
  target_link_libraries(unit__frequency GTest::gtest_main)
  gtest_discover_tests(unit__frequency)

  add_executable(unit__heat_capacity ${PROJECT_SOURCE_DIR}/test/Unit/HeatCapacity.cpp)
  target_link_libraries(unit__heat_capacity GTest::gtest_main)
  gtest_discover_tests(unit__heat_capacity)

  add_executable(unit__length ${PROJECT_SOURCE_DIR}/test/Unit/Length.cpp)
  target_link_libraries(unit__length GTest::gtest_main)
  gtest_discover_tests(unit__length)

  add_executable(unit__mass ${PROJECT_SOURCE_DIR}/test/Unit/Mass.cpp)
  target_link_libraries(unit__mass GTest::gtest_main)
  gtest_discover_tests(unit__mass)

  add_executable(unit__mass_density ${PROJECT_SOURCE_DIR}/test/Unit/MassDensity.cpp)
  target_link_libraries(unit__mass_density GTest::gtest_main)
  gtest_discover_tests(unit__mass_density)

  add_executable(unit__mass_rate ${PROJECT_SOURCE_DIR}/test/Unit/MassRate.cpp)
  target_link_libraries(unit__mass_rate GTest::gtest_main)
  gtest_discover_tests(unit__mass_rate)

  add_executable(unit__memory ${PROJECT_SOURCE_DIR}/test/Unit/Memory.cpp)
  target_link_libraries(unit__memory GTest::gtest_main)
  gtest_discover_tests(unit__memory)

  add_executable(unit__memory_rate ${PROJECT_SOURCE_DIR}/test/Unit/MemoryRate.cpp)
  target_link_libraries(unit__memory_rate GTest::gtest_main)
  gtest_discover_tests(unit__memory_rate)

  add_executable(unit__power ${PROJECT_SOURCE_DIR}/test/Unit/Power.cpp)
  target_link_libraries(unit__power GTest::gtest_main)
  gtest_discover_tests(unit__power)

  add_executable(unit__pressure ${PROJECT_SOURCE_DIR}/test/Unit/Pressure.cpp)
  target_link_libraries(unit__pressure GTest::gtest_main)
  gtest_discover_tests(unit__pressure)

  add_executable(unit__specific_energy ${PROJECT_SOURCE_DIR}/test/Unit/SpecificEnergy.cpp)
  target_link_libraries(unit__specific_energy GTest::gtest_main)
  gtest_discover_tests(unit__specific_energy)

  add_executable(unit__specific_heat_capacity ${PROJECT_SOURCE_DIR}/test/Unit/SpecificHeatCapacity.cpp)
  target_link_libraries(unit__specific_heat_capacity GTest::gtest_main)
  gtest_discover_tests(unit__specific_heat_capacity)

  add_executable(unit__specific_power ${PROJECT_SOURCE_DIR}/test/Unit/SpecificPower.cpp)
  target_link_libraries(unit__specific_power GTest::gtest_main)
  gtest_discover_tests(unit__specific_power)

  add_executable(unit__speed ${PROJECT_SOURCE_DIR}/test/Unit/Speed.cpp)
  target_link_libraries(unit__speed GTest::gtest_main)
  gtest_discover_tests(unit__speed)

  add_executable(unit__substance_amount ${PROJECT_SOURCE_DIR}/test/Unit/SubstanceAmount.cpp)
  target_link_libraries(unit__substance_amount GTest::gtest_main)
  gtest_discover_tests(unit__substance_amount)

  add_executable(unit__temperature ${PROJECT_SOURCE_DIR}/test/Unit/Temperature.cpp)
  target_link_libraries(unit__temperature GTest::gtest_main)
  gtest_discover_tests(unit__temperature)

  add_executable(unit__temperature_difference ${PROJECT_SOURCE_DIR}/test/Unit/TemperatureDifference.cpp)
  target_link_libraries(unit__temperature_difference GTest::gtest_main)
  gtest_discover_tests(unit__temperature_difference)

  add_executable(unit__temperature_gradient ${PROJECT_SOURCE_DIR}/test/Unit/TemperatureGradient.cpp)
  target_link_libraries(unit__temperature_gradient GTest::gtest_main)
  gtest_discover_tests(unit__temperature_gradient)

  add_executable(unit__thermal_conductivity ${PROJECT_SOURCE_DIR}/test/Unit/ThermalConductivity.cpp)
  target_link_libraries(unit__thermal_conductivity GTest::gtest_main)
  gtest_discover_tests(unit__thermal_conductivity)

  add_executable(unit__thermal_expansion ${PROJECT_SOURCE_DIR}/test/Unit/ThermalExpansion.cpp)
  target_link_libraries(unit__thermal_expansion GTest::gtest_main)
  gtest_discover_tests(unit__thermal_expansion)

  add_executable(unit__time ${PROJECT_SOURCE_DIR}/test/Unit/Time.cpp)
  target_link_libraries(unit__time GTest::gtest_main)
  gtest_discover_tests(unit__time)

  add_executable(unit__transport_energy_consumption ${PROJECT_SOURCE_DIR}/test/Unit/TransportEnergyConsumption.cpp)
  target_link_libraries(unit__transport_energy_consumption GTest::gtest_main)
  gtest_discover_tests(unit__transport_energy_consumption)

  add_executable(unit__volume ${PROJECT_SOURCE_DIR}/test/Unit/Volume.cpp)
  target_link_libraries(unit__volume GTest::gtest_main)
  gtest_discover_tests(unit__volume)

  add_executable(unit__volume_rate ${PROJECT_SOURCE_DIR}/test/Unit/VolumeRate.cpp)
  target_link_libraries(unit__volume_rate GTest::gtest_main)
  gtest_discover_tests(unit__volume_rate)

  add_executable(unit_system ${PROJECT_SOURCE_DIR}/test/UnitSystem.cpp)
  target_link_libraries(unit_system GTest::gtest_main)
  gtest_discover_tests(unit_system)

  add_executable(vector ${PROJECT_SOURCE_DIR}/test/Vector.cpp)
  target_link_libraries(vector GTest::gtest_main)
  gtest_discover_tests(vector)

  add_executable(vector_area ${PROJECT_SOURCE_DIR}/test/VectorArea.cpp)
  target_link_libraries(vector_area GTest::gtest_main)
  gtest_discover_tests(vector_area)

  add_executable(velocity ${PROJECT_SOURCE_DIR}/test/Velocity.cpp)
  target_link_libraries(velocity GTest::gtest_main)
  gtest_discover_tests(velocity)

  add_executable(velocity_gradient ${PROJECT_SOURCE_DIR}/test/VelocityGradient.cpp)
  target_link_libraries(velocity_gradient GTest::gtest_main)
  gtest_discover_tests(velocity_gradient)

  add_executable(volume ${PROJECT_SOURCE_DIR}/test/Volume.cpp)
  target_link_libraries(volume GTest::gtest_main)
  gtest_discover_tests(volume)

  add_executable(volume_rate ${PROJECT_SOURCE_DIR}/test/VolumeRate.cpp)
  target_link_libraries(volume_rate GTest::gtest_main)
  gtest_discover_tests(volume_rate)

  add_executable(volumetric_thermal_expansion_coefficient ${PROJECT_SOURCE_DIR}/test/VolumetricThermalExpansionCoefficient.cpp)
  target_link_libraries(volumetric_thermal_expansion_coefficient GTest::gtest_main)
  gtest_discover_tests(volumetric_thermal_expansion_coefficient)

  add_executable(young_modulus ${PROJECT_SOURCE_DIR}/test/YoungModulus.cpp)
  target_link_libraries(young_modulus GTest::gtest_main)
  gtest_discover_tests(young_modulus)

  message(STATUS "The Physical Quantities (PhQ) library tests were configured. Build the tests with \"make --jobs=16\" and run them with \"make test\"")
else()
  message(STATUS "The Physical Quantities (PhQ) library tests were not configured. Run \"cmake .. -DTEST_PHQ_LIBRARY=ON\" to configure the tests.")
endif()

# Define the library directories to be installed.
include(GNUInstallDirs)
install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}_Targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Write the installation configuration files.
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "PhQConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)
file(
  WRITE "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake.input"
  "@PACKAGE_INIT@\ninclude(\"${CMAKE_CURRENT_LIST_DIR}/@PROJECT_NAME@Targets.cmake\")\ncheck_required_components(\"@PROJECT_NAME@\")\n"
)
configure_package_config_file(
  "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake.input"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

# Define the installation instructions.
install(
  EXPORT ${PROJECT_NAME}_Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)
install(
  FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)
install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/include/PhQ
  DESTINATION include
)
