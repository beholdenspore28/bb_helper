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

#include "lite.h"

const l_vec3f_t L_VEC3F_ZERO     =  {.x =  0, .y =  0, .z =  0};
const l_vec3f_t L_VEC3F_ONE	     =	{.x =  1, .y =  1, .z =  1};
const l_vec3f_t L_VEC3F_UP       =  {.x =  0, .y =  1, .z =  0};
const l_vec3f_t L_VEC3F_DOWN     =  {.x =  0, .y = -1, .z =  0};
const l_vec3f_t L_VEC3F_LEFT     =  {.x = -1, .y =  0, .z =  0};
const l_vec3f_t L_VEC3F_RIGHT	   =	{.x =  1, .y =  0, .z =  0};
const l_vec3f_t L_VEC3F_FORWARD	 =  {.x =  0, .y =  0, .z =  1};
const l_vec3f_t L_VEC3F_BACK     =	{.x =  0, .y =  0, .z = -1};

float l_vec3f_magnitude(l_vec3f_t v){
  return sqrt(l_vec3f_sqrmagnitude(v));
}

float l_vec3f_sqrmagnitude(l_vec3f_t v){
  return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

l_vec3f_t l_vec3f_normalize(l_vec3f_t v){
  float m = l_vec3f_magnitude(v);
  return (l_vec3f_t){.x=v.x/m, .y=v.y/m, .z=v.z/m};
}

l_vec3f_t l_vec3f_add(l_vec3f_t a, l_vec3f_t b){
  return (l_vec3f_t){
    .x=a.x+b.x,
    .y=a.y+b.y,
    .z=a.z+b.z};
}

l_vec3f_t l_vec3f_subtract(l_vec3f_t minuend, l_vec3f_t subtrahend){
  return (l_vec3f_t){
    .x=minuend.x-subtrahend.x,
    .y=minuend.y-subtrahend.y,
    .z=minuend.z-subtrahend.z};
}

float l_vec3f_distance(l_vec3f_t a, l_vec3f_t b){
  return l_vec3f_magnitude(l_vec3f_subtract(b,a));
}

l_vec3f_t l_vec3f_scale(l_vec3f_t v, float scalar){
  return (l_vec3f_t){
    .x=v.x*scalar,
    .y=v.y*scalar,
    .z=v.z*scalar};
}

l_vec3f_t l_vec3f_cross(l_vec3f_t a, l_vec3f_t b){
  return (l_vec3f_t){
    .x =  (a.y  * b.z) - (a.z * b.y),
    .y = -((a.x * b.z) - (a.z * b.x)),
    .z =  (a.x  * b.y) - (a.y * b.x)};
}

float l_vec3f_dot(l_vec3f_t a, l_vec3f_t b){
  return (a.x * b.x) + (a.y * b.y) +(a.z * b.z);
}

l_vec3f_t l_vec3f_lerp(l_vec3f_t a, l_vec3f_t b, float t){
  return (l_vec3f_t){
    .x= a.x + (b.x - a.x) * t,
    .y= a.y + (b.y - a.y) * t,
    .z= a.z + (b.z - a.z) * t,
  };
}

l_vec3f_t l_vec3f_lerpclamped(l_vec3f_t a, l_vec3f_t b, float n){
  /*clamp n between 0 and 1*/
  n = n < 0.0f ? 0.0f : n;
  n = n > 1.0f ? 1.0f : n;
  /*perform lerp*/
  return (l_vec3f_t){
    .x= a.x + (b.x - a.x) * n,
    .y= a.y + (b.y - a.y) * n,
    .z= a.z + (b.z - a.z) * n,
  };
}

l_vec3f_t l_vec3f_max(l_vec3f_t a, l_vec3f_t b){
  return (l_vec3f_t){
    .x = a.x >= b.x ? a.x : b.x,
    .y = a.y >= b.y ? a.y : b.y,
    .z = a.z >= b.z ? a.z : b.z,
  };
}

l_vec3f_t l_vec3f_min(l_vec3f_t a, l_vec3f_t b){
  return (l_vec3f_t){
    .x = a.x <= b.x ? a.x : b.x,
    .y = a.y <= b.y ? a.y : b.y,
    .z = a.z <= b.z ? a.z : b.z,
  };
}

l_vec2f_t l_vec3f_toVec2f(l_vec3f_t v){
  return (l_vec2f_t){.x=v.x, .y=v.y};
}

l_vec4f_t l_vec3f_toVec4f(l_vec3f_t v){
  return (l_vec4f_t){.x=v.x, .y=v.y, .z=v.z, .w=1.0f};
}