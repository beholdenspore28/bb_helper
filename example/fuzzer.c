#include "lite.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) { 
/*
  l_noise_perlin2d(*(float*)data, *(float*)data, *(float*)data,*(int*)data);
  l_mathf_sigmoid(*(float*)data);
  l_mathf_rad2deg(*(float*)data);
  l_mathf_norm(*(float*)data,*(float*)data,*(float*)data);
  l_mathf_map(*(float*)data,*(float*)data,*(float*)data,*(float*)data,*(float*)data);
  l_mathf_lerpclamped(*(float*)data,*(float*)data,*(float*)data);
  l_mathf_lerp(*(float*)data, *(float*)data, *(float*)data);
  l_mathf_deg2rad(*(float*)data);
  l_mathf_clamp(*(float*)data, *(float*)data, *(float*)data);
  l_mathf_cosInterpolate(*(float*)data, *(float*)data, *(float*)data);
  l_mathf_abs(*(float*)data);
  l_mathf_aproxequal(*(float*)data, *(float*)data, *(float*)data);
*/
  l_mathf_loop(*(float*)data, *(float*)data);
  return 0;  /*Values other than 0 and -1 are reserved for future use.*/
}
