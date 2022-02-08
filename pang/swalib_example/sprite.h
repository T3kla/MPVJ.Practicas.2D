#pragma once

#include "vec.h"

struct Sprite {
  unsigned int texture = 0;
  Vec2 uv0 = {0.f, 0.f};
  Vec2 uv1 = {1.f, 1.f};

  Sprite(unsigned int texture = 0, Vec2 uv0 = {0.f, 0.f}, Vec2 uv1 = {1.f, 1.f})
      : texture(texture), uv0(uv0), uv1(uv1) {}
};
