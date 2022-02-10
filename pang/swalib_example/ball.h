#pragma once

#include "sizes.h"

struct Ball
{
    bool enable = true;

    float rebound = 100.f;
    Size::Size size = Size::S;
};
