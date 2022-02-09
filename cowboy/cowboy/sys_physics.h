#pragma once

#include "behaviour.h"

struct SysPhysics : public Behaviour {
  SysPhysics();
  virtual ~SysPhysics() override;

  virtual void Awake() override;
  virtual void Start() override;
  virtual void Update() override;
  virtual void Fixed() override;
  virtual void Quit() override;
};
