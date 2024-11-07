/*----------------------------------LEGAL--------------------------------------

MIT License

Copyright (c) 2023 Benjamin Joseph Brooks

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

-----------------------------------------------------------------------------*/

#pragma once

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FLOAT_EPSILON (1e-4)
#define PI 3.14159265358

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

static inline float rad2deg(const float n) { return n * (180.0f / PI); }

static inline float deg2rad(const float n) { return n * (PI / 180.0f); }

static inline float wrapAngle(float a) {
  a = fmod(a, 2 * PI);
  if (a < 0) {
    a += 2 * PI;
  }
  return a;
}

static inline float clamp(float n, const float min, const float max) {
  n = n < min ? min : n;
  return n > max ? max : n;
}

static inline float clamp01(float n) {
  n = n < 0 ? 0 : n;
  return n > 1 ? 1 : n;
}

static inline float lerp(float a, float b, float t) { return a + (b - a) * t; }

static inline float lerpclamped(float a, float b, float t) {
  return a + (b - a) * clamp01(t);
}

static inline float norm(float n, float min, float max) { return (n - min) / (max - min); }

static inline float map(float n, float fromMin, float fromMax, float toMin, float toMax) {
  //return lerp(norm(n, fromMin, fromMax), toMin, toMax);
  return (n - fromMin) * (toMax - toMin) / (fromMax - fromMin) + toMin;
}

static inline int aproxequal(float a, float b, float tolerance) {
  return (fabs(a - b) < tolerance);
}

static inline float cosInterpolate(float a, float b, float x) {
  float f = (1.0f - cosf(x * PI)) * 0.5f;
  return a * (1.0 - f) + b * f;
}

static inline float sigmoid(float n) { return (1 / (1 + pow(2.71828182846, -n))); }

static inline float loop(float n, const float length) {
  return clamp(n - floor(n / length) * length, 0.0f, length);
}

static inline float pingpong(float n, const float length) {
  n = loop(n, length * 2.0f);
  return fabs(n - length);
}

static inline float angleDelta(const float a, const float b) {
  float delta = loop((b - a), 360.0f);
  if (delta > 180.0f) {
    delta -= 360.0f;
  }
  return delta;
}

static inline float noise_1d(int x) {
  x = (x << 13) ^ x;
  return (1.0 - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7FFFFFFF) /
                    1073741824.0);
}

static inline float noise_smoothed1d(float x) {
  return noise_1d(x) / 2 + noise_1d(x - 1) / 4 + noise_1d(x + 1) / 4;
}

static inline float noise_interpolated1d(float x) {
  int integerX = (int)x;
  float fractionalX = x - integerX;
  float v1 = noise_smoothed1d(integerX);
  float v2 = noise_smoothed1d(integerX + 1);
  return cosInterpolate(v1, v2, fractionalX);
}

static inline float noise_perlin1d(float x, float persistance, int octaves) {
  persistance *= 0.5f;
  persistance = clamp(persistance, 0.0f, 1.0f);
  float total = 0.0f;
  int n = octaves - 1;

  int i = 0;
  float freq = 0.0f;
  float amp = 0.0f;
  for (i = 0; i < n; i++) {
    freq = pow(2, i);
    amp = pow(persistance, i);

    total = total + noise_interpolated1d(x * freq) * amp;
  }
  total = (total + 1) * 0.5f;
  assert(total <= 1);
  assert(total >= -1);
  return total;
}

static inline float noise_2d(int x, int y) {
  int n = x + y * 57;
  n = (n << 13) ^ n;
  return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7FFFFFFF) /
                    1073741824.0);
}

static inline float noise_smoothed2d(float x, float y) {
  float corners = (noise_2d(x - 1, y - 1) + noise_2d(x + 1, y - 1) +
                   noise_2d(x - 1, y + 1) + noise_2d(x + 1, y + 1)) /
                  16;
  float sides = (noise_2d(x - 1, y) + noise_2d(x + 1, y) + noise_2d(x, y - 1) +
                 noise_2d(x, y + 1)) /
                8;

  float center = noise_2d(x, y) / 4;
  return corners + sides + center;
}

static inline float noise_interpolated2d(float x, float y) {
  int integerX = (int)x;
  float fractionalX = x - integerX;

  int integerY = (int)y;
  float fractionalY = y - integerY;

  float v1 = noise_smoothed2d(integerX, integerY);
  float v2 = noise_smoothed2d(integerX + 1, integerY);
  float v3 = noise_smoothed2d(integerX, integerY + 1);
  float v4 = noise_smoothed2d(integerX + 1, integerY + 1);

  float i1 = cosInterpolate(v1, v2, fractionalX);
  float i2 = cosInterpolate(v3, v4, fractionalX);

  return cosInterpolate(i1, i2, fractionalY);
}

