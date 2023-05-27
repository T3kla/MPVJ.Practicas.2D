#include "sys_explosions.h"

#include "explosion.h"
#include "game.h"
#include "gameobject.h"
#include "sprite_loader.h"
#include "sprite_renderer.h"
#include "transform.h"

#include <entt/entt.hpp>

static auto GetView = []() { return Game::GetRegistry().view<GameObject, Transform, Explosion, SpriteRenderer>(); };
static bool TryPolling(entt::entity &id);

void SysExplosions::Fixed()
{
    for (auto [entity, go, tf, ex, sr] : GetView().each())
    {
        if (!go.isActive)
            continue;

        if (ex.lifespan > 0.f)
            ex.lifespan -= (float)STP * 0.001f;
        else
            go.isActive = false;
    }
}

void SysExplosions::Instantiate(const Vec2 &pos, Size size)
{
    if (size == Size::None)
        return;

    auto &reg = Game::GetRegistry();

    entt::entity id;

    if (!TryPolling(id))
        id = reg.create();

    Sprite *sprite = nullptr;
    Vec2 spriteSize = {};

    if (size == Size::L)
    {
        sprite = &SpriteLoader::sprExpls[0];
        spriteSize = {260.f, 260.f};
    }
    else if (size == Size::B)
    {
        sprite = &SpriteLoader::sprExpls[1];
        spriteSize = {160.f, 160.f};
    }
    else if (size == Size::M)
    {
        sprite = &SpriteLoader::sprExpls[2];
        spriteSize = {140.f, 140.f};
    }
    else if (size == Size::S)
    {
        sprite = &SpriteLoader::sprExpls[3];
        spriteSize = {110.f, 110.f};
    }

    auto &go = reg.get_or_emplace<GameObject>(id);
    go.isActive = true;

    auto &tf = reg.get_or_emplace<Transform>(id);
    tf.position = pos;
    tf.scale = Vec2::One();
    tf.rotation = 0.f;

    auto &ex = reg.get_or_emplace<Explosion>(id);
    ex.enable = true;
    ex.lifespan = 0.1f;
    ex.size = size;

    auto &sr = reg.get_or_emplace<SpriteRenderer>(id);
    sr.enable = true;
    sr.sprite = sprite;
    sr.offsetPosition = Vec2::Zero();
    sr.offsetRotation = 0.f;
    sr.size = spriteSize;
    sr.pivot = Vec2::One() * 0.5f;
    sr.layer = 2;
    sr.blend = BLEND_ALPHA;
}

bool TryPolling(entt::entity &id)
{
    for (auto [entity, go, tf, ex, sr] : GetView().each())
        if (!go.isActive && ex.enable)
        {
            id = entity;
            return true;
        }

    return false;
}
