#include <stdio.h>
#include "bb_helper.h"

int main(){
  bb_vec3f va = BB_VEC3F_ONE;
  bb_vec3f vb = {.x=1.0f, .y=3.0f, .z=3.0f};
  va = bb_vec3f_add(va, vb);

  printf("%f\n", bb_vec3f_distance(va, vb));
  return 0;
}