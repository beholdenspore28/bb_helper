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

#include "bb_helper.h"

#ifdef BB_ENABLE_VEC3F
const bb_vec3f BB_VEC3F_ZERO     =  {.x =  0, .y =  0, .z =  0};
const bb_vec3f BB_VEC3F_ONE	     =	{.x =  1, .y =  1, .z =  1};
const bb_vec3f BB_VEC3F_UP       =  {.x =  0, .y =  1, .z =  0};
const bb_vec3f BB_VEC3F_DOWN     =  {.x =  0, .y = -1, .z =  0};
const bb_vec3f BB_VEC3F_LEFT     =  {.x = -1, .y =  0, .z =  0};
const bb_vec3f BB_VEC3F_RIGHT	   =	{.x =  1, .y =  0, .z =  0};
const bb_vec3f BB_VEC3F_FORWARD	 =  {.x =  0, .y =  0, .z =  1};
const bb_vec3f BB_VEC3F_BACK     =	{.x =  0, .y =  0, .z = -1};

float bb_vec3f_magnitude(bb_vec3f v){
  return sqrt(bb_vec3f_sqrmagnitude(v));
}

float bb_vec3f_sqrmagnitude(bb_vec3f v){
  return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

bb_vec3f bb_vec3f_normalize(bb_vec3f v){
  float m = bb_vec3f_magnitude(v);
  return (bb_vec3f){.x=v.x/m, .y=v.y/m, .z=v.z/m};
}

bb_vec3f bb_vec3f_add(bb_vec3f a, bb_vec3f b){
  return (bb_vec3f){
    .x=a.x+b.x,
    .y=a.y+b.y,
    .z=a.z+b.z};
}

bb_vec3f bb_vec3f_subtract(bb_vec3f minuend, bb_vec3f subtrahend){
  return (bb_vec3f){
    .x=minuend.x-subtrahend.x,
    .y=minuend.y-subtrahend.y,
    .z=minuend.z-subtrahend.z};
}

float bb_vec3f_distance(bb_vec3f a, bb_vec3f b){
  return bb_vec3f_magnitude(bb_vec3f_subtract(b,a));
}

bb_vec3f bb_vec3f_scale(bb_vec3f v, float scalar){
  return (bb_vec3f){
    .x=v.x*scalar,
    .y=v.y*scalar,
    .z=v.z*scalar};
}

bb_vec3f bb_vec3f_cross(bb_vec3f a, bb_vec3f b){
  return (bb_vec3f){
    .x =  (a.y  * b.z) - (a.z * b.y),
    .y = -((a.x * b.z) - (a.z * b.x)),
    .z =  (a.x  * b.y) - (a.y * b.x)};
}

float bb_vec3f_dot(bb_vec3f a, bb_vec3f b){
  return (a.x * b.x) + (a.y * b.y) +(a.z * b.z);
}

bb_vec3f bb_vec3f_lerp(bb_vec3f a, bb_vec3f b, float t){
  return (bb_vec3f){
    .x= a.x + (b.x - a.x) * t,
    .y= a.y + (b.y - a.y) * t,
    .z= a.z + (b.z - a.z) * t,
  };
}

bb_vec3f bb_vec3f_lerpclamped(bb_vec3f a, bb_vec3f b, float n){
  /*clamp n between 0 and 1*/
  n = n < 0.0f ? 0.0f : n;
  n = n > 1.0f ? 1.0f : n;
  /*perform lerp*/
  return (bb_vec3f){
    .x= a.x + (b.x - a.x) * n,
    .y= a.y + (b.y - a.y) * n,
    .z= a.z + (b.z - a.z) * n,
  };
}

bb_vec3f bb_vec3f_max(bb_vec3f a, bb_vec3f b){
  return (bb_vec3f){
    .x = a.x >= b.x ? a.x : b.x,
    .y = a.y >= b.y ? a.y : b.y,
    .z = a.z >= b.z ? a.z : b.z,
  };
}

bb_vec3f bb_vec3f_min(bb_vec3f a, bb_vec3f b){
  return (bb_vec3f){
    .x = a.x <= b.x ? a.x : b.x,
    .y = a.y <= b.y ? a.y : b.y,
    .z = a.z <= b.z ? a.z : b.z,
  };
}

#endif