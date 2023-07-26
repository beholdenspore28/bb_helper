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
#include "lite.h"

#ifdef L_ENABLE_MATHF

float l_mathf_rad2deg(const float n){
  return n * (180.0f/L_PI);
}

float l_mathf_deg2rad(const float n){
  return n * (L_PI/180.0f);
}

/*TODO see if we can remove the if statement in this function*/
float l_mathf_abs(const float n){
  if (n<0) return -n;
  else return n;
}

float l_mathf_clamp(float n, const float min, const float max){
  n = n < min ? min : n;
  return n > max ? max : n;
}

float l_mathf_lerp(float a, float b, float t) {
  return a + (b - a) * t;
}

float l_mathf_lerpclamped(float a, float b, float t) {
  return a + (b - a) * l_mathf_clamp(t,0.0f,1.0f);
}

float l_mathf_norm(float n, float min, float max){
  return (n - min) / (max - min);
}

float l_mathf_map(float n, float fromMin, float fromMax, float toMin, float toMax){
  return l_mathf_lerp(l_mathf_norm(n, fromMin, fromMax), toMin, toMax);
}

l_bool l_mathf_aproxequal(float a, float b, float tolerance){
  return (l_mathf_abs(a - b) < tolerance);
}

float l_mathf_cosInterpolate(float a, float b, float t){
  float f = (1.0f - cos(t * L_PI)) * 0.5f;
  return a*(1.0-f) + b*f;
}

float l_mathf_sigmoid(float n) {
    return (1 / (1 + powf(2.71828182846, -n)));
}

#endif
