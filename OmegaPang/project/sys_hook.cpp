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

bool TryPoolling(entt::entity &id);

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
        _tf.position -= Vec2::Up() * _hk.speed * (float)STP * 0.001f;
        if (_tf.position.y < 0 + 50.f)
            _go.isActive = false;

        // Collisions
        for (auto [entity, go_, tf_, rb_, bl_, cc_] : GetBallsView().each())
        {
            if (!go_.isActive)
                continue;

            if (!IsColliding(tf_.position, cc_.radius, _tf.position + _sc.center, _sc.size))
                continue;

            _go.isActive = false;
            go_.isActive = false;
            auto size = bl_.size; // Pooling can modify bl_.size in the first instantiation
            SysBalls::Instantiate(tf_.position, true, size.OneSmaller());
            SysBalls::Instantiate(tf_.position, false, size.OneSmaller());
            SysExplosions::Instantiate(tf_.position, size);
            return;
        }
    }
}

void SysHook::Instantiate(const Vec2 &pos)
{
    auto &reg = Game::GetRegistry();

    entt::entity id;

    if (!TryPoolling(id))
        id = reg.create();

    auto &go = reg.get_or_emplace<GameObject>(id);
    go.isActive = true;

    auto &tf = reg.get_or_emplace<Transform>(id);
    tf.position = pos;
    tf.scale = Vec2::One();
    tf.rotation = 0.f;

    auto &hk = reg.get_or_emplace<Hook>(id);
    hk.enable = true;
    hk.speed = -1000.f;

    auto &sc = reg.get_or_emplace<SquareCollider>(id);
    sc.enable = true;
    sc.center = {0.f, 420.f};
    sc.size = {35.f, 950.f};

    auto &sr = reg.get_or_emplace<SpriteRenderer>(id);
    sr.enable = true;
    sr.sprite = &SpriteLoader::sprHook[0];
    sr.offsetPosition = {0.f, 420.f};
    sr.offsetRotation = 0.f;
    sr.size = {100.f, 1000.f};
    sr.pivot = Vec2::One() * 0.5f;
    sr.layer = 5;
    sr.blend = BLEND_ALPHA;

    auto &sa = reg.get_or_emplace<SpriteAnimation>(id);
    sa.enable = true;
    sa.animation = &SpriteLoader::sprHook;
    sa.frame = 0;
    sa.speed = 0.f;
    sa.duration = 0.2f;
    sa.count = 0.f;
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
