#pragma once

#include "scene.h"
#include "system.h"

class SysPhysics ;
class SysMapPlayer;

class SceneAudio1 : public Scene, public System
{
  public:
    void LoadScene() override;
    void UnloadScene() override;

    void Update() override{};
    void Fixed() override;
    void Quit() override{};

  private:
    SysPhysics *sysPhysics = nullptr;
};
