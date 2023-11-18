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

#if !defined(BLIB_MATH_H)
#define BLIB_MATH_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>

/*Returns completely raw, random, single-dimensional noise values*/
float blib_noise_1d(int x);

/*Returns smoothed single-dimensional noise values*/
float blib_noise_smoothed1d(float x);

/*Returns smoothed and interpolated single-dimensional noise values*/
float blib_noise_interpolated1d(float x);

/*Returns perlin-ish single-dimensional noise values.*/
float blib_noise_perlin1d(float x, float persistance, int octaves);

/*Returns completely raw, random, two-dimensional noise values*/
float blib_noise_2d(int x, int y);

/*Returns smoothed two-dimensional noise values*/
float blib_noise_smoothed2d(float x, float y);

/*Returns smoothed and interpolated two-dimensional noise values*/
float blib_noise_interpolated2d(float x, float y);

/*Returns perlin-ish two-dimensional noise values.*/
float blib_noise_perlin2d(float x, float y, float persistance, int octaves);

/*
General floating point math functions
TODO    LerpAngle	Same as Lerp but makes sure the values interpolate 
correctly 
        when they wrap around 360 degrees.
TODO    MoveTowards	Moves a value current towards target.
TODO    MoveTowardsAngle	Same as MoveTowards but makes sure the values 
        interpolate correctly when they wrap around 360 degrees.
TODO    SmoothDamp	Gradually changes a value towards a desired goal over time.
TODO    SmoothDampAngle	Gradually changes an angle given in degrees towards a 
        desired goal angle over time.
TODO    SmoothStep	Interpolates between min and max with smoothing at the 
        limits.
*/

#if !defined(BLIB_PI)
#define BLIB_PI 3.14159265358
#endif

#if !defined(BLIB_TAU)
#define BLIB_TAU 6.28318530718
#endif

/*Converts "n" radians into degrees.*/
float blib_mathf_rad2deg(const float n);

/*Converts "n" degrees into radians*/
float blib_mathf_deg2rad(const float n);

float blib_mathf_wrapAngle(float a);

/*Returns "n" clamped between min and max*/
float blib_mathf_clamp(float n, const float min, const float max);

/*Returns "n" clamped between 0 and 1*/
float blib_mathf_clamp01(float n);

/*Linearly interpolates between "a" and "b" by "t"*/
float blib_mathf_lerp(float a, float b, float t);

/*Linearly interpolates between "a" and "b" by "t".
"t" is always clamped between 0 and 1 before performing the interpolation.*/
float blib_mathf_lerpclamped(float a, float b, float t);

/*Returns the percentage of "n" from "min" to "max".*/
float blib_mathf_norm(float n, float min, float max);

/*Converts a percentage of one range to a percentage of another.*/
float blib_mathf_map(
		float n, float fromMin, float fromMax, float toMin, float toMax);

/*It is very rare that one floating point number is exactly the same as 
 * another. This function will check if two numbers are similar enough to be 
 * considered equal. Returns true if the absolute value of "a" minus the 
 * absolute value of "b" is less than "tolerance".*/
bool blib_mathf_aproxequal(float a, float b, float tolerance);

/*Interpolation using cosine*/
float blib_mathf_cosInterpolate(float a, float b, float t);

/*Returns a point along the sigmoid (logistic) curve*/
float blib_mathf_sigmoid(float n);

/*Ensures a number will stay between a certain range. Unlike clamp, the number
 * will wrap back around to 0 when it is greater than "length"*/
float blib_mathf_loop(float n, const float length);

/*Ensures a number will stay between a certain range. Unlike clamp, the number
 * will bounce back and fourth between 0 and "length"*/
float blib_mathf_pingpong(float n, const float length);

/*Returns the smallest possible difference between angle "a" and angle "b"*/
float blib_mathf_angleDelta(const float a, const float b);

/*TODO vec2f_min()*/
/*TODO vec2f_max()*/

struct blib_vec2f_t;
typedef struct blib_vec2f_t blib_vec2f_t;

