#ifndef BB_TOOL_H_

#include <math.h>

// macros
#ifndef bb_Assert
#define bb_Assert(Expression) if (!(Expression)) *(int *)0 = 0;
#endif

#ifndef bb_ArrayCount
#define bb_ArrayCount(Array) (sizeof(Array) / sizeof(Array[0]))
#endif

#define bb_Kilobytes(Value) (Value * 1024LL)
#define bb_Megabytes(Value) (bb_Kilobytes(Value) * 1024LL)
#define bb_Gigabytes(Value) (bb_Megabytes(Value) * 1024LL)
#define bb_Terabytes(Value) (bb_Gigabytes(Value) * 1024LL)

// c string functions
int bb_StringCompare(const char *A, const char *B);
int bb_StringCompareLength(const char *A, const char *B, unsigned int Length);
char *bb_StringCopy(char *Destination, const char *Source);
int bb_StringLength(const char *String);

// memory operations
void bb_ZeroMemory(void *Buffer, unsigned int Size);
void bb_CopyMemory(void *Source, void *Destination, int Size);

// math lib
#ifndef M_PI
#define M_PI 3.14159265358979323846264f
#endif

struct bb_vec2 {
  union {
    struct { float X, Y; };
    struct { float U, V; };
    struct { float S, T; };
  };

  bb_vec2(float X = 0.0f, float Y = 0.0f) : X(X), Y(Y) {}

  bb_vec2 operator+(const bb_vec2& Value) const { return bb_vec2(X + Value.X, Y + Value.Y); }
  bb_vec2 operator-(const bb_vec2& Value) const { return bb_vec2(X - Value.X, Y - Value.Y); }
  bb_vec2 operator*(const bb_vec2& Value) const { return bb_vec2(X * Value.X, Y * Value.Y); }
  bb_vec2 operator/(const bb_vec2& Value) const { return bb_vec2(X / Value.X, Y / Value.Y); }
  bb_vec2 operator*(float Value) const { return bb_vec2(X * Value, Y * Value); }
  bb_vec2& operator+=(const bb_vec2& Value) { X += Value.X; Y += Value.Y; return *this; }
  bb_vec2& operator-=(const bb_vec2& Value) { X -= Value.X; Y -= Value.Y; return *this; }
  bb_vec2& operator*=(const bb_vec2& Value) { X *= Value.X; Y *= Value.Y; return *this; }
  bb_vec2& operator/=(const bb_vec2& Value) { X /= Value.X; Y /= Value.Y; return *this; }
  bool operator==(const bb_vec2& Value) const { return (X == Value.X && Y == Value.Y); }
  bool operator!=(const bb_vec2& Value) const { return !(*this == Value); }
};

struct bb_vec3 {
  union {
    struct { float X, Y, Z; };
    struct { float R, G, B; };
  };

  bb_vec3(float X = 0.0f, float Y = 0.0f, float Z = 0.0f) : X(X), Y(Y), Z(Z) { }

  bb_vec3 operator+(const bb_vec3& Value) const { return bb_vec3(X + Value.X, Y + Value.Y, Z + Value.Z); }
  bb_vec3 operator-(const bb_vec3& Value) const { return bb_vec3(X - Value.X, Y - Value.Y, Z - Value.Z); }
  bb_vec3 operator*(const bb_vec3& Value) const { return bb_vec3(X * Value.X, Y * Value.Y, Z * Value.Z); }
  bb_vec3 operator/(const bb_vec3& Value) const { return bb_vec3(X / Value.X, Y / Value.Y, Z / Value.Z); }
  bb_vec3 operator*(float Value) const { return bb_vec3(X * Value, Y * Value, Z * Value); }
  bb_vec3& operator+=(const bb_vec3& Value) { X += Value.X; Y += Value.Y; Z += Value.Z; return *this; }
  bb_vec3& operator-=(const bb_vec3& Value) { X -= Value.X; Y -= Value.Y; Z -= Value.Z; return *this; }
  bb_vec3& operator*=(const bb_vec3& Value) { X *= Value.X; Y *= Value.Y; Z *= Value.Z; return *this; }
  bb_vec3& operator/=(const bb_vec3& Value) { X /= Value.X; Y /= Value.Y; Z /= Value.Z; return *this; }
  bool operator==(const bb_vec3& Value) const { return (X == Value.X && Y == Value.Y && Z == Value.Z); }
  bool operator!=(const bb_vec3& Value) const { return !(*this == Value); }
};

