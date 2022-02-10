#pragma once

#include "behaviour.h"
#include "sizes.h"

struct Vec2;

class SysExplosions : public Behaviour
{
  public:
    SysExplosions();
    virtual ~SysExplosions() override;

    virtual void Awake() override;
    virtual void Start() override;
    virtual void Update() override;
    virtual void Fixed() override;
    virtual void Quit() override;

    static void SysExplosions::Instantiate(const Vec2 &pos, Size size);
    static void SysExplosions::InstantiateSmaller(const Vec2 &pos, Size size);
};
