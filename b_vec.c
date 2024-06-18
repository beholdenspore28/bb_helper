#include "b_vec.h"
#include <stdio.h>
#include <math.h>

void vec2_printf (const vec2 v, const char *label) {
  printf ("%s [%f, %f]\n", label, v.x, v.y);
}

vec2 vec2_negate (vec2 v) {
  return (vec2){ .x = -v.x, .y = -v.y };
}

float vec2_magnitude (vec2 v) {
  return sqrt (vec2_sqrmagnitude (v));
}

float vec2_sqrmagnitude (vec2 v) {
  return ((v.x * v.x) + (v.y * v.y));
}

vec2 vec2_normalize (vec2 v) {
  float m = vec2_magnitude (v);
  if (m == 0)
    return VEC2_ZERO;
  return (vec2){ .x = v.x / m, .y = v.y / m };
}

float vec2_distance (vec2 a, vec2 b) {
  return vec2_magnitude (vec2_subtract (b, a));
}

vec2 vec2_add (vec2 a, vec2 b) {
  return (vec2){ .x = a.x + b.x, .y = a.y + b.y };
}

vec2 vec2_subtract (vec2 minuend, vec2 subtrahend) {
  return (vec2){ .x = minuend.x - subtrahend.x,
                      .y = minuend.y - subtrahend.y };
}

vec2 vec2_scale (vec2 v, float scalar) {
  return (vec2){ .x = v.x * scalar, .y = v.y * scalar };
}

float vec2_dot (vec2 a, vec2 b) {
  return (a.x * b.x) + (a.y * b.y);
}

vec2 vec2_lerp (vec2 a, vec2 b, float t) {
  return (vec2){
    .x = a.x + (b.x - a.x) * t,
    .y = a.y + (b.y - a.y) * t,
  };
}

vec2 vec2_lerpclamped (vec2 a, vec2 b, float t) {
  /*clamp n between 0 and 1*/
  t = t < 0.0f ? 0.0f : t;
  t = t > 1.0f ? 1.0f : t;
  /*perform lerp*/
  return (vec2){
    .x = a.x + (b.x - a.x) * t,
    .y = a.y + (b.y - a.y) * t,
  };
}

vec3 vec2_toVec3 (vec2 v) {
  return (vec3){ .x = v.x, .y = v.y, .z = 0.0f };
}

vec4 vec2_toVec4 (vec2 v) {
  return (vec4){ .x = v.x, .y = v.y, .z = 0.0f, .w = 1.0f };
}

void vec3_printf (const vec3 v, const char *label) {
  printf ("%s [%f, %f, %f]\n", label, v.x, v.y, v.z);
}

vec3 vec3_negate (vec3 v) {
  return (vec3){ .x = -v.x, .y = -v.y, .z = -v.z };
}

float vec3_magnitude (vec3 v) {
  return sqrt (vec3_sqrmagnitude (v));
}

