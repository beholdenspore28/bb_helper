#include "bb_helper.h"

#ifdef BB_ENABLE_NOISE

/*BEGIN SINGLE DIMENSIONAL*/

float bb_noise_1d(int x){
  x = (x<<13) ^ x;
  return ( 1.0 - ( (x * (x * x * 15731 + 789221) + 1376312589) & 0x7FFFFFFF) / 1073741824.0);
}

float bb_noise_smoothed1d(float x){
  return bb_noise_1d(x)/2  +  bb_noise_1d(x-1)/4  +  bb_noise_1d(x+1)/4;
}

float bb_noise_interpolated1d(float x){
  int integer_X    = (int)x;
  float fractional_X = x - integer_X;
  float v1 = bb_noise_smoothed1d(integer_X);
  float v2 = bb_noise_smoothed1d(integer_X + 1);
  return bb_mathf_cosInterpolate(v1 , v2 , fractional_X);
}

float bb_noise_perlin1d(float x, float persistance, int octaves){
  float total = 0.0f;
  int n = octaves - 1;
  
  size_t i = 0;
  float freq = 0.0f;
  float amp = 0.0f;
  for (i = 0; i < n; i++)
  {
    freq = 2 * i;
    amp = persistance * i;

    total = total + bb_noise_interpolated1d(x * freq) * amp;
  }

  return total;
}
/*END SINGLE DIMENSIONAL*/

/*BEGIN TWO DIMENSIONAL*/



/*END TWO DIMENSIONAL*/

#endif