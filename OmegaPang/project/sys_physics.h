#pragma once

#include "system.h"
#include "vec.h"

#include <entt/entt.hpp>

struct Box
{
    entt::entity id;
    Vec2 pos;
    Vec2 size;
    const char *type;

    bool operator==(const Box &rhs) const
    {
        return id == rhs.id && type == rhs.type;
    }
};

struct Collision
{
    Box a;
    Box b;

    bool operator==(const Collision &rhs) const
    {
        return a.id == rhs.a.id && b.id == rhs.b.id;
    }
};

struct Possible
{
    Box *a;
    Box *b;

    bool operator==(const Possible &rhs) const
    {
        return a == rhs.a && b == rhs.b;
    }
};

class SysPhysics : public System
{
  public:
    SysPhysics();
    virtual ~SysPhysics() override = default;

    virtual void Update() override{};
    virtual void Fixed() override;
    virtual void Quit() override{};
};
