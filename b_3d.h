#pragma once

#include "b_math.h"

typedef struct {
  float x;
  float y;
} Vector2;

typedef struct {
  float x;
  float y;
  float z;
} Vector3;

typedef struct {
  float x;
  float y;
  float z;
  float w;
} Vector4;

typedef struct {
  float elements[16];
} Matrix4x4;

typedef struct {
  float w;
  float x;
  float y;
  float z;
} Quaternion;

static inline Vector2 Vector2_Zero(void) { return (Vector2){0.0f, 0.0f}; }
static inline Vector2 Vector2_One(float s) { return (Vector2){s, s}; }
static inline Vector2 Vector2_Up(float s) { return (Vector2){0.0f, s}; }
static inline Vector2 Vector2_Down(float s) { return (Vector2){0.0f, -s}; }
static inline Vector2 Vector2_Right(float s) { return (Vector2){s, 0.0f}; }
static inline Vector2 Vector2_Left(float s) { return (Vector2){-s, 0.0f}; }

static inline Vector3 Vector3_Zero(void) { return (Vector3){0.0f, 0.0f, 0.0f}; }
static inline Vector3 Vector3_One(float s) { return (Vector3){s, s, s}; }
static inline Vector3 Vector3_Up(float s) { return (Vector3){0.0f, s, 0.0f}; }
static inline Vector3 Vector3_Down(float s) {
  return (Vector3){0.0f, -s, 0.0f};
}
static inline Vector3 Vector3_Right(float s) {
  return (Vector3){s, 0.0f, 0.0f};
}
static inline Vector3 Vector3_Left(float s) {
  return (Vector3){-s, 0.0f, 0.0f};
}
static inline Vector3 Vector3_Forward(float s) {
  return (Vector3){0.0f, 0.0f, s};
}
static inline Vector3 Vector3_Back(float s) {
  return (Vector3){0.0f, 0.0f, -s};
}

static inline Vector4 Vector4_Zero(void) {
  return (Vector4){0.0f, 0.0f, 0.0f, 1.0f};
}
static inline Vector4 Vector4_One(float s) { return (Vector4){s, s, s, 1.0f}; }
static inline Vector4 Vector4_Up(float s) {
  return (Vector4){0.0f, s, 0.0f, 1.0f};
}
static inline Vector4 Vector4_Down(float s) {
  return (Vector4){0.0f, -s, 0.0f, 1.0f};
}
static inline Vector4 Vector4_Right(float s) {
  return (Vector4){s, 0.0f, 0.0f, 1.0f};
}
static inline Vector4 Vector4_Left(float s) {
  return (Vector4){-s, 0.0f, 0.0f, 1.0f};
}
static inline Vector4 Vector4_Forward(float s) {
  return (Vector4){0.0f, 0.0f, s, 1.0f};
}
static inline Vector4 Vector4_Back(float s) {
  return (Vector4){0.0f, 0.0f, -s, 1.0f};
}

/*Prints a vector "v" using printf*/
static inline void Vector2_Print(const Vector2 v, const char *label) {
  printf("%s [%f, %f]\n", label, v.x, v.y);
}

/*Returns a vector that points in the opposite direction of the given vector
"v". The vector returned has a magnitude identical to the given vector "v"*/
static inline Vector2 Vector2_Negate(Vector2 v) {
  return (Vector2){.x = -v.x, .y = -v.y};
}

/*Subtracts a vector "subtrahend" from another vector "minuend"*/
static inline Vector2 Vector2_Subtract(Vector2 minuend, Vector2 subtrahend) {
  return (Vector2){.x = minuend.x - subtrahend.x,
                   .y = minuend.y - subtrahend.y};
}

/*Adds a vector "a" to another vector "b"*/
static inline Vector2 Vector2_Add(Vector2 a, Vector2 b) {
  return (Vector2){.x = a.x + b.x, .y = a.y + b.y};
}

/*A more performant way of getting the relative length of a
vector "v". This saves a square root operation making it more
performant than Vector2_Magnitude(). If all you have to do is
compare a vectors length relatively, use this function instead of
Vector2_Magnitude()*/
static inline float Vector2_SquareMagnitude(Vector2 v) {
  return ((v.x * v.x) + (v.y * v.y));
}

/*Returns the actual length of a vector "v".
This uses a square root operation. Use Vector2_SquareMagnitudenitude()
to sacrifice accuracy and save on performance when comparing
distances.*/
static inline float Vector2_Magnitude(Vector2 v) {
  return sqrt(Vector2_SquareMagnitude(v));
}

