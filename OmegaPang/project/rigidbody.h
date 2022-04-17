#pragma once

#include "vec.h"

struct RigidBody
{
    bool enable = true;

    Vec2 velocity = {0.f, 0.f};
    float linearDrag = 0.1f;

    bool gravity = false;
    float gravityScale = 1.f;
};
