#pragma once

#include "color.h"
#include "litegfx.h"
#include "vec.h"

struct Sprite;

struct SpriteRenderer
{
    bool enable = true;

    bool reverse = false;

    Sprite *sprite = nullptr;
    Color color = {1.f, 1.f, 1.f, 1.f};

    Vec2 offsetPosition = {0.f, 0.f};
    float offsetRotation = 0.f;

    Vec2 size = {100.f, 100.f};
    Vec2 pivot = {0.5f, 0.5f};
    int layer = 0;

    lblend_t blend = BLEND_ALPHA;
};
