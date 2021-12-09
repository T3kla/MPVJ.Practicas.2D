#pragma once

#include "gameobject.h"
#include "oval.h"
#include "rect.h"

constexpr unsigned int TITLE_LEN = 256;

class P01 : public GameObject {
private:
  Rect rect1{{0.f, 0.f}, {75.f, 75.f}, {1.f, 0.f, 0.f, 1.f}};
  Rect rect2{{0.f, 0.f}, {75.f, 75.f}, {0.f, 1.f, 0.f, 1.f}};
  Oval oval1{{0.f, 0.f}, {50.f, 50.f}, {0.f, 0.f, 1.f, 1.f}};
  Oval oval2{{0.f, 0.f}, {25.f, 25.f}, {0.f, 0.5f, 1.f, 1.f}};

  char title[TITLE_LEN] = "";
  Vec2 rot1 = {1.f, 0.f};
  float dis = 100.f;

public:
  P01();
  ~P01();

  virtual void Start() override;
  virtual void Update() override;
  virtual void Fixed() override;
  virtual void End() override;
};
