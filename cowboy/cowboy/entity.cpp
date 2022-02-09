#include "entity.h"

Entity::Entity() {}

Entity::Entity(const entt::entity &id, entt::registry *reg) {
  this->entityID = id;
  this->entityReg = reg;
}

Entity::~Entity() {}

entt::entity Entity::GetID() { return entityID; }

entt::registry *Entity::GetReg() { return entityReg; }
