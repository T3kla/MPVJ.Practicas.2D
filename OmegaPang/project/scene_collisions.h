#pragma once

#include "scene.h"
#include "system.h"

class SysPhysics;

class SceneCollisions : public Scene, public System
{
  public:
    void LoadScene() override;
    void UnloadScene() override;

    void Update() override{};
    void Fixed() override;
    void Quit() override{};

  private:
    // Systems
	SysPhysics *sysPhysics = nullptr;
};
