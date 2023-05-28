#pragma once

#include "system.h"

class Entity;

class SysMapPlayer : public System
{
  public:
    SysMapPlayer();
    ~SysMapPlayer() override = default;

    void Update() override{};
    void Fixed() override;
    void Quit() override{};

    static Entity *GetPlayer();
};
