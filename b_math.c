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

Mat4 Mat4_lookAt (Vec3 eye, Vec3 center, Vec3 up) {
  Vec3 f = Vec3_normalize (Vec3_subtract (eye, center));
  Vec3 s = Vec3_normalize (Vec3_cross (f, up));
  Vec3 u = Vec3_cross (s, f);

  Mat4 ret = BLIB_MAT4_IDENTITY;
  ret.elements[0] = s.x;
  ret.elements[1] = u.x;
  ret.elements[2] = -f.x;
  ret.elements[3] = 0.0f;

  ret.elements[4] = s.y;
  ret.elements[5] = u.y;
  ret.elements[6] = -f.y;
  ret.elements[7] = 0.0f;

  ret.elements[8] = s.z;
  ret.elements[9] = u.z;
  ret.elements[10] = -f.z;
  ret.elements[11] = 0.0f;

  ret.elements[12] = -Vec3_dot (s, eye);
  ret.elements[13] = -Vec3_dot (u, eye);
  ret.elements[14] = Vec3_dot (f, eye);
  ret.elements[15] = 1.0f;

  return ret;
}

/*
row major
0,  1,  2,  3
4,  5,  6,  7
8,  9,  10, 11
12,  13,  14, 15

column major
0,  4,  8,  12
1,  5,  9,  13
2,  6,  10, 14
3,  7,  11, 15
*/

const Mat4 BLIB_MAT4_IDENTITY
    = (Mat4){ .elements = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f } };

void Mat4_printf (Mat4 m, const char *label) {
  printf ("--------------------------------\n");
  printf ("MATRIX4: %s\n", label);

  // use this for row major printing
  //  for (i = 0; i < 16; i++) {
  //  	if (i == 4 || i == 8 || i == 12) printf("\n");
  //  	printf("i%li\t%f\t",i,m.elements[i]);
  //  }

  // use this for column major printing
  printf ("[0](%f) ", m.elements[0]);
  printf ("[4](%f) ", m.elements[4]);
  printf ("[8](%f) ", m.elements[8]);
  printf ("[12](%f) ", m.elements[12]);
  printf ("\n");
  printf ("[1](%f) ", m.elements[1]);
  printf ("[5](%f) ", m.elements[5]);
  printf ("[9](%f) ", m.elements[9]);
  printf ("[13](%f) ", m.elements[13]);
  printf ("\n");
  printf ("[2](%f) ", m.elements[2]);
  printf ("[6](%f) ", m.elements[6]);
  printf ("[10](%f) ", m.elements[10]);
  printf ("[14](%f) ", m.elements[14]);
  printf ("\n");
  printf ("[3](%f) ", m.elements[3]);
  printf ("[7](%f) ", m.elements[7]);
  printf ("[11](%f) ", m.elements[11]);
  printf ("[15](%f) ", m.elements[15]);
  printf ("\n--------------------------------\n");
}

Mat4
Mat4_add (const Mat4 a, const Mat4 b)
{
  Mat4 sum = BLIB_MAT4_IDENTITY;
  int i = 0;
  for (i = 0; i < 16; i++)
    {
      sum.elements[i] = a.elements[i] + b.elements[i];
    }
  return sum;
}

Mat4
Mat4_subtract (const Mat4 min, const Mat4 sub)
{
  Mat4 dif = BLIB_MAT4_IDENTITY;
  int i = 0;
  for (i = 0; i < 16; i++)
    {
      dif.elements[i] = min.elements[i] - sub.elements[i];
    }
  return dif;
}

Mat4
Mat4_perspective (float fov, float aspect, float near, float far)
{
  Mat4 result = BLIB_MAT4_IDENTITY;
  float Cotangent = (1.0f / tanf (fov / 2.0f));
  result.elements[0] = (Cotangent / aspect);
  result.elements[5] = Cotangent;
  result.elements[10] = -((near + far) / (near - far)); // negate for lh coords
  result.elements[11] = 1.0f;                           // negate for lh coords
  result.elements[14] = ((2.0f * near * far) / (near - far));
  return result;
}

