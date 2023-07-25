#include "bb_helper.h"

void testMathf(){
  printf("=====================================================\n");
  printf("                       MATHF                         \n");
  printf("=====================================================\n");


  printf("abs\n");
  printf("%f\n",bb_mathf_abs(-9.0f));
  printf("%f\n",bb_mathf_abs( 9.0f));
  printf("\n");

  printf("aproxequal\n");
  printf("%d\n",bb_mathf_aproxequal( 0.0f, 2.0f, 0.01f));
  printf("%d\n",bb_mathf_aproxequal( 2.0f, 2.0f, 0.01f));
  printf("%d\n",bb_mathf_aproxequal(-2.0f, 2.0f, 0.01f));
  printf("\n");
  
  printf("clamp\n");
  printf("%f\n",bb_mathf_clamp( 2.0f, 1.0f, 1.5f));
  printf("%f\n",bb_mathf_clamp(-5.0f, 1.0f, 1.5f));
  printf("%f\n",bb_mathf_clamp( 1.2f, 1.0f, 1.5f));
  printf("\n");
  
  printf("deg2rad\n");
  printf("%f\n", bb_mathf_deg2rad( 90.0f));
  printf("%f\n", bb_mathf_deg2rad(-90.0f));
  printf("%f\n", bb_mathf_deg2rad( 180.0f));
  printf("%f\n", bb_mathf_deg2rad(-180.0f));
  printf("%f\n", bb_mathf_deg2rad( 360.0f));
  printf("\n");

  printf("rad2deg\n");
  printf("%f\n", bb_mathf_rad2deg(PIf *  0.5f));
  printf("%f\n", bb_mathf_rad2deg(PIf * -0.5f));
  printf("%f\n", bb_mathf_rad2deg(PIf *  1.0f));
  printf("%f\n", bb_mathf_rad2deg(PIf * -1.0f));
  printf("%f\n", bb_mathf_rad2deg(PIf *  2.0f));
  printf("\n");
  
  printf("lerp\n");
  printf("%f\n",bb_mathf_lerp(0.0f, 1.0f, 0.1f));
  printf("%f\n",bb_mathf_lerp(100.0f, 1000.0f, 0.2f));
  printf("%f\n",bb_mathf_lerp(100.0f, 5000.0f, 0.1f));
  printf("%f\n",bb_mathf_lerp(100.0f, 5000.0f, 0.2f));
  printf("\n");

  printf("lerpclamped\n");
  printf("%f\n",bb_mathf_lerp(0.0f, 1.0f, 0.1f));
  printf("%f\n",bb_mathf_lerp(0.0f, 1.0f, 2.0f));
  printf("%f\n",bb_mathf_lerp(100.0f, 1000.0f, 0.2f));
  printf("%f\n",bb_mathf_lerp(100.0f, 5000.0f, 0.1f));
  printf("%f\n",bb_mathf_lerp(100.0f, 5000.0f, 0.2f));
  printf("%f\n",bb_mathf_lerp(100.0f, 1000.0f, 2.0f));
  printf("\n");

  printf("map\n");
  printf("%f\n",bb_mathf_map(0.2f,0.0f,1.0f,1.0f,2.0f));
  printf("%f\n",bb_mathf_map(1.0f,0.0f,1.0f,10.0f,100.0f));
  printf("\n");

  printf("normalize\n");
  printf("%f\n",bb_mathf_norm(8.0f,0.0f,5.0f));
  printf("\n");
}

void testNoise(){
  printf("=====================================================\n");
  printf("                       NOISE                         \n");
  printf("=====================================================\n");

  float i = 0;
  float j = 0;
  printf("1d perlin-ish noise\n");
  for (i = 0; i < 0.1; i+=0.01f)
  {
    printf("%f\t", bb_noise_perlin1d(i,0.25f,8));
  }
  printf("\n\n");
  
  printf("2d perlin-ish noise\n");
  for (i = 0; i < 0.1f; i+=0.01f){
    for (j = 0; j < 0.1f; j+=0.01f)
    {
      printf("%f\t",bb_noise_perlin2d(i, j, 0.25f, 8));
    }
    printf("\n");
  }
}

