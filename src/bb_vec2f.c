#include "bb_helper.h"
#ifdef BB_ENABLE_VEC2F

const bb_vec2f BB_VEC2F_ZERO     =  {.x =  0, .y =  0};
const bb_vec2f BB_VEC2F_ONE	     =	{.x =  1, .y =  1};
const bb_vec2f BB_VEC2F_UP       =  {.x =  0, .y =  1};
const bb_vec2f BB_VEC2F_DOWN     =  {.x =  0, .y = -1};
const bb_vec2f BB_VEC2F_LEFT     =  {.x = -1, .y =  0};
const bb_vec2f BB_VEC2F_RIGHT	   =	{.x =  1, .y =  0};

float bb_vec2f_magnitude(bb_vec2f v){
return sqrt(bb_vec2f_sqrmagnitude(v));
}

float bb_vec2f_sqrmagnitude(bb_vec2f v){
  return ((v.x * v.x) + (v.y * v.y));
}

bb_vec2f bb_vec2f_normalize(bb_vec2f v){
  float m = bb_vec2f_magnitude(v);
  return (bb_vec2f){.x=v.x/m, .y=v.y/m};
}

float bb_vec2f_distance(bb_vec2f a, bb_vec2f b){
  return bb_vec2f_magnitude(bb_vec2f_subtract(b,a));
}

bb_vec2f bb_vec2f_add(bb_vec2f a, bb_vec2f b){
  return (bb_vec2f){
    .x=a.x+b.x,
    .y=a.y+b.y};
}

bb_vec2f bb_vec2f_subtract(bb_vec2f minuend, bb_vec2f subtrahend){
  return (bb_vec2f){
    .x=minuend.x-subtrahend.x,
    .y=minuend.y-subtrahend.y};
}

bb_vec2f bb_vec2f_scale(bb_vec2f v, float scalar){
  return (bb_vec2f){
    .x=v.x*scalar,
    .y=v.y*scalar};
}

float bb_vec2f_dot(bb_vec2f a, bb_vec2f b){
  return (a.x * b.x) + (a.y * b.y);
}

bb_vec2f bb_vec2f_lerp(bb_vec2f a, bb_vec2f b, float t){
  return (bb_vec2f){
    .x= a.x + (b.x - a.x) * t,
    .y= a.y + (b.y - a.y) * t,
  };
}

bb_vec2f bb_vec2f_lerpclamped(bb_vec2f a, bb_vec2f b, float t){
  /*clamp n between 0 and 1*/
  t = t < 0.0f ? 0.0f : t;
  t = t > 1.0f ? 1.0f : t;
  /*perform lerp*/
  return (bb_vec2f){
    .x= a.x + (b.x - a.x) * t,
    .y= a.y + (b.y - a.y) * t,
  };
}

#endif