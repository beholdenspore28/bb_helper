#pragma once

#include "b_vec.h"

/*A column major 4x4 matrix*/
typedef struct{
  float elements[16];
} mat4;

extern const mat4 MAT4_IDENTITY;

mat4 mat4_lookAt (vec3 eye, vec3 center, vec3 up);
/*Perspective transformation used for calculating depth*/
mat4 mat4_perspective (float fov, float aspect, float near, float far);
/*Adds a 4x4 matrix to another 4x4 matrix.*/
mat4 mat4_add (mat4 a, mat4 b);

/*Returns the difference between two 4x4 matrices.*/
mat4 mat4_subtract (mat4 min, mat4 sub);

/*Prints a formatted mat4 to the console.*/
void mat4_printf (mat4 m, const char *label);

/*Scales (multiplies) a 4x4 matrix by a scalar (number)*/
mat4 mat4_scale (const vec3 scale);

/*Returns a rotation matrix around "axis" by "angle"*/
mat4 mat4_rotate (const float angle, vec3 axis);

/*Translates a vector to a 4x4 matrix*/
mat4 mat4_translateVec3 (vec3 t);

/*Translates a vector to a 4x4 matrix*/
mat4 mat4_translateVec4 (vec4 t);

/*Multiplies a 4x4 matrix with another 4x4 matrix*/
mat4 mat4_multiply (const mat4 a, const mat4 b);

/*Multiplies a 4x4 matrix with a 4 dimensional vector*/
vec4 mat4_multiplyvec4(vec4 Left, mat4 Right);
