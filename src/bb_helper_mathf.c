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

#include <math.h>
#include <stdio.h>
#include "bb_helper.h"

#ifdef BB_ENABLE_MATHF

float bb_mathf_rad2deg(const float n){
  return n * (180.0f/PIf);
}

float bb_mathf_deg2rad(const float n){
  return n * (PIf/180.0f);
}

/*TODO see if we can remove the if statement in this function*/
float bb_mathf_abs(const float n){
  if (n<0) return -n;
  else return n;
}

float bb_mathf_clamp(float n, const float min, const float max){
  n = n < min ? min : n;
  return n > max ? max : n;
}

float bb_mathf_lerp(float a, float b, float t) {
  return a + (b - a) * t;
}

float bb_mathf_lerpclamped(float a, float b, float t) {
  return a + (b - a) * bb_mathf_clamp(t,0.0f,1.0f);
}

float bb_mathf_norm(float n, float min, float max){
  return (n - min) / (max - min);
}

float bb_mathf_map(float n, float fromMin, float fromMax, float toMin, float toMax){
  return bb_mathf_lerp(bb_mathf_norm(n, fromMin, fromMax), toMin, toMax);
}

bb_bool bb_mathf_aproxequal(float a, float b, float tolerance){
  if (bb_mathf_abs(a - b) < tolerance) return 1; else return 0;
}

#endif
