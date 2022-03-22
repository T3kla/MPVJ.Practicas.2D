#pragma once

#include "system.h"
#include <entt/entt.hpp>

struct Vec2;

class SysBee : public System
{
  public:
    SysBee() = default;
    virtual ~SysBee() override = default;

    virtual void Update() override{};
    virtual void Fixed() override;
    virtual void Quit() override{};

    static entt::entity Instantiate(const Vec2 &pos);
};
