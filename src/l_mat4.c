#include "lite.h"
#if defined(L_ENABLE_MATRIX4)

void l_mat4_printf(l_mat4_t m, const char* label){
  size_t i = 0;
  size_t j = 0;
  printf("--------------------------------------\n");
  printf("MATRIX4: %s\n", label);
  for (i = 0; i < 4; i++){
    printf("|");
    for (j = 0; j < 4; j++){
      printf("%f ", m[i][j]);
    }
    printf("|\n");
  }
  printf("--------------------------------------\n");
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



#endif