/*A small data structure for storing 2D positions, rotations, scales, 
 * or lines.*/
struct blib_vec2f_t{
  float x;
  float y;
};

struct blib_vec3f_t;
typedef struct blib_vec3f_t blib_vec3f_t;

/*A small data structure for storing 3D positions, rotations, scales, 
 * or lines.*/
struct blib_vec3f_t{
  float x;
  float y;
  float z;
};

struct blib_vec4f_t;
typedef struct blib_vec4f_t blib_vec4f_t;

/*A small data structure for storing 4D values*/
struct blib_vec4f_t{
  float x;
  float y;
  float z;
  float w;
};

/*shorthand for vector2 (0, 0)*/
extern const blib_vec2f_t BLIB_VEC2F_ZERO;

/*shorthand for vector2 (1, 1)*/
extern const blib_vec2f_t BLIB_VEC2F_ONE;

/*shorthand for vector2 (0, 1)*/
extern const blib_vec2f_t BLIB_VEC2F_UP;

/*shorthand for vector2 (0,-1)*/
extern const blib_vec2f_t BLIB_VEC2F_DOWN;

/*shorthand for vector2 (-1,0)*/
extern const blib_vec2f_t BLIB_VEC2F_LEFT;

/*shorthand for vector2 (1, 0)*/
extern const blib_vec2f_t BLIB_VEC2F_RIGHT;

/*Returns the actual length of a vector "v". 
This uses a square root operation. Use blib_vec2f_sqrmagnitude()
to sacrifice accuracy and save on performance when comparing
distances.*/
float blib_vec2f_magnitude(blib_vec2f_t v);

/*A more performant way of getting the relative length of a 
vector "v". This saves a square root operation making it more 
performant than blib_vec2f_magnitude(). If all you have to do is 
compare a vectors length relatively, use this function instead of 
blib_vec2f_magnitude()*/
float blib_vec2f_sqrmagnitude(blib_vec2f_t v);

/*Returns a given vector "v" as a unit vector.
This means the magnitude(length) of the returned
vector will always be 1 unit. The returned vector always points 
in the same direction as the given vector "v"*/
blib_vec2f_t blib_vec2f_normalize(blib_vec2f_t v);

/*Returns the distance between point a and point b 
in units.*/
float blib_vec2f_distance(blib_vec2f_t a, blib_vec2f_t b);

/*Adds a vector "a" to another vector "b"*/
blib_vec2f_t blib_vec2f_add(blib_vec2f_t a, blib_vec2f_t b);

/*Subtracts a vector "subtrahend" from another vector "minuend"*/
blib_vec2f_t blib_vec2f_subtract(blib_vec2f_t minuend, blib_vec2f_t subtrahend);

/*Scales a vector "v" by "scalar".
increases the magnitude when "scalar" is greater than 1.
decreases the magnitude when "scalar" is less than 0.
The returned vector will point in the same direction as
the given vector "v".*/
blib_vec2f_t blib_vec2f_scale(blib_vec2f_t v, float scalar);

/*For normalized vectors Dot returns 1 if they point in 
exactly the same direction, -1 if they point in completely opposite directions 
and zero if the vectors are perpendicular.*/
float blib_vec2f_dot(blib_vec2f_t a, blib_vec2f_t b);

/*Linearly interpolates between "a" and "b" by "t".
If you want to make sure the returned value stays 
between "a" and "b", use blib_vec3f_lerpclamped() instead.
Returns a point at "t"% of the way between "a" and "b".*/
blib_vec2f_t blib_vec2f_lerp(blib_vec2f_t a, blib_vec2f_t b, float t);

/*Linearly interpolates between "a" and "b" by "t".
Returns a point at "t"% of the way between "a" and "b".*/
blib_vec2f_t blib_vec2f_lerpclamped(blib_vec2f_t a, blib_vec2f_t b, float t);

/*Converts a 2 dimensional vector to a 3 dimensional one*/
blib_vec3f_t blib_vec2f_toVec3f(blib_vec2f_t v);

