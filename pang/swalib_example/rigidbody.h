#pragma once

#include "vec.h"

struct RigidBody {
  Vec2 velocity = {0.f, 0.f};
  float linearDrag = 0.1f;
};
