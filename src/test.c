#include <stdio.h>
#include "bb_helper.h"

int main(){
  bb_vec3f va = {.x=1.0f,.y=1.0f,.z=1.0f};
  bb_vec3f vb = {.x=1.0f, .y=3.0f, .z=3.0f};

  printf("%f\n", bb_vec3f_distance(va, vb));
  return 0;
}