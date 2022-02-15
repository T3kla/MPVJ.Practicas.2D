#pragma once

#include "system.h"
struct Vec2;
struct Font;
struct Color;

class SysUI : public System
{
  public:
    SysUI() = default;
    virtual ~SysUI() override = default;

    virtual void Awake() override{};
    virtual void Start() override{};
    virtual void Update() override{};
    virtual void Fixed() override;
    virtual void Quit() override{};

    static void Instantiate(const Vec2 &pos, const char *text, Font *font, float weight, const Color &color);
};
