#pragma once

#include "behaviour.h"
#include <entt/entt.hpp>

struct SysBullet : public Behaviour {
  SysBullet();
  virtual ~SysBullet() override;

  virtual void Awake() override;
  virtual void Start() override;
  virtual void Update() override;
  virtual void Fixed() override;
  virtual void Quit() override;

  static entt::entity InstantiateBullet();
};