/*Returns a given vector "v" as a unit vector.
This means the magnitude(length) of the returned
vector will always be 1 unit. The returned vector always points
in the same direction as the given vector "v"*/
static inline Vector2 Vector2_Normalize(Vector2 v) {
  float m = Vector2_Magnitude(v);
  if (m == 0)
    return Vector2_Zero();
  return (Vector2){.x = v.x / m, .y = v.y / m};
}

/*Returns the distance between point a and point b
in units.*/
static inline float Vector2_Distance(Vector2 a, Vector2 b) {
  return Vector2_Magnitude(Vector2_Subtract(b, a));
}

/*Scales a vector "v" by "scalar".
increases the magnitude when "scalar" is greater than 1.
decreases the magnitude when "scalar" is less than 0.
The returned vector will point in the same direction as
the given vector "v".*/
static inline Vector2 Vector2_Scale(Vector2 v, float scalar) {
  return (Vector2){.x = v.x * scalar, .y = v.y * scalar};
}

/*For normalized vectors Dot returns 1 if they point in
exactly the same direction, -1 if they point in completely opposite directions
and zero if the vectors are perpendicular.*/
static inline float Vector2_Dot(Vector2 a, Vector2 b) {
  return (a.x * b.x) + (a.y * b.y);
}

/*Linearly interpolates between "a" and "b" by "t".
If you want to make sure the returned value stays
between "a" and "b", use Vector3_Lerpclamped() instead.
Returns a point at "t"% of the way between "a" and "b".*/
static inline Vector2 Vector2_Lerp(Vector2 a, Vector2 b, float t) {
  return (Vector2){
      .x = a.x + (b.x - a.x) * t,
      .y = a.y + (b.y - a.y) * t,
  };
}

/*Linearly interpolates between "a" and "b" by "t".
Returns a point at "t"% of the way between "a" and "b".*/
static inline Vector2 Vector2_Lerpclamped(Vector2 a, Vector2 b, float t) {
  /*clamp n between 0 and 1*/
  t = t < 0.0f ? 0.0f : t;
  t = t > 1.0f ? 1.0f : t;
  /*perform lerp*/
  return (Vector2){
      .x = a.x + (b.x - a.x) * t,
      .y = a.y + (b.y - a.y) * t,
  };
}

/*Converts a 2 dimensional vector to a 3 dimensional one*/
static inline Vector3 Vector2_ToVec3(Vector2 v) {
  return (Vector3){.x = v.x, .y = v.y, .z = 0.0f};
}

/*Converts a 2 dimensional vector to a 4 dimensional one*/
static inline Vector4 Vector2_ToVec4(Vector2 v) {
  return (Vector4){.x = v.x, .y = v.y, .z = 0.0f, .w = 1.0f};
}

/*Prints a vector "v" using printf*/
static inline void Vector3_Print(const Vector3 v, const char *label) {
  printf("%s [%f, %f, %f]\n", label, v.x, v.y, v.z);
}

/*Returns a vector that points in the opposite direction of the given vector
"v". The vector returned has a magnitude identical to the given vector "v"*/
static inline Vector3 Vector3_Negate(Vector3 v) {
  return (Vector3){.x = -v.x, .y = -v.y, .z = -v.z};
}

/*Adds a vector "a" to another vector "b"*/
static inline Vector3 Vector3_Add(Vector3 a, Vector3 b) {
  return (Vector3){.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z};
}

/*Subtracts a vector "subtrahend" from another vector "minuend"*/
static inline Vector3 Vector3_Subtract(Vector3 minuend, Vector3 subtrahend) {
  return (Vector3){.x = minuend.x - subtrahend.x,
                   .y = minuend.y - subtrahend.y,
                   .z = minuend.z - subtrahend.z};
}

