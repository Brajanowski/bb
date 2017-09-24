// simple single file math library created by Brajan Bartoszewicz
// feel free to you use it in your projects
#ifndef BB_MATH_H_
#define BB_MATH_H_

#ifndef u8
typedef unsigned char u8;
typedef char i8;

typedef unsigned short u16;
typedef short i16;

typedef unsigned int u32;
typedef int i32;

typedef float r32;
typedef double r64;
#endif

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define bb_abs(x) ((x) > 0 ? (x) : (-x))

static r32 bb_floor(r32 value) {
  if (value > 0) return (i32)value;
  return (i32)(value - 0.9999999999999999f);
}
static r32 bb_to_radians(r32 degrees) { return (r32)(degrees * (M_PI / 180.0f)); }
static r32 bb_to_degrees(r32 radians) { return (r32)(radians * (180.0f / M_PI)); }

struct bb_vec2 {
  union {
    struct { r32 x, y; };
    struct { r32 u, v; };
    struct { r32 s, t; };
  };

  bb_vec2(r32 x = 0.0f, r32 y = 0.0f) : x(x), y(y) {}

  bb_vec2 operator+(const bb_vec2& rhs) const { return{ x + rhs.x, y + rhs.y }; }
  bb_vec2 operator-(const bb_vec2& rhs) const { return{ x - rhs.x, y - rhs.y }; }
  bb_vec2 operator*(const bb_vec2& rhs) const { return{ x * rhs.x, y * rhs.y }; }
  bb_vec2 operator/(const bb_vec2& rhs) const { return{ x / rhs.x, y / rhs.y }; }
  bb_vec2 operator*(r32 scalar) const { return{ x * scalar, y * scalar }; }
  bb_vec2& operator+=(const bb_vec2& rhs) { x += rhs.x; y += rhs.y; return *this; }
  bb_vec2& operator-=(const bb_vec2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
  bb_vec2& operator*=(const bb_vec2& rhs) { x *= rhs.x; y *= rhs.y; return *this; }
  bb_vec2& operator/=(const bb_vec2& rhs) { x /= rhs.x; y /= rhs.y; return *this; }
  bool operator==(const bb_vec2& rhs) const { return (x == rhs.x && y == rhs.y); }
  bool operator!=(const bb_vec2& rhs) const { return !(*this == rhs); }
};

struct bb_vec3 {
  union {
    struct { r32 x, y, z; };
    struct { r32 r, g, b; };
  };

  bb_vec3(r32 x = 0.0f, r32 y = 0.0f, r32 z = 0.0f) : x(x), y(y), z(z) { }

