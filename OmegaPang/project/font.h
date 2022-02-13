#pragma once

#include "litegfx.h"
#include "stb_truetype.h"

struct Font
{
    ltex_t *texture = nullptr;
    stbtt_bakedchar *bake = nullptr;

    Font(ltex_t *texture = nullptr, stbtt_bakedchar *bake = nullptr) : texture(texture), bake(bake){};
};
