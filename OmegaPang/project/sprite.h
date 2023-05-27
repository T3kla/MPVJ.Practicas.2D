#pragma once

#include "texture.h"
#include "vec.h"

struct Sprite
{
    Texture *texture = nullptr;
    Vec2 uv0 = {0.f, 0.f};
    Vec2 uv1 = {1.f, 1.f};

    Sprite(Texture *texture = nullptr, Vec2 uv0 = {0.f, 0.f}, Vec2 uv1 = {1.f, 1.f})
        : texture(texture), uv0(std::move(uv0)), uv1(std::move(uv1)){}
};
