#pragma once

#include "vec.h"

struct Transform
{
    Vec2 position = {0.f, 0.f};
    Vec2 scale = {1.f, 1.f};
    float rotation = 0.f;
};

struct RectTransform
{
    Vec2 position = {0.f, 0.f};
    Vec2 size = {100.f, 100.f};

    Vec2 anchor0 = {0.f, 0.f};
    Vec2 anchor1 = {0.f, 0.f};

    Vec2 pivot = {0.5f, 0.5f};

    Vec2 scale = {1.f, 1.f};
    float rotation = 0.f;
};
