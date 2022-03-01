#pragma once

#include "system.h"

struct Vec2;

class SysHook : public System
{
  public:
    SysHook() = default;
    virtual ~SysHook() override = default;

    virtual void Update() override{};
    virtual void Fixed() override;
    virtual void Quit() override{};

    static void SysHook::Instantiate(const Vec2 &pos);
};
