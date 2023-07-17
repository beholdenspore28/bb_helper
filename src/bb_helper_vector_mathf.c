#include "bb_helper.h"

#ifdef BB_ENABLE_VEC3F

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
  return (bb_vec3f){.x=minuend.x-subtrahend.x,
                    .y=minuend.y-subtrahend.y,
                    .z=minuend.z-subtrahend.z};
}

bb_vec3f bb_vec3f_add(bb_vec3f a, bb_vec3f b){
  return (bb_vec3f){.x=a.x+b.x,
                    .y=a.y+b.y,
                    .z=a.z+b.z};
}

float bb_vec3f_distance(bb_vec3f a, bb_vec3f b){
  return bb_vec3f_magnitude(bb_vec3f_subtract(b,a));
}

#endif