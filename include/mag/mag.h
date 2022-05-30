/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2022 Bolder Flight Systems Inc
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the “Software”), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#ifndef INCLUDE_MAG_MAG_H_
#define INCLUDE_MAG_MAG_H_

#include <concepts>

namespace bfs {

struct MagConfig {
  float mag_bias_ut[3];
  float mag_scale[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
  float rotation[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
};
struct MagData {
  bool new_data;
  bool healthy;
  float die_temp_c;
  float mag_ut[3];
};

template<typename T>
concept Mag = requires(T mag, const MagConfig &ref) {
  { mag.Config(ref) } -> std::same_as<bool>;
  { mag.mag_data() } -> std::same_as<MagData>;
};  // NOLINT - gets confused with concepts and semicolon after braces

}  // namespace bfs

#endif  // INCLUDE_MAG_MAG_H_
