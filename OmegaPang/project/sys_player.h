#pragma once

#include "system.h"

class Entity;

class SysPlayer : public System
{
  public:
    SysPlayer();
    ~SysPlayer() override = default;

    void Update() override;
    void Fixed() override{};
    void Quit() override{};

    static Entity *GetPlayer();
    static int GetPlayerHealth();
};
