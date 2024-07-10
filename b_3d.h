#pragma once

#include "b_math.h"

/*A small data structure for storing 2D positions, rotations, scales,
 * or lines.*/
typedef struct {
  float 		x;
  float 		y;
} Vector2;

/*A small data structure for storing 3D positions, rotations, scales,
 * or lines.*/
typedef struct {
  float 		x;
  float 		y;
  float 		z;
} Vector3;

/*A small data structure for storing 4D values*/
typedef struct {
  float 		x;
  float 		y;
  float 		z;
  float 		w;
} Vector4;

/*A column major 4x4 matrix*/
typedef struct{
  float 		elements[16];
} Matrix4x4;


typedef struct {
	float 		x;
	float 		y;
	float 		z;
	float 		w;
} Quaternion;


// clang-format off
static inline Vector2 Vector2_Zero	(void)		{ return (Vector2) {0.0f,	0.0f	}; }
static inline Vector2 Vector2_One	(float s)	{ return (Vector2) {s,		s	}; }
static inline Vector2 Vector2_Up	(float s)	{ return (Vector2) {0.0f,	s	}; }
static inline Vector2 Vector2_Down	(float s)	{ return (Vector2) {0.0f,	-s	}; }
static inline Vector2 Vector2_Right	(float s)	{ return (Vector2) {s,		0.0f	}; }
static inline Vector2 Vector2_Left	(float s)	{ return (Vector2) {-s,		0.0f	}; }

static inline Vector3 Vector3_Zero	(void) 	 	{ return (Vector3) {0.0f,	0.0f,	0.0f 	}; }
static inline Vector3 Vector3_One	(float s)	{ return (Vector3) {s,		s,	s	}; }
static inline Vector3 Vector3_Up	(float s)	{ return (Vector3) {0.0f,	s,	0.0f 	}; }
static inline Vector3 Vector3_Down	(float s)	{ return (Vector3) {0.0f,	-s,	0.0f 	}; }
static inline Vector3 Vector3_Right	(float s)	{ return (Vector3) {s,		0.0f, 	0.0f 	}; }
static inline Vector3 Vector3_Left	(float s)	{ return (Vector3) {-s,		0.0f, 	0.0f 	}; }
static inline Vector3 Vector3_Forward	(float s)	{ return (Vector3) {0.0f,	0.0f, 	s	}; }
static inline Vector3 Vector3_Back	(float s)	{ return (Vector3) {0.0f,	0.0f, 	-s	}; }

static inline Vector4 Vector4_Zero	(void) 	 	{ return (Vector4) {0.0f,	0.0f,	0.0f,	1.0f}; }
static inline Vector4 Vector4_One	(float s)	{ return (Vector4) {s,		s,	s,	1.0f}; }
static inline Vector4 Vector4_Up	(float s)	{ return (Vector4) {0.0f,	s,	0.0f,	1.0f}; }
static inline Vector4 Vector4_Down	(float s)	{ return (Vector4) {0.0f,	-s,	0.0f,	1.0f}; }
static inline Vector4 Vector4_Right	(float s)	{ return (Vector4) {s,		0.0f, 	0.0f,	1.0f}; }
static inline Vector4 Vector4_Left	(float s)	{ return (Vector4) {-s,		0.0f, 	0.0f,	1.0f}; }
static inline Vector4 Vector4_Forward	(float s)	{ return (Vector4) {0.0f,	0.0f, 	s,	1.0f}; }
static inline Vector4 Vector4_Back	(float s)	{ return (Vector4) {0.0f,	0.0f, 	-s,	1.0f}; }
// clang-format on

/*Prints a vector "v" using printf*/
static inline void Vector2_Print (const Vector2 v, const char *label) {
  printf ("%s [%f, %f]\n", label, v.x, v.y);
}

/*Returns a vector that points in the opposite direction of the given vector
"v". The vector returned has a magnitude identical to the given vector "v"*/
static inline Vector2 Vector2_Negate (Vector2 v) {
  return (Vector2){ .x = -v.x, .y = -v.y };
}

/*Subtracts a vector "subtrahend" from another vector "minuend"*/
static inline Vector2 Vector2_Subtract (Vector2 minuend, Vector2 subtrahend) {
  return (Vector2){ .x = minuend.x - subtrahend.x,
                      .y = minuend.y - subtrahend.y };
}

/*Adds a vector "a" to another vector "b"*/
static inline Vector2 Vector2_Add (Vector2 a, Vector2 b) {
  return (Vector2){ .x = a.x + b.x, .y = a.y + b.y };
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
  return sqrt (Vector2_SquareMagnitude(v));
}

/*Returns a given vector "v" as a unit vector.
This means the magnitude(length) of the returned
vector will always be 1 unit. The returned vector always points
in the same direction as the given vector "v"*/
static inline Vector2 Vector2_Normalize (Vector2 v) {
  float m = Vector2_Magnitude(v);
  if (m == 0)
    return Vector2_Zero();
  return (Vector2){ .x = v.x / m, .y = v.y / m };
}

/*Returns the distance between point a and point b
in units.*/
static inline float Vector2_Distance (Vector2 a, Vector2 b) {
  return Vector2_Magnitude(Vector2_Subtract (b, a));
}

/*Scales a vector "v" by "scalar".
increases the magnitude when "scalar" is greater than 1.
decreases the magnitude when "scalar" is less than 0.
The returned vector will point in the same direction as
the given vector "v".*/
static inline Vector2 Vector2_Scale (Vector2 v, float scalar) {
  return (Vector2){ .x = v.x * scalar, .y = v.y * scalar };
}

