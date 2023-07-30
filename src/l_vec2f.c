#include "lite.h"
#if defined(L_ENABLE_VEC2F)

const l_vec2f_t L_VEC2F_ZERO     =  {.x =  0, .y =  0};
const l_vec2f_t L_VEC2F_ONE	     =	{.x =  1, .y =  1};
const l_vec2f_t L_VEC2F_UP       =  {.x =  0, .y =  1};
const l_vec2f_t L_VEC2F_DOWN     =  {.x =  0, .y = -1};
const l_vec2f_t L_VEC2F_LEFT     =  {.x = -1, .y =  0};
const l_vec2f_t L_VEC2F_RIGHT	   =	{.x =  1, .y =  0};

float l_vec2f_magnitude(l_vec2f_t v){
return sqrt(l_vec2f_sqrmagnitude(v));
}

float l_vec2f_sqrmagnitude(l_vec2f_t v){
  return ((v.x * v.x) + (v.y * v.y));
}

l_vec2f_t l_vec2f_normalize(l_vec2f_t v){
  float m = l_vec2f_magnitude(v);
  return (l_vec2f_t){.x=v.x/m, .y=v.y/m};
}

float l_vec2f_distance(l_vec2f_t a, l_vec2f_t b){
  return l_vec2f_magnitude(l_vec2f_subtract(b,a));
}

l_vec2f_t l_vec2f_add(l_vec2f_t a, l_vec2f_t b){
  return (l_vec2f_t){
    .x=a.x+b.x,
    .y=a.y+b.y};
}

l_vec2f_t l_vec2f_subtract(l_vec2f_t minuend, l_vec2f_t subtrahend){
  return (l_vec2f_t){
    .x=minuend.x-subtrahend.x,
    .y=minuend.y-subtrahend.y};
}

l_vec2f_t l_vec2f_scale(l_vec2f_t v, float scalar){
  return (l_vec2f_t){
    .x=v.x*scalar,
    .y=v.y*scalar};
}

float l_vec2f_dot(l_vec2f_t a, l_vec2f_t b){
  return (a.x * b.x) + (a.y * b.y);
}

l_vec2f_t l_vec2f_lerp(l_vec2f_t a, l_vec2f_t b, float t){
  return (l_vec2f_t){
    .x= a.x + (b.x - a.x) * t,
    .y= a.y + (b.y - a.y) * t,
  };
}

l_vec2f_t l_vec2f_lerpclamped(l_vec2f_t a, l_vec2f_t b, float t){
  /*clamp n between 0 and 1*/
  t = t < 0.0f ? 0.0f : t;
  t = t > 1.0f ? 1.0f : t;
  /*perform lerp*/
  return (l_vec2f_t){
    .x= a.x + (b.x - a.x) * t,
    .y= a.y + (b.y - a.y) * t,
  };
}

#endif