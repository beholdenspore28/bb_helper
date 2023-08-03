/*----------------------------------LEGAL--------------------------------------

MIT License

Copyright (c) 2023 Benjamin Joseph Brooks

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

------------------------------------------------------------------------------*/

#include "lite.h"
#include "assert.h"

/*BEGIN SINGLE DIMENSIONAL*/

float l_noise_1d(int x){
  x = (x<<13) ^ x;
  return ( 1.0 - ( (x * (x * x * 15731 + 789221) + 1376312589) & 0x7FFFFFFF) / 1073741824.0);
}

float l_noise_smoothed1d(float x){
  return l_noise_1d(x)/2  +  l_noise_1d(x-1)/4  +  l_noise_1d(x+1)/4;
}

float l_noise_interpolated1d(float x){
  int integer_X    = (int)x;
  float fractional_X = x - integer_X;
  float v1 = l_noise_smoothed1d(integer_X);
  float v2 = l_noise_smoothed1d(integer_X + 1);
  return l_mathf_cosInterpolate(v1 , v2 , fractional_X);
}

float l_noise_perlin1d(float x, float persistance, int octaves){
  persistance *= 0.5f;
  persistance = l_mathf_clamp(persistance, 0.0f, 1.0f);
  float total = 0.0f;
  int n = octaves - 1;

  size_t i = 0;
  float freq = 0.0f;
  float amp = 0.0f;
  for (i = 0; i < n; i++){
    freq = pow(2,  i);
    amp = pow(persistance, i);

    total = total + l_noise_interpolated1d(x * freq) * amp;
  }
  total = (total + 1) * 0.5f;
  assert(total <= 1);
  assert(total >= -1);
  return total;
}
/*END SINGLE DIMENSIONAL*/

/*BEGIN TWO DIMENSIONAL*/

float l_noise_2d(int x, int y){
  int n = x + y * 57;
  n = (n<<13) ^ n;
  return ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7FFFFFFF) / 1073741824.0);    
}

float l_noise_smoothed2d(float x, float y){
  float corners = ( l_noise_2d(x-1, y-1)+l_noise_2d(x+1, y-1)+l_noise_2d(x-1, y+1)+l_noise_2d(x+1, y+1) ) / 16;
  float sides   = ( l_noise_2d(x-1, y)  +l_noise_2d(x+1, y)  +l_noise_2d(x, y-1)  +l_noise_2d(x, y+1) ) /  8;
  float center  =  l_noise_2d(x, y) / 4;
  return corners + sides + center;
}

float l_noise_interpolated2d(float x, float y){
  int integer_X    = (int)x;
  float fractional_X = x - integer_X;

  int integer_Y    = (int)y;
  float fractional_Y = y - integer_Y;

  float v1 = l_noise_smoothed2d(integer_X,     integer_Y);
  float v2 = l_noise_smoothed2d(integer_X + 1, integer_Y);
  float v3 = l_noise_smoothed2d(integer_X,     integer_Y + 1);
  float v4 = l_noise_smoothed2d(integer_X + 1, integer_Y + 1);

  float i1 = l_mathf_cosInterpolate(v1 , v2 , fractional_X);
  float i2 = l_mathf_cosInterpolate(v3 , v4 , fractional_X);

  return l_mathf_cosInterpolate(i1 , i2 , fractional_Y);
}

float l_noise_perlin2d(float x, float y, float persistance, int octaves){
  persistance *= 0.5f;
  persistance = l_mathf_clamp(persistance, 0.0f, 1.0f);
  float total = 0.0f;
  float n = octaves - 1;

  size_t i = 0;
  float freq = 0.0f;
  float amp = 0.0f;
  for (i = 0; i < n; i++){
    freq = pow(2, i);
    amp = pow(persistance, i);

    total = total + l_noise_interpolated2d(x * freq, y * freq) * amp;
  }
  total = (total + 1) * 0.5f;
  assert(total <= 1);
  assert(total >= -1);
  return total;
}

/*END TWO DIMENSIONAL*/
