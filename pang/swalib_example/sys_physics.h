#pragma once

#include "behaviour.h"

class SysPhysics : public Behaviour
{
  public:
    SysPhysics() = default;
    virtual ~SysPhysics() override = default;

    virtual void Awake() override{};
    virtual void Start() override{};
    virtual void Update() override{};
    virtual void Fixed() override;
    virtual void Quit() override{};
};
