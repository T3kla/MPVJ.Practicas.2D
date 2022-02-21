#pragma once

#include "litegfx.h"
#include "stb_truetype.h"

struct Font
{
    const char *name = nullptr;
    ltex_t *texture = nullptr;
    stbtt_bakedchar *bake = nullptr;

    Font(const char *name = nullptr, ltex_t *texture = nullptr, stbtt_bakedchar *bake = nullptr)
        : name(name), texture(texture), bake(bake){};
};
