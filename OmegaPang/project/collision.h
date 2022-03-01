#pragma once

#include "vec.h"
#include <entt/entt.hpp>

struct Collision
{
    Vec2 hitPosition;
    Vec2 hitNormal;

    entt::entity id;
};
