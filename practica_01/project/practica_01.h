#pragma once

#include "gameobject.h"
#include "oval.h"
#include "rect.h"

class P01 : public GameObject
{
  private:
    Rect rect1{100.f, 200.f, 100.f, 100.f, Color(1.f, 0.f, 0.f, 1.f)};
    Rect rect2{100.f, 100.f, 50.f, 50.f, Color(0.f, 1.f, 0.f, 1.f)};
    Oval oval1{100.f, 300.f, 25.f, 25.f, Color(0.f, 0.f, 1.f, 1.f)};

  public:
    P01();
    ~P01();

    virtual void Start() override;
    virtual void Update() override;
    virtual void Fixed() override;
    virtual void End() override;
};
