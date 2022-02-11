#pragma once

#include "behaviour.h"

struct Vec2;

class SysHook : public Behaviour
{
  public:
    SysHook() = default;
    virtual ~SysHook() override = default;

    virtual void Awake() override{};
    virtual void Start() override{};
    virtual void Update() override{};
    virtual void Fixed() override;
    virtual void Quit() override{};

    static void SysHook::Instantiate(const Vec2 &pos);
};