float vec3_sqrmagnitude (vec3 v) {
  return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

vec3 vec3_normalize (vec3 v) {
  float m = vec3_magnitude (v);
  if (m == 0)
    return VEC3_ZERO;
  return (vec3){ .x = v.x / m, .y = v.y / m, .z = v.z / m };
}

vec3 vec3_add (vec3 a, vec3 b) {
  return (vec3){ .x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z };
}

vec3 vec3_subtract (vec3 minuend, vec3 subtrahend) {
  return (vec3){ .x = minuend.x - subtrahend.x,
                      .y = minuend.y - subtrahend.y,
                      .z = minuend.z - subtrahend.z };
}

float vec3_distance (vec3 a, vec3 b) {
  return vec3_magnitude (vec3_subtract (b, a));
}

vec3 vec3_scale (vec3 v, float scalar) {
  return (
      vec3){ .x = v.x * scalar, .y = v.y * scalar, .z = v.z * scalar };
}

vec3 vec3_cross (vec3 a, vec3 b) {
  return (vec3){ .x = (a.y * b.z) - (a.z * b.y),
                      .y = -((a.x * b.z) - (a.z * b.x)),
                      .z = (a.x * b.y) - (a.y * b.x) };
}

float vec3_dot (vec3 a, vec3 b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

vec3 vec3_lerp (vec3 a, vec3 b, float t) {
  return (vec3){
    .x = a.x + (b.x - a.x) * t,
    .y = a.y + (b.y - a.y) * t,
    .z = a.z + (b.z - a.z) * t,
  };
}

vec3 vec3_lerpclamped (vec3 a, vec3 b, float n) {
  /*clamp n between 0 and 1*/
  n = n < 0.0f ? 0.0f : n;
  n = n > 1.0f ? 1.0f : n;
  /*perform lerp*/
  return (vec3){
    .x = a.x + (b.x - a.x) * n,
    .y = a.y + (b.y - a.y) * n,
    .z = a.z + (b.z - a.z) * n,
  };
}

vec3 vec3_max (vec3 a, vec3 b) {
  return (vec3){
    .x = a.x >= b.x ? a.x : b.x,
    .y = a.y >= b.y ? a.y : b.y,
    .z = a.z >= b.z ? a.z : b.z,
  };
}

vec3 vec3_min (vec3 a, vec3 b) {
  return (vec3){
    .x = a.x <= b.x ? a.x : b.x,
    .y = a.y <= b.y ? a.y : b.y,
    .z = a.z <= b.z ? a.z : b.z,
  };
}

vec2 vec3_toVec2 (vec3 v) {
  return (vec2){ .x = v.x, .y = v.y };
}

vec4 vec3_toVec4 (vec3 v) {
  return (vec4){ .x = v.x, .y = v.y, .z = v.z, .w = 1.0f };
}

void vec4f_printf (const vec4 v, const char *label) {
  printf ("%s [%f, %f, %f, %f]\n", label, v.x, v.y, v.z, v.w);
}

vec4 vec4f_negate (vec4 v) {
  return (vec4){ .x = -v.x, .y = -v.y, .z = -v.z, .w = -v.w };
}

float vec4f_magnitude (vec4 v) {
  return sqrt (vec4_sqrmagnitude (v));
}

float vec4_sqrmagnitude (vec4 v) {
  return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

vec4 vec4f_normalize (vec4 v) {
  float m = vec4f_magnitude (v);
  if (m == 0)
    return VEC4_ZERO;
  return (vec4){ .x = v.x / m, .y = v.y / m, .z = v.z / m, .w = v.w / m };
}

vec4 vec4f_add (vec4 a, vec4 b) {
  return (vec4){
    .x = a.x + b.x,
    .y = a.y + b.y,
    .z = a.z + b.z,
    .w = a.w + b.w,
  };
}

vec4 vec4f_subtract (vec4 minuend, vec4 subtrahend) {
  return (vec4){
    .x = minuend.x - subtrahend.x,
    .y = minuend.y - subtrahend.y,
    .z = minuend.z - subtrahend.z,
    .w = minuend.w - subtrahend.w,
  };
}

float vec4f_distance (vec4 a, vec4 b) {
  return vec4f_magnitude (vec4f_subtract (b, a));
}

vec4 vec4f_scale (vec4 v, float scalar) {
  return (vec4){
    .x = v.x * scalar,
    .y = v.y * scalar,
    .z = v.z * scalar,
    .w = v.w * scalar,
  };
}

float vec4f_dot (vec4 a, vec4 b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

vec4 vec4f_lerp (vec4 a, vec4 b, float t) {
  return (vec4){
    .x = a.x + (b.x - a.x) * t,
    .y = a.y + (b.y - a.y) * t,
    .z = a.z + (b.z - a.z) * t,
    .w = a.w + (b.w - a.w) * t,
  };
}

vec4 vec4f_lerpclamped (vec4 a, vec4 b, float n) {
  /*clamp n between 0 and 1*/
  n = n < 0.0f ? 0.0f : n;
  n = n > 1.0f ? 1.0f : n;
  /*perform lerp*/
  return (vec4){
    .x = a.x + (b.x - a.x) * n,
    .y = a.y + (b.y - a.y) * n,
    .z = a.z + (b.z - a.z) * n,
    .w = a.w + (b.w - a.w) * n,
  };
}

vec4 vec4f_max (vec4 a, vec4 b) {
  return (vec4){
    .x = a.x >= b.x ? a.x : b.x,
    .y = a.y >= b.y ? a.y : b.y,
    .z = a.z >= b.z ? a.z : b.z,
    .w = a.w >= b.w ? a.w : b.w,
  };
}

vec4 vec4f_min (vec4 a, vec4 b) {
  return (vec4){
    .x = a.x <= b.x ? a.x : b.x,
    .y = a.y <= b.y ? a.y : b.y,
    .z = a.z <= b.z ? a.z : b.z,
    .w = a.w <= b.w ? a.w : b.w,
  };
}

vec2 vec4_toVec2 (vec4 v) {
  return (vec2){ .x = v.x, .y = v.y };
}

vec3 vec4_toVec3 (vec4 v) {
  return (vec3){ .x = v.x, .y = v.y, .z = v.z };
}
