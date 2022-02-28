#pragma once

#include "litegfx.h"

struct Texture
{
    const char *name = nullptr;
    ltex_t *texture = nullptr;

    Texture(const char *name = nullptr, ltex_t *texture = nullptr) : name(name), texture(texture){};
};
