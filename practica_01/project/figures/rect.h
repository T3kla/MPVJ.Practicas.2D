#pragma once

#include "fig.h"

namespace figure
{

class rect : public fig
{
  private:
    float m_w = 0.f;
    float m_h = 0.f;

    virtual void draw() override;

  public:
    rect(float x, float y, float w, float h, color color);
};

} // namespace figure
