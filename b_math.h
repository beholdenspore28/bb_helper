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
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*Returns completely raw, random, single-dimensional noise values*/
float noise_1d (int x);

/*Returns smoothed single-dimensional noise values*/
float noise_smoothed1d (float x);

/*Returns smoothed and interpolated single-dimensional noise values*/
float noise_interpolated1d (float x);

/*Returns perlin-ish single-dimensional noise values.*/
float noise_perlin1d (float x, float persistance, int octaves);

/*Returns completely raw, random, two-dimensional noise values*/
float noise_2d (int x, int y);

/*Returns smoothed two-dimensional noise values*/
float noise_smoothed2d (float x, float y);

/*Returns smoothed and interpolated two-dimensional noise values*/
float noise_interpolated2d (float x, float y);

/*Returns perlin-ish two-dimensional noise values.*/
float noise_perlin2d (float x, float y, float persistance, int octaves);

#if !defined(PI)
#define PI 3.14159265358
#endif

/*Converts "n" radians into degrees.*/
float rad2deg (const float n);

/*Converts "n" degrees into radians*/
float deg2rad (const float n);

float wrapAngle (float a);

/*Returns "n" clamped between min and max*/
float clamp (float n, const float min, const float max);

/*Returns "n" clamped between 0 and 1*/
float clamp01 (float n);

/*Linearly interpolates between "a" and "b" by "t"*/
float lerp (float a, float b, float t);

/*Linearly interpolates between "a" and "b" by "t".
"t" is always clamped between 0 and 1 before performing the interpolation.*/
float lerpclamped (float a, float b, float t);

/*Returns the percentage of "n" from "min" to "max".*/
float norm (float n, float min, float max);

/*Converts a percentage of one range to a percentage of another.*/
float map (float n, float fromMin, float fromMax, float toMin, float toMax);

/*It is very rare that one floating point number is exactly the same as
 * another. This function will check if two numbers are similar enough to be
 * considered equal. Returns true if the absolute value of "a" minus the
 * absolute value of "b" is less than "tolerance".*/
bool aproxEqual (float a, float b, float tolerance);

/*Interpolation using cosine*/
float cosInterpolate (float a, float b, float t);

/*Returns a point along the sigmoid (logistic) curve*/
float sigmoid (float n);

/*Ensures a number will stay between a certain range. Unlike clamp, the number
 * will wrap back around to 0 when it is greater than "length"*/
float loop (float n, const float length);

/*Ensures a number will stay between a certain range. Unlike clamp, the number
 * will bounce back and fourth between 0 and "length"*/
float pingpong (float n, const float length);

/*Returns the smallest possible difference between angle "a" and angle "b"*/
float angleDelta (const float a, const float b);
