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

------------------------------------------------------------------------------*/

#ifndef BB_HELPER_H
#define BB_HELPER_H

/*------------------------------Project Vision----------------------------------

  This project is a general purpose tool library for tasks I believe to be 
common in software development. bb_helper is written in C89. I realise that no 
one asked for this and there is probably someone out there who has already done 
what I am trying to do here. The main goal for me is to learn the 
inner-workings of the code most people take for granted. This will allow me to 
completely understand all of the code that I use in my projects.

----------------------------How-to-Use-This-Library---------------------------*/

/* You can choose which modules of bb_helper you want to enable by defining the 
 * following in this header file. Use comments to enable and disable them. 
 * */

#define BB_ENABLE_VEC3F  /*Enables functions for manipulating 3d float vectors*/
#define BB_ENABLE_VEC2F  /*Enables functions for manipulating 2d float vectors*/
#define BB_ENABLE_MATHF  /*Enables functions for manipulating float values*/
#define BB_ENABLE_NOISE /*Enables functions for generating noise*/ 
#define BB_ENABLE_DEBUG_MEMORY /*Gives useful information for debugging*/

/* If you don't plan on using a certain module of this library, you can simply 
 * remove its #define from the list above and delete its corresponding .c file
 * */

/*-----------------------------------TO-DO--------------------------------------

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
TODO    Infinity	A representation of positive infinity (Read Only).
TODO    NegativeInfinity	A representation of negative infinity (Read Only).
TODO    DeltaAngle	Calculates the shortest difference between two given angles 
        given in degrees.
TODO    LerpAngle	Same as Lerp but makes sure the values interpolate correctly 
        when they wrap around 360 degrees.
TODO    MoveTowards	Moves a value current towards target.
TODO    MoveTowardsAngle	Same as MoveTowards but makes sure the values 
        interpolate correctly when they wrap around 360 degrees.
TODO    PerlinNoise	Generate 2D Perlin noise.
TODO    PerlinNoise1D	Generates a 1D pseudo-random pattern of float values 
        across a 2D plane.
TODO    PingPong	PingPong returns a value that will increment and decrement 
        between the value 0 and length.
TODO    Repeat	Loops the value t, so that it is never larger than length and 
        never smaller than 0.
TODO    SmoothDamp	Gradually changes a value towards a desired goal over time.
TODO    SmoothDampAngle	Gradually changes an angle given in degrees towards a 
        desired goal angle over time.
TODO    SmoothStep	Interpolates between min and max with smoothing at the 
        limits.
------------------------------------------------------------------------------*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
typedef short bb_bool;

#ifdef BB_ENABLE_DEBUG_MEMORY

/*
#define malloc(n) malloc(n) bb_debug_malloc(n)
#define calloc(n) bb_debug_calloc(n)
#define realloc(n) bb_debug_realloc(n)
#define free(n) bb_debug_free(n)
*/

/*
void *bb_debug_malloc(size_t size);
void *bb_debug_calloc(size_t size);
void *bb_debug_realloc(size_t size);
void *bb_debug_free(size_t size);
*/

#endif

#ifdef BB_ENABLE_NOISE

float bb_noise_1d(int x);

float bb_noise_smoothed1d(float x);

float bb_noise_interpolated1d(float x);

float bb_noise_perlin1d(float x, float persistance, int octaves);

float bb_noise_2d(int x, int y);

float bb_noise_smoothed2d(float x, float y);

float bb_noise_interpolated2d(float x, float y);

float bb_noise_perlin2d(float x, float y, float persistance, int octaves);

#endif

#ifdef BB_ENABLE_MATHF

#define PIf 3.141592f

/*Converts "n" radians into degrees.*/
float bb_mathf_rad2deg(const float n);

/*Converts "n" degrees into radians*/
float bb_mathf_deg2rad(const float n);

/*Returns the absolute value of "n"*/
float bb_mathf_abs(const float n);

/*Returns "n" confined to be greater than min and less than max*/
float bb_mathf_clamp(float n, const float min, const float max);

