#pragma once

#include "size.h"
#include "system.h"

struct Vec2;

class SysBalls : public System
{
  public:
    SysBalls() = default;
    virtual ~SysBalls() override = default;

    virtual void Awake() override{};
    virtual void Start() override{};
    virtual void Update() override{};
    virtual void Fixed() override;
    virtual void Quit() override{};

    static void Instantiate(const Vec2 &pos, bool right, Size size);
};
