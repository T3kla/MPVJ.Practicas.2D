#include "sys_hook.h"

#include "ball.h"
#include "circle_collider.h"
#include "game.h"
#include "gameobject.h"
#include "hook.h"
#include "render.h"
#include "rigidbody.h"
#include "sprite_animation.h"
#include "sprite_loader.h"
#include "sprite_renderer.h"
#include "square_collider.h"
#include "sys_balls.h"
#include "sys_explosions.h"
#include "transform.h"

#include <entt/entt.hpp>

auto GetView = []() {
    return Game::GetRegistry().view<GameObject, Transform, Hook, SquareCollider, SpriteRenderer, SpriteAnimation>();
};
auto GetBallsView = []() { return Game::GetRegistry().view<GameObject, Transform, RigidBody, Ball, CircleCollider>(); };

bool IsColliding(Vec2 circlePos, float circleRad, Vec2 sqrPos, Vec2 sqrSize);
float Clamp(float value, float min, float max);

void SysHook::Fixed()
{
    for (auto [entity, _go, _tf, _hk, _sc, _sr, _sa] : GetView().each())
    {
        if (!_go.isActive)
            continue;

        // Travel Up
        int width, height;
        Render::GetWindowSize(width, height);
        _tf.position += Vec2::Up() * _hk.speed * (float)STP * 0.001f;
        if (_tf.position.y > height - 50)
            _go.isActive = false;

        // Collisions
        for (auto [entity, go_, tf_, rb_, bl_, cc_] : GetBallsView().each())
        {
            if (!go_.isActive)
                continue;

            if (IsColliding(tf_.position, cc_.radius, _tf.position + _sc.center, _sc.size))
            {
                _go.isActive = false;
                go_.isActive = false;
                SysBalls::InstantiateSmaller(_tf.position, true, bl_.size);
                SysBalls::InstantiateSmaller(_tf.position, false, bl_.size);
                SysExplosions::InstantiateSmaller(_tf.position, bl_.size);
                return;
            }
        }
    }
}

void SysHook::Instantiate(const Vec2 &pos)
{
    auto &reg = Game::GetRegistry();

    entt::entity id;

    if (!TryPoolling(id))
        id = reg.create();

    auto &lol = reg.get_or_emplace<GameObject>(id, true);
    reg.get_or_emplace<Transform>(id, pos, Vec2::One(), 0.f);
    reg.get_or_emplace<Hook>(id, true, -1000.f);
    reg.get_or_emplace<SquareCollider>(id, true, Vec2(0.f, -420.f), Vec2(35.f, 950.f));
    reg.get_or_emplace<SpriteRenderer>(id, true, &SpriteLoader::sprHook[0], Vec2(0.f, -420.f), 0.f, Vec2(100.f, 1000.f),
                                       Vec2::One() * 0.5f, 5, BLEND_ALPHA);
    reg.get_or_emplace<SpriteAnimation>(id, true, &SpriteLoader::sprHook, 0, 0.f, 0.2f, 0.f, 1);
}

bool TryPoolling(entt::entity &id)
{
    // Pooling
    for (auto [entity, go, tf, hk, sc, sr, sa] : GetView().each())
        if (!go.isActive && hk.enable)
        {
            id = entity;
            return true;
        }

    return false;
}

bool IsColliding(Vec2 circlePos, float circleRad, Vec2 sqrPos, Vec2 sqrSize)
{
    Vec2 point = {0.f, 0.f};

    auto maxX = sqrPos.x + sqrSize.x / 2.f;
    auto minX = sqrPos.x - sqrSize.x / 2.f;

    auto maxY = sqrPos.y + sqrSize.y / 2.f;
    auto minY = sqrPos.y - sqrSize.y / 2.f;

    point.x = Clamp(circlePos.x - sqrPos.x + sqrPos.x, minX, maxX);
    point.y = Clamp(circlePos.y - sqrPos.y + sqrPos.y, minY, maxY);

    auto distance = (point - circlePos).Magnitude();

    return distance < circleRad / 2.f;
}

float Clamp(float value, float min, float max)
{
    return std::max(min, std::min(max, value));
}