/*Linearly interpolates between "a" and "b" by "t"*/
float bb_mathf_lerp(float a, float b, float t);

/*TODO tell the people*/
/*Linearly interpolates between "a" and "b" by "t".
"t" is always clamped between 0 and 1.*/
float bb_mathf_lerpclamped(float a, float b, float t);

/*TODO tell the people*/
/*Returns the percentage of "n" from "min" to "max".*/
float bb_mathf_norm(float n, float min, float max);

/*TODO tell the people*/
/*Converts a percentage of one range to a percentage of another.*/
float bb_mathf_map(float n, float fromMin, float fromMax, float toMin, float toMax);

/*It is very rare that one floating point number is exactly the same as another.
This function will check if two numbers are similar enough to be considered 
equal. Returns true if the absolute value of "a" minus the absolute value of 
"b" is smaller than "tolerance".*/
bb_bool bb_mathf_aproxequal(float a, float b, float tolerance);

float bb_mathf_cosInterpolate(float a, float b, float t);

#endif

/*TODO tell the people*/
#ifdef BB_ENABLE_VEC2F

/*A small data structure for storing 2D positions, rotations, scales, or lines.*/
typedef struct{
  float x;
  float y;
}bb_vec2f;

/*shorthand for vector3 (0, 0)*/
extern const bb_vec2f BB_VEC2F_ZERO;

/*shorthand for vector3 (1, 1)*/
extern const bb_vec2f BB_VEC2F_ONE;

/*shorthand for vector3 (0, 1)*/
extern const bb_vec2f BB_VEC2F_UP;

/*shorthand for vector3 (0,-1)*/
extern const bb_vec2f BB_VEC2F_DOWN;

/*shorthand for vector3 (-1,0)*/
extern const bb_vec2f BB_VEC2F_LEFT;

/*shorthand for vector3 (1, 0)*/
extern const bb_vec2f BB_VEC2F_RIGHT;

/*Returns the actual length of a vector "v". 
This uses a square root operation. Use bb_vec2f_sqrmagnitude()
to sacrifice accuracy and save on performance when comparing
distances.*/
float bb_vec2f_magnitude(bb_vec2f v);

/*A more performant way of getting the relative length of a 
vector "v". This saves a square root operation making it more 
performant than bb_vec2f_magnitude(). If all you have to do is 
compare a vectors length relatively, use this function instead of 
bb_vec2f_magnitude()*/
float bb_vec2f_sqrmagnitude(bb_vec2f v);

/*Returns a given vector "v" as a unit vector.
This means the magnitude(length) of the returned
vector will always be 1 unit. The returned vector always points 
in the same direction as the given vector "v"*/
bb_vec2f bb_vec2f_normalize(bb_vec2f v);

/*Returns the distance between point a and point b 
in units.*/
float bb_vec2f_distance(bb_vec2f a, bb_vec2f b);

/*Adds a vector "a" to another vector "b"*/
bb_vec2f bb_vec2f_add(bb_vec2f a, bb_vec2f b);

/*Subtracts a vector "subtrahend" from another vector "minuend"*/
bb_vec2f bb_vec2f_subtract(bb_vec2f minuend, bb_vec2f subtrahend);

/*Scales a vector "v" by "scalar".
increases the magnitude when "scalar" is greater than 1.
decreases the magnitude when "scalar" is less than 0.
The returned vector will point in the same direction as
the given vector "v".*/
bb_vec2f bb_vec2f_scale(bb_vec2f v, float scalar);

/*For normalized vectors Dot returns 1 if they point in 
exactly the same direction, -1 if they point in completely opposite directions 
and zero if the vectors are perpendicular.*/
float bb_vec2f_dot(bb_vec2f a, bb_vec2f b);

/*Linearly interpolates between "a" and "b" by "t".
If you want to make sure the returned value stays 
between "a" and "b", use bb_vec3f_lerpclamped() instead.
Returns a point at "t"% of the way between "a" and "b".*/
bb_vec2f bb_vec2f_lerp(bb_vec2f a, bb_vec2f b, float t);