struct bb_quaternion {
  union {
    struct { float X, Y, Z, W; };
  };

  bb_quaternion(float X = 0.0f, float Y = 0.0f, float Z = 0.0f, float W = 1.0f) : X(X), Y(Y), Z(Z), W(W) { }

  bb_quaternion operator*(const bb_quaternion& Value) const {
    return bb_quaternion(
      (X * Value.W) + (W * Value.X) + (Y * Value.Z) - (Z * Value.Y),
      (Y * Value.W) + (W * Value.Y) + (Z * Value.X) - (X * Value.Z),
      (Z * Value.W) + (W * Value.Z) + (X * Value.Y) - (Y * Value.X),
      (W * Value.W) - (X * Value.X) - (Y * Value.Y) - (Z * Value.Z)
    );
  }

  bb_quaternion operator*(const bb_vec3& Value) const {
    return bb_quaternion(
      (W * Value.X) + (Y * Value.Z) - (Z * Value.Y),
      (W * Value.Y) + (Z * Value.X) - (X * Value.Z),
      (W * Value.Z) + (X * Value.Y) - (Y * Value.X),
     -(X * Value.X) - (Y * Value.Y) - (Z * Value.Z)
    );
  }
};

struct bb_mat4 {
  float Values[4][4];

  bb_mat4(float Diagonal = 1.0f) {
    for (int I = 0; I < 4; ++I) {
      for (int J = 0; J < 4; ++J) {
        if (I == J) {
          Values[I][J] = 1.0f;
        } else {
          Values[I][J] = 0.0f;
        }
      }
    }
  }

  bb_mat4 operator*(const bb_mat4& Value) const {
    bb_mat4 Result;
    for (int I = 0; I < 4; I++) {
      for (int J = 0; J < 4; J++) {
        Result[I][J] = 
          Values[I][0] * Value[0][J] +
          Values[I][1] * Value[1][J] +
          Values[I][2] * Value[2][J] +
          Values[I][3] * Value[3][J];
      }
    }

    return Result;
  }

  const float *operator[](int Index) const { return Values[Index]; }
  float *operator[](int Index) { return Values[Index]; }
};

float bb_Clamp(float Value, float Min, float Max);
float bb_Max(float A, float B);
float bb_Min(float A, float B);
float bb_ToRadians(float Degrees);
float bb_ToDegrees(float Radians);

float bb_Dot(bb_vec2 A, bb_vec2 B);
float bb_Length(bb_vec2 Value);

float bb_Dot(bb_vec3 A, bb_vec3 B);
float bb_Length(bb_vec3 Value);
bb_vec3 bb_Normalized(bb_vec3 Value);
bb_vec3 bb_Cross(bb_vec3 A, bb_vec3 B);
bb_vec3 bb_Rotate(bb_vec3 V, bb_quaternion Q);

bb_quaternion bb_InitQuaternion(float Angle, bb_vec3 Axis);
bb_quaternion bb_EulerAnglesToQuaternion(float X, float Y, float Z);
float bb_Length(bb_quaternion Value);
bb_quaternion bb_Normalized(bb_quaternion Value);
bb_quaternion bb_Conjugate(bb_quaternion Value);
bb_vec3 bb_Forward(bb_quaternion Value);
bb_vec3 bb_Back(bb_quaternion Value);
bb_vec3 bb_Up(bb_quaternion Value);
bb_vec3 bb_Down(bb_quaternion Value);
bb_vec3 bb_Right(bb_quaternion Value);
bb_vec3 bb_Left(bb_quaternion Value);

bb_mat4 bb_Orthographic(float Left, float Right, float Bottom, float Top, float NearZ, float FarZ);
bb_mat4 bb_Perspective(float Fov, float Aspect, float NearZ, float FarZ);
bb_mat4 bb_Translate(float X, float Y, float Z);
bb_mat4 bb_Translate(bb_vec3 Value);
bb_mat4 bb_Scale(bb_vec3 Value);
bb_mat4 bb_Scale(float X, float Y, float Z);
bb_mat4 bb_Rotate(bb_vec3 N, bb_vec3 V, bb_vec3 U);
bb_mat4 bb_Rotate(bb_quaternion Quaternion);

// ----------------------------------------------------------------------------
// -----------------------------IMPLEMENTATION---------------------------------
// ----------------------------------------------------------------------------
#ifdef BB_TOOL_IMPLEMENTATION

