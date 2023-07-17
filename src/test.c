#include <stdio.h>
#include "bb_helper.h"

int main(){
  bb_vec3f va = BB_VEC3F_ONE;
  bb_vec3f vb = {.x=1.0f, .y=3.0f, .z=3.0f};
  bb_vec3f vc = bb_vec3f_cross(va,vb);
  printf("%f\t%f\t%f\n",vc.x,vc.y,vc.z);

  printf("%f\n", bb_vec3f_distance(va, vb));
  return 0;
}