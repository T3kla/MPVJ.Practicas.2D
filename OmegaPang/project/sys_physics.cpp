#include "sys_physics.h"

#include "game.h"

#include "circle_collider.h"
#include "gameobject.h"
#include "pixel_collider.h"
#include "rigidbody.h"
#include "sprite_renderer.h"
#include "square_collider.h"
#include "transform.h"

#include <vector>

typedef std::vector<entt::entity> eSet;

static constexpr short int RESERVE = 64;

static eSet sqrSet;
static eSet crlSet;
static eSet pxlSet;

SysPhysics::SysPhysics()
{
    sqrSet.reserve(RESERVE);
    crlSet.reserve(RESERVE);
    pxlSet.reserve(RESERVE);
}

void SysPhysics::Fixed()
{
    auto &reg = Game::GetRegistry();

    // Reset buffers
    sqrSet.clear();
    crlSet.clear();
    pxlSet.clear();

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
    auto sqrView = reg.view<GameObject, Transform, RigidBody, SquareCollider>();
    auto crlView = reg.view<GameObject, Transform, RigidBody, CircleCollider>();
    auto pxlView = reg.view<GameObject, Transform, RigidBody, PixelCollider, SpriteRenderer>();

    // Get colliding entities
    for (auto [entity, go, tf, rb, sc] : sqrView.each())
        if (go.isActive && rb.enable && sc.enable)
            sqrSet.emplace_back(entity);

    for (auto [entity, go, tf, rb, cc] : crlView.each())
        if (go.isActive && rb.enable && cc.enable)
            crlSet.emplace_back(entity);

    for (auto [entity, go, tf, rb, pc, sr] : pxlView.each())
        if (go.isActive && rb.enable && pc.enable && sr.enable && sr.sprite)
            pxlSet.emplace_back(entity);

    // Set posible collisions
    for (auto entity : sqrView | crlView | pxlView)
    {
        reg.any_of<position, velocity>(entity)
    }

    // Collide
    //      Check if entity == entity because it may have multiple colliders

    // Send collision events
}
