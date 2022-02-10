#pragma once

#include "behaviour.h"

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

    static void SysExplosions::InstantiateSmaller(const Vec2 &pos, char size);
    static void SysExplosions::InstantiateL(const Vec2 &pos);
    static void SysExplosions::InstantiateB(const Vec2 &pos);
    static void SysExplosions::InstantiateM(const Vec2 &pos);
    static void SysExplosions::InstantiateS(const Vec2 &pos);
};
