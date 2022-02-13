#pragma once

#include "font.h"

#include <string>

struct TextBox
{
    bool enable = true;

    std::string text = "default";
    Font *font = nullptr;
};
