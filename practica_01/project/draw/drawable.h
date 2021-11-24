#pragma once

#include "color.h"

class drawable
{
  public:
    color m_color = color(1.f, 0.f, 0.f, 1.f);
    virtual void draw() = 0;
};
