#pragma once

#include <entt/entt.hpp>

class Entity {
private:
  entt::entity entityID = {};
  entt::registry *entityReg = nullptr;

public:
  Entity();
  Entity(const entt::entity &id, entt::registry *reg);
  ~Entity();

  entt::entity GetID();
  entt::registry *GetReg();

  template <class T> T &&GetComponent();
};

template <class T> inline T &&Entity::GetComponent() {
  return T && (entityReg->get<T>);
}
