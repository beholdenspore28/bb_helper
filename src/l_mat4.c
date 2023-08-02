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
#if defined(L_ENABLE_MATRIX4)

void l_mat4_printf(l_mat4_t m, const char* label){
  size_t i = 0;
  size_t j = 0;
  printf("=======================================================\n");
  printf("MATRIX4: %s\n", label);
  for (i = 0; i < 4; i++){
    printf("|");
    for (j = 0; j < 4; j++){
      printf("%f ", m[i][j]);
    }
    printf("\n");
  }
  printf("=======================================================\n");
}

void l_mat4_add(l_mat4_t a, l_mat4_t b, l_mat4_t sum){
  /*
  A = | a00 a01 a02 a03 |
      | a10 a11 a12 a13 | 
      | a20 a21 a22 a23 | 
      | a30 a31 a32 a33 |

  B = | b00 b01 b02 b03 |
      | b10 b11 b12 b13 | 
      | b20 b21 b22 b23 | 
      | b30 b31 b32 b33 |

  A+B = | a00+b00  a01+b01  a02+b02  a03+b03 |
        | a10+b10  a11+b11  a12+b12  a13+b13 |
        | a20+b20  a21+b21  a22+b22  a23+b23 |
        | a30+b30  a31+b31  a32+b32  a33+b33 |
  */
  size_t j = 0;
  size_t i = 0;
  for (i = 0; i < 4; i++){
    for ( j = 0; j < 4; j++){
      sum[i][j] = a[i][j] + b[i][j];
    }
  }  
}

void l_mat4_subtract(l_mat4_t min, l_mat4_t sub, l_mat4_t dif){
  /*
  M = | m00 m01 m02 m03 |
      | m10 m11 m12 m13 | 
      | m20 m21 m22 m23 | 
      | m30 m31 m32 m33 |

  S = | s00 s01 s02 s03 |
      | s10 s11 s12 s13 | 
      | s20 s21 s22 s23 | 
      | s30 s31 s32 s33 |

  M-S = | m00-s00  m01-s01  m02-s02  m03-s03 |
        | m10-s10  m11-s11  m12-s12  m13-s13 |
        | m20-s20  m21-s21  m22-s22  m23-s23 |
        | m30-s30  m31-s31  m32-s32  m33-s33 |
  */
  size_t j = 0;
  size_t i = 0;
  for (i = 0; i < 4; i++){
    for ( j = 0; j < 4; j++){
      dif[i][j] = min[i][j] - sub[i][j];
    }
  }
}

void l_mat4_scale(l_mat4_t mat, float scalar){
  /*
  M = | m00 m01 m02 m03 |
      | m10 m11 m12 m13 | 
      | m20 m21 m22 m23 | 
      | m30 m31 m32 m33 |

  M*S = | m00*s m01*s m02*s m03*s |
        | m10*s m11*s m12*s m13*s |
        | m20*s m21*s m22*s m23*s |
        | m30*s m31*s m32*s m33*s |
  */
  size_t i = 0;
  size_t j = 0;
  for (i = 0; i < 4; i++){
    for (j = 0; j < 4; j++){
      mat[i][j] *= scalar;
    }    
  }
}

/*Multiplies a 4x4 matrix by another and writes the product to "p"*/
void l_mat4_multiply(const l_mat4_t a, const l_mat4_t b, l_mat4_t p){
  /*im not even going to try to explain this...*/
  size_t i = 0;
  size_t j = 0;
  size_t k = 0;
  for ( i = 0; i < 4; i++){
    for (j = 0; j < 4; j++){
      for(k = 0; k < 4; k++){
        p[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

#endif
