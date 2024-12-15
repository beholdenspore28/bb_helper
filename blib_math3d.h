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

-----------------------------------------------------------------------------*/
#ifndef BLIB_MATH3D_H
#define BLIB_MATH3D_H

#include "blib/blib.h"
#include "blib_math.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct {
	float x;
	float y;
} vec2_t;
DECLARE_LIST(vec2_t)

typedef struct {
	float x;
	float y;
	float z;
} vec3_t;
DECLARE_LIST(vec3_t)

typedef struct {
	float x;
	float y;
	float z;
	float w;
} vec4_t;
DECLARE_LIST(vec4_t)

typedef struct {
	float elements[16];
} mat4_t;
DECLARE_LIST(mat4_t)

typedef struct {
	float w;
	float x;
	float y;
	float z;
} quat_t;
DECLARE_LIST(quat_t)

static inline vec2_t vec2_zero(void) {
	return (vec2_t){0.0f, 0.0f};
}

static inline vec2_t vec2_one(float s) {
	return (vec2_t){s, s};
}

static inline vec2_t vec2_up(float s) {
	return (vec2_t){0.0f, s};
}

static inline vec2_t vec2_down(float s) {
	return (vec2_t){0.0f, -s};
}

static inline vec2_t vec2_right(float s) {
	return (vec2_t){s, 0.0f};
}

static inline vec2_t vec2_left(float s) {
	return (vec2_t){-s, 0.0f};
}

static inline vec3_t vec3_zero(void) {
	return (vec3_t){0.0f, 0.0f, 0.0f};
}

static inline vec3_t vec3_one(float s) {
	return (vec3_t){s, s, s};
}

static inline vec3_t vec3_up(float s) {
	return (vec3_t){0.0f, s, 0.0f};
}
static inline vec3_t vec3_down(float s) {
	return (vec3_t){0.0f, -s, 0.0f};
}

static inline vec3_t vec3_right(float s) {
	return (vec3_t){s, 0.0f, 0.0f};
}

static inline vec3_t vec3_left(float s) {
	return (vec3_t){-s, 0.0f, 0.0f};
}

static inline vec3_t vec3_forward(float s) {
	return (vec3_t){0.0f, 0.0f, s};
}

static inline vec3_t vec3_back(float s) {
	return (vec3_t){0.0f, 0.0f, -s};
}

static inline vec4_t vec4_zero(void) {
	return (vec4_t){0.0f, 0.0f, 0.0f, 1.0f};
}

static inline vec4_t vec4_one(float s) {
	return (vec4_t){s, s, s, 1.0f};
}

static inline vec4_t vec4_up(float s) {
	return (vec4_t){0.0f, s, 0.0f, 1.0f};
}

static inline vec4_t vec4_down(float s) {
	return (vec4_t){0.0f, -s, 0.0f, 1.0f};
}

static inline vec4_t vec4_right(float s) {
	return (vec4_t){s, 0.0f, 0.0f, 1.0f};
}

static inline vec4_t vec4_left(float s) {
	return (vec4_t){-s, 0.0f, 0.0f, 1.0f};
}

static inline vec4_t vec4_forward(float s) {
	return (vec4_t){0.0f, 0.0f, s, 1.0f};
}

static inline vec4_t vec4_back(float s) {
	return (vec4_t){0.0f, 0.0f, -s, 1.0f};
}

/*Prints a vec "v" using printf*/
static inline void vec2_print(const vec2_t v, const char *label) {
	printf("%s [%f, %f]\n", label, v.x, v.y);
}

/*Returns a vec that points in the opposite direction of the given vec
  "v". The vec returned has a magnitude identical to the given vec "v"*/
static inline vec2_t vec2_negate(vec2_t v) {
	return (vec2_t){.x = -v.x, .y = -v.y};
}

/*Subtracts a vec "subtrahend" from another vec "minuend"*/
static inline vec2_t vec2_subtract(vec2_t minuend, vec2_t subtrahend) {
	return (vec2_t){.x = minuend.x - subtrahend.x,
		.y = minuend.y - subtrahend.y};
}

/*Adds a vec "a" to another vec "b"*/
static inline vec2_t vec2_add(vec2_t a, vec2_t b) {
	return (vec2_t){.x = a.x + b.x, .y = a.y + b.y};
}

