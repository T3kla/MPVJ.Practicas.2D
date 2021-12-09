#pragma once

#include "color.h"
#include "drawable.h"
#include "vec.h"

class Oval : public Drawable {
private:
  Vec2 pos = {0.f, 0.f};
  Vec2 size = {0.f, 0.f};
  Color color = {1.f, 1.f, 1.f, 1.f};

public:
  Oval(const Vec2 &pos = {0.f, 0.f}, const Vec2 &size = {0.f, 0.f},
       const Color &color = {1.f, 1.f, 1.f, 1.f});
  ~Oval();

  Vec2 GetPos();
  void SetPos(const Vec2 &pos);

  Vec2 GetSize();
  void SetSize(const Vec2 &size);

  virtual void Draw() const override;
};
