#pragma once

#include "scene.h"

class ScenePang : public Scene
{
  public:
    using Scene::Scene;

    virtual void LoadScene() override;
    virtual void UnloadScene() override;

  private:
    class SysPlayer *sysPlayer = nullptr;
    class SysPhysics *sysPhysics = nullptr;
    class SysHook *sysHook = nullptr;
    class SysBalls *sysBalls = nullptr;
    class SysExplosions *sysExplosions = nullptr;
};
