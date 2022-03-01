#pragma once

#include "system.h"

class SysPhysics : public System
{
  public:
    SysPhysics();
    virtual ~SysPhysics() override = default;

    virtual void Update() override{};
    virtual void Fixed() override;
    virtual void Quit() override{};
};
