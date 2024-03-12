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

#if !defined(B_MATH_H)
#define B_MATH_H

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

/*
General floating point math functions
TODO    LerpAngle	Same as Lerp but makes sure the values interpolate
correctly
        when they wrap around 360 degrees.
TODO    MoveTowards	Moves a value current towards target.
TODO    MoveTowardsAngle	Same as MoveTowards but makes sure the values
        interpolate correctly when they wrap around 360 degrees.
TODO    SmoothDamp	Gradually changes a value towards a desired goal over
time.
TODO    SmoothDampAngle	Gradually changes an angle given in degrees towards a
        desired goal angle over time.
TODO    SmoothStep	Interpolates between min and max with smoothing at the
        limits.
*/

#if !defined(PI)
#define PI 3.14159265358
#endif

#if !defined(TAU)
#define TAU 6.28318530718
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

/*TODO Vec2_min()*/
/*TODO Vec2_max()*/

/*A small data structure for storing 2D positions, rotations, scales,
 * or lines.*/
typedef struct
{
  float x;
  float y;
} Vec2;

/*A small data structure for storing 3D positions, rotations, scales,
 * or lines.*/
typedef struct
{
  float x;
  float y;
  float z;
} Vec3;

/*A small data structure for storing 4D values*/
typedef struct
{
  float x;
  float y;
  float z;
  float w;
} Vec4;

#define VEC2_ZERO                                                             \
  (Vec2) { 0.0f, 0.0f }
#define VEC2_ONE                                                              \
  (Vec2) { 1.0f, 1.0f }
#define VEC2_UP                                                               \
  (Vec2) { 0.0f, 1.0f }
#define VEC2_DOWN                                                             \
  (Vec2) { 0.0f, -1.0f }
#define VEC2_LEFT                                                             \
  (Vec2) { -1.0f, 0.0f }
#define VEC2_RIGHT                                                            \
  (Vec2) { 1.0f, 0.0f }

#define VEC3_ZERO                                                             \
  (Vec3) { 0.0f, 0.0f, 0.0f }
#define VEC3_ONE                                                              \
  (Vec3) { 1.0f, 1.0f, 1.0f }
#define VEC3_UP                                                               \
  (Vec3) { 0.0f, 1.0f, 0.0f }
#define VEC3_DOWN                                                             \
  (Vec3) { 0.0f, -1.0f, 0.0f }
#define VEC3_LEFT                                                             \
  (Vec3) { -1.0f, 0.0f, 0.0f }
#define VEC3_RIGHT                                                            \
  (Vec3) { 1.0f, 0.0f, 0.0f }
#define VEC3_FORWARD                                                          \
  (Vec3) { 0.0f, 0.0f, 1.0f }
#define VEC3_BACK                                                             \
  (Vec3) { 0.0f, 0.0f, -1.0f }

#define VEC4_ZERO                                                             \
  (Vec4) { 0.0f, 0.0f, 0.0f, 1.0f }
#define VEC4_ONE                                                              \
  (Vec4) { 1.0f, 1.0f, 1.0f, 1.0f }
#define VEC4_UP                                                               \
  (Vec4) { 0.0f, 1.0f, 0.0f, 1.0f }
#define VEC4_DOWN                                                             \
  (Vec4) { 0.0f, -1.0f, 0.0f, 1.0f }
#define VEC4_LEFT                                                             \
  (Vec4) { -1.0f, 0.0f, 0.0f, 1.0f }
#define VEC4_RIGHT                                                            \
  (Vec4) { 1.0f, 0.0f, 0.0f, 1.0f }
#define VEC4_FORWARD                                                          \
  (Vec4) { 0.0f, 0.0f, 1.0f, 1.0f }
#define VEC4_BACK                                                             \
  (Vec4) { 0.0f, 0.0f, -1.0f, 1.0f }

///*shorthand for vector2 (0, 0)*/
// extern const Vec2 BLIB_VEC2F_ZERO;
//
///*shorthand for vector2 (1, 1)*/
// extern const Vec2 BLIB_VEC2F_ONE;
//
///*shorthand for vector2 (0, 1)*/
// extern const Vec2 BLIB_VEC2F_UP;
//
///*shorthand for vector2 (0,-1)*/
// extern const Vec2 BLIB_VEC2F_DOWN;
//
///*shorthand for vector2 (-1,0)*/
// extern const Vec2 BLIB_VEC2F_LEFT;
//
///*shorthand for vector2 (1, 0)*/
// extern const Vec2 BLIB_VEC2F_RIGHT;

