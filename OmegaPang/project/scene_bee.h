#pragma once

#include "scene.h"

class SysBee;

class SceneBee : public Scene
{
  public:
    using Scene::Scene;

    virtual void LoadScene() override;
    virtual void UnloadScene() override;

  private:
    SysBee *sysBee = nullptr;
};