/*A more performant way of getting the relative length of a
  vec "v". This saves a square root operation making it more
  performant than vec2_Magnitude(). If all you have to do is
  compare a vecs length relatively, use this function instead of
  vec2_Magnitude()*/
static inline float vec2_square_magnitude(vec2_t v) {
	return ((v.x * v.x) + (v.y * v.y));
}

/*Returns the actual length of a vec "v".
  This uses a square root operation. Use vec2_SquareMagnitudenitude()
  to sacrifice accuracy and save on performance when comparing
  distances.*/
static inline float vec2_magnitude(vec2_t v) {
	return sqrt(vec2_square_magnitude(v));
}

/*Returns a given vec "v" as a unit vec.
  This means the magnitude(length) of the returned
  vec will always be 1 unit. The returned vec always points
  in the same direction as the given vec "v"*/
static inline vec2_t vec2_normalize(vec2_t v) {
	float m = vec2_magnitude(v);
	if (m == 0)
		return vec2_zero();
	return (vec2_t){.x = v.x / m, .y = v.y / m};
}

/*Returns the distance between point a and point b
  in units.*/
static inline float vec2_distance(vec2_t a, vec2_t b) {
	return vec2_magnitude(vec2_subtract(b, a));
}

/*Returns the distance squared between point a and point b
  in units. Faster than vec2_distance, but the result is the distance squared*/
static inline float vec2_square_distance(vec2_t a, vec2_t b) {
	return vec2_square_magnitude(vec2_subtract(b, a));
}

/*Scales a vec "v" by "scalar".
  increases the magnitude when "scalar" is greater than 1.
  decreases the magnitude when "scalar" is less than 0.
  The returned vec will point in the same direction as
  the given vec "v".*/
static inline vec2_t vec2_scale(vec2_t v, float scalar) {
	return (vec2_t){.x = v.x * scalar, .y = v.y * scalar};
}

/*For normalized vecs Dot returns 1 if they point in
  exactly the same direction, -1 if they point in completely opposite directions
  and zero if the vecs are perpendicular.*/
static inline float vec2_dot(vec2_t a, vec2_t b) {
	return (a.x * b.x) + (a.y * b.y);
}

/* Returns the position of a physical body over time by using the given
 * 'acceleration' 'velocity' 'position' and 'time' arguments*/
static inline vec3_t vec3_kinematic_equation(
		vec3_t acceleration, 
		vec3_t velocity,
		vec3_t position, 
		float time) {
	float x = 0.5f * acceleration.x * time * time + velocity.x * time + position.x;
	float y = 0.5f * acceleration.y * time * time + velocity.y * time + position.y;
	float z = 0.5f * acceleration.z * time * time + velocity.z * time + position.z;
	return (vec3_t){x, y, z};
}

/*Linearly interpolates between "a" and "b" by "t".
If you want to make sure the returned value stays
between "a" and "b", use vec3_Lerpclamped() instead.
Returns a point at "t"% of the way between "a" and "b".*/
static inline vec2_t vec2_lerp(vec2_t a, vec2_t b, float t) {
	return (vec2_t){
		.x = a.x + (b.x - a.x) * t,
		.y = a.y + (b.y - a.y) * t,
	};
}

/*Linearly interpolates between "a" and "b" by "t".
  Returns a point at "t"% of the way between "a" and "b".*/
static inline vec2_t vec2_lerp_clamped(vec2_t a, vec2_t b, float t) {
	/*clamp n between 0 and 1*/
	t = t < 0.0f ? 0.0f : t;
	t = t > 1.0f ? 1.0f : t;
	/*perform lerp*/
	return (vec2_t){
		.x = a.x + (b.x - a.x) * t,
			.y = a.y + (b.y - a.y) * t,
	};
}

/*Converts a 2 dimensional vec to a 3 dimensional one*/
static inline vec3_t vec2_to_vec3(vec2_t v) {
	return (vec3_t){.x = v.x, .y = v.y, .z = 0.0f};
}

/*Converts a 2 dimensional vec to a 4 dimensional one*/
static inline vec4_t vec2_to_vec4(vec2_t v) {
	return (vec4_t){.x = v.x, .y = v.y, .z = 0.0f, .w = 1.0f};
}