/*Prints a vector "v" using printf*/
void Vec2_printf (const Vec2 v, const char *label);

/*Returns a vector that points in the opposite direction of the given vector
"v". The vector returned has a magnitude identical to the given vector "v"*/
Vec2 Vec2_negate (Vec2 v);

/*Returns the actual length of a vector "v".
This uses a square root operation. Use Vec2_sqrmagnitude()
to sacrifice accuracy and save on performance when comparing
distances.*/
float Vec2_magnitude (Vec2 v);

/*A more performant way of getting the relative length of a
vector "v". This saves a square root operation making it more
performant than Vec2_magnitude(). If all you have to do is
compare a vectors length relatively, use this function instead of
Vec2_magnitude()*/
float Vec2_sqrmagnitude (Vec2 v);

/*Returns a given vector "v" as a unit vector.
This means the magnitude(length) of the returned
vector will always be 1 unit. The returned vector always points
in the same direction as the given vector "v"*/
Vec2 Vec2_normalize (Vec2 v);

/*Returns the distance between point a and point b
in units.*/
float Vec2_distance (Vec2 a, Vec2 b);

/*Adds a vector "a" to another vector "b"*/
Vec2 Vec2_add (Vec2 a, Vec2 b);

/*Subtracts a vector "subtrahend" from another vector "minuend"*/
Vec2 Vec2_subtract (Vec2 minuend, Vec2 subtrahend);

/*Scales a vector "v" by "scalar".
increases the magnitude when "scalar" is greater than 1.
decreases the magnitude when "scalar" is less than 0.
The returned vector will point in the same direction as
the given vector "v".*/
Vec2 Vec2_scale (Vec2 v, float scalar);

/*For normalized vectors Dot returns 1 if they point in
exactly the same direction, -1 if they point in completely opposite directions
and zero if the vectors are perpendicular.*/
float Vec2_dot (Vec2 a, Vec2 b);

/*Linearly interpolates between "a" and "b" by "t".
If you want to make sure the returned value stays
between "a" and "b", use Vec3_lerpclamped() instead.
Returns a point at "t"% of the way between "a" and "b".*/
Vec2 Vec2_lerp (Vec2 a, Vec2 b, float t);

/*Linearly interpolates between "a" and "b" by "t".
Returns a point at "t"% of the way between "a" and "b".*/
Vec2 Vec2_lerpclamped (Vec2 a, Vec2 b, float t);

/*Converts a 2 dimensional vector to a 3 dimensional one*/
Vec3 Vec2_toVec3f (Vec2 v);

/*Converts a 2 dimensional vector to a 4 dimensional one*/
Vec4 Vec2_toVec4f (Vec2 v);

/*
TODO MoveTowards	Calculate a position between the points specified by
current
and target, moving no farther than the distance specified by maxDistanceDelta.
TODO Slerp	Spherically interpolates between two vectors.
TODO ClampMagnitude	Returns a copy of vector with its magnitude clamped to
maxLength.
TODO Angle	Calculates the angle between vectors from and.
TODO LerpUnclamped	Linearly interpolates between two vectors.
TODO Max	Returns a vector that is made from the largest components of
two vectors.
TODO Min	Returns a vector that is made from the smallest components of
two vectors.
TODO OrthoNormalize	Makes vectors normalized and orthogonal to each other.
TODO Project	Projects a vector onto another vector.
TODO ProjectOnPlane	Projects a vector onto a plane defined by a normal
orthogonal to the plane.
TODO Reflect	Reflects a vector off the plane defined by a normal.
TODO RotateTowards	Rotates a vector current towards target.
TODO SignedAngle	Calculates the signed angle between vectors from and to
in relation to axis.
TODO SlerpUnclamped	Spherically interpolates between two vectors.
TODO SmoothDamp	Gradually changes a vector towards a desired goal over time.

currentTilt = 0f;
float smoothTime = 0.3f;
float refTilt = 0f
currentTilt = Mathf.SmoothDamp(currentTilt, tiltAmount*horizontalInput,
ref refTilt, smoothTime);
transform.localRotation = Quaternion.Euler(0, 0, currentTilt);
*/

