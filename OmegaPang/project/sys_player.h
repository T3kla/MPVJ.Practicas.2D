#pragma once

#include "system.h"

class Entity;

class SysPlayer : public System
{
  public:
    SysPlayer() = default;
    virtual ~SysPlayer() override = default;

    virtual void Awake() override;
    virtual void Start() override{};
    virtual void Update() override;
    virtual void Fixed() override;
    virtual void Quit() override;

    static Entity *GetPlayer();
    static int GetPlayerHealth();
};