/*Prints a vec "v" using printf*/
static inline void vec3_print(const vec3_t v, const char *label) {
	printf("%s [%f, %f, %f]\n", label, v.x, v.y, v.z);
}

/*Returns a vec that points in the opposite direction of the given vec
  "v". The vec returned has a magnitude identical to the given vec "v"*/
static inline vec3_t vec3_negate(vec3_t v) {
	return (vec3_t){.x = -v.x, .y = -v.y, .z = -v.z};
}

/*Adds a vec "a" to another vec "b"*/
static inline vec3_t vec3_add(vec3_t a, vec3_t b) {
	return (vec3_t){.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z};
}

/*Subtracts a vec "subtrahend" from another vec "minuend"*/
static inline vec3_t vec3_subtract(vec3_t minuend, vec3_t subtrahend) {
	return (vec3_t){.x = minuend.x - subtrahend.x,
		.y = minuend.y - subtrahend.y,
		.z = minuend.z - subtrahend.z};
}

/*A more performant way of getting the relative length of a
  vec "v". This saves a square root operation making it more
  performant than vec3_Magnitude(). If all you have to do is
  compare a vecs length relatively, use this function instead of
  vec3_Magnitude()*/
static inline float vec3_square_magnitude(vec3_t v) {
	return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

/*Returns the actual length of a vec "v".
  This uses a square root operation. Use vec3_SquareMagnitudenitude()
  to sacrifice accuracy and save on performance when comparing
  distances.*/
static inline float vec3_magnitude(vec3_t v) {
	return sqrt(vec3_square_magnitude(v));
}

/*Returns a given vec "v" as a unit vec.
  This means the magnitude(length) of the returned
  vec will always be 1 unit. The returned vec always points
  in the same direction as the given vec "v"*/
static inline vec3_t vec3_normalize(vec3_t v) {
	float m = vec3_magnitude(v);
	if (m == 0)
		return vec3_zero();
	return (vec3_t){.x = v.x / m, .y = v.y / m, .z = v.z / m};
}

/*Returns the distance between point a and point b
  in units.*/
static inline float vec3_distance(vec3_t a, vec3_t b) {
	return vec3_magnitude(vec3_subtract(b, a));
}

/*Returns the distance squared between point a and point b
  in units. Faster than vec3_distance, but the result is the distance squared*/
static inline float vec3_square_distance(vec3_t a, vec3_t b) {
	return vec3_square_magnitude(vec3_subtract(b, a));
}

/*Scales a vec "v" by "scalar".
  increases the magnitude when "scalar" is greater than 1.
  decreases the magnitude when "scalar" is less than 1.
  The returned vec will point in the same direction as
  the given vec "v".*/
static inline vec3_t vec3_scale(vec3_t v, float scalar) {
	return (vec3_t){.x = v.x * scalar, .y = v.y * scalar, .z = v.z * scalar};
}

/*Returns a vec parallel to both "a" and "b".*/
static inline vec3_t vec3_cross(vec3_t a, vec3_t b) {
	return (vec3_t){.x = (a.y * b.z) - (a.z * b.y),
		.y = -((a.x * b.z) - (a.z * b.x)),
		.z = (a.x * b.y) - (a.y * b.x)};
}

/*For normalized vecs Dot returns 1 if they point in
  exactly the same direction, -1 if they point in completely opposite directions
  and zero if the vecs are perpendicular.*/
static inline float vec3_dot(vec3_t a, vec3_t b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

/*Linearly interpolates between "a" and "b" by "t".
  If you want to make sure the returned value stays
  between "a" and "b", use vec2_Lerpclamped() instead.
  Returns a point at "t"% of the way between "a" and "b".*/
static inline vec3_t vec3_lerp(vec3_t a, vec3_t b, float t) {
	return (vec3_t){
		.x = a.x + (b.x - a.x) * t,
			.y = a.y + (b.y - a.y) * t,
			.z = a.z + (b.z - a.z) * t,
	};
}

/*Linearly interpolates between "a" and "b" by "t".
  Returns a point at "t"% of the way between "a" and "b".*/
static inline vec3_t vec3_lerp_clamped(vec3_t a, vec3_t b, float n) {
	/*clamp n between 0 and 1*/
	n = n < 0.0f ? 0.0f : n;
	n = n > 1.0f ? 1.0f : n;
	/*perform lerp*/
	return (vec3_t){
		.x = a.x + (b.x - a.x) * n,
			.y = a.y + (b.y - a.y) * n,
			.z = a.z + (b.z - a.z) * n,
	};
}

/*Returns a vec that is made from the largest components of two
  vecs.*/
static inline vec3_t vec3_max(vec3_t a, vec3_t b) {
	return (vec3_t){
		.x = a.x >= b.x ? a.x : b.x,
			.y = a.y >= b.y ? a.y : b.y,
			.z = a.z >= b.z ? a.z : b.z,
	};
}

/*Returns a vec that is made from the smallest components of two
  vecs.*/
static inline vec3_t vec3_min(vec3_t a, vec3_t b) {
	return (vec3_t){
		.x = a.x <= b.x ? a.x : b.x,
			.y = a.y <= b.y ? a.y : b.y,
			.z = a.z <= b.z ? a.z : b.z,
	};
}

/*Converts a 3 dimensional vec to a 2 dimensional one*/
static inline vec2_t vec3_to_vec2(vec3_t v) {
	return (vec2_t){.x = v.x, .y = v.y};
}

/*Converts a 3 dimensional vec to a 4 dimensional one*/
static inline vec4_t vec3_to_vec4(vec3_t v) {
	return (vec4_t){.x = v.x, .y = v.y, .z = v.z, .w = 1.0f};
}

/*Prints a vec "v" using printf*/
static inline void vec4_print(const vec4_t v, const char *label) {
	printf("%s [%f, %f, %f, %f]\n", label, v.x, v.y, v.z, v.w);
}

/*Returns a vec that points in the opposite direction of the given vec
  "v". The vec returned has a magnitude identical to the given vec "v"*/
static inline vec4_t vec4_negate(vec4_t v) {
	return (vec4_t){.x = -v.x, .y = -v.y, .z = -v.z, .w = -v.w};
}

/*A more performant way of getting the relative length of a
  vec "v". This saves a square root operation making it more
  performant than vec4_Magnitude(). If all you have to do is
  compare a vecs length relatively, use this function instead of
  vec4_Magnitude()*/
static inline float vec4_square_magnitude(vec4_t v) {
	return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

/*Returns the actual length of a vec "v".
  This uses a square root operation. Use vec4_SquareMagnitudenitude()
  to sacrifice accuracy and save on performance when comparing
  distances.*/
static inline float vec4_magnitude(vec4_t v) {
	return sqrt(vec4_square_magnitude(v));
}

/*Returns a given vec "v" as a unit vec.
  This means the magnitude(length) of the returned
  vec will always be 1 unit. The returned vec always points
  in the same direction as the given vec "v"*/
static inline vec4_t vec4_normalize(vec4_t v) {
	float m = vec4_magnitude(v);
	if (m == 0)
		return vec4_zero();
	return (vec4_t){.x = v.x / m, .y = v.y / m, .z = v.z / m, .w = v.w / m};
}

/*Adds a vec "a" to another vec "b"*/
static inline vec4_t vec4_add(vec4_t a, vec4_t b) {
	return (vec4_t){
		.x = a.x + b.x,
			.y = a.y + b.y,
			.z = a.z + b.z,
			.w = a.w + b.w,
	};
}

/*Subtracts a vec "subtrahend" from another vec "minuend"*/
static inline vec4_t vec4_subtract(vec4_t minuend, vec4_t subtrahend) {
	return (vec4_t){
		.x = minuend.x - subtrahend.x,
			.y = minuend.y - subtrahend.y,
			.z = minuend.z - subtrahend.z,
			.w = minuend.w - subtrahend.w,
	};
}

/*Returns the distance between point a and point b
  in units.*/
static inline float vec4_distance(vec4_t a, vec4_t b) {
	return vec4_magnitude(vec4_subtract(b, a));
}

/*Returns the distance squared between point a and point b
  in units. Faster than vec4_distance, but the result is the distance squared*/
static inline float vec4_square_distance(vec4_t a, vec4_t b) {
	return vec4_square_magnitude(vec4_subtract(b, a));
}

/*Scales a vec "v" by "scalar".
  increases the magnitude when "scalar" is greater than 1.
  decreases the magnitude when "scalar" is less than 1.
  The returned vec will point in the same direction as
  the given vec "v".*/
static inline vec4_t vec4_scale(vec4_t v, float scalar) {
	return (vec4_t){
		.x = v.x * scalar,
			.y = v.y * scalar,
			.z = v.z * scalar,
			.w = v.w * scalar,
	};
}

/*For normalized vecs Dot returns 1 if they point in
  exactly the same direction, -1 if they point in completely opposite directions
  and zero if the vecs are perpendicular.*/
static inline float vec4_dot(vec4_t a, vec4_t b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

/*Linearly interpolates between "a" and "b" by "t".
  If you want to make sure the returned value stays
  between "a" and "b", use vec2_lerpclamped() instead.
  Returns a point at "t"% of the way between "a" and "b".*/
static inline vec4_t vec4_lerp(vec4_t a, vec4_t b, float t) {
	return (vec4_t){
		.x = a.x + (b.x - a.x) * t,
			.y = a.y + (b.y - a.y) * t,
			.z = a.z + (b.z - a.z) * t,
			.w = a.w + (b.w - a.w) * t,
	};
}

/*Linearly interpolates between "a" and "b" by "t".
  Returns a point at "t"% of the way between "a" and "b".*/
static inline vec4_t vec4_Lerpclamped(vec4_t a, vec4_t b, float n) {
	/*clamp n between 0 and 1*/
	n = n < 0.0f ? 0.0f : n;
	n = n > 1.0f ? 1.0f : n;
	/*perform lerp*/
	return (vec4_t){
		.x = a.x + (b.x - a.x) * n,
			.y = a.y + (b.y - a.y) * n,
			.z = a.z + (b.z - a.z) * n,
			.w = a.w + (b.w - a.w) * n,
	};
}

/*Returns a vec that is made from the largest components of two
  vecs.*/
static inline vec4_t vec4_Max(vec4_t a, vec4_t b) {
	return (vec4_t){
		.x = a.x >= b.x ? a.x : b.x,
			.y = a.y >= b.y ? a.y : b.y,
			.z = a.z >= b.z ? a.z : b.z,
			.w = a.w >= b.w ? a.w : b.w,
	};
}

/*Returns a vec that is made from the smallest components of two
  vecs.*/
static inline vec4_t vec4_Min(vec4_t a, vec4_t b) {
	return (vec4_t){
		.x = a.x <= b.x ? a.x : b.x,
			.y = a.y <= b.y ? a.y : b.y,
			.z = a.z <= b.z ? a.z : b.z,
			.w = a.w <= b.w ? a.w : b.w,
	};
}

/*Converts a 4 dimensional vec to a 2 dimensional one*/
static inline vec2_t vec4_ToVec2(vec4_t v) {
	return (vec2_t){.x = v.x, .y = v.y};
}

/*Converts a 4 dimensional vec to a 3 dimensional one*/
static inline vec3_t vec4_ToVec3(vec4_t v) {
	return (vec3_t){.x = v.x, .y = v.y, .z = v.z};
}
static inline mat4_t mat4_identity(void) {
	// clang-format off
	return (mat4_t){
		.elements = {
			1.0f, 0.0f, 0.0f, 0.0f, 
			0.0f, 1.0f, 0.0f, 0.0f, 
			0.0f, 0.0f, 1.0f, 0.0f, 
			0.0f, 0.0f, 0.0f, 1.0f
		}
	};
	// clang-format on
}

static inline mat4_t mat4_lookAt(vec3_t eye, vec3_t center,
		vec3_t up) {
	vec3_t f = vec3_normalize(vec3_subtract(eye, center));
	vec3_t s = vec3_normalize(vec3_cross(f, up));
	vec3_t u = vec3_cross(s, f);

	mat4_t ret = mat4_identity();
	ret.elements[0] = s.x;
	ret.elements[1] = u.x;
	ret.elements[2] = -f.x;
	ret.elements[3] = 0.0f;

	ret.elements[4] = s.y;
	ret.elements[5] = u.y;
	ret.elements[6] = -f.y;
	ret.elements[7] = 0.0f;

	ret.elements[8] = s.z;
	ret.elements[9] = u.z;
	ret.elements[10] = -f.z;
	ret.elements[11] = 0.0f;

	ret.elements[12] = -vec3_dot(s, eye);
	ret.elements[13] = -vec3_dot(u, eye);
	ret.elements[14] = vec3_dot(f, eye);
	ret.elements[15] = 1.0f;

	return ret;
}

/*Returns the difference between two 4x4 matrices.*/
static inline mat4_t mat4_Subtract(const mat4_t min,
		const mat4_t sub) {
	mat4_t dif = mat4_identity();
	int i = 0;

	for (i = 0; i < 16; i++)
		dif.elements[i] = min.elements[i] - sub.elements[i];

	return dif;
}

static inline mat4_t mat4_perspective(float fov, float aspect,
		float near, float far) {
	mat4_t result = mat4_identity();
	float Cotangent = (1.0f / tanf(fov / 2.0f));
	result.elements[0] = (Cotangent / aspect);
	result.elements[5] = Cotangent;
	result.elements[10] = -((near + far) / (near - far)); // negate for lh coords
	result.elements[11] = 1.0f;                           // negate for lh coords
	result.elements[14] = ((2.0f * near * far) / (near - far));
	return result;
}

/*Multiplies a 4x4 matrix with a 3 dimensional vec*/
static inline vec3_t mat4_multiplyVec3(vec3_t Left, mat4_t Right) {
	vec3_t result;
	result.y = Left.y * Right.elements[0];
	result.x = Left.y * Right.elements[4];
	result.z = Left.y * Right.elements[8];

	result.y += Left.x * Right.elements[1];
	result.x += Left.x * Right.elements[5];
	result.z += Left.x * Right.elements[9];

	result.y += Left.z * Right.elements[2];
	result.x += Left.z * Right.elements[6];
	result.z += Left.z * Right.elements[10];

	return result;
}

/*Multiplies a 4x4 matrix with a 4 dimensional vec*/
static inline vec4_t mat4_multiplyVec4(vec4_t Left, mat4_t Right) {
	vec4_t result;
	result.y = Left.y * Right.elements[0];
	result.x = Left.y * Right.elements[4];
	result.z = Left.y * Right.elements[8];
	result.w = Left.y * Right.elements[12];

	result.y += Left.x * Right.elements[1];
	result.x += Left.x * Right.elements[5];
	result.z += Left.x * Right.elements[9];
	result.w += Left.x * Right.elements[13];

	result.y += Left.z * Right.elements[2];
	result.x += Left.z * Right.elements[6];
	result.z += Left.z * Right.elements[10];
	result.w += Left.z * Right.elements[13];

	result.y += Left.w * Right.elements[3];
	result.x += Left.w * Right.elements[7];
	result.z += Left.w * Right.elements[11];
	result.w += Left.w * Right.elements[15];

	return result;
}

/*Multiplies a 4x4 matrix with another 4x4 matrix*/
static inline mat4_t mat4_multiply(const mat4_t a,
		const mat4_t b) {
	return (mat4_t){
		.elements = {
			// column 0
			a.elements[0] * b.elements[0] + a.elements[4] * b.elements[1] +
				a.elements[8] * b.elements[2] + a.elements[12] * b.elements[3],
				a.elements[0] * b.elements[1] + a.elements[1] * b.elements[5] +
					a.elements[2] * b.elements[9] + a.elements[3] * b.elements[13],
					a.elements[0] * b.elements[2] + a.elements[1] * b.elements[6] +
						a.elements[2] * b.elements[10] + a.elements[3] * b.elements[14],
						a.elements[0] * b.elements[3] + a.elements[1] * b.elements[7] +
							a.elements[2] * b.elements[11] + a.elements[3] * b.elements[15],

							// column 1
							a.elements[4] * b.elements[0] + a.elements[5] * b.elements[4] +
								a.elements[6] * b.elements[8] + a.elements[7] * b.elements[12],
								a.elements[4] * b.elements[1] + a.elements[5] * b.elements[5] +
									a.elements[6] * b.elements[9] + a.elements[7] * b.elements[13],
									a.elements[4] * b.elements[2] + a.elements[5] * b.elements[6] +
										a.elements[6] * b.elements[10] + a.elements[7] * b.elements[14],
										a.elements[4] * b.elements[3] + a.elements[5] * b.elements[7] +
											a.elements[6] * b.elements[11] + a.elements[7] * b.elements[15],

											// column 2
											a.elements[8] * b.elements[0] + a.elements[9] * b.elements[4] +
												a.elements[10] * b.elements[8] + a.elements[11] * b.elements[12],
												a.elements[8] * b.elements[1] + a.elements[9] * b.elements[5] +
													a.elements[10] * b.elements[9] + a.elements[11] * b.elements[13],
													a.elements[8] * b.elements[2] + a.elements[9] * b.elements[6] +
														a.elements[10] * b.elements[10] + a.elements[11] * b.elements[14],
														a.elements[8] * b.elements[3] + a.elements[9] * b.elements[7] +
															a.elements[10] * b.elements[11] + a.elements[11] * b.elements[15],

															// column 3
															a.elements[12] * b.elements[0] + a.elements[13] * b.elements[4] +
																a.elements[14] * b.elements[8] + a.elements[15] * b.elements[12],
																a.elements[12] * b.elements[1] + a.elements[13] * b.elements[5] +
																	a.elements[14] * b.elements[9] + a.elements[15] * b.elements[13],
																	a.elements[12] * b.elements[2] + a.elements[13] * b.elements[6] +
																		a.elements[14] * b.elements[10] + a.elements[15] * b.elements[14],
																		a.elements[12] * b.elements[3] + a.elements[13] * b.elements[7] +
																			a.elements[14] * b.elements[11] +
																			a.elements[15] * b.elements[15]}};
}

/*Scales (multiplies) a 4x4 matrix by a scalar (number)*/
static inline mat4_t mat4_scale(const vec3_t scale) {
	mat4_t m = {0};
	m.elements[0]  = scale.x;
	m.elements[5]  = scale.y;
	m.elements[10] = scale.z;
	m.elements[15] = 1.0f;
	return m;
}

// returns a translation matrix from the specified vec4_t 'v'
static inline mat4_t mat4_translate(vec3_t v) {
	mat4_t result = mat4_identity();
	result.elements[12] = v.x;
	result.elements[13] = v.y;
	result.elements[14] = v.z;
	return result;
}

/*Prints a formatted mat4_t to the console.*/
static inline void mat4_print(mat4_t m, const char *label) {
	// TODO condense this to one printf call.
	printf("--------------------------------\n");
	printf("mat4: %s\n", label);
	printf("[0] %8f \t", m.elements[0]);
	printf("[4] %8f \t", m.elements[4]);
	printf("[8] %8f \t", m.elements[8]);
	printf("[12]%8f \t", m.elements[12]);
	printf("\n");
	printf("[1] %8f \t", m.elements[1]);
	printf("[5] %8f \t", m.elements[5]);
	printf("[9] %8f \t", m.elements[9]);
	printf("[13]%8f \t", m.elements[13]);
	printf("\n");
	printf("[2] %8f \t", m.elements[2]);
	printf("[6] %8f \t", m.elements[6]);
	printf("[10]%8f \t", m.elements[10]);
	printf("[14]%8f \t", m.elements[14]);
	printf("\n");
	printf("[3] %8f \t", m.elements[3]);
	printf("[7] %8f \t", m.elements[7]);
	printf("[11]%8f \t", m.elements[11]);
	printf("[15]%8f \t", m.elements[15]);
	printf("\n--------------------------------\n");
}

static inline quat_t quat_Set(float x, float y, float z, float w) {
	return (quat_t){
		.w = w,
			.x = x,
			.y = y,
			.z = z,
	};
}

static inline quat_t quat_identity(void) {
	return (quat_t){.x = 0.0f, .y = 0.0f, .z = 0.0f, .w = 1.0f};
}

static inline int quat_equal(quat_t a, quat_t b) {
	return
		fabs(a.x - b.x) <= FLOAT_EPSILON &&
		fabs(a.y - b.y) <= FLOAT_EPSILON &&
		fabs(a.z - b.z) <= FLOAT_EPSILON &&
		fabs(a.w - b.w) <= FLOAT_EPSILON;
}

static inline quat_t quat_FromAngleAxis(float angle, vec3_t axis) {
	quat_t ret;
	float s = sinf(angle/2);
	ret.x = axis.x * s;
	ret.y = axis.y * s;
	ret.z = axis.z * s;
	ret.w = cosf(angle/2);
	return ret;
}

static inline float quat_magnitude(quat_t q) {
	return sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
}

static inline quat_t quat_normalize(quat_t q) {
	float mag = quat_magnitude(q);
	if (mag == 0) {
		return quat_identity();
	}
	q.w /= mag;
	q.x /= mag;
	q.y /= mag;
	q.z /= mag;
	return q;
}

static inline quat_t quat_conjugate(quat_t q) {
	return (quat_t) { 
		.w = q.w, 
			.x = -q.x, 
			.y = -q.y, 
			.z = -q.z 
	};
}

static inline quat_t quat_inverse(quat_t q) {
	return (quat_t) {
		.w = -q.w,
			.x = -q.x,
			.y = -q.y,
			.z = -q.z,
	};
}

static inline void quat_print(quat_t q, const char *label) {
	printf("\t%12f, %12f, %12f, %12f\t%s\n", q.x, q.y, q.z, q.w, label);
}

static inline quat_t quat_add(quat_t q1, quat_t q2) {
	return (quat_t) {
		.w = q1.w + q2.w,
			.x = q1.x + q2.x,
			.y = q1.y + q2.y,
			.z = q1.z + q2.z,
	};
}

static inline quat_t quat_multiply(quat_t q1, quat_t q2) {
	quat_t ret = {0};
	ret.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	ret.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	ret.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	ret.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	return ret;
}

/*
   Returns the given vec 'v' rotated by the quat_t 'rotation'.
   */
static inline vec3_t vec3_rotate(vec3_t v, quat_t rotation) {
	quat_t ret = (quat_t) {
		.w = 0,
			.x = v.x,
			.y = v.y,
			.z = v.z,
	};

	ret = quat_multiply(quat_multiply(rotation, ret), quat_conjugate(rotation));

	return (vec3_t) { 
		.x = ret.x, 
			.y = ret.y, 
			.z = ret.z,
	};
}

static inline quat_t quat_from_euler(vec3_t eulerAngles) {
	quat_t q;

	float cRoll = cosf(eulerAngles.x * 0.5f);
	float sRoll = sinf(eulerAngles.x * 0.5f);
	float cPitch = cosf(eulerAngles.y * 0.5f);
	float sPitch = sinf(eulerAngles.y * 0.5f);
	float cYaw = cosf(eulerAngles.z * 0.5f);
	float sYaw = sinf(eulerAngles.z * 0.5f);
	q.w = cRoll * cPitch * cYaw + sRoll * sPitch * sYaw;
	q.x = sRoll * cPitch * cYaw - cRoll * sPitch * sYaw;
	q.y = cRoll * sPitch * cYaw + sRoll * cPitch * sYaw;
	q.z = cRoll * cPitch * sYaw - sRoll * sPitch * cYaw;

	return q;
}

static inline mat4_t quat_to_mat4(quat_t q) {
	mat4_t mat = mat4_identity();
	float* m = mat.elements;

	float xx = q.x * q.x;
	float xy = q.x * q.y;
	float xz = q.x * q.z;
	float xw = q.x * q.w;

	float yy = q.y * q.y;
	float yz = q.y * q.z;
	float yw = q.y * q.w;

	float zz = q.z * q.z;
	float zw = q.z * q.w;

	m[0]  = 1 - 2 * ( yy + zz );
	m[4]  =     2 * ( xy - zw );
	m[8]  =     2 * ( xz + yw );

	m[1]  =     2 * ( xy + zw );
	m[5]  = 1 - 2 * ( xx + zz );
	m[9]  =     2 * ( yz - xw );

	m[2]  =     2 * ( xz - yw );
	m[6]  =     2 * ( yz + xw );
	m[10] = 1 - 2 * ( xx + yy );

	m[12] = m[13] = m[14] = m[3] = m[7] = m[11] = 0;
	m[15] = 1;

	return mat;
}

#ifdef __cplusplus
} // extern "C" {
#endif // __cplusplus

#endif // BLIB_MATH3D_H

#ifdef BLIB_IMPLEMENTATION

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

DEFINE_LIST(vec4_t)
DEFINE_LIST(vec3_t)
DEFINE_LIST(vec2_t)
DEFINE_LIST(quat_t)
DEFINE_LIST(mat4_t)

#ifdef __cplusplus
} // extern "C" {
#endif // __cplusplus

#endif
