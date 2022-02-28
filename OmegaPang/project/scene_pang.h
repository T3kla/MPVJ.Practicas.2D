#pragma once

#include "scene.h"

class SysPlayer;
class SysPhysics;
class SysHook;
class SysBalls;
class SysExplosions;

class ScenePang : public Scene
{
  public:
    using Scene::Scene;

    virtual void LoadScene() override;
    virtual void UnloadScene() override;

  private:
    SysPlayer *sysPlayer = nullptr;
    SysPhysics *sysPhysics = nullptr;
    SysHook *sysHook = nullptr;
    SysBalls *sysBalls = nullptr;
    SysExplosions *sysExplosions = nullptr;
};
