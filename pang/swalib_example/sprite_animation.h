#pragma once

#include <vector>

#include "sprite.h"

struct SpriteAnimation {
  std::vector<Sprite> *animation = nullptr;

  int frame = 0;
  float speed = 0.f;

  float duration = 0.f;
  float count = 0.f;

  bool enable = true;
};
