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

/*===========================================================================*/
/*                                     MAT4                                  */
/*===========================================================================*/

void blib_mat4_printf(blib_mat4_t m, const char* label){
	size_t i = 0;
	size_t j = 0;
	printf("=======================================================\n");
	printf("MATRIX4: %s\n", label);
	for (i = 0; i < 4; i++){
		printf("|");
		for (j = 0; j < 4; j++){
			printf("%f ", m.elements[j][i]);
		}
		printf("\n");
	}
	printf("=======================================================\n");
}

blib_mat4_t blib_mat4_add(const blib_mat4_t a, const blib_mat4_t b){
	blib_mat4_t sum = L_MAT4_IDENTITY;
	size_t j = 0;
	size_t i = 0;
	for (i = 0; i < 4; i++){
		for ( j = 0; j < 4; j++){
			sum.elements[i][j] = a.elements[i][j] + b.elements[i][j];
		}
	}
	return sum;
}

blib_mat4_t blib_mat4_subtract(const blib_mat4_t min, const blib_mat4_t sub){
	blib_mat4_t dif = L_MAT4_IDENTITY;
	size_t i = 0;
	size_t j = 0;
	for (i = 0; i < 4; i++){
		for ( j = 0; j < 4; j++){
			dif.elements[i][j] = min.elements[i][j] - sub.elements[i][j];
		}
	}
	return dif;
}

blib_mat4_t blib_mat4_multiply(const blib_mat4_t a, const blib_mat4_t b){
	blib_mat4_t p = L_MAT4_IDENTITY;
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	for ( i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			for(k = 0; k < 4; k++){
				p.elements[i][j] += a.elements[i][k] * b.elements[k][j];
			}
		}
	}
	return p;
}

blib_mat4_t blib_mat4_scale(blib_mat4_t mat, const float scalar){
	size_t i = 0;
	size_t j = 0;
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			mat.elements[i][j] *= scalar;
		}
	}
	return mat;
}

blib_mat4_t blib_mat4_translateVec3(blib_vec3f_t t){
	blib_mat4_t result = L_MAT4_IDENTITY;
	result.elements[3][0] += t.x;
	result.elements[3][1] += t.y;
	result.elements[3][2] += t.z;
	return result;
}

blib_mat4_t blib_mat4_translateVec4(blib_vec4f_t t){
	blib_mat4_t result = L_MAT4_IDENTITY;
	result.elements[3][0] += t.x;
	result.elements[3][1] += t.y;
	result.elements[3][2] += t.z;
	result.elements[3][3] += t.z;
	return result;
}

/*===========================================================================*/
/*                                    MATHF                                  */
/*===========================================================================*/

float blib_mathf_rad2deg(const float n){
	return n * (180.0f/L_PI);
}

float blib_mathf_deg2rad(const float n){
	return n * (L_PI/180.0f);
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

float blib_mathf_map(float n, float fromMin, float fromMax, float toMin, float toMax){
	return blib_mathf_lerp(blib_mathf_norm(n, fromMin, fromMax), toMin, toMax);
}

bool blib_mathf_aproxequal(float a, float b, float tolerance){
	return (fabs(a - b) < tolerance);
}

float blib_mathf_cosInterpolate(float a, float b, float t){
	float f = (1.0f - cos(t * L_PI)) * 0.5f;
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

/*===========================================================================*/
/*                                   VECTOR2                                 */
/*===========================================================================*/

const blib_vec2f_t L_VEC2F_ZERO     =  {.x =  0, .y =  0};
const blib_vec2f_t L_VEC2F_ONE	    =  {.x =  1, .y =  1};
const blib_vec2f_t L_VEC2F_UP       =  {.x =  0, .y =  1};
const blib_vec2f_t L_VEC2F_DOWN     =  {.x =  0, .y = -1};
const blib_vec2f_t L_VEC2F_LEFT     =  {.x = -1, .y =  0};
const blib_vec2f_t L_VEC2F_RIGHT	=  {.x =  1, .y =  0};

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

blib_vec2f_t blib_vec2f_subtract(blib_vec2f_t minuend, blib_vec2f_t subtrahend){
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

/*===========================================================================*/
/*                                   VECTOR3                                 */
/*===========================================================================*/

const blib_vec3f_t L_VEC3F_ZERO     =  {.x =  0, .y =  0, .z =  0};
const blib_vec3f_t L_VEC3F_ONE	     =	{.x =  1, .y =  1, .z =  1};
const blib_vec3f_t L_VEC3F_UP       =  {.x =  0, .y =  1, .z =  0};
const blib_vec3f_t L_VEC3F_DOWN     =  {.x =  0, .y = -1, .z =  0};
const blib_vec3f_t L_VEC3F_LEFT     =  {.x = -1, .y =  0, .z =  0};
const blib_vec3f_t L_VEC3F_RIGHT	   =	{.x =  1, .y =  0, .z =  0};
const blib_vec3f_t L_VEC3F_FORWARD	 =  {.x =  0, .y =  0, .z =  1};
const blib_vec3f_t L_VEC3F_BACK     =	{.x =  0, .y =  0, .z = -1};

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

blib_vec3f_t blib_vec3f_subtract(blib_vec3f_t minuend, blib_vec3f_t subtrahend){
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

/*===========================================================================*/
/*                                   VECTOR4                                 */
/*===========================================================================*/

const blib_vec4f_t L_VEC4F_ZERO     =  {.x =  0, .y =  0, .z =  0, .w = 1.0};
const blib_vec4f_t L_VEC4F_ONE	     =	{.x =  1, .y =  1, .z =  1, .w = 1.0};
const blib_vec4f_t L_VEC4F_UP       =  {.x =  0, .y =  1, .z =  0, .w = 1.0};
const blib_vec4f_t L_VEC4F_DOWN     =  {.x =  0, .y = -1, .z =  0, .w = 1.0};
const blib_vec4f_t L_VEC4F_LEFT     =  {.x = -1, .y =  0, .z =  0, .w = 1.0};
const blib_vec4f_t L_VEC4F_RIGHT	   =	{.x =  1, .y =  0, .z =  0, .w = 1.0};
const blib_vec4f_t L_VEC4F_FORWARD	 =  {.x =  0, .y =  0, .z =  1, .w = 1.0};
const blib_vec4f_t L_VEC4F_BACK     =	{.x =  0, .y =  0, .z = -1, .w = 1.0};

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

/*===========================================================================*/
/*                                    NOISE                                  */
/*===========================================================================*/

/*BEGIN SINGLE DIMENSIONAL*/

float blib_noise_1d(int x){
	x = (x<<13) ^ x;
	return ( 1.0 - ( (x * (x * x * 15731 + 789221) + 1376312589) & 0x7FFFFFFF) / 1073741824.0);
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