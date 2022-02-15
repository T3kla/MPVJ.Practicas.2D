#pragma once

#include <entt/entt.hpp>

class Entity
{
  private:
    entt::entity entityID = {};
    entt::registry *entityReg = nullptr;

  public:
    Entity();
    Entity(const entt::entity &id, entt::registry *reg);
    ~Entity();

    entt::entity GetID();
    entt::registry &GetReg();
};