/*Converts a 2 dimensional vector to a 4 dimensional one*/
blib_vec4f_t blib_vec2f_toVec4f(blib_vec2f_t v);

/*
TODO MoveTowards	Calculate a position between the points specified by 
current 
and target, moving no farther than the distance specified by maxDistanceDelta.
TODO Slerp	Spherically interpolates between two vectors.
TODO ClampMagnitude	Returns a copy of vector with its magnitude clamped to 
maxLength.
TODO Angle	Calculates the angle between vectors from and.
TODO LerpUnclamped	Linearly interpolates between two vectors.
TODO Max	Returns a vector that is made from the largest components of two 
vectors.
TODO Min	Returns a vector that is made from the smallest components of two 
vectors.
TODO OrthoNormalize	Makes vectors normalized and orthogonal to each other.
TODO Project	Projects a vector onto another vector.
TODO ProjectOnPlane	Projects a vector onto a plane defined by a normal 
orthogonal to the plane.
TODO Reflect	Reflects a vector off the plane defined by a normal.
TODO RotateTowards	Rotates a vector current towards target.
TODO SignedAngle	Calculates the signed angle between vectors from and to in 
relation to axis.
TODO SlerpUnclamped	Spherically interpolates between two vectors.
TODO SmoothDamp	Gradually changes a vector towards a desired goal over time.
 
currentTilt = 0f;
float smoothTime = 0.3f;
float refTilt = 0f
currentTilt = Mathf.SmoothDamp(currentTilt, tiltAmount*horizontalInput, 
ref refTilt, smoothTime);
transform.localRotation = Quaternion.Euler(0, 0, currentTilt);
*/


/*shorthand for vector3 (0, 0, 0)*/
extern const blib_vec3f_t BLIB_VEC3F_ZERO;

/*shorthand for vector3 (0, 1, 0)*/
extern const blib_vec3f_t BLIB_VEC3F_UP;

/*shorthand for vector3 (0,-1, 0)*/
extern const blib_vec3f_t BLIB_VEC3F_DOWN;

/*shorthand for vector3 (-1,0, 0)*/
extern const blib_vec3f_t BLIB_VEC3F_LEFT;

/*shorthand for vector3 (1, 0, 0)*/
extern const blib_vec3f_t BLIB_VEC3F_RIGHT;

/*shorthand for vector3 (0, 0, 1)*/
extern const blib_vec3f_t BLIB_VEC3F_FORWARD;

/*shorthand for vector3 (0, 0,-1)*/
extern const blib_vec3f_t BLIB_VEC3F_BACK;

/*shorthand for vector3 (1, 1, 1)*/
extern const blib_vec3f_t BLIB_VEC3F_ONE;

/*Returns the actual length of a vector "v". 
This uses a square root operation. Use blib_vec3f_sqrmagnitude()
to sacrifice accuracy and save on performance when comparing
distances.*/
float blib_vec3f_magnitude(blib_vec3f_t v);

/*A more performant way of getting the relative length of a 
vector "v". This saves a square root operation making it more 
performant than blib_vec3f_magnitude(). If all you have to do is 
compare a vectors length relatively, use this function instead of 
blib_vec3f_magnitude()*/
float blib_vec3f_sqrmagnitude(blib_vec3f_t v);

/*Returns a given vector "v" as a unit vector.
This means the magnitude(length) of the returned
vector will always be 1 unit. The returned vector always points 
in the same direction as the given vector "v"*/
blib_vec3f_t blib_vec3f_normalize(blib_vec3f_t v);

/*Returns the distance between point a and point b 
in units.*/
float blib_vec3f_distance(blib_vec3f_t a, blib_vec3f_t b);

/*Adds a vector "a" to another vector "b"*/
blib_vec3f_t blib_vec3f_add(blib_vec3f_t a, blib_vec3f_t b);

/*Subtracts a vector "subtrahend" from another vector "minuend"*/
blib_vec3f_t blib_vec3f_subtract(blib_vec3f_t minuend, blib_vec3f_t subtrahend);

