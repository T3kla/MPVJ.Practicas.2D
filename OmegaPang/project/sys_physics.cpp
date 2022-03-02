#include "sys_physics.h"

#include "game.h"

#include "collision.h"

#include "circle_collider.h"
#include "gameobject.h"
#include "pixel_collider.h"
#include "rigidbody.h"
#include "sprite_renderer.h"
#include "square_collider.h"
#include "transform.h"

#include <algorithm>
#include <vector>

struct AABB
{
    entt::entity id;
    Vec2 pos;
    Vec2 size;
    const char *colType;
};

struct PreCol
{
    AABB *a;
    AABB *b;
};

static std::vector<AABB> setup;
static std::vector<PreCol> preCol;
static Vec2 aMax, aMin, bMax, bMin;

static const auto *const ptrSqrName = typeid(SquareCollider).name();
static const auto *const ptrCrlName = typeid(CircleCollider).name();
static const auto *const ptrPxlName = typeid(PixelCollider).name();

SysPhysics::SysPhysics()
{
    setup.reserve(64);
    preCol.reserve(64);
}

void SysPhysics::Fixed()
{
    auto &reg = Game::GetRegistry();

    // Reset buffer
    setup.clear();
    preCol.clear();

    // Apply velocity
    auto rbView = reg.view<GameObject, Transform, RigidBody>();
    for (auto [entity, go, tf, rb] : rbView.each())
    {
        if (!go.isActive || !rb.enable)
            continue;

        tf.position += rb.velocity * (float)STP * 0.001f;
        rb.velocity = rb.velocity * (1.f - rb.linearDrag);
    }

    // Set views
    auto sqrView = reg.view<GameObject, Transform, SquareCollider>();
    auto crlView = reg.view<GameObject, Transform, CircleCollider>();
    auto pxlView = reg.view<GameObject, Transform, PixelCollider, SpriteRenderer>();

    // Get colliding entities
    for (auto [entity, go, tf, sc] : sqrView.each())
        if (go.isActive && sc.enable)
            setup.push_back({entity, tf.position + sc.center, sc.size, ptrSqrName});

    for (auto [entity, go, tf, cc] : crlView.each())
        if (go.isActive && cc.enable)
            setup.push_back({entity, tf.position + cc.center, {cc.radius, cc.radius}, ptrCrlName});

    for (auto [entity, go, tf, pc, sr] : pxlView.each())
        if (go.isActive && pc.enable && sr.enable && sr.sprite)
            setup.push_back({entity, tf.position, sr.size, ptrPxlName});

    // Set posible collisions
    for (auto &&a : setup)
    {
        aMax = a.pos + a.size / 2.f;
        aMin = a.pos - a.size / 2.f;

        for (auto &&b : setup)
        {
            if (a.id == b.id)
                continue;

            bMax = b.pos + b.size / 2.f;
            bMin = b.pos - b.size / 2.f;

            if ((bMax.x > aMax.x && bMin.x > aMax.x) || (bMax.x < aMin.x && bMin.x < aMin.x) ||
                (bMax.y > aMax.y && bMin.y > aMax.y) || (bMax.y < aMin.y && bMin.y < aMin.y))
                continue;

            preCol.push_back({&a, &b});
        }
    }

    // Collide
    //      Check if entity == entity because it may have multiple colliders

    // Send collision events
    for (auto &&collision : preCol)
    {
        Collision col = {collision.a->id, collision.b->id};

        if (collision.a->colType == ptrSqrName)
            reg.get<SquareCollider>(collision.a->id).OnCollision(&col);
        else if (collision.a->colType == ptrCrlName)
            reg.get<CircleCollider>(collision.a->id).OnCollision(&col);
        else if (collision.a->colType == ptrPxlName)
            reg.get<PixelCollider>(collision.a->id).OnCollision(&col);
    }
}
