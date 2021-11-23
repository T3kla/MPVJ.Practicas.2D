#include "vec.h"

// ----------------------------------------------------------------------- vec2

vec2::vec2(const float &x, const float &y) : x(x), y(y)
{
}
vec2::vec2(vec2 &_rhs)
{
    x = _rhs.x;
    y = _rhs.y;
}
vec2::vec2(vec2 &&_rhs) noexcept
{
    x = _rhs.x;
    y = _rhs.y;
}
float vec2::magnitude() const
{
    return sqrt(x * x + y * y);
}
vec2 vec2::normalized() const
{
    return *this / this->magnitude();
}
float vec2::det(const vec2 &a, const vec2 &b)
{
    return a.x * b.y - a.y * b.x;
}
float vec2::dot(const vec2 &a, const vec2 &b)
{
    return a.x * b.x + a.y * b.y;
}
vec2 vec2::had(const vec2 &a, const vec2 &b)
{
    return vec2(a.x * b.x, a.y * b.y);
}
float vec2::ang(const vec2 &a, const vec2 &b)
{
    return std::atan2f(det(a, b), dot(a, b));
}
float vec2::dis(const vec2 &a, const vec2 &b)
{
    return (b - a).magnitude();
}
vec2 vec2::operator+(const vec2 &_rhs) const
{
    return vec2(this->x + _rhs.x, this->y + _rhs.y);
}
vec2 vec2::operator-(const vec2 &_rhs) const
{
    return vec2(this->x - _rhs.x, this->y - _rhs.y);
}
vec2 vec2::operator*(const float &_rhs) const // scale product
{
    return vec2(this->x * _rhs, this->y * _rhs);
}
float vec2::operator*(const vec2 &_rhs) const // hadamard product
{
    return dot(*this, _rhs);
}
vec2 vec2::operator/(const float &_rhs) const
{
    return vec2(this->x / _rhs, this->y / _rhs);
}
vec2 &vec2::operator+=(const vec2 &_rhs)
{
    this->x += _rhs.x;
    this->y += _rhs.y;
    return *this;
}
vec2 &vec2::operator-=(const vec2 &_rhs)
{
    this->x -= _rhs.x;
    this->y -= _rhs.y;
    return *this;
}
vec2 &vec2::operator*=(const float &_rhs)
{
    this->x *= _rhs;
    this->y *= _rhs;
    return *this;
}
vec2 &vec2::operator/=(const float &_rhs)
{
    this->x /= _rhs;
    this->y /= _rhs;
    return *this;
}
bool vec2::operator==(const vec2 &_rhs) const
{
    return (this->x == _rhs.x) && (this->y == _rhs.y);
}
bool vec2::operator!=(const vec2 &_rhs) const
{
    return (this->x != _rhs.x) || (this->y != _rhs.y);
}

// ----------------------------------------------------------------------- vec3

vec3::vec3(const float &x, const float &y, const float &z) : x(x), y(y), z(z)
{
}
float vec3::magnitude() const
{
    return sqrt(x * x + y * y + z * z);
}
vec3 vec3::normalized() const
{
    return *this / this->magnitude();
}
vec3 vec3::operator+(const vec3 &_rhs) const
{
    return vec3(this->x + _rhs.x, this->y + _rhs.y, this->z + _rhs.z);
}
vec3 vec3::operator-(const vec3 &_rhs) const
{
    return vec3(this->x - _rhs.x, this->y - _rhs.y, this->z - _rhs.z);
}
vec3 vec3::operator*(const float &_rhs) const
{
    return vec3(this->x * _rhs, this->y * _rhs, this->z * _rhs);
}
vec3 vec3::operator/(const float &_rhs) const
{
    return vec3(this->x / _rhs, this->y / _rhs, this->z / _rhs);
}
bool vec3::operator==(const vec3 &_rhs) const
{
    return (this->x == _rhs.x) && (this->y == _rhs.y) && (this->z == _rhs.z);
}
bool vec3::operator!=(const vec3 &_rhs) const
{
    return (this->x != _rhs.x) || (this->y != _rhs.y) || (this->z != _rhs.z);
}

vec2i::vec2i(const int &x, const int &y) : x(x), y(y)
{
}
float vec2i::magnitude() const
{
    return sqrtf((float)(x * x) + (float)(y * y));
}
vec2 vec2i::normalized() const
{
    return *this / this->magnitude();
}
vec2i vec2i::operator+(const vec2i &_rhs) const
{
    return vec2i(this->x + _rhs.x, this->y + _rhs.y);
}
vec2i vec2i::operator-(const vec2i &_rhs) const
{
    return vec2i(this->x - _rhs.x, this->y - _rhs.y);
}
vec2i vec2i::operator*(const int &_rhs) const
{
    return vec2i(this->x * _rhs, this->y * _rhs);
}
vec2 vec2i::operator/(const int &_rhs) const
{
    return vec2(roundf((float)(this->x / _rhs)), roundf((float)(this->y / _rhs)));
}
vec2 vec2i::operator*(const float &_rhs) const
{
    return vec2(round(this->x * _rhs), round(this->y * _rhs));
}
vec2 vec2i::operator/(const float &_rhs) const
{
    return vec2(round(this->x / _rhs), round(this->y / _rhs));
}
bool vec2i::operator==(const vec2i &_rhs) const
{
    return (this->x == _rhs.x) && (this->y == _rhs.y);
}
bool vec2i::operator!=(const vec2i &_rhs) const
{
    return (this->x != _rhs.x) || (this->y != _rhs.y);
}

vec3i::vec3i(const int &x, const int &y, const int &z) : x(x), y(y), z(z)
{
}
float vec3i::magnitude() const
{
    return sqrtf((float)(x * x) + (float)(y * y) + (float)(z * z));
}
vec3 vec3i::normalized() const
{
    return *this / this->magnitude();
}
vec3i vec3i::operator+(const vec3i &_rhs) const
{
    return vec3i(this->x + _rhs.x, this->y + _rhs.y, this->z + _rhs.z);
}
vec3i vec3i::operator-(const vec3i &_rhs) const
{
    return vec3i(this->x - _rhs.x, this->y - _rhs.y, this->z - _rhs.z);
}
vec3i vec3i::operator*(const int &_rhs) const
{
    return vec3i(this->x * _rhs, this->y * _rhs, this->z * _rhs);
}
vec3 vec3i::operator/(const int &_rhs) const
{
    return vec3(roundf((float)(this->x / _rhs)), roundf((float)(this->y / _rhs)), roundf((float)(this->z / _rhs)));
}
vec3 vec3i::operator*(const float &_rhs) const
{
    return vec3(roundf(this->x * _rhs), roundf(this->y * _rhs), roundf(this->z * _rhs));
}
vec3 vec3i::operator/(const float &_rhs) const
{
    return vec3(roundf(this->x / _rhs), roundf(this->y / _rhs), roundf(this->z / _rhs));
}
bool vec3i::operator==(const vec3i &_rhs) const
{
    return (this->x == _rhs.x) && (this->y == _rhs.y) && (this->z == _rhs.z);
}
bool vec3i::operator!=(const vec3i &_rhs) const
{
    return (this->x != _rhs.x) || (this->y != _rhs.y) || (this->z != _rhs.z);
}
