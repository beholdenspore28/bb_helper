#ifndef BB_HELPER_H
#define BB_HELPER_H

/*BEGIN LEGAL*/

/*

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

*/

/*END LEGAL*/

/*------------------------------Project Vision----------------------------------

This project is a general purpose tool library for tasks I believe to be common
 in software development. bb_helper is written in C89. I realise that no one 
 asked for this and there might be someone out there who has already done what 
 I am trying to do here. The main goal for me is to learn the inner-workings of 
 the code most people take for granted. This will allow me to completely 
 understand all of the code that I use in my projects.

------------------------------------------------------------------------------*/

/*
Memory tracking system that documents uses of malloc, free, calloc, and realloc.
TODO  This system should be easy to enable and disable using #define #ifdef 
#ifndef, etc.
TODO  This system should provide debugging information reguarding where memory 
has been allocated, reallocated, or freed.
TODO  This system should also make it clear exactly which line of code and in 
which file a piece of 
TODO  memory has been changed.
TODO  Warnings should appear when the user fails to free memory appropriately.
*/

/*
General floating point math functions
DONE    PI	The well-known 3.14159265358979... value (Read Only).
DONE    Deg2Rad	Degrees-to-radians conversion constant (Read Only).
DONE    Rad2Deg	Radians-to-degrees conversion constant (Read Only).
TODO    Epsilon	A tiny floating point value (Read Only).
TODO    Infinity	A representation of positive infinity (Read Only).
TODO    NegativeInfinity	A representation of negative infinity (Read Only).
DONE    Abs	Returns the absolute value of f.
DONE    Acos	Returns the arc-cosine of f - the angle in radians whose cosine 
is f.
        Approximately	Compares two floating point values and returns true if 
        they are similar.
DONE    Asin	Returns the arc-sine of f - the angle in radians whose sine is f.
DONE    Atan	Returns the arc-tangent of f - the angle in radians whose tangent 
is f.
DONE    Atan2	Returns the angle in radians whose Tan is y/x.
DONE    Ceil	Returns the smallest integer greater to or equal to f.
TODO    CeilToInt	Returns the smallest integer greater to or equal to f.
TODO    Clamp	Clamps the given value between the given minimum float and 
maximum float values. 
        Returns the given value if it is within the minimum and maximum range.
TODO    Clamp01	Clamps value between 0 and 1 and returns value.
TODO    ClosestPowerOfTwo	Returns the closest power of two value.
TODO    CorrelatedColorTemperatureToRGB	Convert a color temperature in Kelvin 
to RGB color.
DONE    Cos	Returns the cosine of angle f.
TODO    DeltaAngle	Calculates the shortest difference between two given angles 
given in degrees.
DONE    Exp	Returns e raised to the specified power.
TODO    FloatToHalf	Encode a floating point value into a 16-bit representation.
DONE    Floor	Returns the largest integer smaller than or equal to f.
TODO    FloorToInt	Returns the largest integer smaller to or equal to f.
TODO    GammaToLinearSpace	Converts the given value from gamma (sRGB) to 
linear color space.
DONE    HalfToFloat	Convert a half precision float to a 32-bit floating point 
value.
TODO?   Lerp	Linearly interpolates between a and b by t.
TODO    InverseLerp	Determines where a value lies between two points.
TODO    LerpAngle	Same as Lerp but makes sure the values interpolate correctly 
when they wrap around 360
        degrees.
TODO    LerpUnclamped	Linearly interpolates between a and b by t with no limit 
to t.
TODO    LinearToGammaSpace	Converts the given value from linear to gamma 
(sRGB) color space.
DONE    Log	Returns the logarithm of a specified number in a specified base.
TODO    Log10	Returns the base 10 logarithm of a specified number.
TODO    MoveTowards	Moves a value current towards target.
TODO    MoveTowardsAngle	Same as MoveTowards but makes sure the values 
interpolate correctly when they 
        wrap around 360 degrees.
TODO    PerlinNoise	Generate 2D Perlin noise.
TODO    PerlinNoise1D	Generates a 1D pseudo-random pattern of float values 
across a 2D plane.
TODO    PingPong	PingPong returns a value that will increment and decrement 
between the value 0 and length.
DONE    Pow	Returns f raised to power p.
TODO    Repeat	Loops the value t, so that it is never larger than length and 
never smaller than 0.
TODO    SmoothDamp	Gradually changes a value towards a desired goal over time.
TODO    SmoothDampAngle	Gradually changes an angle given in degrees towards a 
desired goal angle over time.
TODO    SmoothStep	Interpolates between min and max with smoothing at the 
limits.
*/

