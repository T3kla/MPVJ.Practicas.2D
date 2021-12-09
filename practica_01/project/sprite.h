#pragma once

#include "drawable.h"
#include "litegfx.h"
#include "vec.h"

class Sprite : public Drawable {
private:
  void *texture = nullptr;
  Vec2 pos = {0.f, 0.f};
  Vec2 size = {64.f, 64.f};
  Vec2 uv0 = {0.f, 0.f};
  Vec2 uv1 = {1.f, 1.f};
  Vec2 pivot = {0.5f, 0.5f};
  float angle = 0.f;
  lblend_t blend = BLEND_ADD;

public:
  Sprite(void *texture = nullptr, const Vec2 &pos = {0.f, 0.f},
         const Vec2 &size = {64.f, 64.f}, const Vec2 &uv0 = {0.f, 0.f},
         const Vec2 &uv1 = {1.f, 1.f}, const lblend_t &blend = BLEND_ADD,
         const Vec2 &pivot = {0.5f, 0.5f}, const float &angle = 0.f);
  ~Sprite();

  Vec2 GetPos();
  void SetPos(const Vec2 &pos);

  Vec2 GetSize();
  void SetSize(const Vec2 &size);

  void GetUVs(Vec2 &uv0, Vec2 &uv1);
  void SetUVs(const Vec2 &uv0, const Vec2 &uv1);

  Vec2 GetPivot();
  void SetPivot(const Vec2 &pivot);

  float GetAngle();
  void SetAngle(const float &angle);

  lblend_t GetBlendMode();
  void SetBlendMode(const lblend_t &blendMode);

  virtual void Draw() const override;
};