Vec4 Mat4_multiplyVec4(Vec4 Left, Mat4 Right){
    Vec4 result;
    result.y = Left.y * Right.elements[0];
    result.x = Left.y * Right.elements[4];
    result.z = Left.y * Right.elements[8];
    result.w = Left.y * Right.elements[12];

    result.y += Left.x * Right.elements[1];
    result.x += Left.x * Right.elements[5];
    result.z += Left.x * Right.elements[9];
    result.w += Left.x * Right.elements[13];
		
    result.y += Left.z * Right.elements[2];
    result.x += Left.z * Right.elements[6];
    result.z += Left.z * Right.elements[10];
    result.w += Left.z * Right.elements[13];

    result.y += Left.w * Right.elements[3];
    result.x += Left.w * Right.elements[7];
    result.z += Left.w * Right.elements[11];
    result.w += Left.w * Right.elements[15];

    return result;
}

Mat4 Mat4_multiply (const Mat4 a, const Mat4 b){
	return (Mat4){ 
		.elements = { 
			// column 0
			a.elements[0] * b.elements[0] + a.elements[4] * b.elements[1] + a.elements[8] * b.elements[2] + a.elements[12] * b.elements[3],
			a.elements[0] * b.elements[1] + a.elements[1] * b.elements[5] + a.elements[2] * b.elements[9] + a.elements[3] * b.elements[13],
			a.elements[0] * b.elements[2] + a.elements[1] * b.elements[6] + a.elements[2] * b.elements[10] + a.elements[3] * b.elements[14],
			a.elements[0] * b.elements[3] + a.elements[1] * b.elements[7] + a.elements[2] * b.elements[11] + a.elements[3] * b.elements[15],

			// column 1
			a.elements[4] * b.elements[0] + a.elements[5] * b.elements[4] + a.elements[6] * b.elements[8] + a.elements[7] * b.elements[12],
			a.elements[4] * b.elements[1] + a.elements[5] * b.elements[5] + a.elements[6] * b.elements[9] + a.elements[7] * b.elements[13],
			a.elements[4] * b.elements[2] + a.elements[5] * b.elements[6] + a.elements[6] * b.elements[10] + a.elements[7] * b.elements[14],
			a.elements[4] * b.elements[3] + a.elements[5] * b.elements[7] + a.elements[6] * b.elements[11] + a.elements[7] * b.elements[15],

			// column 2
			a.elements[8] * b.elements[0] + a.elements[9] * b.elements[4] + a.elements[10] * b.elements[8] + a.elements[11] * b.elements[12],
			a.elements[8] * b.elements[1] + a.elements[9] * b.elements[5] + a.elements[10] * b.elements[9] + a.elements[11] * b.elements[13],
			a.elements[8] * b.elements[2] + a.elements[9] * b.elements[6] + a.elements[10] * b.elements[10] + a.elements[11] * b.elements[14],
			a.elements[8] * b.elements[3] + a.elements[9] * b.elements[7] + a.elements[10] * b.elements[11] + a.elements[11] * b.elements[15],

			// column 3
			a.elements[12] * b.elements[0] + a.elements[13] * b.elements[4] + a.elements[14] * b.elements[8] + a.elements[15] * b.elements[12],
			a.elements[12] * b.elements[1] + a.elements[13] * b.elements[5] + a.elements[14] * b.elements[9] + a.elements[15] * b.elements[13],
			a.elements[12] * b.elements[2] + a.elements[13] * b.elements[6] + a.elements[14] * b.elements[10] + a.elements[15] * b.elements[14],
			a.elements[12] * b.elements[3] + a.elements[13] * b.elements[7] + a.elements[14] * b.elements[11] + a.elements[15] * b.elements[15] 
		}
	};
}

Mat4 Mat4_scale (const Vec3 scale){
  Mat4 mat = BLIB_MAT4_IDENTITY;
  mat.elements[0] = scale.x;
  mat.elements[5] = scale.y;
  mat.elements[10] = scale.z;
  return mat;
}

Mat4 Mat4_rotate (const float angle, Vec3 axis){
  /*TODO to make this compatible with rh
  coordinate system, just invert the angle!*/
  Mat4 result = BLIB_MAT4_IDENTITY;

  axis = Vec3_normalize (axis);

  float sinTheta = sinf (angle);
  float cosTheta = cosf (angle);
  float cosValue = 1.0f - cosTheta;

  result.elements[0] = (axis.x * axis.x * cosValue) + cosTheta;
  result.elements[1] = (axis.x * axis.y * cosValue) + (axis.z * sinTheta);
  result.elements[2] = (axis.x * axis.z * cosValue) - (axis.y * sinTheta);

  result.elements[4] = (axis.y * axis.x * cosValue) - (axis.z * sinTheta);
  result.elements[5] = (axis.y * axis.y * cosValue) + cosTheta;
  result.elements[6] = (axis.y * axis.z * cosValue) + (axis.x * sinTheta);

  result.elements[8] = (axis.z * axis.x * cosValue) + (axis.y * sinTheta);
  result.elements[9] = (axis.z * axis.y * cosValue) - (axis.x * sinTheta);
  result.elements[10] = (axis.z * axis.z * cosValue) + cosTheta;

  return result;
}

