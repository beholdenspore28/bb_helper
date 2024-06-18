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

#include "b_math.h"
#include <math.h>

float rad2deg (const float n) {
  return n * (180.0f / PI);
}

float deg2rad (const float n) {
  return n * (PI / 180.0f);
}

float wrapAngle (float a) {
  a = fmod (a, 2 * PI);
  if (a < 0) {
      a += 2 * PI;
    }
  return a;
}

float clamp (float n, const float min, const float max){
  n = n < min ? min : n;
  return n > max ? max : n;
}

float clamp01 (float n) {
  n = n < 0 ? 0 : n;
  return n > 1 ? 1 : n;
}

float lerp (float a, float b, float t) {
  return a + (b - a) * t;
}

float lerpclamped (float a, float b, float t) {
  return a + (b - a) * clamp01 (t);
}

float norm (float n, float min, float max) {
  return (n - min) / (max - min);
}

float map (float n, float fromMin, float fromMax, float toMin, float toMax) {
  return lerp (norm (n, fromMin, fromMax), toMin, toMax);
}

bool aproxequal (float a, float b, float tolerance) {
  return (fabs (a - b) < tolerance);
}

float cosInterpolate (float a, float b, float t) {
  float f = (1.0f - cos (t * PI)) * 0.5f;
  return a * (1.0 - f) + b * f;
}

float sigmoid (float n) {
  return (1 / (1 + pow (2.71828182846, -n)));
}

float loop (float n, const float length) {
  return clamp (n - floor (n / length) * length, 0.0f, length);
}

float pingpong (float n, const float length) {
  n = loop (n, length * 2.0f);
  return fabs (n - length);
}

float angleDelta (const float a, const float b) {
  float delta = loop ((b - a), 360.0f);
  if (delta > 180.0f)
    {
      delta -= 360.0f;
    }
  return delta;
}


/*BEGIN SINGLE DIMENSIONAL*/

float noise_1d (int x) {
  x = (x << 13) ^ x;
  return (1.0
          - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7FFFFFFF)
                / 1073741824.0);
}

float noise_smoothed1d (float x) {
  return noise_1d (x) / 2 + noise_1d (x - 1) / 4 + noise_1d (x + 1) / 4;
}

float noise_interpolated1d (float x) {
  int integer_X = (int)x;
  float fractional_X = x - integer_X;
  float v1 = noise_smoothed1d (integer_X);
  float v2 = noise_smoothed1d (integer_X + 1);
  return cosInterpolate (v1, v2, fractional_X);
}

float noise_perlin1d (float x, float persistance, int octaves) {
  persistance *= 0.5f;
  persistance = clamp (persistance, 0.0f, 1.0f);
  float total = 0.0f;
  int n = octaves - 1;

  int i = 0;
  float freq = 0.0f;
  float amp = 0.0f;
  for (i = 0; i < n; i++)
    {
      freq = pow (2, i);
      amp = pow (persistance, i);

      total = total + noise_interpolated1d (x * freq) * amp;
    }
  total = (total + 1) * 0.5f;
  assert (total <= 1);
  assert (total >= -1);
  return total;
}
/*END SINGLE DIMENSIONAL*/

/*BEGIN TWO DIMENSIONAL*/

float noise_2d (int x, int y) {
  int n = x + y * 57;
  n = (n << 13) ^ n;
  return (1.0
          - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7FFFFFFF)
                / 1073741824.0);
}

float noise_smoothed2d (float x, float y) {
  float corners = (noise_2d (x - 1, y - 1) + noise_2d (x + 1, y - 1)
                   + noise_2d (x - 1, y + 1) + noise_2d (x + 1, y + 1))
                  / 16;
  float sides = (noise_2d (x - 1, y) + noise_2d (x + 1, y)
                 + noise_2d (x, y - 1) + noise_2d (x, y + 1))
                / 8;

  float center = noise_2d (x, y) / 4;
  return corners + sides + center;
}

float noise_interpolated2d (float x, float y) {
  int integer_X = (int)x;
  float fractional_X = x - integer_X;

  int integer_Y = (int)y;
  float fractional_Y = y - integer_Y;

  float v1 = noise_smoothed2d (integer_X, integer_Y);
  float v2 = noise_smoothed2d (integer_X + 1, integer_Y);
  float v3 = noise_smoothed2d (integer_X, integer_Y + 1);
  float v4 = noise_smoothed2d (integer_X + 1, integer_Y + 1);

  float i1 = cosInterpolate (v1, v2, fractional_X);
  float i2 = cosInterpolate (v3, v4, fractional_X);

  return cosInterpolate (i1, i2, fractional_Y);
}

float noise_perlin2d (float x, float y, float persistance, int octaves) {
  persistance *= 0.5f;
  persistance = clamp (persistance, 0.0f, 1.0f);
  float total = 0.0f;
  float n = octaves - 1;

  int i = 0;
  float freq = 0.0f;
  float amp = 0.0f;
  for (i = 0; i < n; i++)
    {
      freq = pow (2, i);
      amp = pow (persistance, i);

      total = total + noise_interpolated2d (x * freq, y * freq) * amp;
    }
  total = (total + 1) * 0.5f;
  assert (total <= 1);
  assert (total >= -1);
  return total;
}

/*END TWO DIMENSIONAL*/
