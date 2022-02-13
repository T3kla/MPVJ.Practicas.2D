#include "entity.h"

#include "game.h"

Entity::Entity()
{
}

Entity::Entity(const entt::entity &id, entt::registry *reg) : entityID(id), entityReg(reg)
{
}

Entity::~Entity()
{
}

entt::entity Entity::GetID()
{
    return entityID;
}

entt::registry &Entity::GetReg()
{
    return *entityReg;
}
