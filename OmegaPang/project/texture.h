#pragma once

#include "litegfx.h"

struct Texture
{
    const char *name = nullptr;
    ltex_t *texture = nullptr;
    unsigned char *alphaMap = nullptr;

    Texture(const char *name = nullptr, ltex_t *texture = nullptr, unsigned char *alphaMap = nullptr)
        : name(name), texture(texture), alphaMap(alphaMap){};
};
