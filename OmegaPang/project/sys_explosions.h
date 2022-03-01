#pragma once

#include "size.h"
#include "system.h"

struct Vec2;

class SysExplosions : public System
{
  public:
    SysExplosions() = default;
    virtual ~SysExplosions() override = default;

    virtual void Update() override{};
    virtual void Fixed() override;
    virtual void Quit() override{};

    static void SysExplosions::Instantiate(const Vec2 &pos, Size size);
};
