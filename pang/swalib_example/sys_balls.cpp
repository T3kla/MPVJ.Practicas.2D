#include "sys_balls.h"

#include "ball.h"
#include "circle_collider.h"
#include "game.h"
#include "gameobject.h"
#include "render.h"
#include "rigidbody.h"
#include "sprite_loader.h"
#include "sprite_renderer.h"
#include "transform.h"

#include <entt/entt.hpp>

auto GetView = []() { return Game::GetRegistry().view<GameObject, Transform, RigidBody, Ball, CircleCollider>(); };
bool TryPoolling(entt::entity &id);
float ReboundPerSize(Size size);

void SysBalls::Fixed()
{
    for (auto [entity, go, tf, rb, bl, cc] : GetView().each())
    {
        if (!go.isActive)
            continue;

        // Gravity
        rb.velocity += Vec2::Down() * 600.f * (float)STP * 0.001f;

        // Rebound
        int width, height;
        Render::GetWindowSize(width, height);
        if (tf.position.x > width - cc.radius / 2.f)
        {
            tf.position.x = width - cc.radius / 2.f - 1.f;
            rb.velocity.x *= -1.f;
        }
        if (tf.position.x < cc.radius / 2.f)
        {
            tf.position.x = cc.radius / 2.f + 1.f;
            rb.velocity.x *= -1.f;
        }
        if (tf.position.y < cc.radius / 2.f)
        {
            tf.position.y = cc.radius / 2.f + 1.f;
            rb.velocity.y = ReboundPerSize(bl.size) * 1.2f;
        }
    }
}

void SysBalls::InstantiateSmaller(const Vec2 &pos, bool right, Size size)
{
    Size smaller = size.OneSmaller();

    if (smaller == Size::None)
        return;

    Instantiate(pos, right, smaller);
}

void SysBalls::Instantiate(const Vec2 &pos, bool right, Size size)
{
    auto &reg = Game::GetRegistry();

    entt::entity id;

    if (!TryPoolling(id))
        id = reg.create();

    Sprite *sprite;
    Vec2 spriteSize;
    float colRadius;

    if (size == Size::L)
    {
        sprite = &SpriteLoader::sprBalls[0];
        spriteSize = {260.f, 260.f};
        colRadius = 160.f;
    }
    else if (size == Size::B)
    {
        sprite = &SpriteLoader::sprBalls[1];
        spriteSize = {160.f, 160.f};
        colRadius = 115.f;
    }
    else if (size == Size::M)
    {
        sprite = &SpriteLoader::sprBalls[2];
        spriteSize = {140.f, 140.f};
        colRadius = 65.f;
    }
    else if (size == Size::S)
    {
        sprite = &SpriteLoader::sprBalls[3];
        spriteSize = {110.f, 110.f};
        colRadius = 20.f;
    }

    reg.get_or_emplace<GameObject>(id, true);
    reg.get_or_emplace<Transform>(id, pos, Vec2::One(), 0.f);
    reg.get_or_emplace<RigidBody>(id, true, Vec2(175.f * (right ? 1.f : -1.f), 200.f), 0.0f);
    reg.get_or_emplace<Ball>(id, true, Vec2::Zero(), size);
    reg.get_or_emplace<CircleCollider>(id, true, colRadius);
    reg.get_or_emplace<SpriteRenderer>(id, true, sprite, Vec2::Zero(), 0.f, spriteSize, Vec2::One() * 0.5f, 1,
                                       BLEND_ALPHA);
}

bool TryPoolling(entt::entity &id)
{
    for (auto [entity, go, tf, bl] : GetView().each())
        if (!go.isActive && bl.enable)
        {
            id = entity;
            return true;
        }

    return false;
}

float ReboundPerSize(Size size)
{
    switch (size)
    {
    case Size::L:
        return 650.f;
    case Size::B:
        return 550.f;
    case Size::M:
        return 450.f;
    case Size::S:
        return 350.f;
    default:
        return 100.f;
    }
}