///*shorthand for vector3 (0, 0, 0)*/
// extern const Vec3 BLIB_VEC3F_ZERO;
//
///*shorthand for vector3 (0, 1, 0)*/
// extern const Vec3 BLIB_VEC3F_UP;
//
///*shorthand for vector3 (0,-1, 0)*/
// extern const Vec3 BLIB_VEC3F_DOWN;
//
///*shorthand for vector3 (-1,0, 0)*/
// extern const Vec3 BLIB_VEC3F_LEFT;
//
///*shorthand for vector3 (1, 0, 0)*/
// extern const Vec3 BLIB_VEC3F_RIGHT;
//
///*shorthand for vector3 (0, 0, 1)*/
// extern const Vec3 BLIB_VEC3F_FORWARD;
//
///*shorthand for vector3 (0, 0,-1)*/
// extern const Vec3 BLIB_VEC3F_BACK;
//
///*shorthand for vector3 (1, 1, 1)*/
// extern const Vec3 BLIB_VEC3F_ONE;

/*Prints a vector "v" using printf*/
void Vec3_printf (const Vec3 v, const char *label);

/*Returns a vector that points in the opposite direction of the given vector
"v". The vector returned has a magnitude identical to the given vector "v"*/
Vec3 Vec3_negate (Vec3 v);

/*Returns the actual length of a vector "v".
This uses a square root operation. Use Vec3_sqrmagnitude()
to sacrifice accuracy and save on performance when comparing
distances.*/
float Vec3_magnitude (Vec3 v);

/*A more performant way of getting the relative length of a
vector "v". This saves a square root operation making it more
performant than Vec3_magnitude(). If all you have to do is
compare a vectors length relatively, use this function instead of
Vec3_magnitude()*/
float Vec3_sqrmagnitude (Vec3 v);

/*Returns a given vector "v" as a unit vector.
This means the magnitude(length) of the returned
vector will always be 1 unit. The returned vector always points
in the same direction as the given vector "v"*/
Vec3 Vec3_normalize (Vec3 v);

/*Returns the distance between point a and point b
in units.*/
float Vec3_distance (Vec3 a, Vec3 b);

/*Adds a vector "a" to another vector "b"*/
Vec3 Vec3_add (Vec3 a, Vec3 b);

/*Subtracts a vector "subtrahend" from another vector "minuend"*/
Vec3 Vec3_subtract (Vec3 minuend, Vec3 subtrahend);

/*Scales a vector "v" by "scalar".
increases the magnitude when "scalar" is greater than 1.
decreases the magnitude when "scalar" is less than 1.
The returned vector will point in the same direction as
the given vector "v".*/
Vec3 Vec3_scale (Vec3 v, float scalar);

/*Returns a vector parallel to both "a" and "b".*/
Vec3 Vec3_cross (Vec3 a, Vec3 b);

/*For normalized vectors Dot returns 1 if they point in
exactly the same direction, -1 if they point in completely opposite directions
and zero if the vectors are perpendicular.*/
float Vec3_dot (Vec3 a, Vec3 b);

/*Linearly interpolates between "a" and "b" by "t".
If you want to make sure the returned value stays
between "a" and "b", use Vec2_lerpclamped() instead.
Returns a point at "t"% of the way between "a" and "b".*/
Vec3 Vec3_lerp (Vec3 a, Vec3 b, float t);

/*Linearly interpolates between "a" and "b" by "t".
Returns a point at "t"% of the way between "a" and "b".*/
Vec3 Vec3_lerpclamped (Vec3 a, Vec3 b, float t);

/*Returns a vector that is made from the largest components of two
vectors.*/
Vec3 Vec3_max (Vec3 a, Vec3 b);

/*Returns a vector that is made from the smallest components of two
vectors.*/
Vec3 Vec3_min (Vec3 a, Vec3 b);

/*Converts a 3 dimensional vector to a 2 dimensional one*/
Vec2 Vec3_toVec2f (Vec3 v);

/*Converts a 3 dimensional vector to a 4 dimensional one*/
Vec4 Vec3_toVec4f (Vec3 v);

///*shorthand for vector4 (0, 0, 0, 0)*/
// extern const Vec4 BLIB_VEC4F_ZERO;
//
///*shorthand for vector4 (0, 1, 0, 1)*/
// extern const Vec4 BLIB_VEC4F_UP;
//
///*shorthand for vector4 (0,-1, 0, 1)*/
// extern const Vec4 BLIB_VEC4F_DOWN;
//
///*shorthand for vector4 (-1,0, 0, 1)*/
// extern const Vec4 BLIB_VEC4F_LEFT;
//
///*shorthand for vector4 (1, 0, 0, 1)*/
// extern const Vec4 BLIB_VEC4F_RIGHT;
//
///*shorthand for vector4 (0, 0, 1, 1)*/
// extern const Vec4 BLIB_VEC4F_FORWARD;
//
///*shorthand for vector4 (0, 0,-1, 1)*/
// extern const Vec4 BLIB_VEC4F_BACK;
//
///*shorthand for vector4 (1, 1, 1, 1)*/
// extern const Vec4 BLIB_VEC4F_ONE;

