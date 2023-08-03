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

void l_mat4_printf(l_mat4_t m, const char* label){
  size_t i = 0;
  size_t j = 0;
  printf("=======================================================\n");
  printf("MATRIX4: %s\n", label);
  for (i = 0; i < 4; i++){
    printf("|");
    for (j = 0; j < 4; j++){
      printf("%f ", m.elements[i][j]);
    }
    printf("\n");
  }
  printf("=======================================================\n");
}

l_mat4_t l_mat4_add(const l_mat4_t a, const l_mat4_t b){
  l_mat4_t sum = L_MAT4_IDENTITY;
  size_t j = 0;
  size_t i = 0;
  for (i = 0; i < 4; i++){
    for ( j = 0; j < 4; j++){
      sum.elements[i][j] = a.elements[i][j] + b.elements[i][j];
    }
  }  
  return sum;
}

l_mat4_t l_mat4_subtract(const l_mat4_t min, const l_mat4_t sub){
  l_mat4_t dif = L_MAT4_IDENTITY;
  size_t j = 0;
  size_t i = 0;
  for (i = 0; i < 4; i++){
    for ( j = 0; j < 4; j++){
      dif.elements[i][j] = min.elements[i][j] - sub.elements[i][j];
    }
  }
  return dif;
}

l_mat4_t l_mat4_multiply(const l_mat4_t a, const l_mat4_t b){
  l_mat4_t p = L_MAT4_IDENTITY;
  size_t i = 0;
  size_t j = 0;
  size_t k = 0;
  for ( i = 0; i < 4; i++){
    for (j = 0; j < 4; j++){
      for(k = 0; k < 4; k++){
        p.elements[i][j] += a.elements[i][k] * b.elements[k][j];
      }
    }
  }
  return p;
}

l_mat4_t l_mat4_scale(l_mat4_t mat, const float scalar){
  size_t i = 0;
  size_t j = 0;
  for (i = 0; i < 4; i++){
    for (j = 0; j < 4; j++){
      mat.elements[i][j] *= scalar;
    }    
  }
  return mat;
}

l_mat4_t l_mat4_translateVec3(l_vec3f_t t){
  l_mat4_t result = L_MAT4_IDENTITY;
  result.elements[0][3] += t.x;
  result.elements[1][3] += t.y;
  result.elements[2][3] += t.z;
  return result;
}

l_mat4_t l_mat4_translateVec4(l_vec4f_t t){
  l_mat4_t result = L_MAT4_IDENTITY;
  result.elements[0][3] += t.x;
  result.elements[1][3] += t.y;
  result.elements[2][3] += t.z;
  result.elements[2][3] += t.z;
  return result;
}