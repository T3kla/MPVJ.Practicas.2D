#pragma once

#include "system.h"

class Entity;

class SysMapPlayer : public System
{
  public:
    SysMapPlayer();
    virtual ~SysMapPlayer() override = default;

    virtual void Update() override{};
    virtual void Fixed() override;
    virtual void Quit() override{};

    static Entity *GetPlayer();
};
