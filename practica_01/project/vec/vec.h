#pragma once

#include <iostream>

struct vec2
{
    float x = 0;
    float y = 0;

    vec2(const float &x = 0, const float &y = 0);
    vec2(vec2 &_rhs);
    vec2(vec2 &&_rhs) noexcept;

    float magnitude() const;
    vec2 normalized() const;

    vec2 operator+(const vec2 &_rhs) const;
    vec2 operator-(const vec2 &_rhs) const;
    vec2 operator*(const float &_rhs) const;
    float operator*(const vec2 &_rhs) const;
    vec2 operator/(const float &_rhs) const;

    vec2 &operator+=(const vec2 &_rhs);
    vec2 &operator-=(const vec2 &_rhs);
    vec2 &operator*=(const float &_rhs);
    vec2 &operator/=(const float &_rhs);

    bool operator==(const vec2 &_rhs) const;
    bool operator!=(const vec2 &_rhs) const;

    static float det(const vec2 &a, const vec2 &b); // determinant
    static float dot(const vec2 &a, const vec2 &b); // dot product
    static vec2 had(const vec2 &a, const vec2 &b);  // hadamard product
    static float ang(const vec2 &a, const vec2 &b); // angle between two vec2
    static float dis(const vec2 &a, const vec2 &b); // distance between two vec2

    friend std::ostream &operator<<(std::ostream &os, const vec2 &a)
    {
        return os << '(' << a.x << ',' << a.y << ')';
    }
};

struct vec3
{
    float x = 0;
    float y = 0;
    float z = 0;
    vec3(const float &x = 0, const float &y = 0, const float &z = 0);
    float magnitude() const;
    vec3 normalized() const;
    vec3 operator+(const vec3 &_rhs) const;
    vec3 operator-(const vec3 &_rhs) const;
    vec3 operator*(const float &_rhs) const;
    vec3 operator/(const float &_rhs) const;
    bool operator==(const vec3 &_rhs) const;
    bool operator!=(const vec3 &_rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const vec3 &_rhs)
    {
        return os << '(' << _rhs.x << ',' << _rhs.y << ',' << _rhs.z << ')';
    }
};

struct vec2i
{
    int x = 0;
    int y = 0;
    vec2i(const int &x = 0, const int &y = 0);
    float magnitude() const;
    vec2 normalized() const;
    vec2i operator+(const vec2i &_rhs) const;
    vec2i operator-(const vec2i &_rhs) const;
    vec2i operator*(const int &_rhs) const;
    vec2 operator/(const int &_rhs) const;
    vec2 operator*(const float &_rhs) const;
    vec2 operator/(const float &_rhs) const;
    bool operator==(const vec2i &_rhs) const;
    bool operator!=(const vec2i &_rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const vec2i &_rhs)
    {
        return os << '(' << _rhs.x << ',' << _rhs.y << ')';
    }
};

struct vec3i
{
    int x = 0;
    int y = 0;
    int z = 0;
    vec3i(const int &x = 0, const int &y = 0, const int &z = 0);
    float magnitude() const;
    vec3 normalized() const;
    vec3i operator+(const vec3i &_rhs) const;
    vec3i operator-(const vec3i &_rhs) const;
    vec3i operator*(const int &_rhs) const;
    vec3 operator/(const int &_rhs) const;
    vec3 operator*(const float &_rhs) const;
    vec3 operator/(const float &_rhs) const;
    bool operator==(const vec3i &_rhs) const;
    bool operator!=(const vec3i &_rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const vec3i &_rhs)
    {
        return os << '(' << _rhs.x << ',' << _rhs.y << ',' << _rhs.z << ')';
    }
};
