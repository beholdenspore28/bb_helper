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

#include "blib_math.h"
#include <math.h>

/* 
row major
0,  1,  2,  3
4,  5,  6,  7
8,  9,  10, 11
12,  13,  14, 15
 
column major
0,  4,  8,  12
1,  5,  9,  13
2,  6,  10, 14
3,  7,  11, 15
*/

const blib_mat4_t BLIB_MAT4_IDENTITY = (blib_mat4_t){
	.elements={
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	}
};

void blib_mat4_printf(blib_mat4_t m, const char* label){
	printf("--------------------------------\n");
	printf("MATRIX4: %s\n", label);

	//use this for row major printing
	// for (i = 0; i < 16; i++) {
	// 	if (i == 4 || i == 8 || i == 12) printf("\n");
	// 	printf("i%li\t%f\t",i,m.elements[i]);
	// }
	
	//use this for column major printing
	printf("[0](%f) ", m.elements[0]);
	printf("[4](%f) ", m.elements[4]);
	printf("[8](%f) ", m.elements[8]);
	printf("[12](%f) ", m.elements[12]);
	printf("\n");
	printf("[1](%f) ", m.elements[1]);
	printf("[5](%f) ", m.elements[5]);
	printf("[9](%f) ", m.elements[9]);
	printf("[13](%f) ", m.elements[13]);
	printf("\n");
	printf("[2](%f) ", m.elements[2]);
	printf("[6](%f) ", m.elements[6]);
	printf("[10](%f) ", m.elements[10]);
	printf("[14](%f) ", m.elements[14]);
	printf("\n");
	printf("[3](%f) ", m.elements[3]);
	printf("[7](%f) ", m.elements[7]);
	printf("[11](%f) ", m.elements[11]);
	printf("[15](%f) ", m.elements[15]);
	printf("\n--------------------------------\n");
}

blib_mat4_t blib_mat4_add(const blib_mat4_t a, const blib_mat4_t b){
	blib_mat4_t sum = BLIB_MAT4_IDENTITY;
	size_t i = 0;
	for (i = 0; i < 16; i++) {
		sum.elements[i] = a.elements[i] + b.elements[i];
	}
	return sum;
}

blib_mat4_t blib_mat4_subtract(const blib_mat4_t min, const blib_mat4_t sub){
	blib_mat4_t dif = BLIB_MAT4_IDENTITY;
	size_t i = 0;
	for (i = 0; i < 16; i++) {
		dif.elements[i] = min.elements[i] - sub.elements[i];
	}
	return dif;
}

blib_mat4_t	blib_mat4_perspective(float fov, float aspect, float near, float far) {
	blib_mat4_t result = BLIB_MAT4_IDENTITY;
	float Cotangent = (1.0f / tanf(fov / 2.0f));
	result.elements[0] = (Cotangent / aspect);
	result.elements[5] = Cotangent;
	result.elements[10] = -((near + far) / (near - far)); //negate for lh coords
	result.elements[11] = 1.0f; //negate for lh coords
	result.elements[14] = ((2.0f * near * far) / (near - far));
	return result;
}

blib_mat4_t blib_mat4_multiply(const blib_mat4_t a, const blib_mat4_t b){
	float b0 = b.elements[0];
	float b1 = b.elements[1];
	float b2 = b.elements[2];
	float b3 = b.elements[3];

	float b4 = b.elements[4];
	float b5 = b.elements[5];
	float b6 = b.elements[6];
	float b7 = b.elements[7];
	
	float b8 = b.elements[8];
	float b9 = b.elements[9];
	float b10 = b.elements[10];
	float b11 = b.elements[11];
	
	float b12 = b.elements[12];
	float b13 = b.elements[13];
	float b14 = b.elements[14];
	float b15 = b.elements[15];

	float a0 = a.elements[0];
	float a1 = a.elements[1];
	float a2 = a.elements[2];
	float a3 = a.elements[3];

	float a4 = a.elements[4];
	float a5 = a.elements[5];
	float a6 = a.elements[6];
	float a7 = a.elements[7];
	
	float a8 = a.elements[8];
	float a9 = a.elements[9];
	float a10 = a.elements[10];
	float a11 = a.elements[11];
	
	float a12 = a.elements[12];
	float a13 = a.elements[13];
	float a14 = a.elements[14];
	float a15 = a.elements[15];


return (blib_mat4_t) {
		.elements = {
			//column 0
			a0 * b0 + a4 * b1 + a8 * b2 + a12 * b3,
			a0 * b1 + a1 * b5 + a2 * b9 + a3 * b13,
			a0 * b2 + a1 * b6 + a2 * b10 + a3 * b14,
			a0 * b3 + a1 * b7 + a2 * b11 + a3 * b15, 
			//column 1
			a4 * b0 + a5 * b4 + a6 * b8 + a7 * b12,
			a4 * b1 + a5 * b5 + a6 * b9 + a7 * b13,
			a4 * b2 + a5 * b6 + a6 * b10 + a7 * b14,
			a4 * b3 + a5 * b7 + a6 * b11 + a7 * b15,
			//column 2
			a8 * b0 + a9 * b4 + a10 * b8 + a11 * b12,
			a8 * b1 + a9 * b5 + a10 * b9 + a11 * b13,
			a8 * b2 + a9 * b6 + a10 * b10 + a11 * b14,
			a8 * b3 + a9 * b7 + a10 * b11 + a11 * b15,
			//column 3
			a12 * b0 + a13 * b4 + a14 * b8 + a15 * b12,
			a12 * b1 + a13 * b5 + a14 * b9 + a15 * b13,
			a12 * b2 + a13 * b6 + a14 * b10 + a15 * b14,
			a12 * b3 + a13 * b7 + a14 * b11 + a15 * b15
		}
	};
}