void testvec3(){
  printf("=====================================================\n");
  printf("                       VECTOR3                       \n");
  printf("=====================================================\n");

  bb_vec3f v1 = BB_VEC3F_ONE;
  bb_vec3f v2 = BB_VEC3F_LEFT;

  printf("v1          %f\t%f\t%f\n", v1.x,v1.y,v1.z);
  printf("v2          %f\t%f\t%f\n", v2.x,v2.y,v2.z);

  bb_vec3f add = bb_vec3f_add(v1,v2);
  printf("add         %f\t%f\t%f\n", add.x,add.y,add.z);

  bb_vec3f cross = bb_vec3f_cross(v1,v2);
  printf("cross       %f\t%f\t%f\n", cross.x,cross.y,cross.z);

  float dist = bb_vec3f_distance(v1,v2);
  printf("distance    %f\n", dist);

  float dot = bb_vec3f_dot(v1,v2);
  printf("dot         %f\n", dot);

  bb_vec3f lerp = bb_vec3f_lerp(v1,v2,2.0f);
  printf("lerp        %f\t%f\t%f\n", lerp.x, lerp.y, lerp.z);

  bb_vec3f lerpc = bb_vec3f_lerpclamped(v1,v2, 2.0f);
  printf("lerpclamped %f\t%f\t%f\n", lerpc.x, lerpc.y, lerpc.z);

  float mag = bb_vec3f_magnitude(v1);
  printf("magnitude   %f\n", mag);

  bb_vec3f max = bb_vec3f_max(v1,v2);
  printf("max         %f\t%f\t%f\n", max.x, max.y, max.z);

  bb_vec3f min = bb_vec3f_min(v1,v2);
  printf("max         %f\t%f\t%f\n", min.x, min.y, min.z);

  bb_vec3f norm = bb_vec3f_normalize(v1);
  printf("normalize   %f\n", bb_vec3f_magnitude(norm));

  bb_vec3f scale = bb_vec3f_scale(v1, 2.0f);
  printf("scale       %f\t%f\t%f\n", scale.x, scale.y, scale.z);

  float sqrmag = bb_vec3f_sqrmagnitude(v1);
  printf("sqrmag      %f\n",sqrmag);

  bb_vec3f subt = bb_vec3f_subtract(v1,v2);
  printf("subtract    %f\t%f\t%f\n", subt.x, subt.y, subt.z);
}

void testvec2(){
  printf("=====================================================\n");
  printf("                       VECTOR2                       \n");
  printf("=====================================================\n");

  bb_vec2f v1 = BB_VEC2F_ONE;
  bb_vec2f v2 = BB_VEC2F_LEFT;

  bb_vec2f add = bb_vec2f_add(v1, v2);
  printf("add        %f\t%f\n", add.x, add.y);

  float dist = bb_vec2f_distance(v1,v2);
  printf("distance   %f\n", dist);

  float dot = bb_vec2f_dot(v1,v2);
  printf("dot        %f\n", dot);

  bb_vec2f lerp = bb_vec2f_lerp(v1,v2,2.0f);
  printf("lerp       %f\t%f\n", lerp.x, lerp.y);

  bb_vec2f lerpc = bb_vec2f_lerpclamped(v1,v2,2.0f);
  printf("lerpc      %f\t%f\n", lerpc.x, lerpc.y);

  float mag = bb_vec2f_magnitude(v1);
  printf("mag        %f\n", mag);

  bb_vec2f norm = bb_vec2f_normalize(v1);
  printf("norm       %f\t%f\n", norm.x, norm.y);

  bb_vec2f scale = bb_vec2f_scale(v1, 2.0f);
  printf("scale      %f\t%f\n", scale.x, scale.y);

  float sqrmag = bb_vec2f_sqrmagnitude(v1);
  printf("sqrmag     %f\n", sqrmag);

  bb_vec2f subt = bb_vec2f_subtract(v1,v2);
  printf("subtract   %f\t%f\n", subt.x, subt.y);
}

int main(int argc,char **argv){
  testNoise();
  testMathf();
  testvec2();
  testvec3();  
  
  return EXIT_SUCCESS;
}
