#pragma once

#include "scene.h"
#include "system.h"

class SceneBee : public Scene, public System
{
  public:
    virtual void LoadScene() override;
    virtual void UnloadScene() override;

    virtual void Update() override{};
    virtual void Fixed() override;
    virtual void Quit() override{};

  private:
    class SysBee *sysBee = nullptr;
};
