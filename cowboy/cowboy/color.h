#pragma once

struct Color {
  float r = 1.f, g = 1.f, b = 1.f, a = 1.f;

  Color(float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f)
      : r(r), g(g), b(b), a(a) {}
  ~Color(){};
};
