#pragma once

#include "scene.h"

class SceneFonts : public Scene
{
  public:
    using Scene::Scene;

    virtual void LoadScene() override;
    virtual void UnloadScene() override;
};