/*For normalized vectors Dot returns 1 if they point in
exactly the same direction, -1 if they point in completely opposite directions
and zero if the vectors are perpendicular.*/
static inline float Vector2_Dot (Vector2 a, Vector2 b) {
  return (a.x * b.x) + (a.y * b.y);
}

/*Linearly interpolates between "a" and "b" by "t".
If you want to make sure the returned value stays
between "a" and "b", use Vector3_Lerpclamped() instead.
Returns a point at "t"% of the way between "a" and "b".*/
static inline Vector2 Vector2_Lerp (Vector2 a, Vector2 b, float t) {
  return (Vector2){
    .x = a.x + (b.x - a.x) * t,
    .y = a.y + (b.y - a.y) * t,
  };
}

/*Linearly interpolates between "a" and "b" by "t".
Returns a point at "t"% of the way between "a" and "b".*/
static inline Vector2 Vector2_Lerpclamped (Vector2 a, Vector2 b, float t) {
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
static inline Vector3 Vector2_ToVec3 (Vector2 v) {
  return (Vector3){ .x = v.x, .y = v.y, .z = 0.0f };
}

/*Converts a 2 dimensional vector to a 4 dimensional one*/
static inline Vector4 Vector2_ToVec4 (Vector2 v) {
  return (Vector4){ .x = v.x, .y = v.y, .z = 0.0f, .w = 1.0f };
}

/*Prints a vector "v" using printf*/
static inline void Vector3_Print (const Vector3 v, const char *label) {
  printf ("%s [%f, %f, %f]\n", label, v.x, v.y, v.z);
}

/*Returns a vector that points in the opposite direction of the given vector
"v". The vector returned has a magnitude identical to the given vector "v"*/
static inline Vector3 Vector3_Negate (Vector3 v) {
  return (Vector3){ .x = -v.x, .y = -v.y, .z = -v.z };
}

/*Adds a vector "a" to another vector "b"*/
static inline Vector3 Vector3_Add (Vector3 a, Vector3 b) {
  return (Vector3){ .x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z };
}

/*Subtracts a vector "subtrahend" from another vector "minuend"*/
static inline Vector3 Vector3_Subtract (Vector3 minuend, Vector3 subtrahend) {
  return (Vector3){ .x = minuend.x - subtrahend.x,
                      .y = minuend.y - subtrahend.y,
                      .z = minuend.z - subtrahend.z };
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
  return sqrt (Vector3_SquareMagnitude(v));
}

/*Returns a given vector "v" as a unit vector.
This means the magnitude(length) of the returned
vector will always be 1 unit. The returned vector always points
in the same direction as the given vector "v"*/
static inline Vector3 Vector3_Normalize (Vector3 v) {
  float m = Vector3_Magnitude(v);
  if (m == 0)
    return Vector3_Zero();
  return (Vector3){ .x = v.x / m, .y = v.y / m, .z = v.z / m };
}

/*Returns the distance between point a and point b
in units.*/
static inline float Vector3_Distance (Vector3 a, Vector3 b) {
  return Vector3_Magnitude(Vector3_Subtract (b, a));
}

/*Scales a vector "v" by "scalar".
increases the magnitude when "scalar" is greater than 1.
decreases the magnitude when "scalar" is less than 1.
The returned vector will point in the same direction as
the given vector "v".*/
static inline Vector3 Vector3_Scale (Vector3 v, float scalar) {
  return (
      Vector3){ .x = v.x * scalar, .y = v.y * scalar, .z = v.z * scalar };
}

/*Returns a vector parallel to both "a" and "b".*/
static inline Vector3 Vector3_Cross (Vector3 a, Vector3 b) {
  return (Vector3){ .x = (a.y * b.z) - (a.z * b.y),
                      .y = -((a.x * b.z) - (a.z * b.x)),
                      .z = (a.x * b.y) - (a.y * b.x) };
}

/*For normalized vectors Dot returns 1 if they point in
exactly the same direction, -1 if they point in completely opposite directions
and zero if the vectors are perpendicular.*/
static inline float Vector3_Dot (Vector3 a, Vector3 b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

/*Linearly interpolates between "a" and "b" by "t".
If you want to make sure the returned value stays
between "a" and "b", use Vector2_Lerpclamped() instead.
Returns a point at "t"% of the way between "a" and "b".*/
static inline Vector3 Vector3_Lerp (Vector3 a, Vector3 b, float t) {
  return (Vector3){
    .x = a.x + (b.x - a.x) * t,
    .y = a.y + (b.y - a.y) * t,
    .z = a.z + (b.z - a.z) * t,
  };
}

/*Linearly interpolates between "a" and "b" by "t".
Returns a point at "t"% of the way between "a" and "b".*/
static inline Vector3 Vector3_Lerpclamped (Vector3 a, Vector3 b, float n) {
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
static inline Vector3 Vector3_Max (Vector3 a, Vector3 b) {
  return (Vector3){
    .x = a.x >= b.x ? a.x : b.x,
    .y = a.y >= b.y ? a.y : b.y,
    .z = a.z >= b.z ? a.z : b.z,
  };
}

/*Returns a vector that is made from the smallest components of two
vectors.*/
static inline Vector3 Vector3_Min (Vector3 a, Vector3 b) {
  return (Vector3){
    .x = a.x <= b.x ? a.x : b.x,
    .y = a.y <= b.y ? a.y : b.y,
    .z = a.z <= b.z ? a.z : b.z,
  };
}

/*Converts a 3 dimensional vector to a 2 dimensional one*/
static inline Vector2 Vector3_ToVec2 (Vector3 v) {
  return (Vector2){ .x = v.x, .y = v.y };
}

/*Converts a 3 dimensional vector to a 4 dimensional one*/
static inline Vector4 Vector3_ToVec4 (Vector3 v) {
  return (Vector4){ .x = v.x, .y = v.y, .z = v.z, .w = 1.0f };
}

/*Prints a vector "v" using printf*/
static inline void Vector4_Printf (const Vector4 v, const char *label) {
  printf ("%s [%f, %f, %f, %f]\n", label, v.x, v.y, v.z, v.w);
}

/*Returns a vector that points in the opposite direction of the given vector
"v". The vector returned has a magnitude identical to the given vector "v"*/
static inline Vector4 Vector4_Negate (Vector4 v) {
  return (Vector4){ .x = -v.x, .y = -v.y, .z = -v.z, .w = -v.w };
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
  return sqrt (Vector4_SquareMagnitude(v));
}

/*Returns a given vector "v" as a unit vector.
This means the magnitude(length) of the returned
vector will always be 1 unit. The returned vector always points
in the same direction as the given vector "v"*/
static inline Vector4 Vector4_Normalize (Vector4 v) {
  float m = Vector4_Magnitude(v);
  if (m == 0)
    return Vector4_Zero();
  return (Vector4){ .x = v.x / m, .y = v.y / m, .z = v.z / m, .w = v.w / m };
}

/*Adds a vector "a" to another vector "b"*/
static inline Vector4 Vector4_Add (Vector4 a, Vector4 b) {
  return (Vector4){
    .x = a.x + b.x,
    .y = a.y + b.y,
    .z = a.z + b.z,
    .w = a.w + b.w,
  };
}

/*Subtracts a vector "subtrahend" from another vector "minuend"*/
static inline Vector4 Vector4_Subtract (Vector4 minuend, Vector4 subtrahend) {
  return (Vector4){
    .x = minuend.x - subtrahend.x,
    .y = minuend.y - subtrahend.y,
    .z = minuend.z - subtrahend.z,
    .w = minuend.w - subtrahend.w,
  };
}

/*Returns the distance between point a and point b
in units.*/
static inline float Vector4_Distance (Vector4 a, Vector4 b) {
  return Vector4_Magnitude(Vector4_Subtract (b, a));
}

/*Scales a vector "v" by "scalar".
increases the magnitude when "scalar" is greater than 1.
decreases the magnitude when "scalar" is less than 1.
The returned vector will point in the same direction as
the given vector "v".*/
static inline Vector4 Vector4_Scale (Vector4 v, float scalar) {
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
static inline float Vector4_Dot (Vector4 a, Vector4 b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

/*Linearly interpolates between "a" and "b" by "t".
If you want to make sure the returned value stays
between "a" and "b", use Vector2_Lerpclamped() instead.
Returns a point at "t"% of the way between "a" and "b".*/
static inline Vector4 Vector4_Lerp (Vector4 a, Vector4 b, float t) {
  return (Vector4){
    .x = a.x + (b.x - a.x) * t,
    .y = a.y + (b.y - a.y) * t,
    .z = a.z + (b.z - a.z) * t,
    .w = a.w + (b.w - a.w) * t,
  };
}

/*Linearly interpolates between "a" and "b" by "t".
Returns a point at "t"% of the way between "a" and "b".*/
static inline Vector4 Vector4_Lerpclamped (Vector4 a, Vector4 b, float n) {
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
static inline Vector4 Vector4_Max (Vector4 a, Vector4 b) {
  return (Vector4){
    .x = a.x >= b.x ? a.x : b.x,
    .y = a.y >= b.y ? a.y : b.y,
    .z = a.z >= b.z ? a.z : b.z,
    .w = a.w >= b.w ? a.w : b.w,
  };
}

/*Returns a vector that is made from the smallest components of two
vectors.*/
static inline Vector4 Vector4_Min (Vector4 a, Vector4 b) {
  return (Vector4){
    .x = a.x <= b.x ? a.x : b.x,
    .y = a.y <= b.y ? a.y : b.y,
    .z = a.z <= b.z ? a.z : b.z,
    .w = a.w <= b.w ? a.w : b.w,
  };
}

/*Converts a 4 dimensional vector to a 2 dimensional one*/
static inline Vector2 Vector4_ToVec2 (Vector4 v) {
  return (Vector2){ .x = v.x, .y = v.y };
}

/*Converts a 4 dimensional vector to a 3 dimensional one*/
static inline Vector3 Vector4_ToVec3 (Vector4 v) {
  return (Vector3){ .x = v.x, .y = v.y, .z = v.z };
}
static inline Matrix4x4 Matrix4x4_identity(void) {
	return (Matrix4x4){
		.elements = { 
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f 
		} 
	};
}

static inline Matrix4x4 Matrix4x4_scale(Matrix4x4 m, float scalar) {
	for (int i = 0; i < 16; i++) {
		m.elements[i] *= scalar;
	}
	return m;
}

#if 0
static inline float Matrix4x4_determinant(Matrix4x4 mat) {
	float* m = mat.elements;
#if 0
	return 
		m[3]*m[6]*m[9]*m[12] - m[2]*m[7]*m[9]*m[12] - m[3]*m[5]*m[10]*m[12] + m[1]*m[7]*m[10]*m[12]+
		m[2]*m[5]*m[11]*m[12] - m[1]*m[6]*m[11]*m[12] - m[3]*m[6]*m[8]*m[13] + m[2]*m[7]*m[8]*m[13]+
		m[3]*m[4]*m[10]*m[13] - m[0]*m[7]*m[10]*m[13] - m[2]*m[4]*m[11]*m[13] + m[0]*m[6]*m[11]*m[13]+
		m[3]*m[5]*m[8]*m[14] - m[1]*m[7]*m[8]*m[14] - m[3]*m[4]*m[9]*m[14] + m[0]*m[7]*m[9]*m[14]+
		m[1]*m[4]*m[11]*m[14] - m[0]*m[5]*m[11]*m[14] - m[2]*m[5]*m[8]*m[15] + m[1]*m[6]*m[8]*m[15]+
		m[2]*m[4]*m[9]*m[15] - m[0]*m[6]*m[9]*m[15] - m[1]*m[4]*m[10]*m[15] + m[0]*m[5]*m[10]*m[15];
#else
	return
		m[12]*m[9]*m[6]*m[3] - m[8]*m[13]*m[6]*m[3] - m[12]*m[5]*m[10]*m[3] + m[4]*m[13]*m[10]*m[3]+
   m[8]*m[5]*m[14]*m[3] - m[4]*m[9]*m[14]*m[3] - m[12]*m[9]*m[2]*m[7] + m[8]*m[13]*m[2]*m[7]+
   m[12]*m[1]*m[10]*m[7] - m[0]*m[13]*m[10]*m[7] - m[8]*m[1]*m[14]*m[7] + m[0]*m[9]*m[14]*m[7]+
   m[12]*m[5]*m[2]*m[11] - m[4]*m[13]*m[2]*m[11] - m[12]*m[1]*m[6]*m[11] + m[0]*m[13]*m[6]*m[11]+
   m[4]*m[1]*m[14]*m[11] - m[0]*m[5]*m[14]*m[11] - m[8]*m[5]*m[2]*m[15] + m[4]*m[9]*m[2]*m[15]+
   m[8]*m[1]*m[6]*m[15] - m[0]*m[9]*m[6]*m[15] - m[4]*m[1]*m[10]*m[15] + m[0]*m[5]*m[10]*m[15];
#endif
}
		
static inline Matrix4x4 Matrix4x4_inverse(Matrix4x4 mat) {
	float* m = mat.elements;
#if 1 //switch between column and row major 
	m[0]	= m[6]*m[11]*m[13] - m[7]*m[10]*m[13] + m[7]*m[9]*m[14] - m[5]*m[11]*m[14] - m[6]*m[9]*m[15] + m[5]*m[10]*m[15];
	m[1]	= m[3]*m[10]*m[13] - m[2]*m[11]*m[13] - m[3]*m[9]*m[14] + m[1]*m[11]*m[14] + m[2]*m[9]*m[15] - m[1]*m[10]*m[15];
	m[2]	= m[2]*m[7]*m[13] - m[3]*m[6]*m[13] + m[3]*m[5]*m[14] - m[1]*m[7]*m[14] - m[2]*m[5]*m[15] + m[1]*m[6]*m[15];
	m[3]	= m[3]*m[6]*m[9] - m[2]*m[7]*m[9] - m[3]*m[5]*m[10] + m[1]*m[7]*m[10] + m[2]*m[5]*m[11] - m[1]*m[6]*m[11];
	m[4]	= m[7]*m[10]*m[12] - m[6]*m[11]*m[12] - m[7]*m[8]*m[14] + m[4]*m[11]*m[14] + m[6]*m[8]*m[15] - m[4]*m[10]*m[15];
	m[5]	= m[2]*m[11]*m[12] - m[3]*m[10]*m[12] + m[3]*m[8]*m[14] - m[0]*m[11]*m[14] - m[2]*m[8]*m[15] + m[0]*m[10]*m[15];
	m[6]	= m[3]*m[6]*m[12] - m[2]*m[7]*m[12] - m[3]*m[4]*m[14] + m[0]*m[7]*m[14] + m[2]*m[4]*m[15] - m[0]*m[6]*m[15];
	m[7]	= m[2]*m[7]*m[8] - m[3]*m[6]*m[8] + m[3]*m[4]*m[10] - m[0]*m[7]*m[10] - m[2]*m[4]*m[11] + m[0]*m[6]*m[11];
	m[8]	= m[5]*m[11]*m[12] - m[7]*m[9]*m[12] + m[7]*m[8]*m[13] - m[4]*m[11]*m[13] - m[5]*m[8]*m[15] + m[4]*m[9]*m[15];
	m[9]	= m[3]*m[9]*m[12] - m[1]*m[11]*m[12] - m[3]*m[8]*m[13] + m[0]*m[11]*m[13] + m[1]*m[8]*m[15] - m[0]*m[9]*m[15];
	m[10] = m[1]*m[7]*m[12] - m[3]*m[5]*m[12] + m[3]*m[4]*m[13] - m[0]*m[7]*m[13] - m[1]*m[4]*m[15] + m[0]*m[5]*m[15];
	m[11] = m[3]*m[5]*m[8] - m[1]*m[7]*m[8] - m[3]*m[4]*m[9] + m[0]*m[7]*m[9] + m[1]*m[4]*m[11] - m[0]*m[5]*m[11];
	m[12] = m[6]*m[9]*m[12] - m[5]*m[10]*m[12] - m[6]*m[8]*m[13] + m[4]*m[10]*m[13] + m[5]*m[8]*m[14] - m[4]*m[9]*m[14];
	m[13] = m[1]*m[10]*m[12] - m[2]*m[9]*m[12] + m[2]*m[8]*m[13] - m[0]*m[10]*m[13] - m[1]*m[8]*m[14] + m[0]*m[9]*m[14];
	m[14] = m[2]*m[5]*m[12] - m[1]*m[6]*m[12] - m[2]*m[4]*m[13] + m[0]*m[6]*m[13] + m[1]*m[4]*m[14] - m[0]*m[5]*m[14];
	m[15] = m[1]*m[6]*m[8] - m[2]*m[5]*m[8] + m[2]*m[4]*m[9] - m[0]*m[6]*m[9] - m[1]*m[4]*m[10] + m[0]*m[5]*m[10];
#else
	m[0] = m[9]*m[14]*m[7] - m[13]*m[10]*m[7] + m[13]*m[6]*m[11] - m[5]*m[14]*m[11] - m[9]*m[6]*m[15] + m[5]*m[10]*m[15];
  m[4] = m[12]*m[10]*m[7] - m[8]*m[14]*m[7] - m[12]*m[6]*m[11] + m[4]*m[14]*m[11] + m[8]*m[6]*m[15] - m[4]*m[10]*m[15];
  m[8] = m[8]*m[13]*m[7] - m[12]*m[9]*m[7] + m[12]*m[5]*m[11] - m[4]*m[13]*m[11] - m[8]*m[5]*m[15] + m[4]*m[9]*m[15];
  m[12] = m[12]*m[9]*m[6] - m[8]*m[13]*m[6] - m[12]*m[5]*m[10] + m[4]*m[13]*m[10] + m[8]*m[5]*m[14] - m[4]*m[9]*m[14];
  m[1] = m[13]*m[10]*m[3] - m[9]*m[14]*m[3] - m[13]*m[2]*m[11] + m[1]*m[14]*m[11] + m[9]*m[2]*m[15] - m[1]*m[10]*m[15];
  m[5] = m[8]*m[14]*m[3] - m[12]*m[10]*m[3] + m[12]*m[2]*m[11] - m[0]*m[14]*m[11] - m[8]*m[2]*m[15] + m[0]*m[10]*m[15];
  m[9] = m[12]*m[9]*m[3] - m[8]*m[13]*m[3] - m[12]*m[1]*m[11] + m[0]*m[13]*m[11] + m[8]*m[1]*m[15] - m[0]*m[9]*m[15];
  m[13] = m[8]*m[13]*m[2] - m[12]*m[9]*m[2] + m[12]*m[1]*m[10] - m[0]*m[13]*m[10] - m[8]*m[1]*m[14] + m[0]*m[9]*m[14];
  m[2] = m[5]*m[14]*m[3] - m[13]*m[6]*m[3] + m[13]*m[2]*m[7] - m[1]*m[14]*m[7] - m[5]*m[2]*m[15] + m[1]*m[6]*m[15];
  m[6] = m[12]*m[6]*m[3] - m[4]*m[14]*m[3] - m[12]*m[2]*m[7] + m[0]*m[14]*m[7] + m[4]*m[2]*m[15] - m[0]*m[6]*m[15];
  m[10] = m[4]*m[13]*m[3] - m[12]*m[5]*m[3] + m[12]*m[1]*m[7] - m[0]*m[13]*m[7] - m[4]*m[1]*m[15] + m[0]*m[5]*m[15];
  m[14] = m[12]*m[5]*m[2] - m[4]*m[13]*m[2] - m[12]*m[1]*m[6] + m[0]*m[13]*m[6] + m[4]*m[1]*m[14] - m[0]*m[5]*m[14];
  m[3] = m[9]*m[6]*m[3] - m[5]*m[10]*m[3] - m[9]*m[2]*m[7] + m[1]*m[10]*m[7] + m[5]*m[2]*m[11] - m[1]*m[6]*m[11];
  m[7] = m[4]*m[10]*m[3] - m[8]*m[6]*m[3] + m[8]*m[2]*m[7] - m[0]*m[10]*m[7] - m[4]*m[2]*m[11] + m[0]*m[6]*m[11];
  m[11] = m[8]*m[5]*m[3] - m[4]*m[9]*m[3] - m[8]*m[1]*m[7] + m[0]*m[9]*m[7] + m[4]*m[1]*m[11] - m[0]*m[5]*m[11];
  m[15] = m[4]*m[9]*m[2] - m[8]*m[5]*m[2] + m[8]*m[1]*m[6] - m[0]*m[9]*m[6] - m[4]*m[1]*m[10] + m[0]*m[5]*m[10];
#endif

	Matrix4x4 ret = Matrix4x4_scale(mat, 1 / Matrix4x4_determinant(mat));

	return ret;
}
#endif

static inline Matrix4x4 Matrix4x4_lookAt (Vector3 eye, Vector3 center, Vector3 up) {
  Vector3 f = Vector3_Normalize (Vector3_Subtract (eye, center));
  Vector3 s = Vector3_Normalize (Vector3_Cross (f, up));
  Vector3 u = Vector3_Cross (s, f);

  Matrix4x4 ret = Matrix4x4_identity();
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

  ret.elements[12] = -Vector3_Dot (s, eye);
  ret.elements[13] = -Vector3_Dot (u, eye);
  ret.elements[14] = Vector3_Dot (f, eye);
  ret.elements[15] = 1.0f;

  return ret;
}

/*Returns the difference between two 4x4 matrices.*/
static inline Matrix4x4 Matrix4x4_subtract (const Matrix4x4 min, const Matrix4x4 sub) {
  Matrix4x4 dif = Matrix4x4_identity();
  int i = 0;

  for (i = 0; i < 16; i++)
      dif.elements[i] = min.elements[i] - sub.elements[i];

  return dif;
}

static inline Matrix4x4 Matrix4x4_perspective (float fov, float aspect, float near, float far) {
  Matrix4x4 result = Matrix4x4_identity();
  float Cotangent = (1.0f / tanf (fov / 2.0f));
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
static inline Matrix4x4 Matrix4x4_Multiply (const Matrix4x4 a, const Matrix4x4 b){
	return (Matrix4x4){ 
		.elements = { 
			// column 0
			a.elements[0] * b.elements[0] + a.elements[4] * b.elements[1] + a.elements[8] * b.elements[2] + a.elements[12] * b.elements[3],
			a.elements[0] * b.elements[1] + a.elements[1] * b.elements[5] + a.elements[2] * b.elements[9] + a.elements[3] * b.elements[13],
			a.elements[0] * b.elements[2] + a.elements[1] * b.elements[6] + a.elements[2] * b.elements[10] + a.elements[3] * b.elements[14],
			a.elements[0] * b.elements[3] + a.elements[1] * b.elements[7] + a.elements[2] * b.elements[11] + a.elements[3] * b.elements[15],

			// column 1
			a.elements[4] * b.elements[0] + a.elements[5] * b.elements[4] + a.elements[6] * b.elements[8] + a.elements[7] * b.elements[12],
			a.elements[4] * b.elements[1] + a.elements[5] * b.elements[5] + a.elements[6] * b.elements[9] + a.elements[7] * b.elements[13],
			a.elements[4] * b.elements[2] + a.elements[5] * b.elements[6] + a.elements[6] * b.elements[10] + a.elements[7] * b.elements[14],
			a.elements[4] * b.elements[3] + a.elements[5] * b.elements[7] + a.elements[6] * b.elements[11] + a.elements[7] * b.elements[15],

			// column 2
			a.elements[8] * b.elements[0] + a.elements[9] * b.elements[4] + a.elements[10] * b.elements[8] + a.elements[11] * b.elements[12],
			a.elements[8] * b.elements[1] + a.elements[9] * b.elements[5] + a.elements[10] * b.elements[9] + a.elements[11] * b.elements[13],
			a.elements[8] * b.elements[2] + a.elements[9] * b.elements[6] + a.elements[10] * b.elements[10] + a.elements[11] * b.elements[14],
			a.elements[8] * b.elements[3] + a.elements[9] * b.elements[7] + a.elements[10] * b.elements[11] + a.elements[11] * b.elements[15],

			// column 3
			a.elements[12] * b.elements[0] + a.elements[13] * b.elements[4] + a.elements[14] * b.elements[8] + a.elements[15] * b.elements[12],
			a.elements[12] * b.elements[1] + a.elements[13] * b.elements[5] + a.elements[14] * b.elements[9] + a.elements[15] * b.elements[13],
			a.elements[12] * b.elements[2] + a.elements[13] * b.elements[6] + a.elements[14] * b.elements[10] + a.elements[15] * b.elements[14],
			a.elements[12] * b.elements[3] + a.elements[13] * b.elements[7] + a.elements[14] * b.elements[11] + a.elements[15] * b.elements[15] 
		}
	};
}

/*Scales (multiplies) a 4x4 matrix by a scalar (number)*/
static inline Matrix4x4 Matrix4x4_setScale (const Vector3 scale){
  Matrix4x4 mat = Matrix4x4_identity();
  mat.elements[0] = scale.x;
  mat.elements[5] = scale.y;
  mat.elements[10] = scale.z;
  return mat;
}

/*Returns a rotation matrix around "axis" by "angle"*/
static inline Matrix4x4 Matrix4x4_rotate (const float angle, Vector3 axis){
  /*TODO to make this compatible with rh
  coordinate system, just invert the angle!*/
  Matrix4x4 result = Matrix4x4_identity();

  axis = Vector3_Normalize (axis);

  float sinTheta = sinf (angle);
  float cosTheta = cosf (angle);
  float cosValue = 1.0f - cosTheta;

  result.elements[0] = (axis.x * axis.x * cosValue) + cosTheta;
  result.elements[1] = (axis.x * axis.y * cosValue) + (axis.z * sinTheta);
  result.elements[2] = (axis.x * axis.z * cosValue) - (axis.y * sinTheta);

  result.elements[4] = (axis.y * axis.x * cosValue) - (axis.z * sinTheta);
  result.elements[5] = (axis.y * axis.y * cosValue) + cosTheta;
  result.elements[6] = (axis.y * axis.z * cosValue) + (axis.x * sinTheta);

  result.elements[8] = (axis.z * axis.x * cosValue) + (axis.y * sinTheta);
  result.elements[9] = (axis.z * axis.y * cosValue) - (axis.x * sinTheta);
  result.elements[10] = (axis.z * axis.z * cosValue) + cosTheta;

  return result;
}

/*Translates a vector to a 4x4 matrix*/
static inline Matrix4x4 Matrix4x4_translateVec3 (Vector3 t) {
  Matrix4x4 result = Matrix4x4_identity();
  result.elements[12] += t.x;
  result.elements[13] += t.y;
  result.elements[14] += t.z;
  return result;
}

/*Translates a vector to a 4x4 matrix*/
static inline Matrix4x4 Matrix4x4_translateVec4 (Vector4 t) {
  Matrix4x4 result = Matrix4x4_identity();
  result.elements[12] += t.x;
  result.elements[13] += t.y;
  result.elements[14] += t.z;
  result.elements[15] += t.w;
  return result;
}

/*Perspective transformation used for calculating depth*/
/*Adds a 4x4 matrix to another 4x4 matrix.*/
static inline Matrix4x4 Matrix4x4_add (const Matrix4x4 a, const Matrix4x4 b) {
  Matrix4x4 sum = Matrix4x4_identity();
  int i = 0;

  for (i = 0; i < 16; i++)
      sum.elements[i] = a.elements[i] + b.elements[i];

  return sum;
}



/*Prints a formatted Matrix4x4 to the console.*/
static inline void Matrix4x4_print (Matrix4x4 m, const char *label) {
  printf ("--------------------------------\n");
  printf ("MATRIX4: %s\n", label);

  // use this for row major printing
  //  for (i = 0; i < 16; i++) {
  //  	if (i == 4 || i == 8 || i == 12) printf("\n");
  //  	printf("i%li\t%f\t",i,m.elements[i]);
  //  }

  // use this for column major printing
  printf ("[0](%f) ", m.elements[0]);
  printf ("[4](%f) ", m.elements[4]);
  printf ("[8](%f) ", m.elements[8]);
  printf ("[12](%f) ", m.elements[12]);
  printf ("\n");
  printf ("[1](%f) ", m.elements[1]);
  printf ("[5](%f) ", m.elements[5]);
  printf ("[9](%f) ", m.elements[9]);
  printf ("[13](%f) ", m.elements[13]);
  printf ("\n");
  printf ("[2](%f) ", m.elements[2]);
  printf ("[6](%f) ", m.elements[6]);
  printf ("[10](%f) ", m.elements[10]);
  printf ("[14](%f) ", m.elements[14]);
  printf ("\n");
  printf ("[3](%f) ", m.elements[3]);
  printf ("[7](%f) ", m.elements[7]);
  printf ("[11](%f) ", m.elements[11]);
  printf ("[15](%f) ", m.elements[15]);
  printf ("\n--------------------------------\n");
}

//QUATERNION START

static inline Vector3 Quaternion_Imaginary(Quaternion q) {
	return (Vector3) { .x=q.x, .y=q.y, .z=q.z };
}

static inline Quaternion Quaternion_Identity(void) {
	return (Quaternion){ .x = 0.0f, .y = 0.0f, .z = 0.0f, .w=1.0f };
}

/*
The negative of a Quaternion:
(-a, -b, -c, -d)
*/
static inline Quaternion Quaternion_Negate(Quaternion q) {
	q.x = -q.x;
	q.y = -q.y;
	q.z = -q.z;
	q.w = -q.w;
	return q;
}

/*
The conjugate of a Quaternion:
(-x, -y, -z, w)
*/
static inline Quaternion Quaternion_Conj(Quaternion q) {
	Quaternion ret;
	ret.w = q.w;
	ret.x = -q.x;
	ret.y = -q.y;
	ret.z = -q.z;
	return ret;
}

/*
Addition of a real number   r   and a Quaternion   q:
r + q = q + r = (a+r, b, c, d)
*/
static inline Quaternion Quaternion_AddReal(Quaternion Quaternion, float real) {
	Quaternion.w += real;
	return Quaternion;
}

/*
Addition of two Quaternion:
q1 + q2 = (a1+a2, b1+b2, c1+c2, d1+d2)
*/
static inline Quaternion Quaternion_Add(Quaternion q1, Quaternion q2) {
	q1.x += q2.x;
	q1.y += q2.y;
	q1.z += q2.z;
	q1.w += q2.w;
	return q1;
}

/*
Multiplication of a real number and a Quaternion:
qr = rq = (ar, br, cr, dr)
*/
static inline Quaternion Quaternion_Scale(Quaternion q, float scalar) {
	q.x *= scalar;
	q.y *= scalar;
	q.z *= scalar;
	q.w *= scalar;
	return q;
}

/*
Multiplication of two Quaternion   q1   and   q2   is given by:
q1q2 ≠ q2q1
*/
static inline Quaternion Quaternion_Multiply(Quaternion q1, Quaternion q2) {
	Quaternion ret;
	ret.x =   q1.x * q2.w + q1.y * q2.z - q1.z * q2.y + q1.w * q2.x;
	ret.y =  -q1.x * q2.z + q1.y * q2.w + q1.z * q2.x + q1.w * q2.y;
	ret.z =   q1.x * q2.y - q1.y * q2.x + q1.z * q2.w + q1.w * q2.z;
	ret.w =  -q1.x * q2.x - q1.y * q2.y - q1.z * q2.z + q1.w * q2.w;
	return ret;
}

/*Dot product of two Quaternion*/
static inline float Quaternion_Dot(Quaternion a, Quaternion b) {
	return (a.w + a.x + a.y + a.z) *
	(b.w + b.x + b.y + b.z);
}

/*
Returns 1 if q1 is equal to q2.
Returns 0 if q1 is not equal to q2.
*/
static inline int Quaternion_Equal(Quaternion q1, Quaternion q2) {
	return 
		q1.w == q2.w &&
		q1.x == q2.x &&
		q1.y == q2.y &&
		q1.z == q2.z;
}

/*
Prints the given Quaternionto standard out.
*/
static inline void Quaternion_Print(Quaternion q, const char* label) {
	printf("\t%12f, %12f, %12f, %12f\t%s\n", 
			q.x, q.y, q.z, q.w, label);
}

/*
Returns the squared magnitude of a given Quaternion
*/
static inline float Quaternion_SquareMagnitude(Quaternion q) {
	return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
}

/*
Returns the magnitude of a given Quaternion.
*/
static inline float Quaternion_Magnitude(Quaternion q) {
	return sqrt(Quaternion_SquareMagnitude(q));
}

static inline Matrix4x4 Quaternion_ToMatrix4x4(Quaternion q) {
	Matrix4x4 ret;
	ret = Matrix4x4_identity();
	double sqw = q.w*q.w;
	double sqx = q.x*q.x;
	double sqy = q.y*q.y;
	double sqz = q.z*q.z;

	// invs (inverse square length) is only required if Quaternion is not already normalised
	double invs = 1 / (sqx + sqy + sqz + sqw);
	// since sqw + sqx + sqy + sqz =1/invs*invs
	ret.elements[0] = ( sqx - sqy - sqz + sqw)*invs; //0.133333 
	ret.elements[5] = (-sqx + sqy - sqz + sqw)*invs; //0.333333
	ret.elements[10] = (-sqx - sqy + sqz + sqw)*invs; //0.666667

	double tmp1 = q.x*q.y;
	double tmp2 = q.z*q.w;
	ret.elements[1] = 2.0 * (tmp1 + tmp2)*invs;//0.933333
	ret.elements[4] = 2.0 * (tmp1 - tmp2)*invs;//-0.666667

	tmp1 = q.x*q.z;
	tmp2 = q.y*q.w;
	ret.elements[2] = 2.0 * (tmp1 - tmp2)*invs; //-0.333333
	ret.elements[8] = 2.0 * (tmp1 + tmp2)*invs; //0.733333
	tmp1 = q.y*q.z;
	tmp2 = q.x*q.w;
	ret.elements[6] = 2.0 * (tmp1 + tmp2)*invs; //0.666667
	ret.elements[9] = 2.0 * (tmp1 - tmp2)*invs; //0.133333   
	return ret;
}

/*
Returns the Quaternion t% from qa to qb
*/
static inline Quaternion Quaternion_Slerp(Quaternion qa, Quaternion qb, double t) {
	Quaternion ret = Quaternion_Identity();
	// Calculate angle between them.
	double cosHalfTheta = qa.w * qb.w + qa.x * qb.x + qa.y * qb.y + qa.z * qb.z;
	// if qa=qb or qa=-qb then theta = 0 and we can return qa
	if (fabs(cosHalfTheta) >= 1.0){
		ret.w = qa.w;ret.x = qa.x;ret.y = qa.y;ret.z = qa.z;
		return ret;
	}
	double halfTheta = acos(cosHalfTheta);
	double sinHalfTheta = sqrt(1.0 - cosHalfTheta*cosHalfTheta);
	// if theta = 180 degrees then result is not fully defined
	// we could rotate around any axis normal to qa or qb
	if (fabs(sinHalfTheta) < 0.001){ // fabs is floating point absolute
		ret.w = (qa.w * 0.5 + qb.w * 0.5);
		ret.x = (qa.x * 0.5 + qb.x * 0.5);
		ret.y = (qa.y * 0.5 + qb.y * 0.5);
		ret.z = (qa.z * 0.5 + qb.z * 0.5);
		return ret;
	}
	double ratioA = sin((1 - t) * halfTheta) / sinHalfTheta;
	double ratioB = sin(t * halfTheta) / sinHalfTheta; 
	//calculate Quaternion.
	ret.w = (qa.w * ratioA + qb.w * ratioB);
	ret.x = (qa.x * ratioA + qb.x * ratioB);
	ret.y = (qa.y * ratioA + qb.y * ratioB);
	ret.z = (qa.z * ratioA + qb.z * ratioB);
	return ret;
}

/*
Returns the given euler angles converted to a Quaternion.
*/
static inline Quaternion Quaternion_FromEuler(Vector3 eulerAngles) {
	Quaternion q;
	float c1, s1, c2, s2, c3, s3, c1c2, s1s2;

	c1 = (float)cos(eulerAngles.y/2.0f);
	s1 = (float)sin(eulerAngles.y/2.0f);
	c2 = (float)cos(eulerAngles.x/2.0f);
	s2 = (float)sin(eulerAngles.x/2.0f);
	c3 = (float)cos(eulerAngles.z/2.0f);
	s3 = (float)sin(eulerAngles.z/2.0f);

	c1c2 = c1 * c2;
	s1s2 = s1 * s2;
	
	q.w = c1c2 * c3 - s1s2 * s3;
	q.x = c1c2 * s3 + s1s2 * c3;
	q.y = s1   * c2 * c3   + c1 * s2 * s3;
	q.z = c1   * s2 * c3   - s1 * c2 * s3;

	return q;
}

/*
Returns the given Quaternion converted to euler angles.
*/
static inline Vector3 Quaternion_ToEuler(Quaternion q) {
	float test, sqx, sqy, sqz;
	Vector3 ret;

	test = q.x*q.y + q.z*q.w;
	sqx = q.x*q.x;
	sqy = q.y*q.y;
	sqz = q.z*q.z;

	if (test > 0.499f) { /* singularity at north pole */
		ret.y = 2 * (float)atan2(q.x,q.w);
		ret.x = PI*0.5;
		ret.z = 0;
		return ret;
	}

	if (test < -0.499) { /* singularity at south pole */
		ret.y = -2 * atan2(q.x,q.w);
		ret.x = - PI*0.5;
		ret.z = 0;
		return ret;
	}

	sqx = q.x*q.x;
	sqy = q.y*q.y;
	sqz = q.z*q.z;
	ret.y = atan2(2*q.y*q.w-2*q.x*q.z , 1 - 2*sqy - 2*sqz);
	ret.x = asin(2*test);
	ret.z = atan2(2*q.x*q.w-2*q.y*q.z , 1 - 2*sqx - 2*sqz);
	return ret;
}

/*
Returns a Quaternion representing the given rotation by 'angle' around 'axis'.
*/
static inline Quaternion Quaternion_AngleAxis(float angle, Vector3 axis) {
	Quaternion ret;
	float s = (float)sin(angle / 2.0);
	ret.x = axis.x * s;
	ret.y = axis.y * s;
	ret.z = axis.z * s;
	ret.w = (float)cos(angle / 2.0);
	return ret;
}

static inline Quaternion Quaternion_Set(float x, float y, float z, float w) {
	Quaternion q;
	q.x = x;
	q.y = y;
	q.z = z;
	q.w = w;
	return q;
}
