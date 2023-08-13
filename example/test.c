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

#include "lite.h"

void testMathf(){
	float n = 0.0f;
	size_t i = 0;

	printf("=========================================================================\n");
	printf("                               MATHF TEST                                \n");
	printf("=========================================================================\n");

	printf("aproxequal\n");
	printf("%d\n",l_mathf_aproxequal( 0.0f, 2.0f, 0.01f));
	printf("%d\n",l_mathf_aproxequal( 2.0f, 2.0f, 0.01f));
	printf("%d\n",l_mathf_aproxequal(-2.0f, 2.0f, 0.01f));
	printf("\n");
	
	printf("clamp\n");
	printf("%f\n",l_mathf_clamp( 2.0f, 1.0f, 1.5f));
	printf("%f\n",l_mathf_clamp(-5.0f, 1.0f, 1.5f));
	printf("%f\n",l_mathf_clamp( 1.2f, 1.0f, 1.5f));
	printf("\n");
	
	printf("deg2rad\n");
	printf("%f\n", l_mathf_deg2rad( 90.0f));
	printf("%f\n", l_mathf_deg2rad(-90.0f));
	printf("%f\n", l_mathf_deg2rad( 180.0f));
	printf("%f\n", l_mathf_deg2rad(-180.0f));
	printf("%f\n", l_mathf_deg2rad( 360.0f));
	printf("\n");

	printf("rad2deg\n");
	printf("%f\n", l_mathf_rad2deg(L_PI *  0.5f));
	printf("%f\n", l_mathf_rad2deg(L_PI * -0.5f));
	printf("%f\n", l_mathf_rad2deg(L_PI *  1.0f));
	printf("%f\n", l_mathf_rad2deg(L_PI * -1.0f));
	printf("%f\n", l_mathf_rad2deg(L_PI *  2.0f));
	printf("\n");
	
	printf("lerp\n");
	printf("%f\n",l_mathf_lerp(0.0f, 1.0f, 0.1f));
	printf("%f\n",l_mathf_lerp(100.0f, 1000.0f, 0.2f));
	printf("%f\n",l_mathf_lerp(100.0f, 5000.0f, 0.1f));
	printf("%f\n",l_mathf_lerp(100.0f, 5000.0f, 0.2f));
	printf("\n");

	printf("lerpclamped\n");
	printf("%f\n",l_mathf_lerp(0.0f, 1.0f, 0.1f));
	printf("%f\n",l_mathf_lerp(0.0f, 1.0f, 2.0f));
	printf("%f\n",l_mathf_lerp(100.0f, 1000.0f, 0.2f));
	printf("%f\n",l_mathf_lerp(100.0f, 5000.0f, 0.1f));
	printf("%f\n",l_mathf_lerp(100.0f, 5000.0f, 0.2f));
	printf("%f\n",l_mathf_lerp(100.0f, 1000.0f, 2.0f));
	printf("\n");

	printf("map\n");
	printf("%f\n",l_mathf_map(0.2f,0.0f,1.0f,1.0f,2.0f));
	printf("%f\n",l_mathf_map(1.0f,0.0f,1.0f,10.0f,100.0f));
	printf("\n");

	printf("normalize\n");
	printf("%f\n",l_mathf_norm(8.0f,0.0f,5.0f));
	printf("\n");
	
	printf("loop\n");
	n = 0.0f;
	i = 0;
	for (i = 0; i < 15; i++){
		n++;
		n = l_mathf_loop(n, 5.0f);
		printf("%f\n", n);
	}
	printf("\n");

	printf("pingpong\n");
	n = 0.0f;
	i = 0;
	for (i = 0; i < 15; i++){
		n++;
		n = l_mathf_pingpong(i, 5.0f);
		printf("%f\n", n);
	}
}

void testNoise1(){
	printf("=========================================================================\n");
	printf("                               NOISE1 TEST                               \n");
	printf("=========================================================================\n");

	float range = 0.2f;
	float step = 0.001f;
	float persistance = 0.25f;
	int octaves = 16;
	float i = 0;

	printf("pseudo-random noise\n");
	for (i = 0; i < range/step ; i++){
		printf("%f ", l_noise_1d(i));
	}
	printf("\n\n");

	printf("pseudo-random smoothed noise\n");
	for (i = 0; i < range ; i += step){
		printf("%f ", l_noise_smoothed1d(i));
	}
	printf("\n\n");

	printf("pseudo-random, smoothed, cos interpolated noise\n");
	for (i = 0; i < range ; i += step){
		printf("%f ", l_noise_smoothed1d(i));
	}
	printf("\n\n");

	printf("perlin-ish noise\n");
	for (i = 0; i < range ; i += step){
		printf("%f ", l_noise_perlin1d(i,persistance, octaves));
	}
	printf("\n\n");
}

