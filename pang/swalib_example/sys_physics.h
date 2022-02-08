#pragma once

#include "behaviour.h"

class SysPhysics : public Behaviour {
  virtual void Awake() override;
  virtual void Start() override;
  virtual void Update() override;
  virtual void Fixed() override;
  virtual void Quit() override;

public:
  SysPhysics();
  ~SysPhysics();
};
