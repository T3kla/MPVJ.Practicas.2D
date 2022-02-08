#pragma once

#include "behaviour.h"

class Entity;

class SysPlayer : public Behaviour {
  virtual void Awake() override;
  virtual void Start() override;
  virtual void Update() override;
  virtual void Fixed() override;
  virtual void Quit() override;

public:
  SysPlayer();
  ~SysPlayer();

  static Entity *GetPlayer();
  static int GetPlayerHealth();
};
