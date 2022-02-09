#pragma once

#include "behaviour.h"
#include <entt/entt.hpp>

struct SysPlayer : public Behaviour {
  float speed = 200.f;

  SysPlayer();
  virtual ~SysPlayer() override;

  virtual void Awake() override;
  virtual void Start() override;
  virtual void Update() override;
  virtual void Fixed() override;
  virtual void Quit() override;

  static entt::entity GetPlayer();
  static entt::entity InstantiatePlayer();
};
