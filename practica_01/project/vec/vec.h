#pragma once

#include <iostream>

struct vec2
{
    float x = 0;
    float y = 0;
    vec2(const float &x = 0, const float &y = 0);
    vec2(vec2 &b);
    vec2(vec2 &&b) noexcept;
    float magnitude() const;
    vec2 normalized() const;
    float det(const vec2 &b) const;
    float dot(const vec2 &b) const;
    float angle(const vec2 &b) const;
    float distance(const vec2 &b) const;
    vec2 operator+(const vec2 &b) const;
    void operator+=(const vec2 &b);
    vec2 operator-(const vec2 &b) const;
    void operator-=(const vec2 &b);
    vec2 operator*(const float &b) const; // scale product
    vec2 operator*(const vec2 &b) const;  // hadamard product
    vec2 operator/(const float &b) const;
    bool operator==(const vec2 &b) const;
    bool operator!=(const vec2 &b) const;
    friend std::ostream &operator<<(std::ostream &os, const vec2 &b)
    {
        return os << '(' << b.x << ',' << b.y << ')';
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
    vec3 operator+(const vec3 &b) const;
    vec3 operator-(const vec3 &b) const;
    vec3 operator*(const float &b) const;
    vec3 operator/(const float &b) const;
    bool operator==(const vec3 &b) const;
    bool operator!=(const vec3 &b) const;
    friend std::ostream &operator<<(std::ostream &os, const vec3 &b)
    {
        return os << '(' << b.x << ',' << b.y << ',' << b.z << ')';
    }
};

struct vec2i
{
    int x = 0;
    int y = 0;
    vec2i(const int &x = 0, const int &y = 0);
    float magnitude() const;
    vec2 normalized() const;
    vec2i operator+(const vec2i &b) const;
    vec2i operator-(const vec2i &b) const;
    vec2i operator*(const int &b) const;
    vec2 operator/(const int &b) const;
    vec2 operator*(const float &b) const;
    vec2 operator/(const float &b) const;
    bool operator==(const vec2i &b) const;
    bool operator!=(const vec2i &b) const;
    friend std::ostream &operator<<(std::ostream &os, const vec2i &b)
    {
        return os << '(' << b.x << ',' << b.y << ')';
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
    vec3i operator+(const vec3i &b) const;
    vec3i operator-(const vec3i &b) const;
    vec3i operator*(const int &b) const;
    vec3 operator/(const int &b) const;
    vec3 operator*(const float &b) const;
    vec3 operator/(const float &b) const;
    bool operator==(const vec3i &b) const;
    bool operator!=(const vec3i &b) const;
    friend std::ostream &operator<<(std::ostream &os, const vec3i &b)
    {
        return os << '(' << b.x << ',' << b.y << ',' << b.z << ')';
    }
};
