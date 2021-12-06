#pragma once

#include "gameobject.h"
#include "rect.h"

class P01 : public GameObject
{
  private:
    Rect rect1{0.f, 0.f, 100.f, 100.f, Color(1.f, 0.f, 0.f, 1.f)};
    Rect rect2{0.f, 0.f, 100.f, 100.f, Color(1.f, 0.f, 0.f, 1.f)};
    Rect rect3{0.f, 0.f, 100.f, 100.f, Color(0.f, 0.f, 1.f, 1.f)};

  public:
    P01();
    ~P01();

    virtual void Start() override;
    virtual void Update(const double &dt) override;
    virtual void Fixed(const double &dt) override;
    virtual void End() override;
};
