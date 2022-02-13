#pragma once

#include "color.h"
#include "font.h"

#include <string>

struct TextBox
{
    bool enable = true;

    std::string text = "default";
    Font *font = nullptr;
    float weight = 11.f;
    Color color = {1.f, 1.f, 1.f, 1.f};

    int layer = 0;
    lblend_t blend = BLEND_ALPHA;
};
