#pragma once

#include <entt/entt.hpp>

class Entity
{
  private:
    entt::entity entityID = {};
    const entt::registry &entityReg;

  public:
    Entity() = delete;
    Entity(const entt::entity &id, const entt::registry &reg);
    ~Entity();

    entt::entity GetID();
    const entt::registry &GetReg();

    template <class T> T &&GetComponent();
};

template <class T> inline T &&Entity::GetComponent()
{
    return T && (entityReg->get<T>);
}