/*Prints a vector "v" using printf*/
void Vec4_printf (const Vec4 v, const char *label);

/*Returns a vector that points in the opposite direction of the given vector
"v". The vector returned has a magnitude identical to the given vector "v"*/
Vec4 Vec4_negate (Vec4 v);

/*Returns the actual length of a vector "v".
This uses a square root operation. Use Vec4_sqrmagnitude()
to sacrifice accuracy and save on performance when comparing
distances.*/
float Vec4_magnitude (Vec4 v);

/*A more performant way of getting the relative length of a
vector "v". This saves a square root operation making it more
performant than Vec4_magnitude(). If all you have to do is
compare a vectors length relatively, use this function instead of
Vec4_magnitude()*/
float Vec4_sqrmagnitude (Vec4 v);

/*Returns a given vector "v" as a unit vector.
This means the magnitude(length) of the returned
vector will always be 1 unit. The returned vector always points
in the same direction as the given vector "v"*/
Vec4 Vec4_normalize (Vec4 v);

/*Returns the distance between point a and point b
in units.*/
float Vec4_distance (Vec4 a, Vec4 b);

/*Adds a vector "a" to another vector "b"*/
Vec4 Vec4_add (Vec4 a, Vec4 b);

/*Subtracts a vector "subtrahend" from another vector "minuend"*/
Vec4 Vec4_subtract (Vec4 minuend, Vec4 subtrahend);

/*Scales a vector "v" by "scalar".
increases the magnitude when "scalar" is greater than 1.
decreases the magnitude when "scalar" is less than 1.
The returned vector will point in the same direction as
the given vector "v".*/
Vec4 Vec4_scale (Vec4 v, float scalar);

/*For normalized vectors Dot returns 1 if they point in
exactly the same direction, -1 if they point in completely opposite directions
and zero if the vectors are perpendicular.*/
float Vec4_dot (Vec4 a, Vec4 b);

/*Linearly interpolates between "a" and "b" by "t".
If you want to make sure the returned value stays
between "a" and "b", use Vec2_lerpclamped() instead.
Returns a point at "t"% of the way between "a" and "b".*/
Vec4 Vec4_lerp (Vec4 a, Vec4 b, float t);

/*Linearly interpolates between "a" and "b" by "t".
Returns a point at "t"% of the way between "a" and "b".*/
Vec4 Vec4_lerpclamped (Vec4 a, Vec4 b, float t);

/*Returns a vector that is made from the largest components of two
vectors.*/
Vec4 Vec4_max (Vec4 a, Vec4 b);

/*Returns a vector that is made from the smallest components of two
vectors.*/
Vec4 Vec4_min (Vec4 a, Vec4 b);

/*Converts a 4 dimensional vector to a 2 dimensional one*/
Vec2 Vec4_toVec2f (Vec4 v);

/*Converts a 4 dimensional vector to a 3 dimensional one*/
Vec3 Vec4_toVec3f (Vec4 v);

/*A column major 4x4 matrix*/
typedef struct
{
  float elements[16];
} Mat4;

extern const Mat4 BLIB_MAT4_IDENTITY;

Mat4 Mat4_lookAt (Vec3 eye, Vec3 center, Vec3 up);
/*Perspective transformation used for calculating depth*/
Mat4 Mat4_perspective (float fov, float aspect, float near, float far);
/*Adds a 4x4 matrix to another 4x4 matrix.*/
Mat4 Mat4_add (Mat4 a, Mat4 b);

/*Returns the difference between two 4x4 matrices.*/
Mat4 Mat4_subtract (Mat4 min, Mat4 sub);

/*Prints a formatted Mat4 to the console.*/
void Mat4_printf (Mat4 m, const char *label);

/*Scales (multiplies) a 4x4 matrix by a scalar (number)*/
Mat4 Mat4_scale (const Vec3 scale);

/*Returns a rotation matrix around "axis" by "angle"*/
Mat4 Mat4_rotate (const float angle, Vec3 axis);

/*Translates a vector to a 4x4 matrix*/
Mat4 Mat4_translateVec3 (Vec3 t);

/*Translates a vector to a 4x4 matrix*/
Mat4 Mat4_translateVec4 (Vec4 t);

/*Multiplies a 4x4 matrix with another 4x4 matrix*/
Mat4 Mat4_multiply (const Mat4 a, const Mat4 b);

#endif /*B_MATH_H*/