blib_mat4_t blib_mat4_scale(const blib_vec3f_t scale){
	blib_mat4_t mat = BLIB_MAT4_IDENTITY;
	mat.elements[0] = scale.x;
	mat.elements[5] = scale.y;
	mat.elements[10] = scale.z;
	return mat;
}

blib_mat4_t blib_mat4_rotate(const float angle, blib_vec3f_t axis){
	/*TODO to make this compatible with rh 
	coordinate system, just invert the angle!*/
		blib_mat4_t result = BLIB_MAT4_IDENTITY;

    float sinTheta = sinf(angle);
    float cosTheta = cosf(angle);
    float cosValue = 1.0f - cosTheta;

    result.elements[0] = (axis.x * axis.x * cosValue) + cosTheta;
    result.elements[1] = (axis.x * axis.y * cosValue) + (axis.z * sinTheta);
    result.elements[2] = (axis.x * axis.z * cosValue) - (axis.y * sinTheta);

    result.elements[4] = (axis.y * axis.x * cosValue) - (axis.z * sinTheta);
    result.elements[5] = (axis.y * axis.y * cosValue) + cosTheta;
    result.elements[6] = (axis.y * axis.z * cosValue) + (axis.x * sinTheta);

    result.elements[8] = (axis.z * axis.x * cosValue) + (axis.y * sinTheta);
    result.elements[9] = (axis.z * axis.y * cosValue) - (axis.x * sinTheta);
    result.elements[10] = (axis.z * axis.z * cosValue) + cosTheta;

    return result;
}

blib_mat4_t blib_mat4_translateVec3(blib_vec3f_t t){
	blib_mat4_t result = BLIB_MAT4_IDENTITY;
	result.elements[12] += t.x;
	result.elements[13] += t.y;
	result.elements[14] += t.z;
	return result;
}

blib_mat4_t blib_mat4_translateVec4(blib_vec4f_t t){
	blib_mat4_t result = BLIB_MAT4_IDENTITY;
	result.elements[12] += t.x;
	result.elements[13] += t.y;
	result.elements[14] += t.z;
	result.elements[15] += t.w;
	return result;
}

float blib_mathf_rad2deg(const float n){
	return n * (180.0f/BLIB_PI);
}

float blib_mathf_deg2rad(const float n){
	return n * (BLIB_PI/180.0f);
}

float blib_mathf_clamp(float n, const float min, const float max){
	n = n < min ? min : n;
	return n > max ? max : n;
}

float blib_mathf_clamp01(float n){
	n = n < 0 ? 0 : n;
	return n > 1 ? 1 : n;
}

float blib_mathf_lerp(float a, float b, float t) {
	return a + (b - a) * t;
}

float blib_mathf_lerpclamped(float a, float b, float t) {
	return a + (b - a) * blib_mathf_clamp01(t);
}

float blib_mathf_norm(float n, float min, float max){
	return (n - min) / (max - min);
}

float blib_mathf_map(
		float n, float fromMin, float fromMax, float toMin, float toMax){
	return blib_mathf_lerp(blib_mathf_norm(n, fromMin, fromMax), toMin, toMax);
}

