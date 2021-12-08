#define LITE_GFX_IMPLEMENTATION

#include "oval.h"
#include "drawer.h"
#include "litegfx.h"

Oval::Oval(float x, float y, float w, float h, Color color) : x(x), y(y), width(w), heigth(h), color(color)
{
    Drawer::Get().Subscribe(this);
}

Oval::~Oval()
{
    Drawer::Get().UnSubscribe(this);
}

Vec2 Oval::GetPos()
{
    return Vec2(x, y);
}

void Oval::SetPos(const Vec2 &pos)
{
    x = pos.x;
    y = pos.y;
}

void Oval::Draw() const
{
    lgfx_setcolor(color.r, color.g, color.b, color.a);
    lgfx_drawoval(x - width / 2.f, y - heigth / 2.f, width, heigth);
}
