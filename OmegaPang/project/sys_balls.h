#pragma once

#include "size.h"
#include "system.h"

struct Vec2;

class SysBalls : public System
{
  public:
    SysBalls() = default;
    ~SysBalls() override = default;

    void Update() override{};
    void Fixed() override;
    void Quit() override{};

    static void Instantiate(const Vec2 &pos, bool right, Size size);
};