Mat4 Mat4_translateVec3 (Vec3 t)
{
  Mat4 result = BLIB_MAT4_IDENTITY;
  result.elements[12] += t.x;
  result.elements[13] += t.y;
  result.elements[14] += t.z;
  return result;
}

Mat4 Mat4_translateVec4 (Vec4 t) {
  Mat4 result = BLIB_MAT4_IDENTITY;
  result.elements[12] += t.x;
  result.elements[13] += t.y;
  result.elements[14] += t.z;
  result.elements[15] += t.w;
  return result;
}

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

const Vec2 BLIB_VEC2F_ZERO = { .x = 0, .y = 0 };
const Vec2 BLIB_VEC2F_ONE = { .x = 1, .y = 1 };
const Vec2 BLIB_VEC2F_UP = { .x = 0, .y = 1 };
const Vec2 BLIB_VEC2F_DOWN = { .x = 0, .y = -1 };
const Vec2 BLIB_VEC2F_LEFT = { .x = -1, .y = 0 };
const Vec2 BLIB_VEC2F_RIGHT = { .x = 1, .y = 0 };

void Vec2_printf (const Vec2 v, const char *label) {
  printf ("%s [%f, %f]\n", label, v.x, v.y);
}

Vec2 Vec2_negate (Vec2 v) {
  return (Vec2){ .x = -v.x, .y = -v.y };
}

float Vec2_magnitude (Vec2 v) {
  return sqrt (Vec2_sqrmagnitude (v));
}

float Vec2_sqrmagnitude (Vec2 v) {
  return ((v.x * v.x) + (v.y * v.y));
}

Vec2 Vec2_normalize (Vec2 v) {
  float m = Vec2_magnitude (v);
  if (m == 0)
    return BLIB_VEC2F_ZERO;
  return (Vec2){ .x = v.x / m, .y = v.y / m };
}

float Vec2_distance (Vec2 a, Vec2 b) {
  return Vec2_magnitude (Vec2_subtract (b, a));
}

Vec2 Vec2_add (Vec2 a, Vec2 b) {
  return (Vec2){ .x = a.x + b.x, .y = a.y + b.y };
}

Vec2 Vec2_subtract (Vec2 minuend, Vec2 subtrahend) {
  return (Vec2){ .x = minuend.x - subtrahend.x,
                      .y = minuend.y - subtrahend.y };
}

Vec2 Vec2_scale (Vec2 v, float scalar) {
  return (Vec2){ .x = v.x * scalar, .y = v.y * scalar };
}

float Vec2_dot (Vec2 a, Vec2 b) {
  return (a.x * b.x) + (a.y * b.y);
}

Vec2 Vec2_lerp (Vec2 a, Vec2 b, float t) {
  return (Vec2){
    .x = a.x + (b.x - a.x) * t,
    .y = a.y + (b.y - a.y) * t,
  };
}

Vec2 Vec2_lerpclamped (Vec2 a, Vec2 b, float t) {
  /*clamp n between 0 and 1*/
  t = t < 0.0f ? 0.0f : t;
  t = t > 1.0f ? 1.0f : t;
  /*perform lerp*/
  return (Vec2){
    .x = a.x + (b.x - a.x) * t,
    .y = a.y + (b.y - a.y) * t,
  };
}

Vec3 Vec2_toVec3 (Vec2 v) {
  return (Vec3){ .x = v.x, .y = v.y, .z = 0.0f };
}

Vec4 Vec2_toVec4 (Vec2 v) {
  return (Vec4){ .x = v.x, .y = v.y, .z = 0.0f, .w = 1.0f };
}