void testNoise2(){
	float range = 1.0f;
	float step = 0.01f;
	float persistance = 0.25f;
	int octaves = 4;
	float i = 0;
	float j = 0;

	printf("2D perlin-ish noise\n");
	for (i = 0; i < range ; i += step){
		for ( j = 0; j < range; j += step){
			printf("%f ", l_noise_perlin2d(i, j,persistance, octaves));
		}
		printf("\n");
	}
	printf("\n\n");
}

void testvec4(){
	printf("=========================================================================\n");
	printf("                               VECTOR4 TEST                              \n");
	printf("=========================================================================\n");

	l_vec4f_t v1 = L_VEC4F_ONE;
	l_vec4f_t v2 = L_VEC4F_LEFT;

	printf("v1                                %f\t%f\t%f\n", v1.x,v1.y,v1.z);
	printf("v2                                %f\t%f\t%f\n", v2.x,v2.y,v2.z);

	l_vec4f_t add = l_vec4f_add(v1,v2);
	printf("add v1 + v2                       %f\t%f\t%f\n", add.x,add.y,add.z);

	float dist = l_vec4f_distance(v1,v2);
	printf("distance from v1 to v2            %f\n", dist);

	float dot = l_vec4f_dot(v1,v2);
	printf("dot v1 * v2                       %f\n", dot);

	l_vec4f_t lerp = l_vec4f_lerp(v1,v2,2.0f);
	printf("lerp v1 v2 2                      %f\t%f\t%f\n", lerp.x, lerp.y, lerp.z);

	l_vec4f_t lerpc = l_vec4f_lerpclamped(v1,v2, 2.0f);
	printf("lerpclamped v1 v2 2               %f\t%f\t%f\n", lerpc.x, lerpc.y, lerpc.z);

	float mag = l_vec4f_magnitude(v1);
	printf("magnitude v1                      %f\n", mag);

	l_vec4f_t max = l_vec4f_max(v1,v2);
	printf("max v1 v2                         %f\t%f\t%f\n", max.x, max.y, max.z);

	l_vec4f_t min = l_vec4f_min(v1,v2);
	printf("min v1 v2                         %f\t%f\t%f\n", min.x, min.y, min.z);

	l_vec4f_t norm = l_vec4f_normalize(v1);
	printf("normalize v1                      %f\n", l_vec4f_magnitude(norm));

	l_vec4f_t scale = l_vec4f_scale(v1, 2.0f);
	printf("scale v1 * 2                      %f\t%f\t%f\n", scale.x, scale.y, scale.z);

	float sqrmag = l_vec4f_sqrmagnitude(v1);
	printf("sqrmag v1                         %f\n",sqrmag);

	l_vec4f_t subt = l_vec4f_subtract(v1,v2);
	printf("subtract v1 - v2                  %f\t%f\t%f\n", subt.x, subt.y, subt.z);
}

void testvec3(){
	printf("=========================================================================\n");
	printf("                               VECTOR3 TEST                              \n");
	printf("=========================================================================\n");
	
	l_vec3f_t v1 = L_VEC3F_ONE;
	l_vec3f_t v2 = L_VEC3F_LEFT;
	
	printf("v1                                %f\t%f\t%f\n", v1.x,v1.y,v1.z);
	printf("v2                                %f\t%f\t%f\n", v2.x,v2.y,v2.z);

	l_vec3f_t add = l_vec3f_add(v1,v2);
	printf("add v1 + v2                       %f\t%f\t%f\n", add.x,add.y,add.z);

	l_vec3f_t cross = l_vec3f_cross(v1,v2);
	printf("cross v1 x v2                     %f\t%f\t%f\n", cross.x,cross.y,cross.z);

	float dist = l_vec3f_distance(v1,v2);
	printf("distance from v1 to v2            %f\n", dist);

	float dot = l_vec3f_dot(v1,v2);
	printf("dot v1 * v2                       %f\n", dot);

	l_vec3f_t lerp = l_vec3f_lerp(v1,v2,2.0f);
	printf("lerp v1 v2 2                      %f\t%f\t%f\n", lerp.x, lerp.y, lerp.z);
	
	l_vec3f_t lerpc = l_vec3f_lerpclamped(v1,v2, 2.0f);
	printf("lerpclamped v1 v2 2               %f\t%f\t%f\n", lerpc.x, lerpc.y, lerpc.z);

	float mag = l_vec3f_magnitude(v1);
	printf("magnitude v1                      %f\n", mag);

	l_vec3f_t max = l_vec3f_max(v1,v2);
	printf("max v1 v2                         %f\t%f\t%f\n", max.x, max.y, max.z);

	l_vec3f_t min = l_vec3f_min(v1,v2);
	printf("min v1 v2                         %f\t%f\t%f\n", min.x, min.y, min.z);

	l_vec3f_t norm = l_vec3f_normalize(v1);
	printf("normalize v1                      %f\n", l_vec3f_magnitude(norm));

	l_vec3f_t scale = l_vec3f_scale(v1, 2.0f);
	printf("scale v1 * 2                      %f\t%f\t%f\n", scale.x, scale.y, scale.z);

	float sqrmag = l_vec3f_sqrmagnitude(v1);
	printf("sqrmag v1                         %f\n",sqrmag);

	l_vec3f_t subt = l_vec3f_subtract(v1,v2);
	printf("subtract v1 v2                    %f\t%f\t%f\n", subt.x, subt.y, subt.z);
}

