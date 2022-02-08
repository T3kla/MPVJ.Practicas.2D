#pragma once

#include "behaviour.h"

class Entity;
struct Vec2;

class SysHook : public Behaviour {
  virtual void Awake() override;
  virtual void Start() override;
  virtual void Update() override;
  virtual void Fixed() override;
  virtual void Quit() override;

public:
  SysHook();
  ~SysHook();

  static void SysHook::InstantiateHook(const Vec2 &pos);
};
