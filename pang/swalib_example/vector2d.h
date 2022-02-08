
#ifndef _VECTOR3D_H
#define _VECTOR3D_H

#include <math.h>

class vec2 {
public:
  float x;
  float y;

  vec2(void) : x(0), y(0) {}

  vec2(float f) { x = y = f; }

  vec2(float _x, float _y) {
    x = _x;
    y = _y;
  }

  vec2(const float f[2]) {
    x = f[0];
    y = f[1];
  }

  const float &operator[](int i) const { return (&x)[i]; }

  float &operator[](int i) { return (&x)[i]; }

  vec2 &operator+=(const vec2 &v) {
    x += v.x;
    y += v.y;
    return *this;
  }

  vec2 &operator-=(const vec2 &v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  vec2 &operator*=(const vec2 &v) {
    x *= v.x;
    y *= v.y;
    return *this;
  }

  vec2 &operator/=(const vec2 &v) {
    x /= v.x;
    y /= v.y;
    return *this;
  }

  vec2 &operator*=(float s) {
    x *= s;
    y *= s;
    return *this;
  }

  vec2 &operator/=(float s) {
    float a = 1.0f / s;
    x *= a;
    y *= a;
    return *this;
  }
};

vec2 operator+(const vec2 &v1, const vec2 &v2);

vec2 operator-(const vec2 &v1, const vec2 &v2);

vec2 operator*(const vec2 &v1, const vec2 &v2);

vec2 operator/(const vec2 &v1, const vec2 &v2);

vec2 operator*(const vec2 &v, float s);

vec2 operator/(const vec2 &v, float s);

bool operator==(const vec2 &v1, const vec2 &v2);

bool operator!=(const vec2 &v1, const vec2 &v2);

float vdot(const vec2 &v1, const vec2 &v2);

float vlen(const vec2 &v);

float vlen2(const vec2 &v);

vec2 vnorm(const vec2 &v);

// Angle between [0,PI].
double vang(const vec2 &v1, const vec2 &v2);

#endif
