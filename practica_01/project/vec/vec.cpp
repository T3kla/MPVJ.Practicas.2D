#include "vec.h"

vec2::vec2(const float &x, const float &y) : x(x), y(y)
{
}
vec2::vec2(vec2 &b)
{
    x = b.x;
    y = b.y;
}
vec2::vec2(vec2 &&b) noexcept
{
    x = b.x;
    y = b.y;
}
float vec2::magnitude() const
{
    return sqrt(x * x + y * y);
}
vec2 vec2::normalized() const
{
    return *this / this->magnitude();
}
float vec2::det(const vec2 &b) const
{
    return this->x * b.y - this->y * b.x;
}
float vec2::dot(const vec2 &b) const
{
    return this->x * b.x + this->y * b.y;
}
float vec2::angle(const vec2 &b) const
{
    return std::atan2f(det(b), dot(b));
}
float vec2::distance(const vec2 &b) const
{
    return (b - *this).magnitude();
}
vec2 vec2::operator+(const vec2 &b) const
{
    return vec2(this->x + b.x, this->y + b.y);
}
void vec2::operator+=(const vec2 &b)
{
    this->x += b.x;
    this->y += b.y;
}
vec2 vec2::operator-(const vec2 &b) const
{
    return vec2(this->x - b.x, this->y - b.y);
}
void vec2::operator-=(const vec2 &b)
{
    this->x *= b.x;
    this->y *= b.y;
}
vec2 vec2::operator*(const float &b) const // scale product
{
    return vec2(this->x * b, this->y * b);
}
vec2 vec2::operator*(const vec2 &b) const // hadamard product
{
    return vec2(this->x * b.x, this->y * b.y);
}
vec2 vec2::operator/(const float &b) const
{
    return vec2(this->x / b, this->y / b);
}
bool vec2::operator==(const vec2 &b) const
{
    return (this->x == b.x) && (this->y == b.y);
}
bool vec2::operator!=(const vec2 &b) const
{
    return (this->x != b.x) || (this->y != b.y);
}

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
vec3 vec3::operator+(const vec3 &b) const
{
    return vec3(this->x + b.x, this->y + b.y, this->z + b.z);
}
vec3 vec3::operator-(const vec3 &b) const
{
    return vec3(this->x - b.x, this->y - b.y, this->z - b.z);
}
vec3 vec3::operator*(const float &b) const
{
    return vec3(this->x * b, this->y * b, this->z * b);
}
vec3 vec3::operator/(const float &b) const
{
    return vec3(this->x / b, this->y / b, this->z / b);
}
bool vec3::operator==(const vec3 &b) const
{
    return (this->x == b.x) && (this->y == b.y) && (this->z == b.z);
}
bool vec3::operator!=(const vec3 &b) const
{
    return (this->x != b.x) || (this->y != b.y) || (this->z != b.z);
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
vec2i vec2i::operator+(const vec2i &b) const
{
    return vec2i(this->x + b.x, this->y + b.y);
}
vec2i vec2i::operator-(const vec2i &b) const
{
    return vec2i(this->x - b.x, this->y - b.y);
}
vec2i vec2i::operator*(const int &b) const
{
    return vec2i(this->x * b, this->y * b);
}
vec2 vec2i::operator/(const int &b) const
{
    return vec2(roundf((float)(this->x / b)), roundf((float)(this->y / b)));
}
vec2 vec2i::operator*(const float &b) const
{
    return vec2(round(this->x * b), round(this->y * b));
}
vec2 vec2i::operator/(const float &b) const
{
    return vec2(round(this->x / b), round(this->y / b));
}
bool vec2i::operator==(const vec2i &b) const
{
    return (this->x == b.x) && (this->y == b.y);
}
bool vec2i::operator!=(const vec2i &b) const
{
    return (this->x != b.x) || (this->y != b.y);
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
vec3i vec3i::operator+(const vec3i &b) const
{
    return vec3i(this->x + b.x, this->y + b.y, this->z + b.z);
}
vec3i vec3i::operator-(const vec3i &b) const
{
    return vec3i(this->x - b.x, this->y - b.y, this->z - b.z);
}
vec3i vec3i::operator*(const int &b) const
{
    return vec3i(this->x * b, this->y * b, this->z * b);
}
vec3 vec3i::operator/(const int &b) const
{
    return vec3(roundf((float)(this->x / b)), roundf((float)(this->y / b)), roundf((float)(this->z / b)));
}
vec3 vec3i::operator*(const float &b) const
{
    return vec3(roundf(this->x * b), roundf(this->y * b), roundf(this->z * b));
}
vec3 vec3i::operator/(const float &b) const
{
    return vec3(roundf(this->x / b), roundf(this->y / b), roundf(this->z / b));
}
bool vec3i::operator==(const vec3i &b) const
{
    return (this->x == b.x) && (this->y == b.y) && (this->z == b.z);
}
bool vec3i::operator!=(const vec3i &b) const
{
    return (this->x != b.x) || (this->y != b.y) || (this->z != b.z);
}
