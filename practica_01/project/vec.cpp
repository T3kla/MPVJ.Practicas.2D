#include "vec.h"
#include "pi.h"

// ----------------------------------------------------------------------- vec2

static Vec2 sUp(0.f, -1.f);
static Vec2 sDown(0.f, -1.f);
static Vec2 sRight(1.f, 0.f);
static Vec2 sLeft(-1.f, 0.f);
static Vec2 sZero(0.f, 0.f);
static Vec2 sOne(1.f, 1.f);

Vec2::Vec2(const float &x, const float &y) : x(x), y(y) {}

Vec2::Vec2(Vec2 &_rhs) {
  x = _rhs.x;
  y = _rhs.y;
}

Vec2::Vec2(const Vec2 &_rhs) {
  x = _rhs.x;
  y = _rhs.y;
}

Vec2::Vec2(Vec2 &&_rhs) noexcept {
  x = _rhs.x;
  y = _rhs.y;
}

float Vec2::Magnitude() const { return sqrt(x * x + y * y); }

Vec2 Vec2::Normalized() const { return *this / this->Magnitude(); }

float Vec2::AngleDeg() const {
  auto result = ToDeg(Vec2::Angle(*this, sRight));
  result += result < 0. ? 360. : 0.;
  return (float)result;
}

float Vec2::AngleRad() const { return Vec2::Angle(*this, sRight); }

float Vec2::Determinant(const Vec2 &a, const Vec2 &b) {
  return a.x * b.y - a.y * b.x;
}

float Vec2::Dot(const Vec2 &a, const Vec2 &b) { return a.x * b.x + a.y * b.y; }

Vec2 Vec2::Hadamard(const Vec2 &a, const Vec2 &b) {
  return Vec2(a.x * b.x, a.y * b.y);
}

float Vec2::Angle(const Vec2 &a, const Vec2 &b) {
  return std::atan2f(b.y, b.x) - std::atan2f(a.y, a.x);
}

float Vec2::Distance(const Vec2 &a, const Vec2 &b) {
  return (b - a).Magnitude();
}

Vec2 Vec2::RotateAround(const float &angle, const Vec2 &a, const Vec2 &axis) {
  float rad = (float)ToRad(-angle);
  float x = cos(rad) * (a.x - axis.x) - sin(rad) * (a.y - axis.y) + axis.x;
  float y = sin(rad) * (a.x - axis.x) + cos(rad) * (a.y - axis.y) + axis.y;
  return Vec2(x, y);
}

const Vec2 &Vec2::Up() { return sUp; }
const Vec2 &Vec2::Down() { return sDown; }
const Vec2 &Vec2::Right() { return sRight; }
const Vec2 &Vec2::Left() { return sLeft; }
const Vec2 &Vec2::Zero() { return sZero; }
const Vec2 &Vec2::One() { return sOne; }

Vec2 Vec2::operator+(const Vec2 &_rhs) const {
  return Vec2(this->x + _rhs.x, this->y + _rhs.y);
}

Vec2 Vec2::operator-(const Vec2 &_rhs) const {
  return Vec2(this->x - _rhs.x, this->y - _rhs.y);
}

Vec2 Vec2::operator*(const float &_rhs) const {
  return Vec2(this->x * _rhs, this->y * _rhs);
}

float Vec2::operator*(const Vec2 &_rhs) const { return Dot(*this, _rhs); }

Vec2 Vec2::operator/(const float &_rhs) const {
  return Vec2(this->x / _rhs, this->y / _rhs);
}

Vec2 &Vec2::operator=(const Vec2 &_rhs) {
  this->x = _rhs.x;
  this->y = _rhs.y;
  return *this;
}

Vec2 &Vec2::operator+=(const Vec2 &_rhs) {
  this->x += _rhs.x;
  this->y += _rhs.y;
  return *this;
}

Vec2 &Vec2::operator-=(const Vec2 &_rhs) {
  this->x -= _rhs.x;
  this->y -= _rhs.y;
  return *this;
}

Vec2 &Vec2::operator*=(const float &_rhs) {
  this->x *= _rhs;
  this->y *= _rhs;
  return *this;
}

Vec2 &Vec2::operator/=(const float &_rhs) {
  this->x /= _rhs;
  this->y /= _rhs;
  return *this;
}

bool Vec2::operator==(const Vec2 &_rhs) const {
  return (this->x == _rhs.x) && (this->y == _rhs.y);
}

bool Vec2::operator!=(const Vec2 &_rhs) const {
  return (this->x != _rhs.x) || (this->y != _rhs.y);
}

// ----------------------------------------------------------------------- vec3

