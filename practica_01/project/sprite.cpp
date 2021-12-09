#include "sprite.h"
#include "drawer.h"

Sprite::Sprite(void *texture, const Vec2 &pos, const Vec2 &size,
               const Vec2 &uv0, const Vec2 &uv1, const lblend_t &blend,
               const Vec2 &pivot, const float &angle)
    : texture(texture), pos(pos), size(size), uv0(uv0), uv1(uv1), blend(blend),
      pivot(pivot), angle(angle) {
  Drawer::Get().Subscribe(this);
}

Sprite::~Sprite() { Drawer::Get().UnSubscribe(this); }

Vec2 Sprite::GetPos() { return pos; }
void Sprite::SetPos(const Vec2 &pos) { this->pos = pos; }

Vec2 Sprite::GetSize() { return size; }
void Sprite::SetSize(const Vec2 &size) { this->size = size; }

Vec2 Sprite::GetPivot() { return pivot; }
void Sprite::SetPivot(const Vec2 &pivot) { this->pivot = pivot; }

float Sprite::GetAngle() { return angle; }
void Sprite::SetAngle(const float &angle) { this->angle = angle; }

lblend_t Sprite::GetBlendMode() { return blend; }
void Sprite::SetBlendMode(const lblend_t &blendMode) { this->blend = blend; }

void Sprite::GetUVs(Vec2 &uv0, Vec2 &uv1) {
  uv0 = this->uv0;
  uv1 = this->uv1;
}

void Sprite::SetUVs(const Vec2 &uv0, const Vec2 &uv1) {
  this->uv0 = uv0;
  this->uv1 = uv1;
}

void Sprite::Draw() const {
  if (!texture)
    return;
  lgfx_setblend(blend);
  ltex_drawrotsized((ltex_t *)texture, pos.x - size.x / 2.f,
                    pos.y - size.y / 2.f, angle, pivot.x, pivot.y, size.x,
                    size.y, uv0.x, uv0.y, uv1.x, uv1.y);
}
