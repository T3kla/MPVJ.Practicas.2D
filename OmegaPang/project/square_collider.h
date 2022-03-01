#pragma once

#include "collider.h"
#include "vec.h"

struct SquareCollider : public Collider
{
    Vec2 center = {0.0f, 0.0f};
    Vec2 size = {1.0f, 1.0f};
};