/*Scales a vector "v" by "scalar".
increases the magnitude when "scalar" is greater than 1.
decreases the magnitude when "scalar" is less than 1.
The returned vector will point in the same direction as
the given vector "v".*/
blib_vec3f_t blib_vec3f_scale(blib_vec3f_t v, float scalar);

/*Returns a vector parallel to both "a" and "b".*/
blib_vec3f_t blib_vec3f_cross(blib_vec3f_t a, blib_vec3f_t b);

/*For normalized vectors Dot returns 1 if they point in 
exactly the same direction, -1 if they point in completely opposite directions 
and zero if the vectors are perpendicular.*/
float blib_vec3f_dot(blib_vec3f_t a, blib_vec3f_t b);

/*Linearly interpolates between "a" and "b" by "t".
If you want to make sure the returned value stays 
between "a" and "b", use blib_vec2f_lerpclamped() instead.
Returns a point at "t"% of the way between "a" and "b".*/
blib_vec3f_t blib_vec3f_lerp(blib_vec3f_t a, blib_vec3f_t b, float t);

/*Linearly interpolates between "a" and "b" by "t".
Returns a point at "t"% of the way between "a" and "b".*/
blib_vec3f_t blib_vec3f_lerpclamped(blib_vec3f_t a, blib_vec3f_t b, float t);

/*Returns a vector that is made from the largest components of two 
vectors.*/
blib_vec3f_t blib_vec3f_max(blib_vec3f_t a, blib_vec3f_t b);

/*Returns a vector that is made from the smallest components of two 
vectors.*/
blib_vec3f_t blib_vec3f_min(blib_vec3f_t a, blib_vec3f_t b);

/*Converts a 3 dimensional vector to a 2 dimensional one*/
blib_vec2f_t blib_vec3f_toVec2f(blib_vec3f_t v);

/*Converts a 3 dimensional vector to a 4 dimensional one*/
blib_vec4f_t blib_vec3f_toVec4f(blib_vec3f_t v);

/*shorthand for vector4 (0, 0, 0, 0)*/
extern const blib_vec4f_t BLIB_VEC4F_ZERO;

/*shorthand for vector4 (0, 1, 0, 1)*/
extern const blib_vec4f_t BLIB_VEC4F_UP;

/*shorthand for vector4 (0,-1, 0, 1)*/
extern const blib_vec4f_t BLIB_VEC4F_DOWN;

/*shorthand for vector4 (-1,0, 0, 1)*/
extern const blib_vec4f_t BLIB_VEC4F_LEFT;

/*shorthand for vector4 (1, 0, 0, 1)*/
extern const blib_vec4f_t BLIB_VEC4F_RIGHT;

/*shorthand for vector4 (0, 0, 1, 1)*/
extern const blib_vec4f_t BLIB_VEC4F_FORWARD;

/*shorthand for vector4 (0, 0,-1, 1)*/
extern const blib_vec4f_t BLIB_VEC4F_BACK;

/*shorthand for vector4 (1, 1, 1, 1)*/
extern const blib_vec4f_t BLIB_VEC4F_ONE;

/*Returns the actual length of a vector "v". 
This uses a square root operation. Use blib_vec4f_sqrmagnitude()
to sacrifice accuracy and save on performance when comparing
distances.*/
float blib_vec4f_magnitude(blib_vec4f_t v);

/*A more performant way of getting the relative length of a 
vector "v". This saves a square root operation making it more 
performant than blib_vec4f_magnitude(). If all you have to do is 
compare a vectors length relatively, use this function instead of 
blib_vec4f_magnitude()*/
float blib_vec4f_sqrmagnitude(blib_vec4f_t v);

/*Returns a given vector "v" as a unit vector.
This means the magnitude(length) of the returned
vector will always be 1 unit. The returned vector always points 
in the same direction as the given vector "v"*/
blib_vec4f_t blib_vec4f_normalize(blib_vec4f_t v);

