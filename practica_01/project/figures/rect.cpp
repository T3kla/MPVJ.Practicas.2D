#include "rect.h"
#include "litegfx.h"

#define LITE_GFX_IMPLEMENTATION

namespace figure
{

rect::rect(float x, float y, float w, float h, color color)
{
    m_x = x;
    m_y = y;
    m_w = w;
    m_h = h;
    m_color = color;
}

void rect::draw()
{
    lgfx_setcolor(m_color.m_r, m_color.m_g, m_color.m_b, m_color.m_a);
    lgfx_drawrect(m_x, m_y, m_w, m_h);
}

} // namespace figure