/*Linearly interpolates between "a" and "b" by "t".
Returns a point at "t"% of the way between "a" and "b".*/
bb_vec2f bb_vec2f_lerpclamped(bb_vec2f a, bb_vec2f b, float t);

#endif


#ifdef BB_ENABLE_VEC3F

/*
TODO MoveTowards	Calculate a position between the points specified by current 
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
*/

/*A small data structure for storing 3D positions, rotations, scales, or lines.*/
typedef struct{
  float x;
  float y;
  float z;
}bb_vec3f;

/*shorthand for vector3 (0, 0, 0)*/
extern const bb_vec3f BB_VEC3F_ZERO;

/*shorthand for vector3 (0, 1, 0)*/
extern const bb_vec3f BB_VEC3F_UP;

/*shorthand for vector3 (0,-1, 0)*/
extern const bb_vec3f BB_VEC3F_DOWN;

/*shorthand for vector3 (-1,0, 0)*/
extern const bb_vec3f BB_VEC3F_LEFT;

/*shorthand for vector3 (1, 0, 0)*/
extern const bb_vec3f BB_VEC3F_RIGHT;

/*shorthand for vector3 (0, 0, 1)*/
extern const bb_vec3f BB_VEC3F_FORWARD;

/*shorthand for vector3 (0, 0,-1)*/
extern const bb_vec3f BB_VEC3F_BACK;

/*shorthand for vector3 (1, 1, 1)*/
extern const bb_vec3f BB_VEC3F_ONE;

/*Returns the actual length of a vector "v". 
This uses a square root operation. Use bb_vec3f_sqrmagnitude()
to sacrifice accuracy and save on performance when comparing
distances.*/
float bb_vec3f_magnitude(bb_vec3f v);

/*A more performant way of getting the relative length of a 
vector "v". This saves a square root operation making it more 
performant than bb_vec3f_magnitude(). If all you have to do is 
compare a vectors length relatively, use this function instead of 
bb_vec3f_magnitude()*/
float bb_vec3f_sqrmagnitude(bb_vec3f v);

/*Returns a given vector "v" as a unit vector.
This means the magnitude(length) of the returned
vector will always be 1 unit. The returned vector always points 
in the same direction as the given vector "v"*/
bb_vec3f bb_vec3f_normalize(bb_vec3f v);

/*Returns the distance between point a and point b 
in units.*/
float bb_vec3f_distance(bb_vec3f a, bb_vec3f b);

/*Adds a vector "a" to another vector "b"*/
bb_vec3f bb_vec3f_add(bb_vec3f a, bb_vec3f b);

/*Subtracts a vector "subtrahend" from another vector "minuend"*/
bb_vec3f bb_vec3f_subtract(bb_vec3f minuend, bb_vec3f subtrahend);

/*Scales a vector "v" by "scalar".
increases the magnitude when "scalar" is greater than 1.
decreases the magnitude when "scalar" is less than 0.
The returned vector will point in the same direction as
the given vector "v".*/
bb_vec3f bb_vec3f_scale(bb_vec3f v, float scalar);

/*Returns a vector parallel to both "a" and "b".*/
bb_vec3f bb_vec3f_cross(bb_vec3f a, bb_vec3f b);

/*For normalized vectors Dot returns 1 if they point in 
exactly the same direction, -1 if they point in completely opposite directions 
and zero if the vectors are perpendicular.*/
float bb_vec3f_dot(bb_vec3f a, bb_vec3f b);

/*Linearly interpolates between "a" and "b" by "t".
If you want to make sure the returned value stays 
between "a" and "b", use bb_vec3f_lerpclamped() instead.
Returns a point at "t"% of the way between "a" and "b".*/
bb_vec3f bb_vec3f_lerp(bb_vec3f a, bb_vec3f b, float t);

/*Linearly interpolates between "a" and "b" by "t".
Returns a point at "t"% of the way between "a" and "b".*/
bb_vec3f bb_vec3f_lerpclamped(bb_vec3f a, bb_vec3f b, float t);

#endif
#endif
