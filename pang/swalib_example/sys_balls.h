#pragma once

#include "behaviour.h"

struct Vec2;
class Size;

class SysBalls : public Behaviour
{
  public:
    SysBalls();
    virtual ~SysBalls() override;

    virtual void Awake() override;
    virtual void Start() override;
    virtual void Update() override;
    virtual void Fixed() override;
    virtual void Quit() override;

    static void SysBalls::Instantiate(const Vec2 &pos, bool right, Size size);
    static void SysBalls::InstantiateSmaller(const Vec2 &pos, bool right, Size size);
};