static inline float noise_perlin2d(float x, float y, float persistance, int octaves) {
  persistance *= 0.5f;
  persistance = clamp(persistance, 0.0f, 1.0f);
  float total = 0.0f;
  float n = octaves - 1;

  int i = 0;
  float freq = 0.0f;
  float amp = 0.0f;
  for (i = 0; i < n; i++) {
    freq = pow(2, i);
    amp = pow(persistance, i);

    total = total + noise_interpolated2d(x * freq, y * freq) * amp;
  }
  total = (total + 1) * 0.5f;
  assert(total <= 1);
  assert(total >= -1);
  return total;
}

static inline float noise_3d(int x, int y, int z) {
  int n = x + y + z * 57;
  n = (n << 13) ^ n;
  return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7FFFFFFF) /
                    1073741824.0);
}

static inline float noise_smoothed3d(float x, float y, float z) {
  float corner1 = noise_3d(x - 1, y - 1, z - 1),
        corner2 = noise_3d(x + 1, y - 1, z - 1),
        corner3 = noise_3d(x - 1, y + 1, z - 1),
        corner4 = noise_3d(x + 1, y + 1, z - 1),
        corner5 = noise_3d(x - 1, y - 1, z + 1),
        corner6 = noise_3d(x + 1, y - 1, z + 1),
        corner7 = noise_3d(x - 1, y + 1, z + 1),
        corner8 = noise_3d(x + 1, y + 1, z + 1),
        corners = (corner1 + corner2 + corner3 + corner4 + 
            corner5 + corner6 + corner7 + corner8),
        side1   = noise_3d( x - 1, y,     z - 1),
        side2   = noise_3d( x + 1, y,     z - 1),
        side3   = noise_3d( x,     y - 1, z - 1),
        side4   = noise_3d( x,     y + 1, z - 1),
        side5   = noise_3d( x - 1, y,     z),
        side6   = noise_3d( x + 1, y,     z),
        side7   = noise_3d( x,     y - 1, z),
        side8   = noise_3d( x,     y + 1, z),
        side9   = noise_3d( x - 1, y,     z + 1),
        side10  = noise_3d( x + 1, y,     z + 1),
        side11  = noise_3d( x,     y - 1, z + 1),
        side12  = noise_3d( x,     y + 1, z + 1),
        sides = 
          side1 + side2 + side3 + side4 + 
          side5 + side6 + side7 + side8 + 
          side9 + side10 + side11 + side12,
        center = noise_3d(x,y,z);
  return (corners + sides + center) / 128;
}

static inline float noise_interpolated3d(float x, float y, float z) {
  int integerX = (int)x,
      integerY = (int)y,
      integerZ = (int)z;

  float fractionalX = x - integerX,
        fractionalY = y - integerY,
        fractionalZ = z - integerZ,

        v1 = noise_smoothed3d(integerX,     integerY,     integerZ),
        v2 = noise_smoothed3d(integerX + 1, integerY,     integerZ),
        v3 = noise_smoothed3d(integerX,     integerY + 1, integerZ),
        v4 = noise_smoothed3d(integerX + 1, integerY + 1, integerZ),
        v5 = noise_smoothed3d(integerX,     integerY,     integerZ + 1),
        v6 = noise_smoothed3d(integerX + 1, integerY,     integerZ + 1),
        v7 = noise_smoothed3d(integerX,     integerY + 1, integerZ + 1),
        v8 = noise_smoothed3d(integerX + 1, integerY + 1, integerZ + 1),

        i1 = cosInterpolate(v1, v2, fractionalX),
        i2 = cosInterpolate(v3, v4, fractionalX),
        i3 = cosInterpolate(i1, i2, fractionalY),

        i4 = cosInterpolate(v5, v6, fractionalY),
        i5 = cosInterpolate(v7, v8, fractionalY),
        i6 = cosInterpolate(i4, i5, fractionalZ),

        i7 = cosInterpolate(i3, i6, fractionalY);
  return i7;
}

static inline float noise_perlin3d(float x, float y, float z, float persistance, int octaves) {
  float total = 0.0;
  for (int i = 0; i < octaves; i++) {
    float freq = pow(2, i),
          amp = pow(persistance, i);
    total = total + noise_interpolated3d(x * freq, y * freq, z * freq) * amp;
  }
  return total * 0.1;
}

#ifdef __cplusplus
} // extern "C" {
#endif // __cplusplus