bool blib_mathf_aproxequal(float a, float b, float tolerance){
	return (fabs(a - b) < tolerance);
}

float blib_mathf_cosInterpolate(float a, float b, float t){
	float f = (1.0f - cos(t * BLIB_PI)) * 0.5f;
	return a*(1.0-f) + b*f;
}

float blib_mathf_sigmoid(float n) {
	return (1 / (1 + pow(2.71828182846, -n)));
}

float blib_mathf_loop(float n, const float length){
	return blib_mathf_clamp(n - floor(n / length) * length, 0.0f, length);
}

float blib_mathf_pingpong(float n, const float length){
	n = blib_mathf_loop(n, length * 2.0f);
	return fabs(n - length);
}

float blib_mathf_angleDelta(const float a, const float b){
	float delta = blib_mathf_loop((b - a), 360.0f);
	if (delta > 180.0f){
		delta -= 360.0f;
	}
	return delta;
}

const blib_vec2f_t BLIB_VEC2F_ZERO     =  {.x =  0, .y =  0};
const blib_vec2f_t BLIB_VEC2F_ONE	    =  {.x =  1, .y =  1};
const blib_vec2f_t BLIB_VEC2F_UP       =  {.x =  0, .y =  1};
const blib_vec2f_t BLIB_VEC2F_DOWN     =  {.x =  0, .y = -1};
const blib_vec2f_t BLIB_VEC2F_LEFT     =  {.x = -1, .y =  0};
const blib_vec2f_t BLIB_VEC2F_RIGHT	=  {.x =  1, .y =  0};

float blib_vec2f_magnitude(blib_vec2f_t v){
	return sqrt(blib_vec2f_sqrmagnitude(v));
}

float blib_vec2f_sqrmagnitude(blib_vec2f_t v){
	return ((v.x * v.x) + (v.y * v.y));
}

blib_vec2f_t blib_vec2f_normalize(blib_vec2f_t v){
	float m = blib_vec2f_magnitude(v);
	return (blib_vec2f_t){.x=v.x/m, .y=v.y/m};
}

float blib_vec2f_distance(blib_vec2f_t a, blib_vec2f_t b){
	return blib_vec2f_magnitude(blib_vec2f_subtract(b,a));
}

blib_vec2f_t blib_vec2f_add(blib_vec2f_t a, blib_vec2f_t b){
	return (blib_vec2f_t){
		.x=a.x+b.x,
			.y=a.y+b.y};
}

blib_vec2f_t blib_vec2f_subtract(
		blib_vec2f_t minuend, blib_vec2f_t subtrahend){
	return (blib_vec2f_t){
		.x=minuend.x-subtrahend.x,
			.y=minuend.y-subtrahend.y};
}

blib_vec2f_t blib_vec2f_scale(blib_vec2f_t v, float scalar){
	return (blib_vec2f_t){
		.x=v.x*scalar,
			.y=v.y*scalar};
}

float blib_vec2f_dot(blib_vec2f_t a, blib_vec2f_t b){
	return (a.x * b.x) + (a.y * b.y);
}

blib_vec2f_t blib_vec2f_lerp(blib_vec2f_t a, blib_vec2f_t b, float t){
	return (blib_vec2f_t){
		.x= a.x + (b.x - a.x) * t,
			.y= a.y + (b.y - a.y) * t,
	};
}

blib_vec2f_t blib_vec2f_lerpclamped(blib_vec2f_t a, blib_vec2f_t b, float t){
	/*clamp n between 0 and 1*/
	t = t < 0.0f ? 0.0f : t;
	t = t > 1.0f ? 1.0f : t;
	/*perform lerp*/
	return (blib_vec2f_t){
		.x= a.x + (b.x - a.x) * t,
			.y= a.y + (b.y - a.y) * t,
	};
}

blib_vec3f_t blib_vec2f_toVec3f(blib_vec2f_t v){
	return (blib_vec3f_t){.x=v.x, .y=v.y, .z=0.0f};
}

blib_vec4f_t blib_vec2f_toVec4f(blib_vec2f_t v){
	return (blib_vec4f_t){.x=v.x, .y=v.y, .z=0.0f, .w=1.0f};
}

