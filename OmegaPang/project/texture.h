#pragma once

#include "litegfx.h"

struct Texture
{
    const char *name = nullptr;
    ltex_t *texture = nullptr;
    unsigned char *alphaMap = nullptr;
    int width = 0;
    int height = 0;

    Texture(const char *name = nullptr, ltex_t *texture = nullptr, unsigned char *alphaMap = nullptr, int width = 0,
            int height = 0)
        : name(name), texture(texture), alphaMap(alphaMap), width(width), height(height){};
};