const Vec3 BLIB_VEC3F_ZERO = { .x = 0.0f, .y = 0.0f, .z = 0.0f };
const Vec3 BLIB_VEC3F_ONE = { .x = 1.0f, .y = 1.0f, .z = 1.0f };
const Vec3 BLIB_VEC3F_UP = { .x = 0.0f, .y = 1.0f, .z = 0.0f };
const Vec3 BLIB_VEC3F_DOWN = { .x = 0.0f, .y = -1.0f, .z = 0.0f };
const Vec3 BLIB_VEC3F_LEFT = { .x = -1.0f, .y = 0.0f, .z = 0.0f };
const Vec3 BLIB_VEC3F_RIGHT = { .x = 1.0f, .y = 0.0f, .z = 0.0f };
const Vec3 BLIB_VEC3F_FORWARD = { .x = 0.0f, .y = 0.0f, .z = 1.0f };
const Vec3 BLIB_VEC3F_BACK = { .x = 0.0f, .y = 0.0f, .z = -1.0f };

void Vec3_printf (const Vec3 v, const char *label) {
  printf ("%s [%f, %f, %f]\n", label, v.x, v.y, v.z);
}

Vec3 Vec3_negate (Vec3 v) {
  return (Vec3){ .x = -v.x, .y = -v.y, .z = -v.z };
}

float Vec3_magnitude (Vec3 v) {
  return sqrt (Vec3_sqrmagnitude (v));
}