const blib_vec3f_t BLIB_VEC3F_ZERO     =  {.x =  0.0f, .y =  0.0f, .z =  0.0f};
const blib_vec3f_t BLIB_VEC3F_ONE	     =	{.x =  1.0f, .y =  1.0f, .z =  1.0f};
const blib_vec3f_t BLIB_VEC3F_UP       =  {.x =  0.0f, .y =  1.0f, .z =  0.0f};
const blib_vec3f_t BLIB_VEC3F_DOWN     =  {.x =  0.0f, .y = -1.0f, .z =  0.0f};
const blib_vec3f_t BLIB_VEC3F_LEFT     =  {.x = -1.0f, .y =  0.0f, .z =  0.0f};
const blib_vec3f_t BLIB_VEC3F_RIGHT	   =	{.x =  1.0f, .y =  0.0f, .z =  0.0f};
const blib_vec3f_t BLIB_VEC3F_FORWARD	 =  {.x =  0.0f, .y =  0.0f, .z =  1.0f};
const blib_vec3f_t BLIB_VEC3F_BACK     =	{.x =  0.0f, .y =  0.0f, .z = -1.0f};

float blib_vec3f_magnitude(blib_vec3f_t v){
	return sqrt(blib_vec3f_sqrmagnitude(v));
}

