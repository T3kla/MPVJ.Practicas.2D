#pragma once

#include "color.h"
#include "drawable.h"
#include "vec.h"

class Rect : public Drawable
{
  private:
    float x = 0.f;
    float y = 0.f;
    float width = 0.f;
    float heigth = 0.f;
    Color color = Color(1.f, 1.f, 1.f, 1.f);

  public:
    Rect(float x, float y, float w, float h, Color color);
    ~Rect();

    virtual void Draw() const override;

    vec2 GetPos();
    void SetPos(const vec2 &pos);
};
