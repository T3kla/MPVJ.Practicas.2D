#pragma once

#include <entt/entt.hpp>

#include "behaviour.h"
#include "entity.h"

class Scene : public Behaviour {
private:
  char title[256] = "Cowboy";

public:
  Scene();
  ~Scene();

  virtual void Awake() override;
  virtual void Start() override;
  virtual void Update() override;
  virtual void Fixed() override;
  virtual void Quit() override;

  static void InstantiateFloor();
};
