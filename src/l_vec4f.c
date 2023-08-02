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

#if defined(L_ENABLE_VEC4F)
const l_vec4f_t L_VEC4F_ZERO     =  {.x =  0, .y =  0, .z =  0};
const l_vec4f_t L_VEC4F_ONE	     =	{.x =  1, .y =  1, .z =  1};
const l_vec4f_t L_VEC4F_UP       =  {.x =  0, .y =  1, .z =  0};
const l_vec4f_t L_VEC4F_DOWN     =  {.x =  0, .y = -1, .z =  0};
const l_vec4f_t L_VEC4F_LEFT     =  {.x = -1, .y =  0, .z =  0};
const l_vec4f_t L_VEC4F_RIGHT	   =	{.x =  1, .y =  0, .z =  0};
const l_vec4f_t L_VEC4F_FORWARD	 =  {.x =  0, .y =  0, .z =  1};
const l_vec4f_t L_VEC4F_BACK     =	{.x =  0, .y =  0, .z = -1};

float l_vec4f_magnitude(l_vec4f_t v){
  return sqrt(l_vec4f_sqrmagnitude(v));
}

float l_vec4f_sqrmagnitude(l_vec4f_t v){
  return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

l_vec4f_t l_vec4f_normalize(l_vec4f_t v){
  float m = l_vec4f_magnitude(v);
  return (l_vec4f_t){.x = v.x / m, .y = v.y / m, .z = v.z / m, .w = v.w / m};
}

l_vec4f_t l_vec4f_add(l_vec4f_t a, l_vec4f_t b){
  return (l_vec4f_t){
    .x = a.x + b.x,
    .y = a.y + b.y,
    .z = a.z + b.z,
    .w = a.w + b.w,
  };
}

l_vec4f_t l_vec4f_subtract(l_vec4f_t minuend, l_vec4f_t subtrahend){
  return (l_vec4f_t){
    .x = minuend.x - subtrahend.x,
    .y = minuend.y - subtrahend.y,
    .z = minuend.z - subtrahend.z,
    .w = minuend.w - subtrahend.w,
  };
}

float l_vec4f_distance(l_vec4f_t a, l_vec4f_t b){
  return l_vec4f_magnitude(l_vec4f_subtract(b,a));
}

l_vec4f_t l_vec4f_scale(l_vec4f_t v, float scalar){
  return (l_vec4f_t){
    .x = v.x * scalar,
    .y = v.y * scalar,
    .z = v.z * scalar,
    .w = v.w * scalar,
  };
}

float l_vec4f_dot(l_vec4f_t a, l_vec4f_t b){
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

l_vec4f_t l_vec4f_lerp(l_vec4f_t a, l_vec4f_t b, float t){
  return (l_vec4f_t){
    .x = a.x + (b.x - a.x) * t,
    .y = a.y + (b.y - a.y) * t,
    .z = a.z + (b.z - a.z) * t,
    .w = a.w + (b.w - a.w) * t,
  };
}

l_vec4f_t l_vec4f_lerpclamped(l_vec4f_t a, l_vec4f_t b, float n){
  /*clamp n between 0 and 1*/
  n = n < 0.0f ? 0.0f : n;
  n = n > 1.0f ? 1.0f : n;
  /*perform lerp*/
  return (l_vec4f_t){
    .x = a.x + (b.x - a.x) * n,
    .y = a.y + (b.y - a.y) * n,
    .z = a.z + (b.z - a.z) * n,
    .w = a.w + (b.w - a.w) * n,
  };
}

l_vec4f_t l_vec4f_max(l_vec4f_t a, l_vec4f_t b){
  return (l_vec4f_t){
    .x = a.x >= b.x ? a.x : b.x,
    .y = a.y >= b.y ? a.y : b.y,
    .z = a.z >= b.z ? a.z : b.z,
    .w = a.w >= b.w ? a.w : b.w,
  };
}

l_vec4f_t l_vec4f_min(l_vec4f_t a, l_vec4f_t b){
  return (l_vec4f_t){
    .x = a.x <= b.x ? a.x : b.x,
    .y = a.y <= b.y ? a.y : b.y,
    .z = a.z <= b.z ? a.z : b.z,
    .w = a.w <= b.w ? a.w : b.w,
  };
}

#endif
