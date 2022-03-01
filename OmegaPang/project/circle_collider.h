#pragma once

#include "collider.h"
#include "vec.h"

struct CircleCollider : public Collider
{
    Vec2 center = {0.0f, 0.0f};
    float radius = 0.f;
};