// c string functions
int
bb_StringCompare(const char *A, const char *B) {
  while (*A && (*A++ == *B++));
  return *A - *B;
}

int
bb_StringCompareLength(const char *A, const char *B, unsigned int Length) {
  while (Length--)
    if (*A++ != *B++)
      return *(unsigned char *)(A - 1) - *(unsigned char *)(B - 1);
  return 0;
}

char *
bb_StringCopy(char *Destination, const char *Source) {
  char *Result = Destination;
  while (*Destination++ = *Source++);
  return Destination;
}

int
bb_StringLength(const char *String) {
  char *Begin = (char *)String;
  while (*(++String));
  return (int)(String - Begin);
}

// memory operations
void
bb_ZeroMemory(void *Buffer, unsigned int Size) {
  char *Pointer = (char *)Buffer;
  while (Size--)
    *(Pointer++) = 0;
}

void
bb_CopyMemory(void *Source, void *Destination, int Size) {
  char *S = (char *)Source;
  char *D = (char *)Destination;
  while (Size--)
    *D++ = *S++;
}

// math
float
bb_Clamp(float Value, float Min, float Max) {
  if (Value > Max) {
    return Max;
  } else if (Value < Min) {
    return Min;
  }
  return Value;
}

float
bb_Max(float A, float B) {
  return A > B ? A : B;
}

float
bb_Min(float A, float B) {
  return A > B ? B : A;
}

float
bb_ToRadians(float Degrees) {
  return Degrees * (M_PI / 180.0f);
}

float
bb_ToDegrees(float Radians) {
  return Radians * (180.0f / M_PI);
}


float
bb_Dot(bb_vec2 A, bb_vec2 B) {
  return A.X * B.X + A.Y * B.Y;
}

float
bb_Length(bb_vec2 Value) {
  return sqrtf(bb_Dot(Value, Value));
}


float
bb_Dot(bb_vec3 A, bb_vec3 B) {
  return A.X * B.X + A.Y * B.Y + A.Z * B.Z;
}

float
bb_Length(bb_vec3 Value) {
  return bb_Dot(Value, Value);
}

bb_vec3
bb_Normalized(bb_vec3 Value) {
  float Length = bb_Length(Value);
  return Value / Length;
}

bb_vec3
bb_Cross(bb_vec3 A, bb_vec3 B) {
  return bb_vec3(
    A.Y * B.Z - A.Z * B.Y,
    A.Z * B.X - A.X * B.Z,
    A.X * B.Y - A.Y * B.X
  );
}

bb_vec3
bb_Rotate(bb_vec3 V, bb_quaternion Q) {
  bb_quaternion Conjugate = bb_Conjugate(Q);
  bb_quaternion Result = Q * V * Conjugate;
  return bb_vec3(Result.X, Result.Y, Result.Z);
}


bb_quaternion
bb_InitQuaternion(float Angle, bb_vec3 Axis) {
  float SinHalfAngle = sinf(bb_ToRadians(Angle) / 2.0f);
  float CosHalfAngle = cosf(bb_ToRadians(Angle) / 2.0f);
  return bb_quaternion(Axis.X * SinHalfAngle, Axis.Y * SinHalfAngle, Axis.Z * SinHalfAngle, CosHalfAngle);
}

bb_quaternion
bb_EulerAnglesToQuaternion(float X, float Y, float Z) {
  bb_quaternion Result = bb_InitQuaternion(X, bb_vec3(1, 0, 0)) * 
                         bb_InitQuaternion(Y, bb_vec3(0, 1, 0)) * 
                         bb_InitQuaternion(Z, bb_vec3(0, 0, 1));
  return Result;
}

float
bb_Length(bb_quaternion Value) {
  return sqrtf(Value.X * Value.X + Value.Y * Value.Y + Value.Z * Value.Z + Value.W * Value.W);
}

bb_quaternion
bb_Normalized(bb_quaternion Value) {
  float Length = bb_Length(Value);
  return bb_quaternion(Value.X / Length, Value.Y / Length, Value.Z / Length, Value.W / Length);
}

bb_quaternion
bb_Conjugate(bb_quaternion Value) {
  return bb_quaternion(-Value.X, -Value.Y, -Value.Z, Value.W);
}

bb_vec3
bb_Forward(bb_quaternion Value) {
  return bb_Rotate(bb_vec3(0, 0, 1), Value);
}

