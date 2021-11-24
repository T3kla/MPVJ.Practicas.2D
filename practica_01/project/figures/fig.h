#pragma once

#include "../draw/drawable.h"

namespace figure
{

class fig : public drawable
{
  protected:
    float m_x = 0.f;
    float m_y = 0.f;

  public:
    virtual void draw() override = 0;
};

} // namespace figure
