#include "lite.h"

void testMathf(){
  printf("=====================================================\n");
  printf("                     MATHF TEST                      \n");
  printf("=====================================================\n");


  printf("abs\n");
  printf("%f\n",l_mathf_abs(-9.0f));
  printf("%f\n",l_mathf_abs( 9.0f));
  printf("\n");

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
}

void testNoise(){
  printf("=====================================================\n");
  printf("                     NOISE TEST                      \n");
  printf("=====================================================\n");

  float i = 0;
  float j = 0;
  
  printf("noise 1d\n");
  for (i = 0; i < 1.0f; i+=0.01f)
  {
    printf("%f ", l_noise_1d(i));
  }
  printf("\n\n");

  printf("smooth noise 1d\n");
  for (i = 0; i < 1.0f; i+=0.01f)
  {
    printf("%f ", l_noise_smoothed1d(i));
  }
  printf("\n\n");
  
  printf("interpolated noise 1d\n");
  for (i = 0; i < 1.0f; i+=0.01f)
  {
    printf("%f ", l_noise_interpolated1d(i));
  }
  printf("\n\n");
  
  printf("1d perlin-ish noise\n");
  for (i = 0; i < 1.0; i+=0.01f)
  {
    printf("%f ", l_noise_perlin1d(i,0.1f,8));
  }
  printf("\n\n");

  printf("noise 2d\n");
  for (i = 0; i < 10.0f; i++)
  {
    for (j = 0; j < 10.0f; j++)
    {
      printf("%f\t", l_noise_2d(i,j));
    }
    printf("\n");
  }
  printf("\n\n");

  printf("smooth noise 2d\n");
  for (i = 0; i < 10.0f; i++)
  {
    for (j = 0; j < 10.0f; j++)
    {
      printf("%f\t", l_noise_smoothed2d(i,j));
    }
    printf("\n");
  }
  printf("\n\n");

  printf("interpolated noise 2d\n");
  for (i = 0; i < 10.0f; i++)
  {
    for (j = 0; j < 10.0f; j++)
    {
      printf("%f\t", l_noise_interpolated2d(i,j));
    }
    printf("\n");
  }
  printf("\n\n");

  printf("2d perlin-ish noise\n");
  for (i = 0; i < 0.1f; i+=0.01f){
    for (j = 0; j < 0.1f; j+=0.01f)
    {
      printf("%f\t",l_noise_perlin2d(i, j, 0.25f, 8));
    }
    printf("\n");
  }
}

void testvec3(){
  printf("=====================================================\n");
  printf("                     VECTOR3 TEST                    \n");
  printf("=====================================================\n");

  l_vec3f v1 = L_VEC3F_ONE;
  l_vec3f v2 = L_VEC3F_LEFT;

  printf("v1          %f\t%f\t%f\n", v1.x,v1.y,v1.z);
  printf("v2          %f\t%f\t%f\n", v2.x,v2.y,v2.z);

  l_vec3f add = l_vec3f_add(v1,v2);
  printf("add         %f\t%f\t%f\n", add.x,add.y,add.z);

  l_vec3f cross = l_vec3f_cross(v1,v2);
  printf("cross       %f\t%f\t%f\n", cross.x,cross.y,cross.z);

  float dist = l_vec3f_distance(v1,v2);
  printf("distance    %f\n", dist);

  float dot = l_vec3f_dot(v1,v2);
  printf("dot         %f\n", dot);

  l_vec3f lerp = l_vec3f_lerp(v1,v2,2.0f);
  printf("lerp        %f\t%f\t%f\n", lerp.x, lerp.y, lerp.z);

  l_vec3f lerpc = l_vec3f_lerpclamped(v1,v2, 2.0f);
  printf("lerpclamped %f\t%f\t%f\n", lerpc.x, lerpc.y, lerpc.z);

  float mag = l_vec3f_magnitude(v1);
  printf("magnitude   %f\n", mag);

  l_vec3f max = l_vec3f_max(v1,v2);
  printf("max         %f\t%f\t%f\n", max.x, max.y, max.z);

  l_vec3f min = l_vec3f_min(v1,v2);
  printf("max         %f\t%f\t%f\n", min.x, min.y, min.z);

  l_vec3f norm = l_vec3f_normalize(v1);
  printf("normalize   %f\n", l_vec3f_magnitude(norm));

  l_vec3f scale = l_vec3f_scale(v1, 2.0f);
  printf("scale       %f\t%f\t%f\n", scale.x, scale.y, scale.z);

  float sqrmag = l_vec3f_sqrmagnitude(v1);
  printf("sqrmag      %f\n",sqrmag);

  l_vec3f subt = l_vec3f_subtract(v1,v2);
  printf("subtract    %f\t%f\t%f\n", subt.x, subt.y, subt.z);
}

void testvec2(){
  printf("=====================================================\n");
  printf("                     VECTOR2 TEST                    \n");
  printf("=====================================================\n");

  l_vec2f v1 = L_VEC2F_ONE;
  l_vec2f v2 = L_VEC2F_LEFT;

  l_vec2f add = l_vec2f_add(v1, v2);
  printf("add        %f\t%f\n", add.x, add.y);

  float dist = l_vec2f_distance(v1,v2);
  printf("distance   %f\n", dist);

  float dot = l_vec2f_dot(v1,v2);
  printf("dot        %f\n", dot);

  l_vec2f lerp = l_vec2f_lerp(v1,v2,2.0f);
  printf("lerp       %f\t%f\n", lerp.x, lerp.y);

  l_vec2f lerpc = l_vec2f_lerpclamped(v1,v2,2.0f);
  printf("lerpc      %f\t%f\n", lerpc.x, lerpc.y);

  float mag = l_vec2f_magnitude(v1);
  printf("mag        %f\n", mag);

  l_vec2f norm = l_vec2f_normalize(v1);
  printf("norm       %f\t%f\n", norm.x, norm.y);

  l_vec2f scale = l_vec2f_scale(v1, 2.0f);
  printf("scale      %f\t%f\n", scale.x, scale.y);

  float sqrmag = l_vec2f_sqrmagnitude(v1);
  printf("sqrmag     %f\n", sqrmag);

  l_vec2f subt = l_vec2f_subtract(v1,v2);
  printf("subtract   %f\t%f\n", subt.x, subt.y);
}

int main(int argc,char **argv){
  /*
  */
  testMathf();
  testvec2();
  testvec3();
  testNoise();
 
  return EXIT_SUCCESS;
}