/*Returns the distance between point a and point b 
in units.*/
float blib_vec4f_distance(blib_vec4f_t a, blib_vec4f_t b);

/*Adds a vector "a" to another vector "b"*/
blib_vec4f_t blib_vec4f_add(blib_vec4f_t a, blib_vec4f_t b);

/*Subtracts a vector "subtrahend" from another vector "minuend"*/
blib_vec4f_t blib_vec4f_subtract(blib_vec4f_t minuend, blib_vec4f_t subtrahend);

/*Scales a vector "v" by "scalar".
increases the magnitude when "scalar" is greater than 1.
decreases the magnitude when "scalar" is less than 1.
The returned vector will point in the same direction as
the given vector "v".*/
blib_vec4f_t blib_vec4f_scale(blib_vec4f_t v, float scalar);

/*For normalized vectors Dot returns 1 if they point in 
exactly the same direction, -1 if they point in completely opposite directions 
and zero if the vectors are perpendicular.*/
float blib_vec4f_dot(blib_vec4f_t a, blib_vec4f_t b);

/*Linearly interpolates between "a" and "b" by "t".
If you want to make sure the returned value stays 
between "a" and "b", use blib_vec2f_lerpclamped() instead.
Returns a point at "t"% of the way between "a" and "b".*/
blib_vec4f_t blib_vec4f_lerp(blib_vec4f_t a, blib_vec4f_t b, float t);

/*Linearly interpolates between "a" and "b" by "t".
Returns a point at "t"% of the way between "a" and "b".*/
blib_vec4f_t blib_vec4f_lerpclamped(blib_vec4f_t a, blib_vec4f_t b, float t);

/*Returns a vector that is made from the largest components of two
vectors.*/
blib_vec4f_t blib_vec4f_max(blib_vec4f_t a, blib_vec4f_t b);

/*Returns a vector that is made from the smallest components of two
vectors.*/
blib_vec4f_t blib_vec4f_min(blib_vec4f_t a, blib_vec4f_t b);

/*Converts a 4 dimensional vector to a 2 dimensional one*/
blib_vec2f_t blib_vec4f_toVec2f(blib_vec4f_t v);

/*Converts a 4 dimensional vector to a 3 dimensional one*/
blib_vec3f_t blib_vec4f_toVec3f(blib_vec4f_t v);

struct blib_mat4_t;
typedef struct blib_mat4_t blib_mat4_t;

/*A column major 4x4 matrix*/
struct blib_mat4_t{
  float elements[16];
};

extern const blib_mat4_t BLIB_MAT4_IDENTITY;

/*Perspective transformation used for calculating depth*/
blib_mat4_t	blib_mat4_perspective(float fov, float aspect, float near, float far);
/*Adds a 4x4 matrix to another 4x4 matrix.*/
blib_mat4_t blib_mat4_add(blib_mat4_t a, blib_mat4_t b);

/*Returns the difference between two 4x4 matrices.*/
blib_mat4_t blib_mat4_subtract(blib_mat4_t min, blib_mat4_t sub);

/*Prints a formatted blib_mat4_t to the console.*/
void blib_mat4_printf(blib_mat4_t m, const char* label);

/*Scales (multiplies) a 4x4 matrix by a scalar (number)*/
blib_mat4_t blib_mat4_scale(const blib_vec3f_t scale);

/*Returns a rotation matrix around "axis" by "angle"*/
blib_mat4_t blib_mat4_rotate(const float angle, blib_vec3f_t axis);

/*Translates a vector to a 4x4 matrix*/
blib_mat4_t blib_mat4_translateVec3(blib_vec3f_t t);

/*Translates a vector to a 4x4 matrix*/
blib_mat4_t blib_mat4_translateVec4(blib_vec4f_t t);

/*Multiplies a 4x4 matrix with another 4x4 matrix*/
blib_mat4_t blib_mat4_multiply(const blib_mat4_t a, const blib_mat4_t b);

#endif /*BLIB_MATH_H*/
