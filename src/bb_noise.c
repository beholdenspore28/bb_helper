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

float bb_noise_2d(int x, int y){
  int n = x + y * 57;
  n = (n<<13) ^ n;
  return ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7FFFFFFF) / 1073741824.0);    
}

float bb_noise_smoothed2d(float x, float y){
  float corners = ( bb_noise_2d(x-1, y-1)+bb_noise_2d(x+1, y-1)+bb_noise_2d(x-1, y+1)+bb_noise_2d(x+1, y+1) ) / 16;
  float sides   = ( bb_noise_2d(x-1, y)  +bb_noise_2d(x+1, y)  +bb_noise_2d(x, y-1)  +bb_noise_2d(x, y+1) ) /  8;
  float center  =  bb_noise_2d(x, y) / 4;
  return corners + sides + center;
}

float bb_noise_interpolated2d(float x, float y){
  int integer_X    = (int)x;
  float fractional_X = x - integer_X;

  int integer_Y    = (int)y;
  float fractional_Y = y - integer_Y;

  float v1 = bb_noise_smoothed2d(integer_X,     integer_Y);
  float v2 = bb_noise_smoothed2d(integer_X + 1, integer_Y);
  float v3 = bb_noise_smoothed2d(integer_X,     integer_Y + 1);
  float v4 = bb_noise_smoothed2d(integer_X + 1, integer_Y + 1);

  float i1 = bb_mathf_cosInterpolate(v1 , v2 , fractional_X);
  float i2 = bb_mathf_cosInterpolate(v3 , v4 , fractional_X);

  return bb_mathf_cosInterpolate(i1 , i2 , fractional_Y);
}

float bb_noise_perlin2d(float x, float y, float persistance, int octaves){
  float total = 0.0f;
  float n = octaves - 1;

  size_t i = 0;
  float freq = 0.0f;
  float amp = 0.0f;
  for (i = 0; i < n; i++)
  {
    freq = 2 * i;
    amp = persistance * i;

    total = total + bb_noise_interpolated2d(x * freq, y * freq) * amp;
    
  }
  
  return total;
}

/*END TWO DIMENSIONAL*/

#endif