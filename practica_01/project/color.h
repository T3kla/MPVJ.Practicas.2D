#pragma once

class Color {
public:
  float r = 0.f;
  float g = 0.f;
  float b = 0.f;
  float a = 0.f;

  Color(float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f)
      : r(r), g(g), b(b), a(a) {}
};
