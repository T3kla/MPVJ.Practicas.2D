#include "vector2d.h"

vec2 operator+(const vec2 &v1, const vec2 &v2) {
  return vec2(v1.x + v2.x, v1.y + v2.y);
}

vec2 operator-(const vec2 &v1, const vec2 &v2) {
  return vec2(v1.x - v2.x, v1.y - v2.y);
}

vec2 operator*(const vec2 &v1, const vec2 &v2) {
  return vec2(v1.x * v2.x, v1.y * v2.y);
}

vec2 operator/(const vec2 &v1, const vec2 &v2) {
  return vec2(v1.x / v2.x, v1.y / v2.y);
}

vec2 operator*(const vec2 &v, float s) { return vec2(s * v.x, s * v.y); }

vec2 operator/(const vec2 &v, float s) {
  float a = 1.0f / s;
  return vec2(v.x * a, v.y * a);
}

bool operator==(const vec2 &v1, const vec2 &v2) {
  return v1.x == v2.x && v1.y == v2.y;
}

bool operator!=(const vec2 &v1, const vec2 &v2) {
  return v1.x != v2.x || v1.y != v2.y;
}

float vdot(const vec2 &v1, const vec2 &v2) { return v1.x * v2.x + v1.y * v2.y; }

float vlen(const vec2 &v) {
  double dValueX = static_cast<double>(v.x);
  double dValueY = static_cast<double>(v.y);
  return static_cast<float>(sqrt((dValueX * dValueX) + (dValueY * dValueY)));
}

float vlen2(const vec2 &v) { return v.x * v.x + v.y * v.y; }

vec2 vnorm(const vec2 &v) {
  float M = vlen(v);
  return (M == 0.0) ? v : v * (1.0f / M);
}

// Angle between [0,PI].
double vang(const vec2 &v1, const vec2 &v2) {
  vec2 v1Norm = vnorm(v1);
  vec2 v2Norm = vnorm(v2);
  float dot = vdot(v1Norm, v2Norm);
  dot = dot > 1.0f ? 1.0f : dot;
  dot = dot < -1.0f ? -1.0f : dot;
  return acos(dot);
}