// vec3::vec3(const float &x, const float &y, const float &z) : x(x), y(y), z(z)
//{
// }
// float vec3::magnitude() const
//{
//     return sqrt(x * x + y * y + z * z);
// }
// vec3 vec3::normalized() const
//{
//     return *this / this->magnitude();
// }
// vec3 vec3::operator+(const vec3 &_rhs) const
//{
//     return vec3(this->x + _rhs.x, this->y + _rhs.y, this->z + _rhs.z);
// }
// vec3 vec3::operator-(const vec3 &_rhs) const
//{
//     return vec3(this->x - _rhs.x, this->y - _rhs.y, this->z - _rhs.z);
// }
// vec3 vec3::operator*(const float &_rhs) const
//{
//     return vec3(this->x * _rhs, this->y * _rhs, this->z * _rhs);
// }
// vec3 vec3::operator/(const float &_rhs) const
//{
//     return vec3(this->x / _rhs, this->y / _rhs, this->z / _rhs);
// }
// bool vec3::operator==(const vec3 &_rhs) const
//{
//     return (this->x == _rhs.x) && (this->y == _rhs.y) && (this->z == _rhs.z);
// }
// bool vec3::operator!=(const vec3 &_rhs) const
//{
//     return (this->x != _rhs.x) || (this->y != _rhs.y) || (this->z != _rhs.z);
// }
//
// vec2i::vec2i(const int &x, const int &y) : x(x), y(y)
//{
// }
// float vec2i::magnitude() const
//{
//     return sqrtf((float)(x * x) + (float)(y * y));
// }
// vec2 vec2i::normalized() const
//{
//     return *this / this->magnitude();
// }
// vec2i vec2i::operator+(const vec2i &_rhs) const
//{
//     return vec2i(this->x + _rhs.x, this->y + _rhs.y);
// }
// vec2i vec2i::operator-(const vec2i &_rhs) const
//{
//     return vec2i(this->x - _rhs.x, this->y - _rhs.y);
// }
// vec2i vec2i::operator*(const int &_rhs) const
//{
//     return vec2i(this->x * _rhs, this->y * _rhs);
// }
// vec2 vec2i::operator/(const int &_rhs) const
//{
//     return vec2(roundf((float)(this->x / _rhs)), roundf((float)(this->y /
//     _rhs)));
// }
// vec2 vec2i::operator*(const float &_rhs) const
//{
//     return vec2(round(this->x * _rhs), round(this->y * _rhs));
// }
// vec2 vec2i::operator/(const float &_rhs) const
//{
//     return vec2(round(this->x / _rhs), round(this->y / _rhs));
// }
// bool vec2i::operator==(const vec2i &_rhs) const
//{
//     return (this->x == _rhs.x) && (this->y == _rhs.y);
// }
// bool vec2i::operator!=(const vec2i &_rhs) const
//{
//     return (this->x != _rhs.x) || (this->y != _rhs.y);
// }
//
// vec3i::vec3i(const int &x, const int &y, const int &z) : x(x), y(y), z(z)
//{
// }
// float vec3i::magnitude() const
//{
//     return sqrtf((float)(x * x) + (float)(y * y) + (float)(z * z));
// }
// vec3 vec3i::normalized() const
//{
//     return *this / this->magnitude();
// }
// vec3i vec3i::operator+(const vec3i &_rhs) const
//{
//     return vec3i(this->x + _rhs.x, this->y + _rhs.y, this->z + _rhs.z);
// }
// vec3i vec3i::operator-(const vec3i &_rhs) const
//{
//     return vec3i(this->x - _rhs.x, this->y - _rhs.y, this->z - _rhs.z);
// }
// vec3i vec3i::operator*(const int &_rhs) const
//{
//     return vec3i(this->x * _rhs, this->y * _rhs, this->z * _rhs);
// }
// vec3 vec3i::operator/(const int &_rhs) const
//{
//     return vec3(roundf((float)(this->x / _rhs)), roundf((float)(this->y /
//     _rhs)), roundf((float)(this->z / _rhs)));
// }
// vec3 vec3i::operator*(const float &_rhs) const
//{
//     return vec3(roundf(this->x * _rhs), roundf(this->y * _rhs),
//     roundf(this->z * _rhs));
// }
// vec3 vec3i::operator/(const float &_rhs) const
//{
//     return vec3(roundf(this->x / _rhs), roundf(this->y / _rhs),
//     roundf(this->z / _rhs));
// }
// bool vec3i::operator==(const vec3i &_rhs) const
//{
//     return (this->x == _rhs.x) && (this->y == _rhs.y) && (this->z == _rhs.z);
// }
// bool vec3i::operator!=(const vec3i &_rhs) const
//{
//     return (this->x != _rhs.x) || (this->y != _rhs.y) || (this->z != _rhs.z);
// }
