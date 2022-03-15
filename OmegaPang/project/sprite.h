#pragma once

#include "litegfx.h"
#include "texture.h"
#include "vec.h"

struct Sprite
{
    Texture *texture = nullptr;
    Vec2 uv0 = {0.f, 0.f};
    Vec2 uv1 = {1.f, 1.f};

    Sprite(Texture *texture = nullptr, Vec2 uv0 = {0.f, 0.f}, Vec2 uv1 = {1.f, 1.f})
        : texture(texture), uv0(uv0), uv1(uv1){};
};