void testvec2(){
	printf("=========================================================================\n");
	printf("                               VECTOR2 TEST                              \n");
	printf("=========================================================================\n");
	
	l_vec2f_t v1 = L_VEC2F_ONE;
	l_vec2f_t v2 = L_VEC2F_LEFT;
	
	l_vec2f_t add = l_vec2f_add(v1, v2);
	printf("add v1 + v2                       %f\t%f\n", add.x, add.y);
	
	float dist = l_vec2f_distance(v1,v2);
	printf("distance from v1 to v2            %f\n", dist);
	
	float dot = l_vec2f_dot(v1,v2);
	printf("dot v1 * v2                       %f\n", dot);
	
	l_vec2f_t lerp = l_vec2f_lerp(v1,v2,2.0f);
	printf("lerp v1 v2 2                      %f\t%f\n", lerp.x, lerp.y);
	
	l_vec2f_t lerpc = l_vec2f_lerpclamped(v1,v2,2.0f);
	printf("lerpc v1 v2 2                     %f\t%f\n", lerpc.x, lerpc.y);
	
	float mag = l_vec2f_magnitude(v1);
	printf("mag v1                            %f\n", mag);
	
	l_vec2f_t norm = l_vec2f_normalize(v1);
	printf("norm v1                           %f\t%f\n", norm.x, norm.y);
	
	l_vec2f_t scale = l_vec2f_scale(v1, 2.0f);
	printf("scale v1 * 2                      %f\t%f\n", scale.x, scale.y);
	
	float sqrmag = l_vec2f_sqrmagnitude(v1);
	printf("sqrmag v1                         %f\n", sqrmag);
	
	l_vec2f_t subt = l_vec2f_subtract(v1,v2);
	printf("subtract v1 - v2                  %f\t%f\n", subt.x, subt.y);
}

void writeNoiseFile2D(){
	printf("creating noise map..\n");
	float range = 100.0f;
	float step = (range/1024);
	float i = 0;
	float j = 0;
	float value = 0;
	FILE *fptr = fopen("build/example/noise2.pbm", "w");
	fputs("P2\n", fptr);
	fprintf(fptr, "%d %d\n", (int)ceil(range/step), (int)ceil(range/step));
	fputs("256\n", fptr);
	for (i = 0; i < range; i += step){
		for ( j = 0; j < range; j += step){
			value = l_noise_perlin2d(i, j, 1.0f, 32);
			value = ((value + 1) * 0.5f) * 256;
			fprintf(fptr, "%d ", (int)value);
		}
	}
	fclose(fptr);
}

void writeNoiseFile1D(){
	printf("creating noise map..\n");
	float range = 10.0f;
	float step = (range/1024);
	float i = 0;
	float value = 0;
	FILE *fptr = fopen("build/example/noise1.pbm", "w");
	fputs("P2\n", fptr);
	fprintf(fptr, "%d %d\n", (int)ceil(range), 1);
	fputs("256\n", fptr);
	for (i = 0; i < range; i += step){
		value = l_noise_perlin1d(i,1.0f,16);
		value = ((value + 1) * 0.5f) * 256;
		fprintf(fptr, "%d ", (int)value);
	}
	fclose(fptr);
}

int main(int argc,char **argv){
	printf("rev up those fryers!\n");
	/*
	testNoise1();
	testNoise2();
	writeNoiseFile1D();
	writeNoiseFile2D();
	*/

	testMathf();
	
	testvec2();
	testvec3();
	testvec4();
	
	l_mat4_t a = { .elements={
		{1,2,3,4,},
		{5,6,7,8,},
		{9,10,11,12,},
		{13,14,15,16,},
	}};

	l_mat4_t b = { .elements={
		{1,2,3,4,},
		{5,6,7,8,},
		{9,10,11,12,},
		{13,14,15,16,},
	}};

	l_mat4_printf(a,"a");
	l_mat4_printf(b,"b");
	l_mat4_t c = l_mat4_multiply(a, b);
	l_mat4_printf(c, "product of a and b");

	l_mat4_t id = L_MAT4_IDENTITY;
	l_mat4_printf(id, "IDENTITY MATRIX");
	
	l_vec3f_t vec = l_vec3f_scale(L_VEC3F_ONE, 5.0f);
	l_mat4_t translation = l_mat4_translateVec3(vec);
	l_mat4_printf(translation, "VEC3 (5,5,5) TRANSLATIION");

	return EXIT_SUCCESS; 
}
