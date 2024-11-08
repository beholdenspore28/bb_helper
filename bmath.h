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

static inline float cosInterpolate(float a, float b, float t) {
  float f = (1.0f - cos(t * PI)) * 0.5f;
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

static inline float fraction(float x) {
  int i = (int)x;
  return x - i;
}

// Single dimensional pseudo-random noise
static inline float noise1(int x) {
  float wave = sinf(x*100)*5647;
  return fraction(wave);
}

// Two dimensional pseudo-random noise
static inline float noise2(int x, int y) {
  float wave = sinf(x*100+y*6574)*5647;
  return fraction(wave);
}

// Three dimensional pseudo-random noise
static inline float noise3(int x, int y, int z) {
  float wave = sinf(x*2951+y*69905+z*9214)*53647;
  return fraction(wave);
}

// Three dimensional pseudo-random noise
#if 0
static inline float noise3_smooth(float x, float y, float z) {
  float wave = 
    (noise3(x, y, z) +
     noise3(x,   y-1, z+1) +
     noise3(x,   y-1, z+1) +
     noise3(x,   y+1, z+1) +
     noise3(x,   y+1, z+1) +
     noise3(x,   y-1, z-1) +
     noise3(x,   y-1, z-1) +
     noise3(x,   y+1, z-1) +
     noise3(x,   y+1, z-1) +
     noise3(x-1, y,   z+1) +
     noise3(x+1, y,   z+1) +
     noise3(x-1, y,   z+1) +
     noise3(x+1, y,   z+1) +
     noise3(x-1, y,   z-1) +
     noise3(x+1, y,   z-1) +
     noise3(x-1, y,   z-1) +
     noise3(x+1, y,   z-1) +
     noise3(x-1, y-1, z  ) +
     noise3(x+1, y-1, z  ) +
     noise3(x-1, y+1, z  ) +
     noise3(x+1, y+1, z  ) +
     noise3(x-1, y-1, z  ) +
     noise3(x+1, y-1, z  ) +
     noise3(x-1, y+1, z  ) +
     noise3(x+1, y+1, z  ) +
     noise3(x-1, y-1, z+1) +
     noise3(x+1, y-1, z+1) +
     noise3(x-1, y+1, z+1) +
     noise3(x+1, y+1, z+1) +
     noise3(x-1, y-1, z-1) +
     noise3(x+1, y-1, z-1) +
     noise3(x-1, y+1, z-1) +
     noise3(x+1, y+1, z-1) ) / 64;
  return wave;
}
#else
static inline float noise3_lerp(float x, float y, float z) {
  float c = noise3(x, y, z);

  float fractX = fraction(x);
  float fractY = fraction(y);
  float fractZ = fraction(z);

  float floorX = floor(x);
  float floorY = floor(y);
  float floorZ = floor(z);

  float bbl = noise3(floorX, floorY, floorZ);
  float bbr = noise3(floorX + 1, floorY, floorZ);
  float bb = cosInterpolate(bbl, bbr, fractX);

  float btl = noise3(floorX, floorY + 1, floorZ);
  float btr = noise3(floorX + 1, floorY + 1, floorZ);
  float bt = cosInterpolate(btl, btr, fractX);

  float fbl = noise3(floorX, floorY, floorZ);
  float fbr = noise3(floorX + 1, floorY, floorZ);
  float fb = cosInterpolate(fbl, fbr, fractX);

  float ftl = noise3(floorX, floorY + 1, floorZ);
  float ftr = noise3(floorX + 1, floorY + 1, floorZ);
  float ft = cosInterpolate(ftl, ftr, fractX);

  float fbt = cosInterpolate(fb, ft, fractY);
  float bbt = cosInterpolate(bb, bt, fractY);

  float fbtbbt = cosInterpolate(fbt, bbt, fractZ);
  return fbtbbt / 50; 
}
#endif

static inline float noise3_perlin(float x, float y, float z) {
  float total = 0.0;
  float freq = 1.0;
  float amplitude = 1.0;
  float persistance = 0.25;
  int octaves = 4;
  for (int i = 0; i < octaves; i++) {
    freq = pow(2, i);
    amplitude = pow(persistance, i);
    total += noise3_smooth(x*freq, y*freq, z*freq) * amplitude; 
  }
  return total;
}

#ifdef __cplusplus
} // extern "C" {
#endif // __cplusplus
