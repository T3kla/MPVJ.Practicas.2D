#pragma once

#include "gameobject.h"
#include "sprite.h"
#include "stb_image.h"
#include <vector>

class P02 : public GameObject {
private:
  float defSize = 400.f;
  stbi_uc *pixels = nullptr;
  ltex_t *texture = nullptr;

  Sprite *torch = nullptr;
  Sprite *light = nullptr;
  std::vector<Sprite *> wall;
  std::vector<Sprite *> fence;

public:
  P02();
  ~P02();

  virtual void Start() override;
  virtual void Update() override;
  virtual void Fixed() override;
  virtual void End() override;
};
