#pragma once

#include "color.h"
#include "drawable.h"
#include "vec.h"

class Oval : public Drawable
{
  private:
    float x = 0.f;
    float y = 0.f;
    float width = 0.f;
    float heigth = 0.f;
    Color color = Color(1.f, 1.f, 1.f, 1.f);

  public:
    Oval(float x, float y, float w, float h, Color color);
    ~Oval();

    Vec2 GetPos();
    void SetPos(const Vec2 &pos);

    virtual void Draw() const override;
};
