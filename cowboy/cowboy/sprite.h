#pragma once

#include "vec.h"

struct Sprite {
  void *texture = nullptr;
  Vec2 uv0 = {0.f, 0.f};
  Vec2 uv1 = {1.f, 1.f};
};