#include <math.h>
typedef int bb_bool;
/*
These functions will be seperated by data type.
You can choose which functions you want to enable by using the following 
defines:
*/
#define BB_ENABLE_VEC3F  /*Enables functions for manipulating 3d float vectors*/
#define BB_ENABLE_MATHF         /*Enables functions for manipulating float 
values*/
#define BB_ENABLE_MATHD         /*Enables functions for manipulating double 
values*/

#ifdef BB_ENABLE_MATHF

#define PIf 3.141592f

/*Converts n radians into degrees.*/
float bb_rad2degf(const float n);

/*Converts n degrees into radians*/
float bb_deg2radf(const float n);

/*Returns the absolute value of n*/
float bb_absf(const float n);

/*Returns n confined to be greater than min and less than max*/
float bb_clampf(float n, const float min, const float max);

/*TODO Test this function*/
/*Linearly interpolates between a and b by t*/
float bb_lerpf(float a, float b, float t);

bb_bool bb_aproxequalf(float a, float b, float tolerance);

#endif

#ifdef BB_ENABLE_VEC3F

/*
DONE magnitude	Returns the length of this vector (Read Only).
DONE sqrMagnitude	Returns the squared length of this vector (Read Only).
DONE normalized	Returns this vector with a magnitude of 1 (Read Only).
DONE Equals	Returns true if the given vector is exactly equal to this vector.
DONE Distance	Returns the distance between a and b.
DONE Scale	Multiplies two vectors component-wise.
DONE Cross	Cross Product of two vectors.
DONE Dot	Dot Product of two vectors.
TODO MoveTowards	Calculate a position between the points specified by current 
and target, moving no farther than the distance specified by maxDistanceDelta.
TODO Lerp	Linearly interpolates between two points.
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
*/

typedef struct{
  float x;
  float y;
  float z;
}bb_vec3f;

extern const bb_vec3f BB_VEC3F_ZERO;      /*shorthand for vector3 (0, 0, 0)*/
extern const bb_vec3f BB_VEC3F_UP;        /*shorthand for vector3 (0, 1, 0)*/
extern const bb_vec3f BB_VEC3F_DOWN;      /*shorthand for vector3 (0,-1, 0)*/
extern const bb_vec3f BB_VEC3F_LEFT;      /*shorthand for vector3 (-1,0, 0)*/
extern const bb_vec3f BB_VEC3F_RIGHT;     /*shorthand for vector3 (1, 0, 0)*/
extern const bb_vec3f BB_VEC3F_FORWARD;   /*shorthand for vector3 (0, 0, 1)*/
extern const bb_vec3f BB_VEC3F_BACK;      /*shorthand for vector3 (0, 0,-1)*/
extern const bb_vec3f BB_VEC3F_ONE;       /*shorthand for vector3 (1, 1, 1)*/

float bb_vec3f_magnitude(bb_vec3f v);
float bb_vec3f_sqrmagnitude(bb_vec3f v);
bb_vec3f bb_vec3f_normalize(bb_vec3f v);
float bb_vec3f_distance(bb_vec3f a, bb_vec3f b);
bb_vec3f bb_vec3f_add(bb_vec3f a, bb_vec3f b);
bb_vec3f bb_vec3f_scale(bb_vec3f v, float scalar);
bb_vec3f bb_vec3f_cross(bb_vec3f a, bb_vec3f b);
float bb_vec3f_dot(bb_vec3f a, bb_vec3f b);
#endif
#endif