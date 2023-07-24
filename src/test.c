#include "bb_helper.h"

int main(int argc,char **argv){
  
  /*COMPLETED TESTS*/
  
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

  /*ONGOING TESTS*/
  
  
  
  return EXIT_SUCCESS;
}