bb_vec3
bb_Back(bb_quaternion Value) {
  return bb_Rotate(bb_vec3(0, 0, -1), Value);
}

bb_vec3
bb_Up(bb_quaternion Value) {
  return bb_Rotate(bb_vec3(0, 1, 0), Value);
}

bb_vec3
bb_Down(bb_quaternion Value) {
  return bb_Rotate(bb_vec3(0, -1, 0), Value);
}

bb_vec3
bb_Right(bb_quaternion Value) {
  return bb_Rotate(bb_vec3(1, 0, 0), Value);
}

bb_vec3
bb_Left(bb_quaternion Value) {
  return bb_Rotate(bb_vec3(-1, 0, 0), Value);
}

bb_mat4
bb_Orthographic(float Left, float Right, float Bottom, float Top, float NearZ, float FarZ) {
  bb_mat4 Result(1.0f);
  Result[0][0] = 2.0f / (Right - Left);
  Result[1][1] = 2.0f / (Top - Bottom);
  Result[2][2] = 2.0f / (FarZ - NearZ);

  Result[0][3] = -(Right + Left) / (Right - Left);
  Result[1][3] = -(Top + Bottom) / (Top - Bottom);
  Result[2][3] = -(FarZ + NearZ) / (FarZ - NearZ);
  
  return Result;
}

bb_mat4
bb_Perspective(float Fov, float Aspect, float NearZ, float FarZ) {
  bb_mat4 Result(1.0f);
  float Range = NearZ - FarZ;
  float TanHalfFov = tanf(Fov / 2.0f);
  
  Result[0][0] = 1.0f / (TanHalfFov * Aspect);
  Result[1][1] = 1.0f / TanHalfFov;
  Result[2][2] = (-NearZ - FarZ) / Range;
  Result[2][3] = 2.0f * FarZ * NearZ / Range;
  Result[3][3] = 0.0f;
  Result[3][2] = 1.0f;

  return Result;
}

bb_mat4
bb_Translate(float X, float Y, float Z) {
  bb_mat4 Result(1.0f);
  Result[0][3] = X;
  Result[1][3] = Y;
  Result[2][3] = Z;
  return Result;
}

bb_mat4
bb_Translate(bb_vec3 Value) {
  return bb_Translate(Value.X, Value.Y, Value.Z);
}

bb_mat4
bb_Scale(float X, float Y, float Z) {
  bb_mat4 Result(1.0f);
  Result[0][0] = X;
  Result[1][1] = Y;
  Result[2][2] = Z;
  return Result;
}

bb_mat4
bb_Scale(bb_vec3 Value) {
  return bb_Scale(Value.X, Value.Y, Value.Z);
}

bb_mat4
bb_Rotate(bb_vec3 N, bb_vec3 V, bb_vec3 U) {
  bb_mat4 Result(1.0f);

  Result[0][0] = U.X;
  Result[1][0] = V.X;
  Result[2][0] = N.X;
  
  Result[0][1] = U.Y;
  Result[1][1] = V.Y;
  Result[2][1] = N.Y;
  
  Result[0][2] = U.Z;
  Result[1][2] = V.Z;
  Result[2][2] = N.Z;
  return Result;
}

bb_mat4
bb_Rotate(bb_quaternion Quaternion) {
  bb_vec3 Forward = bb_vec3(2.0f * (Quaternion.X * Quaternion.Z - Quaternion.W * Quaternion.Y), 2.0f * (Quaternion.Y * Quaternion.Z + Quaternion.W * Quaternion.X), 1.0f - 2.0f * (Quaternion.X * Quaternion.X + Quaternion.Y * Quaternion.Y));
  bb_vec3 Up      = bb_vec3(2.0f * (Quaternion.X * Quaternion.Y + Quaternion.W * Quaternion.Z), 1.0f - 2.0f * (Quaternion.X * Quaternion.X + Quaternion.Z * Quaternion.Z), 2.0f * (Quaternion.Y * Quaternion.Z - Quaternion.W * Quaternion.X));
  bb_vec3 Right   = bb_vec3(1.0f - 2.0f * (Quaternion.Y * Quaternion.Y + Quaternion.Z * Quaternion.Z), 2.0f * (Quaternion.X * Quaternion.Y - Quaternion.W * Quaternion.Z), 2.0f * (Quaternion.X * Quaternion.Z + Quaternion.W * Quaternion.Y));
  return bb_Rotate(Forward, Up, Right);
}

#endif

#define BB_TOOL_H_
#endif