float blib_vec3f_sqrmagnitude(blib_vec3f_t v){
	return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

blib_vec3f_t blib_vec3f_normalize(blib_vec3f_t v){
	float m = blib_vec3f_magnitude(v);
	return (blib_vec3f_t){.x=v.x/m, .y=v.y/m, .z=v.z/m};
}

blib_vec3f_t blib_vec3f_add(blib_vec3f_t a, blib_vec3f_t b){
	return (blib_vec3f_t){
		.x=a.x+b.x,
			.y=a.y+b.y,
			.z=a.z+b.z};
}

blib_vec3f_t blib_vec3f_subtract(
		blib_vec3f_t minuend, blib_vec3f_t subtrahend){
	return (blib_vec3f_t){
		.x=minuend.x-subtrahend.x,
			.y=minuend.y-subtrahend.y,
			.z=minuend.z-subtrahend.z};
}

float blib_vec3f_distance(blib_vec3f_t a, blib_vec3f_t b){
	return blib_vec3f_magnitude(blib_vec3f_subtract(b,a));
}

blib_vec3f_t blib_vec3f_scale(blib_vec3f_t v, float scalar){
	return (blib_vec3f_t){
		.x=v.x*scalar,
			.y=v.y*scalar,
			.z=v.z*scalar};
}

blib_vec3f_t blib_vec3f_cross(blib_vec3f_t a, blib_vec3f_t b){
	return (blib_vec3f_t){
		.x =  (a.y  * b.z) - (a.z * b.y),
			.y = -((a.x * b.z) - (a.z * b.x)),
			.z =  (a.x  * b.y) - (a.y * b.x)};
}

float blib_vec3f_dot(blib_vec3f_t a, blib_vec3f_t b){
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

blib_vec3f_t blib_vec3f_lerp(blib_vec3f_t a, blib_vec3f_t b, float t){
	return (blib_vec3f_t){
		.x= a.x + (b.x - a.x) * t,
			.y= a.y + (b.y - a.y) * t,
			.z= a.z + (b.z - a.z) * t,
	};
}

blib_vec3f_t blib_vec3f_lerpclamped(blib_vec3f_t a, blib_vec3f_t b, float n){
	/*clamp n between 0 and 1*/
	n = n < 0.0f ? 0.0f : n;
	n = n > 1.0f ? 1.0f : n;
	/*perform lerp*/
	return (blib_vec3f_t){
		.x= a.x + (b.x - a.x) * n,
			.y= a.y + (b.y - a.y) * n,
			.z= a.z + (b.z - a.z) * n,
	};
}

blib_vec3f_t blib_vec3f_max(blib_vec3f_t a, blib_vec3f_t b){
	return (blib_vec3f_t){
		.x = a.x >= b.x ? a.x : b.x,
			.y = a.y >= b.y ? a.y : b.y,
			.z = a.z >= b.z ? a.z : b.z,
	};
}

blib_vec3f_t blib_vec3f_min(blib_vec3f_t a, blib_vec3f_t b){
	return (blib_vec3f_t){
		.x = a.x <= b.x ? a.x : b.x,
			.y = a.y <= b.y ? a.y : b.y,
			.z = a.z <= b.z ? a.z : b.z,
	};
}

blib_vec2f_t blib_vec3f_toVec2f(blib_vec3f_t v){
	return (blib_vec2f_t){.x=v.x, .y=v.y};
}

blib_vec4f_t blib_vec3f_toVec4f(blib_vec3f_t v){
	return (blib_vec4f_t){.x=v.x, .y=v.y, .z=v.z, .w=1.0f};
}

const blib_vec4f_t BLIB_VEC4F_ZERO =		{.x =  0, .y =  0, .z =  0, .w = 1.0};
const blib_vec4f_t BLIB_VEC4F_ONE =			{.x =  1, .y =  1, .z =  1, .w = 1.0};
const blib_vec4f_t BLIB_VEC4F_UP =			{.x =  0, .y =  1, .z =  0, .w = 1.0};
const blib_vec4f_t BLIB_VEC4F_DOWN =		{.x =  0, .y = -1, .z =  0, .w = 1.0};
const blib_vec4f_t BLIB_VEC4F_LEFT =		{.x = -1, .y =  0, .z =  0, .w = 1.0};
const blib_vec4f_t BLIB_VEC4F_RIGHT =		{.x =  1, .y =  0, .z =  0, .w = 1.0};
const blib_vec4f_t BLIB_VEC4F_FORWARD =	{.x =  0, .y =  0, .z =  1, .w = 1.0};
const blib_vec4f_t BLIB_VEC4F_BACK =		{.x =  0, .y =  0, .z = -1, .w = 1.0};

float blib_vec4f_magnitude(blib_vec4f_t v){
	return sqrt(blib_vec4f_sqrmagnitude(v));
}

float blib_vec4f_sqrmagnitude(blib_vec4f_t v){
	return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

blib_vec4f_t blib_vec4f_normalize(blib_vec4f_t v){
	float m = blib_vec4f_magnitude(v);
	return (blib_vec4f_t){
		.x = v.x / m, 
			.y = v.y / m, 
			.z = v.z / m, 
			.w = v.w / m};
}

blib_vec4f_t blib_vec4f_add(blib_vec4f_t a, blib_vec4f_t b){
	return (blib_vec4f_t){
		.x = a.x + b.x,
			.y = a.y + b.y,
			.z = a.z + b.z,
			.w = a.w + b.w,
	};
}

blib_vec4f_t blib_vec4f_subtract(blib_vec4f_t minuend, blib_vec4f_t subtrahend){
	return (blib_vec4f_t){
		.x = minuend.x - subtrahend.x,
			.y = minuend.y - subtrahend.y,
			.z = minuend.z - subtrahend.z,
			.w = minuend.w - subtrahend.w,
	};
}

float blib_vec4f_distance(blib_vec4f_t a, blib_vec4f_t b){
	return blib_vec4f_magnitude(blib_vec4f_subtract(b,a));
}

blib_vec4f_t blib_vec4f_scale(blib_vec4f_t v, float scalar){
	return (blib_vec4f_t){
		.x = v.x * scalar,
			.y = v.y * scalar,
			.z = v.z * scalar,
			.w = v.w * scalar,
	};
}

float blib_vec4f_dot(blib_vec4f_t a, blib_vec4f_t b){
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

blib_vec4f_t blib_vec4f_lerp(blib_vec4f_t a, blib_vec4f_t b, float t){
	return (blib_vec4f_t){
		.x = a.x + (b.x - a.x) * t,
			.y = a.y + (b.y - a.y) * t,
			.z = a.z + (b.z - a.z) * t,
			.w = a.w + (b.w - a.w) * t,
	};
}

blib_vec4f_t blib_vec4f_lerpclamped(blib_vec4f_t a, blib_vec4f_t b, float n){
	/*clamp n between 0 and 1*/
	n = n < 0.0f ? 0.0f : n;
	n = n > 1.0f ? 1.0f : n;
	/*perform lerp*/
	return (blib_vec4f_t){
		.x = a.x + (b.x - a.x) * n,
			.y = a.y + (b.y - a.y) * n,
			.z = a.z + (b.z - a.z) * n,
			.w = a.w + (b.w - a.w) * n,
	};
}

blib_vec4f_t blib_vec4f_max(blib_vec4f_t a, blib_vec4f_t b){
	return (blib_vec4f_t){
		.x = a.x >= b.x ? a.x : b.x,
			.y = a.y >= b.y ? a.y : b.y,
			.z = a.z >= b.z ? a.z : b.z,
			.w = a.w >= b.w ? a.w : b.w,
	};
}

blib_vec4f_t blib_vec4f_min(blib_vec4f_t a, blib_vec4f_t b){
	return (blib_vec4f_t){
		.x = a.x <= b.x ? a.x : b.x,
			.y = a.y <= b.y ? a.y : b.y,
			.z = a.z <= b.z ? a.z : b.z,
			.w = a.w <= b.w ? a.w : b.w,
	};
}

blib_vec2f_t blib_vec4f_toVec2f(blib_vec4f_t v){
	return (blib_vec2f_t){.x=v.x, .y=v.y};
}

blib_vec3f_t blib_vec4f_toVec3f(blib_vec4f_t v){
	return (blib_vec3f_t){.x=v.x, .y=v.y, .z=v.z};
}

/*BEGIN SINGLE DIMENSIONAL*/

float blib_noise_1d(int x){
	x = (x<<13) ^ x;
	return ( 1.0 - ( (x * (x * x * 15731 + 789221) +
					1376312589) & 0x7FFFFFFF) / 1073741824.0);
}

float blib_noise_smoothed1d(float x){
	return blib_noise_1d(x)/2  +  blib_noise_1d(x-1)/4  +  blib_noise_1d(x+1)/4;
}

float blib_noise_interpolated1d(float x){
	int integer_X    = (int)x;
	float fractional_X = x - integer_X;
	float v1 = blib_noise_smoothed1d(integer_X);
	float v2 = blib_noise_smoothed1d(integer_X + 1);
	return blib_mathf_cosInterpolate(v1 , v2 , fractional_X);
}

float blib_noise_perlin1d(float x, float persistance, int octaves){
	persistance *= 0.5f;
	persistance = blib_mathf_clamp(persistance, 0.0f, 1.0f);
	float total = 0.0f;
	int n = octaves - 1;

	size_t i = 0;
	float freq = 0.0f;
	float amp = 0.0f;
	for (i = 0; i < n; i++){
		freq = pow(2,  i);
		amp = pow(persistance, i);

		total = total + blib_noise_interpolated1d(x * freq) * amp;
	}
	total = (total + 1) * 0.5f;
	assert(total <= 1);
	assert(total >= -1);
	return total;
}
/*END SINGLE DIMENSIONAL*/

/*BEGIN TWO DIMENSIONAL*/

float blib_noise_2d(int x, int y){
	int n = x + y * 57;
	n = (n<<13) ^ n;
	return ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7FFFFFFF) / 1073741824.0);    
}

float blib_noise_smoothed2d(float x, float y){
	float corners = ( blib_noise_2d(x-1, y-1) +
			blib_noise_2d(x+1, y-1) +
			blib_noise_2d(x-1, y+1) +
			blib_noise_2d(x+1, y+1) ) / 16;
	float sides = ( blib_noise_2d(x-1, y) + 
			blib_noise_2d(x+1, y) + 
			blib_noise_2d(x, y-1) +
			blib_noise_2d(x, y+1) ) /  8;

	float center  =  blib_noise_2d(x, y) / 4;
	return corners + sides + center;
}

float blib_noise_interpolated2d(float x, float y){
	int integer_X    = (int)x;
	float fractional_X = x - integer_X;

	int integer_Y    = (int)y;
	float fractional_Y = y - integer_Y;

	float v1 = blib_noise_smoothed2d(integer_X,     integer_Y);
	float v2 = blib_noise_smoothed2d(integer_X + 1, integer_Y);
	float v3 = blib_noise_smoothed2d(integer_X,     integer_Y + 1);
	float v4 = blib_noise_smoothed2d(integer_X + 1, integer_Y + 1);

	float i1 = blib_mathf_cosInterpolate(v1 , v2 , fractional_X);
	float i2 = blib_mathf_cosInterpolate(v3 , v4 , fractional_X);

	return blib_mathf_cosInterpolate(i1 , i2 , fractional_Y);
}

float blib_noise_perlin2d(float x, float y, float persistance, int octaves){
	persistance *= 0.5f;
	persistance = blib_mathf_clamp(persistance, 0.0f, 1.0f);
	float total = 0.0f;
	float n = octaves - 1;

	size_t i = 0;
	float freq = 0.0f;
	float amp = 0.0f;
	for (i = 0; i < n; i++){
		freq = pow(2, i);
		amp = pow(persistance, i);

		total = total + blib_noise_interpolated2d(x * freq, y * freq) * amp;
	}
	total = (total + 1) * 0.5f;
	assert(total <= 1);
	assert(total >= -1);
	return total;
}

/*END TWO DIMENSIONAL*/