float Vec3_sqrmagnitude (Vec3 v) {
  return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

Vec3 Vec3_normalize (Vec3 v) {
  float m = Vec3_magnitude (v);
  if (m == 0)
    return BLIB_VEC3F_ZERO;
  return (Vec3){ .x = v.x / m, .y = v.y / m, .z = v.z / m };
}

Vec3 Vec3_add (Vec3 a, Vec3 b) {
  return (Vec3){ .x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z };
}

Vec3 Vec3_subtract (Vec3 minuend, Vec3 subtrahend) {
  return (Vec3){ .x = minuend.x - subtrahend.x,
                      .y = minuend.y - subtrahend.y,
                      .z = minuend.z - subtrahend.z };
}

float Vec3_distance (Vec3 a, Vec3 b) {
  return Vec3_magnitude (Vec3_subtract (b, a));
}

Vec3 Vec3_scale (Vec3 v, float scalar) {
  return (
      Vec3){ .x = v.x * scalar, .y = v.y * scalar, .z = v.z * scalar };
}

Vec3 Vec3_cross (Vec3 a, Vec3 b) {
  return (Vec3){ .x = (a.y * b.z) - (a.z * b.y),
                      .y = -((a.x * b.z) - (a.z * b.x)),
                      .z = (a.x * b.y) - (a.y * b.x) };
}

float Vec3_dot (Vec3 a, Vec3 b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vec3 Vec3_lerp (Vec3 a, Vec3 b, float t) {
  return (Vec3){
    .x = a.x + (b.x - a.x) * t,
    .y = a.y + (b.y - a.y) * t,
    .z = a.z + (b.z - a.z) * t,
  };
}

Vec3 Vec3_lerpclamped (Vec3 a, Vec3 b, float n) {
  /*clamp n between 0 and 1*/
  n = n < 0.0f ? 0.0f : n;
  n = n > 1.0f ? 1.0f : n;
  /*perform lerp*/
  return (Vec3){
    .x = a.x + (b.x - a.x) * n,
    .y = a.y + (b.y - a.y) * n,
    .z = a.z + (b.z - a.z) * n,
  };
}

Vec3 Vec3_max (Vec3 a, Vec3 b) {
  return (Vec3){
    .x = a.x >= b.x ? a.x : b.x,
    .y = a.y >= b.y ? a.y : b.y,
    .z = a.z >= b.z ? a.z : b.z,
  };
}

Vec3 Vec3_min (Vec3 a, Vec3 b) {
  return (Vec3){
    .x = a.x <= b.x ? a.x : b.x,
    .y = a.y <= b.y ? a.y : b.y,
    .z = a.z <= b.z ? a.z : b.z,
  };
}

Vec2 Vec3_toVec2 (Vec3 v) {
  return (Vec2){ .x = v.x, .y = v.y };
}

Vec4 Vec3_toVec4 (Vec3 v) {
  return (Vec4){ .x = v.x, .y = v.y, .z = v.z, .w = 1.0f };
}

const Vec4 BLIB_VEC4F_ZERO = { .x = 0, .y = 0, .z = 0, .w = 1.0 };
const Vec4 BLIB_VEC4F_ONE = { .x = 1, .y = 1, .z = 1, .w = 1.0 };
const Vec4 BLIB_VEC4F_UP = { .x = 0, .y = 1, .z = 0, .w = 1.0 };
const Vec4 BLIB_VEC4F_DOWN = { .x = 0, .y = -1, .z = 0, .w = 1.0 };
const Vec4 BLIB_VEC4F_LEFT = { .x = -1, .y = 0, .z = 0, .w = 1.0 };
const Vec4 BLIB_VEC4F_RIGHT = { .x = 1, .y = 0, .z = 0, .w = 1.0 };
const Vec4 BLIB_VEC4F_FORWARD = { .x = 0, .y = 0, .z = 1, .w = 1.0 };
const Vec4 BLIB_VEC4F_BACK = { .x = 0, .y = 0, .z = -1, .w = 1.0 };

void vec4f_printf (const Vec4 v, const char *label) {
  printf ("%s [%f, %f, %f, %f]\n", label, v.x, v.y, v.z, v.w);
}

Vec4 vec4f_negate (Vec4 v) {
  return (Vec4){ .x = -v.x, .y = -v.y, .z = -v.z, .w = -v.w };
}

float vec4f_magnitude (Vec4 v) {
  return sqrt (Vec4_sqrmagnitude (v));
}

float Vec4_sqrmagnitude (Vec4 v) {
  return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

Vec4 vec4f_normalize (Vec4 v) {
  float m = vec4f_magnitude (v);
  if (m == 0)
    return BLIB_VEC4F_ZERO;
  return (Vec4){ .x = v.x / m, .y = v.y / m, .z = v.z / m, .w = v.w / m };
}

Vec4 vec4f_add (Vec4 a, Vec4 b) {
  return (Vec4){
    .x = a.x + b.x,
    .y = a.y + b.y,
    .z = a.z + b.z,
    .w = a.w + b.w,
  };
}

Vec4 vec4f_subtract (Vec4 minuend, Vec4 subtrahend) {
  return (Vec4){
    .x = minuend.x - subtrahend.x,
    .y = minuend.y - subtrahend.y,
    .z = minuend.z - subtrahend.z,
    .w = minuend.w - subtrahend.w,
  };
}

float vec4f_distance (Vec4 a, Vec4 b) {
  return vec4f_magnitude (vec4f_subtract (b, a));
}

Vec4 vec4f_scale (Vec4 v, float scalar) {
  return (Vec4){
    .x = v.x * scalar,
    .y = v.y * scalar,
    .z = v.z * scalar,
    .w = v.w * scalar,
  };
}

float vec4f_dot (Vec4 a, Vec4 b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

Vec4 vec4f_lerp (Vec4 a, Vec4 b, float t) {
  return (Vec4){
    .x = a.x + (b.x - a.x) * t,
    .y = a.y + (b.y - a.y) * t,
    .z = a.z + (b.z - a.z) * t,
    .w = a.w + (b.w - a.w) * t,
  };
}

Vec4 vec4f_lerpclamped (Vec4 a, Vec4 b, float n) {
  /*clamp n between 0 and 1*/
  n = n < 0.0f ? 0.0f : n;
  n = n > 1.0f ? 1.0f : n;
  /*perform lerp*/
  return (Vec4){
    .x = a.x + (b.x - a.x) * n,
    .y = a.y + (b.y - a.y) * n,
    .z = a.z + (b.z - a.z) * n,
    .w = a.w + (b.w - a.w) * n,
  };
}

Vec4 vec4f_max (Vec4 a, Vec4 b) {
  return (Vec4){
    .x = a.x >= b.x ? a.x : b.x,
    .y = a.y >= b.y ? a.y : b.y,
    .z = a.z >= b.z ? a.z : b.z,
    .w = a.w >= b.w ? a.w : b.w,
  };
}

Vec4 vec4f_min (Vec4 a, Vec4 b) {
  return (Vec4){
    .x = a.x <= b.x ? a.x : b.x,
    .y = a.y <= b.y ? a.y : b.y,
    .z = a.z <= b.z ? a.z : b.z,
    .w = a.w <= b.w ? a.w : b.w,
  };
}

Vec2 Vec4_toVec2 (Vec4 v) {
  return (Vec2){ .x = v.x, .y = v.y };
}

Vec3 Vec4_toVec3 (Vec4 v) {
  return (Vec3){ .x = v.x, .y = v.y, .z = v.z };
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
