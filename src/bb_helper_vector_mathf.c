#include "bb_helper.h"

#ifdef BB_ENABLE_VEC3F
const bb_vec3f BB_VEC3F_ZERO     =  {.x =  0, .y =  0, .z =  0};
const bb_vec3f BB_VEC3F_UP       =  {.x =  0, .y =  1, .z =  0};
const bb_vec3f BB_VEC3F_DOWN     =  {.x =  0, .y = -1, .z =  0};
const bb_vec3f BB_VEC3F_LEFT     =  {.x = -1, .y =  0, .z =  0};
const bb_vec3f BB_VEC3F_RIGHT	   =	{.x =  1, .y =  0, .z =  0};
const bb_vec3f BB_VEC3F_FORWARD	 =  {.x =  0, .y =  0, .z =  1};
const bb_vec3f BB_VEC3F_BACK     =	{.x =  0, .y =  0, .z = -1};
const bb_vec3f BB_VEC3F_ONE	     =	{.x =  1, .y =  1, .z =  1};

float bb_vec3f_sqrmagnitude(bb_vec3f v){
  return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

/*|V| = √(x² + y² + z²)*/
float bb_vec3f_magnitude(bb_vec3f v){
  return sqrt(bb_vec3f_sqrmagnitude(v));
}

bb_vec3f bb_vec3f_normalize(bb_vec3f v){
  float m = bb_vec3f_magnitude(v);
  return (bb_vec3f){.x=v.x/m, .y=v.y/m, .z=v.z/m};
}

bb_vec3f bb_vec3f_subtract(bb_vec3f minuend, bb_vec3f subtrahend){
  return (bb_vec3f){
    .x=minuend.x-subtrahend.x,
    .y=minuend.y-subtrahend.y,
    .z=minuend.z-subtrahend.z};
}

bb_vec3f bb_vec3f_add(bb_vec3f a, bb_vec3f b){
  return (bb_vec3f){
    .x=a.x+b.x,
    .y=a.y+b.y,
    .z=a.z+b.z};
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

  /*
  product[0] = (A[1] * B[2]) - (A[2] * B[1]);
  product[1] = -((A[0] * B[2]) - (A[2] * B[0]));
  product[2] = (A[0] * B[1]) - (A[1] * B[0]);
  */
  return (bb_vec3f){
    .x =  (a.y  * b.z) - (a.z * b.y),
    .y = -((a.x * b.z) - (a.z * b.x)),
    .z =  (a.x  * b.y) - (a.y * b.x)};
}

float bb_vec3f_dot(bb_vec3f a, bb_vec3f b){
  return (a.x * b.x) +(a.y * b.y) +(a.z * b.z);
}

#endif