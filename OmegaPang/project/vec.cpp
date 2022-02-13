#include "vec.h"
#include "pi.h"

static Vec2 f2Up(0.f, -1.f);
static Vec2 f2Down(0.f, -1.f);
static Vec2 f2Right(1.f, 0.f);
static Vec2 f2Left(-1.f, 0.f);
static Vec2 f2Zero(0.f, 0.f);
static Vec2 f2One(1.f, 1.f);

static Vec2i i2Up(0, -1);
static Vec2i i2Down(0, -1);
static Vec2i i2Right(1, 0);
static Vec2i i2Left(-1, 0);
static Vec2i i2Zero(0, 0);
static Vec2i i2One(1, 1);

// ----------------------------------------------------------------------- Vec2

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

Vec2::Vec2(Vec2i _rhs) {
  x = (float)_rhs.x;
  y = (float)_rhs.y;
}

Vec2::Vec2(const Vec2i &_rhs) {
  x = (float)_rhs.x;
  y = (float)_rhs.y;
}

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

float Vec2::Magnitude() const { return sqrt(x * x + y * y); }

float Vec2::MagnitudeSq() const { return x * x + y * y; }

Vec2 Vec2::Normalized() const { return *this / this->Magnitude(); }

float Vec2::AngleDeg() const {
  auto result = ToDeg(Vec2::Angle(*this, f2Right));
  result += result < 0. ? 360. : 0.;
  return (float)result;
}

float Vec2::AngleRad() const { return Vec2::Angle(*this, f2Right); }

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

const Vec2 &Vec2::Up() { return f2Up; }
const Vec2 &Vec2::Down() { return f2Down; }
const Vec2 &Vec2::Right() { return f2Right; }
const Vec2 &Vec2::Left() { return f2Left; }
const Vec2 &Vec2::Zero() { return f2Zero; }
const Vec2 &Vec2::One() { return f2One; }

// ----------------------------------------------------------------------- Vec2i

Vec2i::Vec2i(const int &x, const int &y) : x(x), y(y) {}

Vec2i::Vec2i(Vec2i &_rhs) {
  x = _rhs.x;
  y = _rhs.y;
}

Vec2i::Vec2i(const Vec2i &_rhs) {
  x = _rhs.x;
  y = _rhs.y;
}

Vec2i::Vec2i(Vec2i &&_rhs) noexcept {
  x = _rhs.x;
  y = _rhs.y;
}

Vec2i::Vec2i(Vec2 _rhs) {
  x = (int)_rhs.x;
  y = (int)_rhs.y;
}

Vec2i::Vec2i(const Vec2 &_rhs) {
  x = (int)_rhs.x;
  y = (int)_rhs.y;
}

Vec2i Vec2i::operator+(const Vec2i &_rhs) const {
  return Vec2i(this->x + _rhs.x, this->y + _rhs.y);
}

Vec2i Vec2i::operator-(const Vec2i &_rhs) const {
  return Vec2i(this->x - _rhs.x, this->y - _rhs.y);
}

Vec2i Vec2i::operator*(const int &_rhs) const {
  return Vec2i(this->x * _rhs, this->y * _rhs);
}

Vec2i &Vec2i::operator=(const Vec2i &_rhs) {
  this->x = _rhs.x;
  this->y = _rhs.y;
  return *this;
}

Vec2i &Vec2i::operator+=(const Vec2i &_rhs) {
  this->x += _rhs.x;
  this->y += _rhs.y;
  return *this;
}

Vec2i &Vec2i::operator-=(const Vec2i &_rhs) {
  this->x -= _rhs.x;
  this->y -= _rhs.y;
  return *this;
}

Vec2i &Vec2i::operator*=(const int&_rhs) {
  this->x *= _rhs;
  this->y *= _rhs;
  return *this;
}

bool Vec2i::operator==(const Vec2i &_rhs) const {
  return (this->x == _rhs.x) && (this->y == _rhs.y);
}

bool Vec2i::operator!=(const Vec2i &_rhs) const {
  return (this->x != _rhs.x) || (this->y != _rhs.y);
}

Vec2i Vec2i::Hadamard(const Vec2i &a, const Vec2i &b) {
  return Vec2i(a.x * b.x, a.y * b.y);
}

const Vec2i &Vec2i::Up() { return i2Up; }
const Vec2i &Vec2i::Down() { return i2Down; }
const Vec2i &Vec2i::Right() { return i2Right; }
const Vec2i &Vec2i::Left() { return i2Left; }
const Vec2i &Vec2i::Zero() { return i2Zero; }
const Vec2i &Vec2i::One() { return i2One; }
