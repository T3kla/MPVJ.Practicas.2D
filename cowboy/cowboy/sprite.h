#pragma once

#include "vec.h"

struct Sprite {
  void *texture = nullptr;
  Vec2 uv0 = {0.f, 0.f};
  Vec2 uv1 = {1.f, 1.f};

  Sprite(){};
  Sprite(void *texture, const Vec2 &uv0, const Vec2 &uv1)
      : texture(texture), uv0(uv0), uv1(uv1) {}
};
