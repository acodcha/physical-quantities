# Physical Quantities

[![build and test](https://github.com/acodcha/physical-quantities/actions/workflows/build_and_test.yaml/badge.svg?branch=main)](https://github.com/acodcha/physical-quantities/actions/workflows/build_and_test.yaml)

C++ library of physical quantities, physical models, and units of measure for scientific computation.

If you have ever made a unit conversion error, or if you have ever asked yourself questions such as "what is the correct unit of mass density in the inch-pound-second system?", "how do I compute a stress field given a strain field?", or "what the heck is a slug unit?" then this library is for you!

- Physical quantities are implemented efficiently with no memory overhead compared to using raw floating point numbers to represent the same data.
- Mathematical operations between physical quantities are implemented efficiently with no runtime overhead compared to using raw floating point numbers to represent the same data.
- Unit conversions are handled automatically. Never again will you make a unit conversion error!
- Physical models allow complex mathematical calculations to be performed easily. Never again will you make a tensor-vector multiplication error!
- Unit systems allow scientific data to be expressed in a consistent system of units for use in other applications. Never again will you accidentally use pounds when you should have used slugs!

Contents:

- [Requirements](#requirements)
- [Configuration](#configuration)
- [Usage](#usage)
  - [Basics](#usage-basics)
  - [Vectors and Tensors](#usage-vectors-and-tensors)
  - [Operations](#usage-operations)
  - [Units](#usage-units)
  - [Unit Systems](#usage-unit-systems)
  - [Physical Models](#usage-physical-models)
  - [Divisions by Zero](#usage-divisions-by-zero)
  - [Exceptions](#usage-exceptions)
- [Installation](#installation)
- [Testing](#testing)
- [License](#license)

## Requirements

This library requires the following packages:

- **C++17 Compiler:** Any C++17 compiler will do, such as GCC or Clang. On Ubuntu, install GCC with `sudo apt install g++` or Clang with `sudo apt install clang`.
- **CMake:** On Ubuntu, install CMake with `sudo apt install cmake`.

[(Back to Top)](#physical-quantities)

## Configuration

To use the Physical Quantities library in one of your CMake projects, add the following to your `CMakeLists.txt` file:

```cmake
include(FetchContent)
FetchContent_Declare(
  PhQ
  GIT_REPOSITORY https://github.com/acodcha/physical-quantities.git
  GIT_TAG main
)
FetchContent_MakeAvailable(PhQ)

[...]

target_link_libraries(your-target-name [other-options] PhQ)
```

This automatically downloads, builds, and links the Physical Quantities library to your target.

Alternatively, if you have installed the Physical Quantities library on your system as described in the [Installation](#installation) section, you can instead simply add the following to your `CMakeLists.txt` file:

```cmake
find_package(PhQ CONFIG REQUIRED)

[...]

target_link_libraries(your-target-name [other-options] PhQ)
```

To use the Physical Quantities library in your source code, simply include this library's headers in your project's source files, such as `#include <PhQ/Position.hpp>` for the `PhQ::Position` class. The `PhQ::` namespace encapsulates all of the Physical Quantities library's contents.

[(Back to Top)](#physical-quantities)

## Usage

- [Basics](#usage-basics)
- [Vectors and Tensors](#usage-vectors-and-tensors)
- [Operations](#usage-operations)
- [Units](#usage-units)
- [Unit Systems](#usage-unit-systems)
- [Physical Models](#usage-physical-models)
- [Divisions by Zero](#usage-divisions-by-zero)
- [Exceptions](#usage-exceptions)

[(Back to Top)](#physical-quantities)

### Usage: Basics

Physical quantities are constructed from a value and a unit. For example:

```C++
PhQ::Temperature low{10.0, PhQ::Unit::Temperature::Celsius};
PhQ::Temperature high{68.0, PhQ::Unit::Temperature::Fahrenheit};
PhQ::Temperature average = 0.5 * (low + high);
std::cout << "Average: " << average << std::endl;
```

The above example creates two temperature quantities, computes their average, and prints the result, which is 15 °C.

Physical quantities are implemented efficiently with no memory overhead compared to using raw floating point numbers to represent the same data. For example:

```C++
PhQ::Area area{10.0, PhQ::Unit::Area::Hectare};
assert(sizeof(area) == sizeof(double));

PhQ::Position position{{-1.11, 2.22, -3.33}, PhQ::Unit::Length::Mile};
assert(sizeof(position) == 3 * sizeof(double));
```

[(Back to Usage)](#usage)

### Usage: Vectors and Tensors

Values can be scalars, vectors, or dyadic tensors. Vectors and dyadic tensors are represented internally in a Cartesian (x-y-z) coordinate system. For example:

```C++
PhQ::Force force{{/*x=*/300.0, /*y=*/0.0, /*z=*/-400.0}, PhQ::Unit::Force::Pound};
force /= 5.0;
PhQ::ForceMagnitude magnitude = force.Magnitude();
std::cout << "Magnitude: " << magnitude.Print(PhQ::Unit::Force::Pound) << std::endl;
```

The above example creates a force quantity of (300, 0, -400) lbf, divides it by 5, computes its magnitude, and prints the magnitude in pounds, which results in 100 lbf.

Some dyadic tensor quantities are symmetric. For example:

```C++
PhQ::Stress stress{
    {/*xx=*/32.0, /*xy=*/-4.0, /*xz=*/-2.0, /*yy=*/16.0, /*yz=*/-1.0, /*zz=*/8.0},
    PhQ::Unit::Pressure::Megapascal};
std::cout << "Von Mises stress: " << stress.VonMises() << std::endl;
```

The above example creates a stress quantity and computes and prints its equivalent von Mises stress.

[(Back to Usage)](#usage)

### Usage: Operations

Meaningful arithmetic operations between different physical quantities are supported via operator overloading. Mathematical operations between physical quantities are implemented efficiently with no runtime overhead compared to using raw floating point numbers to represent the same data. For example:

```C++
PhQ::Velocity velocity{{50.0, -10.0, 20.0}, PhQ::Unit::Speed::MetrePerSecond};
PhQ::Time time{10.0, PhQ::Unit::Time::Second};
PhQ::Acceleration acceleration = velocity / time;
std::cout << "Acceleration: " << acceleration << std::endl;
```

The above example creates a velocity quantity of (50, -10, 20) m/s and a time quantity of 10 s, then divides the velocity by the time to produce an acceleration quantity of (5, -1, 2) m/s^2.

Similarly, other meaningful mathematical operations are supported via member methods. For example:

```C++
PhQ::Displacement displacement{{0.0, 6.0, 0.0}, PhQ::Unit::Length::Inch};
PhQ::Length length = displacement.Magnitude();
PhQ::Direction direction = displacement.Direction();
std::cout << "Length: " << length << ", Direction: " << direction << std::endl;

PhQ::Displacement other_displacement{{0.0, 0.0, -3.0}, PhQ::Unit::Length::Inch};
PhQ::Angle angle{displacement, other_displacement};
std::cout << "Angle: " << angle.Print(PhQ::Unit::Angle::Degree) << std::endl;
```

The above example creates a displacement quantity of (0, 6, 0) in, computes and prints its magnitude and direction, then creates a second displacement of (0, 0, -3) in, and computes and prints the angle between the two displacements, which is 90 deg.

[(Back to Usage)](#usage)

### Usage: Units

Unit conversions are handled automatically. Internally, physical quantities maintain their values in a consistent unit system: the metre-kilogram-second-kelvin (m·kg·s·K) system. This approach minimizes the number of unit conversions during program execution; when a physical quantity is constructed, it is immediately converted to its standard unit of measure in the standard unit system. The only other instances where a physical quantity undergoes a unit conversion is when its value is expressed in a different unit of measure or when the physical quantity itself is printed as a string expressed in a different unit of measure.

A physical quantity's value can be expressed in any unit of measure through its `Value` method. For example:

```C++
PhQ::Mass mass{10.0, PhQ::Unit::Mass::Pound};

double standard_value = mass.Value();
PhQ::Unit::Mass standard_unit = PhQ::Mass::Unit();  // PhQ::Unit::Mass::Kilogram
std::string standard_abbreviation = PhQ::Abbreviation(standard_unit);
std::cout << standard_value << " " << standard_abbreviation << std::endl;

PhQ::Unit::Mass other_unit = PhQ::Unit::Mass::Gram;
std::string other_abbreviation = PhQ::Abbreviation(other_unit);
double other_value = mass.Value(other_unit);
std::cout << other_value << " " << other_abbreviation << std::endl;
```

The above example creates a 10 lbm mass and prints its value as 4.535924 kg and 4535.924 g.

A physical quantity can be expressed in any unit of measure through its `Print` method. For example:

```C++
PhQ::Frequency frequency{10.0, PhQ::Unit::Frequency::Hertz};
std::string standard = frequency.Print();
std::string kilohertz = frequency.Print(PhQ::Unit::Frequency::Kilohertz);
std::cout << standard << " = " << kilohertz << std::endl;
```

The above example creates a 10 Hz frequency and prints it both in hertz and in kilohertz.

Unit conversions can also be done explicitly without the use of physical quantities through the `PhQ::Convert` function, which takes a value, an original unit, and a new unit. For example:

```C++
double value = 10.0;
PhQ::Convert(value, PhQ::Unit::Energy::Joule, PhQ::Unit::Energy::FootPound)
std::cout << value << std::endl;
```

The above example converts 10 J to 7.375621 ft·lbf. The same can also be achieved with:

```C++
PhQ::Energy energy{10.0, PhQ::Unit::Energy::Joule};
double foot_pounds = energy.Value(PhQ::Unit::Energy::FootPound);
std::cout << foot_pounds << std::endl;
```

In general, it is easier to use physical quantities instead of manually invoking the `PhQ::Convert` function.

[(Back to Usage)](#usage)

### Usage: Unit Systems

Internally, all data is stored in the metre-kilogram-second-kelvin (m·kg·s·K) system. However, other common systems of units of measure are also defined:

- Metre-kilogram-second-kelvin (m·kg·s·K) system
- Millimetre-gram-second-kelvin (mm·g·s·K) system
- Foot-pound-second-rankine (ft·lbf·s·°R) system
- Inch-pound-second-rankine (in·lbf·s·°R) system

Data can be expressed in the consistent units of any of these unit systems. The unit of measure of a given type that corresponds to a given unit system can be obtained with the `PhQ::ConsistentUnit` function. For example:

```C++
PhQ::SpecificEnergy specific_energy{10.0, PhQ::Unit::SpecificEnergy::JoulePerKilogram};
PhQ::UnitSystem system = PhQ::UnitSystem::FootPoundSecondRankine;
PhQ::Unit::SpecificEnergy unit = PhQ::ConsistentUnit<PhQ::Unit::SpecificEnergy>(system);
std::cout << unit << std::endl;  // ft·lbf/slug
double value = energy.Value(unit);
std::cout << value << std::endl;
```

The above example creates a mass-specific energy quantity of 10 J/kg. Then, the mass-specific energy unit corresponding to the foot-pound-second-rankine (ft·lbf·s·°R) system is obtained, and the mass-specific energy value is expressed in this unit of measure.

Given a unit, it is also possible to obtain its related unit system, if any, with the `PhQ::RelatedUnitSystem` function. For example:

```C++
PhQ::Unit::Mass unit = PhQ::Unit::Mass::Slug;
std::optional<PhQ::UnitSystem> optional_system = PhQ::RelatedUnitSystem(unit);
assert(optional_system.has_value());
std::cout << optional_system.value() << std::endl;  // ft·lbf·s·°R
```

The above example obtains the related unit system of the slug mass unit, which is the foot-pound-second-rankine (ft·lbf·s·°R) system.

However, not all units have a corresponding unit system. For example:

```C++
PhQ::Unit::Mass unit = PhQ::Unit::Mass::Pound;
std::optional<PhQ::UnitSystem> optional_system = PhQ::RelatedUnitSystem(unit);
assert(!optional_system.has_value());
```

The above example shows that the pound (lbm) mass unit does not belong to any unit system.

[(Back to Usage)](#usage)

### Usage: Physical Models

Some physical models and related operations are also supported. Physical models allow complex mathematical calculations to be performed easily. For example:

```C++
PhQ::YoungModulus young_modulus{70.0, PhQ::Unit::Pressure::Gigapascal};
PhQ::PoissonRatio poisson_ratio{0.33};

std::unique_ptr<ConstitutiveModel> constitutive_model =
    std::make_unique<ConstitutiveModel::ElasticIsotropicSolid>(young_modulus, poisson_ratio);

PhQ::Strain strain{
    {/*xx=*/32.0, /*xy=*/-4.0, /*xz=*/-2.0, /*yy=*/16.0, /*yz=*/-1.0, /*zz=*/8.0}};

PhQ::Stress stress = constitutive_model->Stress(strain);
std::cout << stress << std::endl;
```

The above example creates an elastic isotropic solid constitutive model from a Young's modulus and a Poisson's ratio, and then uses it to compute the stress tensor given a strain tensor.

[(Back to Usage)](#usage)

### Usage: Divisions by Zero

The Physical Quantities library carefully handles divisions by zero in its internal arithmetic operations. For example, `PhQ::Direction` carefully checks for the zero vector case when normalizing its magnitude, and `PhQ::Value::Dyad` and `PhQ::Value::SymmetricDyad` carefully check for a zero determinant when computing their inverse. However, in general, divisions by zero can occur during arithmetic operations between physical quantities. For example, `PhQ::Length::Zero() / PhQ::Time::Zero()` results in a `PhQ::Speed` with a value of "not-a-number" (`NaN`). C++ uses the IEEE 754 floating point arithmetic standard, which supports divisions by zero such as `1.0/0.0 = inf`, `-1.0/0.0 = -inf`, and `0.0/0.0 = NaN`. If any of these special cases are a concern, use try-catch blocks or standard C++ utilities such as `std::isfinite`.

[(Back to Usage)](#usage)

### Usage: Exceptions

The only circumstance in which the Physical Quantities library throws an exception is a memory allocation failure due to running out of memory on your system when instantiating a new object, which throws a `std::bad_alloc` exception. If maintaining a strong exception guarantee is a concern, use try-catch blocks when instantiating new objects to handle this exception. Other than this case, the Physical Quantities library does not throw exceptions. As a result, many of this library's functions and methods are marked `noexcept`.

[(Back to Usage)](#usage)

## Installation

You may optionally install the Physical Quantities library on your system to use it in your projects. Alternatively, see the [Configuration](#configuration) section for other methods of use.

First, clone the Physical Quantities library's repository and configure it with:

```bash
git clone git@github.com:acodcha/physical-quantities.git
cd physical-quantities
mkdir build
cd build
cmake ..
```

This is a header-only library, so no compilation is needed.

Second, install the Physical Quantities library on your system from the `build` directory with:

```bash
sudo make install
```

On most systems, this installs the Physical Quantities library's headers to `/usr/local/include/PhQ` and writes configuration files to `/usr/local/share/PhQ`. You can uninstall the Physical Quantities library by simply deleting these directories.

[(Back to Top)](#physical-quantities)

## Testing

Testing is optional, disabled by default, and requires the following additional package:

- **GoogleTest**: The GoogleTest library (<https://github.com/google/googletest>) is used for testing. On Ubuntu, install it with `sudo apt install libgtest-dev`. When testing is enabled, if the GoogleTest library is not found on your system, it is automatically downloaded, built, and linked with the Physical Quantities library.

You can manually test the Physical Quantities library on your system from the `build` directory with:

```bash
cmake .. -DTEST_PHQ_LIBRARY=ON
make --jobs=16
make test
```

[(Back to Top)](#physical-quantities)

## License

This project is maintained by Alexandre Coderre-Chabot (<https://github.com/acodcha>) and licensed under the GNU Lesser General Public License v3.0 (LGPL-3.0). For more details, see the `LICENSE` file or <https://www.gnu.org/licenses/lgpl-3.0.en.html>.

[(Back to Top)](#physical-quantities)
