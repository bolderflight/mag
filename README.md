[![Pipeline](https://gitlab.com/bolderflight/software/mag/badges/main/pipeline.svg)](https://gitlab.com/bolderflight/software/mag/) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

![Bolder Flight Systems Logo](img/logo-words_75.png)

# Mag
Defines a common interface for magnetometers.
   * [License](LICENSE.md)
   * [Changelog](CHANGELOG.md)
   * [Contributing guide](CONTRIBUTING.md)

# Description
This library defines what a *Mag* interface should look like, enabling higher level code to abstract out magnetometer specifics and design against this interface.

## Installation
CMake is used to build this library, which is exported as a library target called *mag*. The header is added as:

```
#include "mag/mag.h"
```

The library can be also be compiled stand-alone using the CMake idiom of creating a *build* directory and then, from within that directory issuing:

```
cmake ..
make
```

This will build the library and an example called *example*, which has source code located in *examples/example.cc*.

## Namespace
This library is within the namespace *bfs*.

## Class / Methods

**struct MagConfig** defines a structure used to configure the magnetometer. The data fields are:

| Name | Description |
| --- | --- |
| float mag_bias_ut[3] | A vector of mag biases, uT |
| float mag_scale[3][3] | A matrix of mag scale factors |
| float rotation[3][3] | Rotation matrix to align sensor data with vehicle frame |

The mag biases and scale factors should be determined offline and input here, they are relatively stable with respect to temperature. The bias and scale factor should be input such that:

```
y = c * x + b
```

Where y is the corrected sensor output, c is the scale factor matrix, x is the uncorrected sensor output, and b is the bias vector. An ideal sensor would have a bias vector of zeros and an identity scale factor matrix.

The rotation matrix is used to align the sensor data with the vehicle frame. This is useful if the sensor cannot be installed aligned with the vehicle axes. The rotation should be used to align the sensor x-axis out the vehicle nose, the y-axis out the right, and the z-axis down.

**struct MagData** defines a structure of data returned from the magnetometer. The data fields are:

| Name | Description |
| --- | --- |
| bool new_data | Whether new data was received |
| bool healthy | Whether the magnetometer is healthy |
| die_temp_c | The sensor die temperature, C |
| mag_ut[3] | The 3-axis mag data, uT |

Health is determined by whether the sensor fails to read 5 times in a row at the expected sampling rate.

**Mag** Concepts are used to define what an *Mag* compliant object looks like and provide a means to templating against an *Mag* interface. The required methods are:

**bool Config(const MagConfig &ref)** This method should receive an *MagConfig* struct and setup the sensor driver configuration. Note that the configuration should be applied in the *Init* method, this simply checks the configuration for validity and sets up the sensor driver object. True is returned if the config is valid, otherwise false if returned.

**MagData mag_data()** This method returns the *MagData* from the last successful *Read*.
