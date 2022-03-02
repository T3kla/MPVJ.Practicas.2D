#pragma once

#include "vec.h"
#include <entt/entt.hpp>

struct Collision
{
    entt::entity colliderSelf;
    entt::entity colliderOther;
};
