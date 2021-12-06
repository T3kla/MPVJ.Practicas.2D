#define LITE_GFX_IMPLEMENTATION

#include "rect.h"
#include "drawer.h"
#include "litegfx.h"

Rect::Rect(float x, float y, float w, float h, Color color) : x(x), y(y), width(w), heigth(h), color(color)
{
    Drawer::Get().Subscribe(this);
}

Rect::~Rect()
{
    Drawer::Get().UnSubscribe(this);
}

Vec2 Rect::GetPos()
{
    return Vec2(x, y);
}

void Rect::SetPos(const Vec2 &pos)
{
    x = pos.x;
    y = pos.y;
}

void Rect::Draw() const
{
    lgfx_setcolor(color.r, color.g, color.b, color.a);
    lgfx_drawrect(x - width / 2.f, y - heigth / 2.f, width, heigth);
}
