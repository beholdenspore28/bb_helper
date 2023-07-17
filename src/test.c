#include <stdio.h>
#include "bb_helper.h"

int main(){
  bb_vec3f va = BB_VEC3F_ONE;
  bb_vec3f vb = {.x=1.0f, .y=3.0f, .z=3.0f};
  printf("%f\n", bb_vec3f_dot(va,vb));
  return 0;
}