/*A more performant way of getting the relative length of a
vector "v". This saves a square root operation making it more
performant than Vector3_Magnitude(). If all you have to do is
compare a vectors length relatively, use this function instead of
Vector3_Magnitude()*/
static inline float Vector3_SquareMagnitude(Vector3 v) {
  return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

/*Returns the actual length of a vector "v".
This uses a square root operation. Use Vector3_SquareMagnitudenitude()
to sacrifice accuracy and save on performance when comparing
distances.*/
static inline float Vector3_Magnitude(Vector3 v) {
  return sqrt(Vector3_SquareMagnitude(v));
}

/*Returns a given vector "v" as a unit vector.
This means the magnitude(length) of the returned
vector will always be 1 unit. The returned vector always points
in the same direction as the given vector "v"*/
static inline Vector3 Vector3_Normalize(Vector3 v) {
  float m = Vector3_Magnitude(v);
  if (m == 0)
    return Vector3_Zero();
  return (Vector3){.x = v.x / m, .y = v.y / m, .z = v.z / m};
}

/*Returns the distance between point a and point b
in units.*/
static inline float Vector3_Distance(Vector3 a, Vector3 b) {
  return Vector3_Magnitude(Vector3_Subtract(b, a));
}

/*Scales a vector "v" by "scalar".
increases the magnitude when "scalar" is greater than 1.
decreases the magnitude when "scalar" is less than 1.
The returned vector will point in the same direction as
the given vector "v".*/
static inline Vector3 Vector3_Scale(Vector3 v, float scalar) {
  return (Vector3){.x = v.x * scalar, .y = v.y * scalar, .z = v.z * scalar};
}

/*Returns a vector parallel to both "a" and "b".*/
static inline Vector3 Vector3_Cross(Vector3 a, Vector3 b) {
  return (Vector3){.x = (a.y * b.z) - (a.z * b.y),
                   .y = -((a.x * b.z) - (a.z * b.x)),
                   .z = (a.x * b.y) - (a.y * b.x)};
}

/*For normalized vectors Dot returns 1 if they point in
exactly the same direction, -1 if they point in completely opposite directions
and zero if the vectors are perpendicular.*/
static inline float Vector3_Dot(Vector3 a, Vector3 b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

/*Linearly interpolates between "a" and "b" by "t".
If you want to make sure the returned value stays
between "a" and "b", use Vector2_Lerpclamped() instead.
Returns a point at "t"% of the way between "a" and "b".*/
static inline Vector3 Vector3_Lerp(Vector3 a, Vector3 b, float t) {
  return (Vector3){
      .x = a.x + (b.x - a.x) * t,
      .y = a.y + (b.y - a.y) * t,
      .z = a.z + (b.z - a.z) * t,
  };
}

/*Linearly interpolates between "a" and "b" by "t".
Returns a point at "t"% of the way between "a" and "b".*/
static inline Vector3 Vector3_Lerpclamped(Vector3 a, Vector3 b, float n) {
  /*clamp n between 0 and 1*/
  n = n < 0.0f ? 0.0f : n;
  n = n > 1.0f ? 1.0f : n;
  /*perform lerp*/
  return (Vector3){
      .x = a.x + (b.x - a.x) * n,
      .y = a.y + (b.y - a.y) * n,
      .z = a.z + (b.z - a.z) * n,
  };
}

/*Returns a vector that is made from the largest components of two
vectors.*/
static inline Vector3 Vector3_Max(Vector3 a, Vector3 b) {
  return (Vector3){
      .x = a.x >= b.x ? a.x : b.x,
      .y = a.y >= b.y ? a.y : b.y,
      .z = a.z >= b.z ? a.z : b.z,
  };
}

/*Returns a vector that is made from the smallest components of two
vectors.*/
static inline Vector3 Vector3_Min(Vector3 a, Vector3 b) {
  return (Vector3){
      .x = a.x <= b.x ? a.x : b.x,
      .y = a.y <= b.y ? a.y : b.y,
      .z = a.z <= b.z ? a.z : b.z,
  };
}

/*Converts a 3 dimensional vector to a 2 dimensional one*/
static inline Vector2 Vector3_ToVec2(Vector3 v) {
  return (Vector2){.x = v.x, .y = v.y};
}

/*Converts a 3 dimensional vector to a 4 dimensional one*/
static inline Vector4 Vector3_ToVec4(Vector3 v) {
  return (Vector4){.x = v.x, .y = v.y, .z = v.z, .w = 1.0f};
}

/*Prints a vector "v" using printf*/
static inline void Vector4_Printf(const Vector4 v, const char *label) {
  printf("%s [%f, %f, %f, %f]\n", label, v.x, v.y, v.z, v.w);
}

/*Returns a vector that points in the opposite direction of the given vector
"v". The vector returned has a magnitude identical to the given vector "v"*/
static inline Vector4 Vector4_Negate(Vector4 v) {
  return (Vector4){.x = -v.x, .y = -v.y, .z = -v.z, .w = -v.w};
}

/*A more performant way of getting the relative length of a
vector "v". This saves a square root operation making it more
performant than Vector4_Magnitude(). If all you have to do is
compare a vectors length relatively, use this function instead of
Vector4_Magnitude()*/
static inline float Vector4_SquareMagnitude(Vector4 v) {
  return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

/*Returns the actual length of a vector "v".
This uses a square root operation. Use Vector4_SquareMagnitudenitude()
to sacrifice accuracy and save on performance when comparing
distances.*/
static inline float Vector4_Magnitude(Vector4 v) {
  return sqrt(Vector4_SquareMagnitude(v));
}

/*Returns a given vector "v" as a unit vector.
This means the magnitude(length) of the returned
vector will always be 1 unit. The returned vector always points
in the same direction as the given vector "v"*/
static inline Vector4 Vector4_Normalize(Vector4 v) {
  float m = Vector4_Magnitude(v);
  if (m == 0)
    return Vector4_Zero();
  return (Vector4){.x = v.x / m, .y = v.y / m, .z = v.z / m, .w = v.w / m};
}

/*Adds a vector "a" to another vector "b"*/
static inline Vector4 Vector4_Add(Vector4 a, Vector4 b) {
  return (Vector4){
      .x = a.x + b.x,
      .y = a.y + b.y,
      .z = a.z + b.z,
      .w = a.w + b.w,
  };
}

/*Subtracts a vector "subtrahend" from another vector "minuend"*/
static inline Vector4 Vector4_Subtract(Vector4 minuend, Vector4 subtrahend) {
  return (Vector4){
      .x = minuend.x - subtrahend.x,
      .y = minuend.y - subtrahend.y,
      .z = minuend.z - subtrahend.z,
      .w = minuend.w - subtrahend.w,
  };
}

/*Returns the distance between point a and point b
in units.*/
static inline float Vector4_Distance(Vector4 a, Vector4 b) {
  return Vector4_Magnitude(Vector4_Subtract(b, a));
}

/*Scales a vector "v" by "scalar".
increases the magnitude when "scalar" is greater than 1.
decreases the magnitude when "scalar" is less than 1.
The returned vector will point in the same direction as
the given vector "v".*/
static inline Vector4 Vector4_Scale(Vector4 v, float scalar) {
  return (Vector4){
      .x = v.x * scalar,
      .y = v.y * scalar,
      .z = v.z * scalar,
      .w = v.w * scalar,
  };
}

/*For normalized vectors Dot returns 1 if they point in
exactly the same direction, -1 if they point in completely opposite directions
and zero if the vectors are perpendicular.*/
static inline float Vector4_Dot(Vector4 a, Vector4 b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

/*Linearly interpolates between "a" and "b" by "t".
If you want to make sure the returned value stays
between "a" and "b", use Vector2_Lerpclamped() instead.
Returns a point at "t"% of the way between "a" and "b".*/
static inline Vector4 Vector4_Lerp(Vector4 a, Vector4 b, float t) {
  return (Vector4){
      .x = a.x + (b.x - a.x) * t,
      .y = a.y + (b.y - a.y) * t,
      .z = a.z + (b.z - a.z) * t,
      .w = a.w + (b.w - a.w) * t,
  };
}

/*Linearly interpolates between "a" and "b" by "t".
Returns a point at "t"% of the way between "a" and "b".*/
static inline Vector4 Vector4_Lerpclamped(Vector4 a, Vector4 b, float n) {
  /*clamp n between 0 and 1*/
  n = n < 0.0f ? 0.0f : n;
  n = n > 1.0f ? 1.0f : n;
  /*perform lerp*/
  return (Vector4){
      .x = a.x + (b.x - a.x) * n,
      .y = a.y + (b.y - a.y) * n,
      .z = a.z + (b.z - a.z) * n,
      .w = a.w + (b.w - a.w) * n,
  };
}

/*Returns a vector that is made from the largest components of two
vectors.*/
static inline Vector4 Vector4_Max(Vector4 a, Vector4 b) {
  return (Vector4){
      .x = a.x >= b.x ? a.x : b.x,
      .y = a.y >= b.y ? a.y : b.y,
      .z = a.z >= b.z ? a.z : b.z,
      .w = a.w >= b.w ? a.w : b.w,
  };
}

/*Returns a vector that is made from the smallest components of two
vectors.*/
static inline Vector4 Vector4_Min(Vector4 a, Vector4 b) {
  return (Vector4){
      .x = a.x <= b.x ? a.x : b.x,
      .y = a.y <= b.y ? a.y : b.y,
      .z = a.z <= b.z ? a.z : b.z,
      .w = a.w <= b.w ? a.w : b.w,
  };
}

/*Converts a 4 dimensional vector to a 2 dimensional one*/
static inline Vector2 Vector4_ToVec2(Vector4 v) {
  return (Vector2){.x = v.x, .y = v.y};
}

/*Converts a 4 dimensional vector to a 3 dimensional one*/
static inline Vector3 Vector4_ToVec3(Vector4 v) {
  return (Vector3){.x = v.x, .y = v.y, .z = v.z};
}
static inline Matrix4x4 Matrix4x4_Identity(void) {
  // clang-format off
  return (Matrix4x4){
      .elements = {
      1.0f, 0.0f, 0.0f, 0.0f, 
      0.0f, 1.0f, 0.0f, 0.0f, 
      0.0f, 0.0f, 1.0f, 0.0f, 
      0.0f, 0.0f, 0.0f, 1.0f
      }
  };
  // clang-format on
}

static inline Matrix4x4 Matrix4x4_scale(Matrix4x4 m, float scalar) {
  for (int i = 0; i < 16; i++) {
    m.elements[i] *= scalar;
  }
  return m;
}

static inline Matrix4x4 Matrix4x4_lookAt(Vector3 eye, Vector3 center,
                                         Vector3 up) {
  Vector3 f = Vector3_Normalize(Vector3_Subtract(eye, center));
  Vector3 s = Vector3_Normalize(Vector3_Cross(f, up));
  Vector3 u = Vector3_Cross(s, f);

  Matrix4x4 ret = Matrix4x4_Identity();
  ret.elements[0] = s.x;
  ret.elements[1] = u.x;
  ret.elements[2] = -f.x;
  ret.elements[3] = 0.0f;

  ret.elements[4] = s.y;
  ret.elements[5] = u.y;
  ret.elements[6] = -f.y;
  ret.elements[7] = 0.0f;

  ret.elements[8] = s.z;
  ret.elements[9] = u.z;
  ret.elements[10] = -f.z;
  ret.elements[11] = 0.0f;

  ret.elements[12] = -Vector3_Dot(s, eye);
  ret.elements[13] = -Vector3_Dot(u, eye);
  ret.elements[14] = Vector3_Dot(f, eye);
  ret.elements[15] = 1.0f;

  return ret;
}

/*Returns the difference between two 4x4 matrices.*/
static inline Matrix4x4 Matrix4x4_Subtract(const Matrix4x4 min,
                                           const Matrix4x4 sub) {
  Matrix4x4 dif = Matrix4x4_Identity();
  int i = 0;

  for (i = 0; i < 16; i++)
    dif.elements[i] = min.elements[i] - sub.elements[i];

  return dif;
}

static inline Matrix4x4 Matrix4x4_Perspective(float fov, float aspect,
                                              float near, float far) {
  Matrix4x4 result = Matrix4x4_Identity();
  float Cotangent = (1.0f / tanf(fov / 2.0f));
  result.elements[0] = (Cotangent / aspect);
  result.elements[5] = Cotangent;
  result.elements[10] = -((near + far) / (near - far)); // negate for lh coords
  result.elements[11] = 1.0f;                           // negate for lh coords
  result.elements[14] = ((2.0f * near * far) / (near - far));
  return result;
}

/*Multiplies a 4x4 matrix with a 3 dimensional vector*/
static inline Vector3 Matrix4x4_MultiplyVec3(Vector3 Left, Matrix4x4 Right) {
  Vector3 result;
  result.y = Left.y * Right.elements[0];
  result.x = Left.y * Right.elements[4];
  result.z = Left.y * Right.elements[8];

  result.y += Left.x * Right.elements[1];
  result.x += Left.x * Right.elements[5];
  result.z += Left.x * Right.elements[9];

  result.y += Left.z * Right.elements[2];
  result.x += Left.z * Right.elements[6];
  result.z += Left.z * Right.elements[10];

  return result;
}

/*Multiplies a 4x4 matrix with a 4 dimensional vector*/
static inline Vector4 Matrix4x4_MultiplyVec4(Vector4 Left, Matrix4x4 Right) {
  Vector4 result;
  result.y = Left.y * Right.elements[0];
  result.x = Left.y * Right.elements[4];
  result.z = Left.y * Right.elements[8];
  result.w = Left.y * Right.elements[12];

  result.y += Left.x * Right.elements[1];
  result.x += Left.x * Right.elements[5];
  result.z += Left.x * Right.elements[9];
  result.w += Left.x * Right.elements[13];

  result.y += Left.z * Right.elements[2];
  result.x += Left.z * Right.elements[6];
  result.z += Left.z * Right.elements[10];
  result.w += Left.z * Right.elements[13];

  result.y += Left.w * Right.elements[3];
  result.x += Left.w * Right.elements[7];
  result.z += Left.w * Right.elements[11];
  result.w += Left.w * Right.elements[15];

  return result;
}

/*Multiplies a 4x4 matrix with another 4x4 matrix*/
static inline Matrix4x4 Matrix4x4_Multiply(const Matrix4x4 a,
                                           const Matrix4x4 b) {
  return (Matrix4x4){
      .elements = {
          // column 0
          a.elements[0] * b.elements[0] + a.elements[4] * b.elements[1] +
              a.elements[8] * b.elements[2] + a.elements[12] * b.elements[3],
          a.elements[0] * b.elements[1] + a.elements[1] * b.elements[5] +
              a.elements[2] * b.elements[9] + a.elements[3] * b.elements[13],
          a.elements[0] * b.elements[2] + a.elements[1] * b.elements[6] +
              a.elements[2] * b.elements[10] + a.elements[3] * b.elements[14],
          a.elements[0] * b.elements[3] + a.elements[1] * b.elements[7] +
              a.elements[2] * b.elements[11] + a.elements[3] * b.elements[15],

          // column 1
          a.elements[4] * b.elements[0] + a.elements[5] * b.elements[4] +
              a.elements[6] * b.elements[8] + a.elements[7] * b.elements[12],
          a.elements[4] * b.elements[1] + a.elements[5] * b.elements[5] +
              a.elements[6] * b.elements[9] + a.elements[7] * b.elements[13],
          a.elements[4] * b.elements[2] + a.elements[5] * b.elements[6] +
              a.elements[6] * b.elements[10] + a.elements[7] * b.elements[14],
          a.elements[4] * b.elements[3] + a.elements[5] * b.elements[7] +
              a.elements[6] * b.elements[11] + a.elements[7] * b.elements[15],

          // column 2
          a.elements[8] * b.elements[0] + a.elements[9] * b.elements[4] +
              a.elements[10] * b.elements[8] + a.elements[11] * b.elements[12],
          a.elements[8] * b.elements[1] + a.elements[9] * b.elements[5] +
              a.elements[10] * b.elements[9] + a.elements[11] * b.elements[13],
          a.elements[8] * b.elements[2] + a.elements[9] * b.elements[6] +
              a.elements[10] * b.elements[10] + a.elements[11] * b.elements[14],
          a.elements[8] * b.elements[3] + a.elements[9] * b.elements[7] +
              a.elements[10] * b.elements[11] + a.elements[11] * b.elements[15],

          // column 3
          a.elements[12] * b.elements[0] + a.elements[13] * b.elements[4] +
              a.elements[14] * b.elements[8] + a.elements[15] * b.elements[12],
          a.elements[12] * b.elements[1] + a.elements[13] * b.elements[5] +
              a.elements[14] * b.elements[9] + a.elements[15] * b.elements[13],
          a.elements[12] * b.elements[2] + a.elements[13] * b.elements[6] +
              a.elements[14] * b.elements[10] + a.elements[15] * b.elements[14],
          a.elements[12] * b.elements[3] + a.elements[13] * b.elements[7] +
              a.elements[14] * b.elements[11] +
              a.elements[15] * b.elements[15]}};
}

/*Scales (multiplies) a 4x4 matrix by a scalar (number)*/
static inline Matrix4x4 Matrix4x4_SetScale(const Vector3 scale) {
  Matrix4x4 mat = Matrix4x4_Identity();
  mat.elements[0] = scale.x;
  mat.elements[5] = scale.y;
  mat.elements[10] = scale.z;
  return mat;
}

// returns a translation matrix from the specified Vector4 'v'
static inline Matrix4x4 Matrix4x4_Translation(Vector3 v) {
  Matrix4x4 result = Matrix4x4_Identity();
  result.elements[12] += v.x;
  result.elements[13] += v.y;
  result.elements[14] += v.z;
  return result;
}

/*Prints a formatted Matrix4x4 to the console.*/
static inline void Matrix4x4_Print(Matrix4x4 m, const char *label) {
  // TODO condense this to one printf call.
  printf("--------------------------------\n");
  printf("MATRIX4: %s\n", label);
  printf("[0] %8f \t", m.elements[0]);
  printf("[4] %8f \t", m.elements[4]);
  printf("[8] %8f \t", m.elements[8]);
  printf("[12]%8f \t", m.elements[12]);
  printf("\n");
  printf("[1] %8f \t", m.elements[1]);
  printf("[5] %8f \t", m.elements[5]);
  printf("[9] %8f \t", m.elements[9]);
  printf("[13]%8f \t", m.elements[13]);
  printf("\n");
  printf("[2] %8f \t", m.elements[2]);
  printf("[6] %8f \t", m.elements[6]);
  printf("[10]%8f \t", m.elements[10]);
  printf("[14]%8f \t", m.elements[14]);
  printf("\n");
  printf("[3] %8f \t", m.elements[3]);
  printf("[7] %8f \t", m.elements[7]);
  printf("[11]%8f \t", m.elements[11]);
  printf("[15]%8f \t", m.elements[15]);
  printf("\n--------------------------------\n");
}

#define QUATERNION_EPSILON (1e-4)

static inline Quaternion Quaternion_Set(float x, float y, float z, float w) {
  return (Quaternion){
      .w = w,
      .x = x,
      .y = y,
      .z = z,
  };
}

static inline Quaternion Quaternion_Identity(void) {
  return (Quaternion){.x = 0.0f, .y = 0.0f, .z = 0.0f, .w = 1.0f};
}

static inline int Quaternion_Equal(Quaternion a, Quaternion b) {
	return
		fabs(a.x - b.x) <= FLOAT_EPSILON &&
		fabs(a.y - b.y) <= FLOAT_EPSILON &&
		fabs(a.z - b.z) <= FLOAT_EPSILON &&
		fabs(a.w - b.w) <= FLOAT_EPSILON;
}

static inline Quaternion Quaternion_FromAngleAxis(float angle, Vector3 axis) {
	Quaternion ret;
	float s = sinf(angle/2);
  ret.x = axis.x * s;
  ret.y = axis.y * s;
  ret.z = axis.z * s;
  ret.w = cosf(angle/2);
  return ret;
}

static inline float Quaternion_Magnitude(Quaternion q) {
	return sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
}

static inline Quaternion Quaternion_Normalize(Quaternion q) {
	float mag = Quaternion_Magnitude(q);
	if (mag == 0) {
		return Quaternion_Identity();
	}
	q.w /= mag;
	q.x /= mag;
	q.y /= mag;
	q.z /= mag;
	return q;
}

static inline Quaternion Quaternion_Conjugate(Quaternion q) {
	return (Quaternion) { 
		.w = q.w, 
		.x = -q.x, 
		.y = -q.y, 
		.z = -q.z 
	};
}

static inline Quaternion Quaternion_Inverse(Quaternion q) {
	return (Quaternion) {
		.w = -q.w,
		.x = -q.x,
		.y = -q.y,
		.z = -q.z,
	};
}

static inline void Quaternion_Print(Quaternion q, const char *label) {
  printf("\t%12f, %12f, %12f, %12f\t%s\n", q.x, q.y, q.z, q.w, label);
}

static inline Quaternion Quaterion_Add(Quaternion q1, Quaternion q2) {
	return (Quaternion) {
		.w = q1.w + q2.w,
		.x = q1.x + q2.x,
		.y = q1.y + q2.y,
		.z = q1.z + q2.z,
	};
}

static inline Quaternion Quaternion_Multiply(Quaternion q1, Quaternion q2) {
  Quaternion ret = {0};
#if 0
  ret.w = q1.x * q2.w + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
  ret.x = q1.x * q2.x + q1.y * q2.z + q1.z * q2.y + q1.w * q2.x;
  ret.y = q1.x * q2.y + q1.y * q2.w + q1.z * q2.x + q1.w * q2.y;
  ret.z = q1.x * q2.z + q1.y * q2.x + q1.z * q2.w + q1.w * q2.z;
#elif 0
	ret.w = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
	ret.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z + q1.z * q2.y;
	ret.y = q1.w * q2.y + q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	ret.z = q1.w * q2.z + q1.x * q2.y + q1.y * q2.x + q1.z * q2.w;
#elif 0
	ret.w += q1.w * q2.w;
	ret.x += q1.w * q2.x;
	ret.y += q1.w * q2.y;
	ret.z += q1.w * q2.z;

	ret.x += q1.x * q2.x;
#elif 1
	ret.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	ret.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	ret.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	ret.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
#endif
  return ret;
}
#if 0
static inline Vector3 Vector3_Rotate(Vector3 v, Quaternion rotation) {
	Quaternion vq = (quaternion) {

	};
}
#else
/*
Returns the given vector 'v' rotated by the quaternion 'rotation'.
*/
static inline Vector3 Vector3_Rotate(Vector3 v, Quaternion rotation) {
	Quaternion ret = (Quaternion) {
		.w = 0,
		.x = v.x,
		.y = v.y,
		.z = v.z,
	};
	
	//Quaternion conjvq = Quaternion_Conjugate(rotation);
	//Quaternion temp1 = Quaternion_Multiply(rotation, vq);
	//Quaternion ret = Quaternion_Multiply(temp1, conjvq);
	//vq = Quaternion_Multiply(rotation, vq);
	ret = Quaternion_Multiply(Quaternion_Multiply(rotation, ret), Quaternion_Conjugate(rotation));

	return (Vector3) { 
		.x = ret.x, 
		.y = ret.y, 
		.z = ret.z,
	};
}
#endif

static inline Quaternion Quaternion_FromEuler(Vector3 eulerAngles) {
  Quaternion q;

#if 0
  float c1 = cosf(eulerAngles.y / 2.0f);
  float c2 = cosf(eulerAngles.x / 2.0f);
  float c3 = cosf(eulerAngles.z / 2.0f);

  float s1 = sinf(eulerAngles.y / 2.0f);
  float s2 = sinf(eulerAngles.x / 2.0f);
  float s3 = sinf(eulerAngles.z / 2.0f);

  q.w = c1 * c2 * c3 - s1 * s2 * s3;
  q.z = c1 * c2 * s3 + s1 * s2 * c3;
  q.y = s1 * c2 * c3 + c1 * s2 * s3;
  q.x = c1 * s2 * c3 - s1 * c2 * s3;
#else
	float cRoll = cosf(eulerAngles.x * 0.5f);
	float sRoll = sinf(eulerAngles.x * 0.5f);
	float cPitch = cosf(eulerAngles.y * 0.5f);
	float sPitch = sinf(eulerAngles.y * 0.5f);
	float cYaw = cosf(eulerAngles.z * 0.5f);
	float sYaw = sinf(eulerAngles.z * 0.5f);
	q.w = cRoll * cPitch * cYaw + sRoll * sPitch * sYaw;
	q.x = sRoll * cPitch * cYaw - cRoll * sPitch * sYaw;
	q.y = cRoll * sPitch * cYaw + sRoll * cPitch * sYaw;
	q.z = cRoll * cPitch * sYaw - sRoll * sPitch * cYaw;
#endif

  return q;
}

/* euclideanspace.com matrix index key
m00	m01	m02 m03
m10	m11	m12 m13
m20	m21	m22 m23
m30 m31 m32 m33
*/

static inline Matrix4x4 Quaternion_ToMatrix4x4(Quaternion q) {
  Matrix4x4 mat = Matrix4x4_Identity();
	float* m = mat.elements;
	
	float xx = q.x * q.x;
  float xy = q.x * q.y;
  float xz = q.x * q.z;
  float xw = q.x * q.w;
		
  float yy = q.y * q.y;
  float yz = q.y * q.z;
  float yw = q.y * q.w;
		
  float zz = q.z * q.z;
  float zw = q.z * q.w;

	m[0]  = 1 - 2 * ( yy + zz );
	m[4]  =     2 * ( xy - zw );
	m[8]  =     2 * ( xz + yw );

	m[1]  =     2 * ( xy + zw );
	m[5]  = 1 - 2 * ( xx + zz );
	m[9]  =     2 * ( yz - xw );

	m[2]  =     2 * ( xz - yw );
	m[6]  =     2 * ( yz + xw );
	m[10] = 1 - 2 * ( xx + yy );

	m[12] = m[13] = m[14] = m[3] = m[7] = m[11] = 0;
	m[15] = 1;

  return mat;
}
