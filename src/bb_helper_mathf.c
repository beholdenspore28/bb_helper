/*BEGIN LEGAL*/

/*

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

*/

/*END LEGAL*/

#include <math.h>
#include <stdio.h>
#include "bb_helper.h"

#ifdef BB_ENABLE_MATHF

float bb_rad2degf(const float n){
  return n * (180.0f/PIf);
}

float bb_deg2radf(const float n){
  return n * (PIf/180.0f);
}

/*TODO see if we can remove the if statement in this function*/
float bb_absf(const float n){
  if (n<0) return -n;
  else return n;
}

float bb_clampf(float n, const float min, const float max){
  if (min >= max) {
    printf("[ERROR]\tminimum constraint cannot be greater than or equal to maximum constraint.\nFILE:%s\nLINE:%d\n", __FILE__, __LINE__);
  }
  if (n > max) n = max;
  if (n < min) n = min;
  return n;
}
/*TODO Test this function.*/
float bb_lerpf(float a, float b, float t) {
  return (1 - t) * a + t * b;
}

bb_bool bb_aproxequalf(float a, float b, float tolerance){
  if (bb_absf(a - b) < tolerance) return 1; else return 0;
}

#endif