  bb_vec3 operator+(const bb_vec3& rhs) const { return{ x + rhs.x, y + rhs.y, z + rhs.z }; }
  bb_vec3 operator-(const bb_vec3& rhs) const { return{ x - rhs.x, y - rhs.y, z - rhs.z }; }
  bb_vec3 operator*(const bb_vec3& rhs) const { return{ x * rhs.x, y * rhs.y, z * rhs.z }; }
  bb_vec3 operator/(const bb_vec3& rhs) const { return{ x / rhs.x, y / rhs.y, z / rhs.z }; }
  bb_vec3 operator*(r32 scalar) const { return{ x * scalar, y * scalar, z * scalar }; }
  bb_vec3& operator+=(const bb_vec3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
  bb_vec3& operator-=(const bb_vec3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
  bb_vec3& operator*=(const bb_vec3& rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this; }
  bb_vec3& operator/=(const bb_vec3& rhs) { x /= rhs.x; y /= rhs.y; z /= rhs.z; return *this; }
  bool operator==(const bb_vec3& rhs) const { return (x == rhs.x && y == rhs.y && z == rhs.z); }
  bool operator!=(const bb_vec3& rhs) const { return !(*this == rhs); }
};

struct bb_vec4 {
  union {
    struct { r32 x, y, z, w; };
    struct { r32 r, g, b, a; };
    bb_vec3 xyz;
    bb_vec3 rgb;
    bb_vec2 xy;
  };

  bb_vec4(r32 x = 0.0f, r32 y = 0.0f, r32 z = 0.0f, r32 w = 0.0f) : x(x), y(y), z(z), w(w) { }
};

struct bb_quat {
  union {
    bb_vec4 xyzw;
    struct { r32 x, y, z, w; };
  };

  bb_quat(r32 x = 0.0f, r32 y = 0.0f, r32 z = 0.0f, r32 w = 1.0f) : x(x), y(y), z(z), w(w) { }

  bb_quat(r32 angle, const bb_vec3& axis) {
    r32 sin_half_angle = sinf(bb_to_radians(angle) / 2.0f);
    r32 cos_half_angle = cosf(bb_to_radians(angle) / 2.0f);

    x = axis.x * sin_half_angle;
    y = axis.y * sin_half_angle;
    z = axis.z * sin_half_angle;
    w = cos_half_angle;
  }

  bb_quat(const bb_vec3& angles) {
    bb_quat result = bb_quat(angles.x, { 1, 0, 0 }) * bb_quat(angles.y, { 0, 1, 0 }) * bb_quat(angles.z, { 0, 0, 1 });

    x = result.x;
    y = result.y;
    z = result.z;
    w = result.w;
  }

  bb_quat operator*(const bb_quat& v) const {
    return {
            (x * v.w) + (w * v.x) + (y * v.z) - (z * v.y),
            (y * v.w) + (w * v.y) + (z * v.x) - (x * v.z),
            (z * v.w) + (w * v.z) + (x * v.y) - (y * v.x),
            (w * v.w) - (x * v.x) - (y * v.y) - (z * v.z)
           };
  }

  bb_quat operator*(const bb_vec3& v) const {
    return {
            (w * v.x) + (y * v.z) - (z * v.y),
            (w * v.y) + (z * v.x) - (x * v.z),
            (w * v.z) + (x * v.y) - (y * v.x),
            -(x * v.x) - (y * v.y) - (z * v.z)
           };
  }
};

struct bb_mat4 {
  r32 m[4][4];

  bb_mat4(r32 diagonal = 1.0f) {
    for (uint32 i = 0; i < 4; i++) {
      for (uint32 j = 0; j < 4; j++) {
        if (i == j) {
          m[i][j] = diagonal;
        } else {
          m[i][j] = 0.0f;
        }
      }
    }
  }

  bb_mat4 operator*(const bb_mat4& rhs) const {
    bb_mat4 result;
    for (uint32 i = 0; i < 4; i++) {
      for (uint32 j = 0; j < 4; j++) {
        result[i][j] = 
          m[i][0] * rhs[0][j] +
          m[i][1] * rhs[1][j] +
          m[i][2] * rhs[2][j] +
          m[i][3] * rhs[3][j];
      }
    }

    return result;
  }

  const r32* operator[](uint32 index) const { return m[index]; }
  r32* operator[](uint32 index) { return m[index]; }
};

static bb_quat bb_init_quaternion(r32 angle, const bb_vec3& axis) {
  r32 sin_half_angle = sinf(bb_to_radians(angle) / 2.0f);
  r32 cos_half_angle = cosf(bb_to_radians(angle) / 2.0f);

  return { axis.x * sin_half_angle, axis.y * sin_half_angle, axis.z * sin_half_angle, cos_half_angle };
}

static bb_quat bb_init_quaternion(const bb_vec3& angles) {
  bb_quat result = bb_quat(angles.x, { 1, 0, 0 }) * bb_quat(angles.y, { 0, 1, 0 }) * bb_quat(angles.z, { 0, 0, 1 });
  return result;
}

static r32 bb_dot(const bb_vec2& a, const bb_vec2& b) { return a.x * b.x + a.y * b.y; }
static r32 bb_length(const bb_vec2& v) { return sqrtf(bb_dot(v, v)); }
static r32 bb_dot(const bb_vec3& a, const bb_vec3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
static r32 bb_length(const bb_vec3& v) { return sqrtf(bb_dot(v, v)); }
static bb_vec3 bb_normalize(const bb_vec3& v) { r32 l = bb_length(v); return{ v.x / l, v.y / l, v.z / l }; }
static bb_vec3 bb_cross(const bb_vec3& a, const bb_vec3& b) {
  return bb_vec3(
    a.y * b.z - a.z * b.y,
    a.z * b.x - a.x * b.z,
    a.x * b.y - a.y * b.x
  );
}

static bb_quat bb_conjugate(const bb_quat& v);
static bb_vec3 bb_rotate(const bb_vec3& v, const bb_quat& q) {
  bb_quat conjugate = bb_conjugate(q);
  bb_quat w = q * v * conjugate;

  return { w.x, w.y, w.z };
}

static r32 bb_length(const bb_quat& v) { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w); }
static bb_quat bb_normalize(const bb_quat& v) { r32 l = bb_length(v); return{ v.x / l, v.y / l, v.z / l, v.w / l }; }
static bb_quat bb_conjugate(const bb_quat& v) { return{ -v.x, -v.y, -v.z, v.w }; }
static bb_vec3 bb_forward(const bb_quat& v) { return bb_rotate({0, 0, 1}, v); }
static bb_vec3 bb_back(const bb_quat& v) { return bb_rotate({ 0, 0, -1 }, v); }
static bb_vec3 bb_up(const bb_quat& v) { return bb_rotate({ 0, 1, 0 }, v); }
static bb_vec3 bb_down(const bb_quat& v) { return bb_rotate({ 0, -1, 0 }, v); }
static bb_vec3 bb_right(const bb_quat& v) { return bb_rotate({ 1, 0, 0 }, v); }
static bb_vec3 bb_left(const bb_quat& v) { return bb_rotate({ -1, 0, 0 }, v); }

static bb_mat4 bb_orthographic(r32 left, r32 right, r32 bottom, r32 top, r32 near_z, r32 far_z) {
  bb_mat4 ret(1.0f);

  ret[0][0] = 2.0f / (right - left);
  ret[1][1] = 2.0f / (top - bottom);
  ret[2][2] = 2.0f / (far_z - near_z);

  ret[0][3] = -(right + left) / (right - left);
  ret[1][3] = -(top + bottom) / (top - bottom);
  ret[2][3] = -(far_z + near_z) / (far_z - near_z);
  return ret;
}

static bb_mat4 bb_perspective(r32 fov, r32 aspect, r32 near_z, r32 far_z) {
  bb_mat4 ret(1.0f);

  r32 range = near_z - far_z;
  r32 tan_half_fov = tanf(fov / 2.0f);

  ret[0][0] = 1.0f / (tan_half_fov * aspect);
  ret[1][1] = 1.0f / tan_half_fov;
  ret[2][2] = (-near_z - far_z) / range;
  ret[2][3] = 2.0f * far_z * near_z / range;
  ret[3][3] = 0.0f;
  ret[3][2] = 1.0f;

  return ret;
}

static bb_mat4 bb_translate(const bb_vec3& v) {
  bb_mat4 mat(1.0f);
  mat[0][3] = v.x;
  mat[1][3] = v.y;
  mat[2][3] = v.z;
  return mat;
}

static bb_mat4 bb_scale(const bb_vec3& v) {
  bb_mat4 mat(1.0f);
  mat[0][0] = v.x;
  mat[1][1] = v.y;
  mat[2][2] = v.z;
  return mat;
}

static bb_mat4 bb_rotate(const bb_vec3& v) {
  bb_mat4 rx(1.0f);
  bb_mat4 ry(1.0f);
  bb_mat4 rz(1.0f);

  r32 x = bb_to_radians(v.x);
  r32 y = bb_to_radians(v.y);
  r32 z = bb_to_radians(v.z);

  rx[1][1] = cosf(x);
  rx[2][1] = sinf(x);
  rx[1][2] = -sinf(x);
  rx[2][2] = cosf(x);

  ry[0][0] = cosf(y);
  ry[2][0] = sinf(y);
  ry[0][2] = -sinf(y);
  ry[2][2] = cosf(y);

  rz[0][0] = cosf(z);
  rz[1][0] = sinf(z);
  rz[0][1] = -sinf(z);
  rz[1][1] = cosf(z);

  return rz * ry * rx;
}

static bb_mat4 bb_rotate(r32 angle, const bb_vec3& axis) {
  bb_mat4 result(1.0f);

  r32 r = bb_to_radians(angle);
  r32 c = cosf(r);
  r32 s = sinf(r);
  r32 omc = 1.0f - c;

  r32 x = axis.x;
  r32 y = axis.y;
  r32 z = axis.z;

  result[0][0] = x * omc + c;
  result[1][0] = y * x * omc + z * s;
  result[2][0] = x * z * omc - y * s;

  result[0][1] = x * y * omc - z * s;
  result[1][1] = y * omc + c;
  result[2][1] = y * z * omc + x * s;

  result[0][2] = x * z * omc + y * s;
  result[1][2] = y * z * omc - x * s;
  result[2][2] = z * omc + c;
  return result;
}

static bb_mat4 bb_rotate(const bb_vec3& n, const bb_vec3& v, const bb_vec3& u) {
  bb_mat4 result(1.0f);

  result[0][0] = u.x;
  result[1][0] = v.x;
  result[2][0] = n.x;

  result[0][1] = u.y;
  result[1][1] = v.y;
  result[2][1] = n.y;

  result[0][2] = u.z;
  result[1][2] = v.z;
  result[2][2] = n.z;
  return result;
}

static bb_mat4 bb_rotate(const bb_vec3& forward, const bb_vec3& up) {
  bb_vec3 n = bb_normalize(forward);
  bb_vec3 u = bb_cross(bb_normalize(up), n);
  bb_vec3 v = bb_cross(n, u);
  return bb_rotate(n, v, u);
}

static bb_mat4 bb_rotate(const bb_quat& q) {
  bb_vec3 forward = bb_vec3(2.0f * (q.x * q.z - q.w * q.y), 2.0f * (q.y * q.z + q.w * q.x), 1.0f - 2.0f * (q.x * q.x + q.y * q.y));
  bb_vec3 up      = bb_vec3(2.0f * (q.x * q.y + q.w * q.z), 1.0f - 2.0f * (q.x * q.x + q.z * q.z), 2.0f * (q.y * q.z - q.w * q.x));
  bb_vec3 right   = bb_vec3(1.0f - 2.0f * (q.y * q.y + q.z * q.z), 2.0f * (q.x * q.y - q.w * q.z), 2.0f * (q.x * q.z + q.w * q.y));
  return bb_rotate(forward, up, right);
}

static bb_vec3 bb_transform(const bb_mat4& m, const bb_vec3& v) {
  return bb_vec3(m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3],
                m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3],
                m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3]);
}

static r32 bb_clamp(r32 value, r32 min, r32 max) {
  if (value > max)
    return max;
  else if (value < min)
    return min;
  return value;
}

static r32 bb_max(r32 a, r32 b) {
  return a > b ? a : b;
}

static r32 bb_min(r32 a, r32 b) {
  return a > b ? b : a;
}

#endif
