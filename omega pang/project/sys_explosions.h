#pragma once

#include "behaviour.h"
#include "size.h"

struct Vec2;

class SysExplosions : public Behaviour
{
  public:
    SysExplosions() = default;
    virtual ~SysExplosions() override = default;

    virtual void Awake() override{};
    virtual void Start() override{};
    virtual void Update() override{};
    virtual void Fixed() override;
    virtual void Quit() override{};

    static void SysExplosions::Instantiate(const Vec2 &pos, Size size);
};
