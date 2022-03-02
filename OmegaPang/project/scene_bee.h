#pragma once

#include "scene.h"

class SceneBee : public Scene
{
  public:
    virtual void LoadScene() override;
    virtual void UnloadScene() override;

  private:
    class SysBee *sysBee = nullptr;
};
