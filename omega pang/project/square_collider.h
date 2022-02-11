#pragma once

#include "vec.h"

struct SquareCollider
{
    bool enable = true;

    Vec2 center = {0.0f, 0.0f};
    Vec2 size = {1.0f, 1.0f};
};
