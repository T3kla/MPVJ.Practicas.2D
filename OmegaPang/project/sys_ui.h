#pragma once

#include "system.h"

#include <entt/entt.hpp>

struct Vec2;
struct Font;
struct Color;

class SysUI : public System
{
  public:
    SysUI() = default;
    virtual ~SysUI() override = default;

    virtual void Update() override{};
    virtual void Fixed() override;
    virtual void Quit() override{};

    static entt::entity Instantiate(const Vec2 &pos, const char *text, Font *font, float weight, const Color &color);
};
