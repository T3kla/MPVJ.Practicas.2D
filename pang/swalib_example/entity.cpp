#include "entity.h"

Entity::Entity(const entt::entity &id, const entt::registry &reg) : entityID(id), entityReg(reg)
{
}

Entity::~Entity()
{
}

entt::entity Entity::GetID()
{
    return entityID;
}

const entt::registry &Entity::GetReg()
{
    return entityReg;
}
