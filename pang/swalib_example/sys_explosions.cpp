#include "sys_explosions.h"

#include "explosion.h"
#include "game.h"
#include "gameobject.h"
#include "sprite_loader.h"
#include "sprite_renderer.h"
#include "transform.h"

#include <entt/entt.hpp>

bool TryPoolling(entt::entity &id);

SysExplosions::SysExplosions()
{
}

SysExplosions::~SysExplosions()
{
}

void SysExplosions::Awake()
{
}

void SysExplosions::Start()
{
}

void SysExplosions::Update()
{
}

void SysExplosions::Fixed()
{
    auto &reg = Game::GetRegistry();
    auto explosions = reg.view<GameObject, Transform, Explosion>();

    for (auto [entity, go, tf, ex] : explosions.each())
    {
        if (!go.isActive)
            continue;

        if (ex.lifespan > 0.f)
            ex.lifespan -= (float)STP * 0.001f;
        else
            go.isActive = false;
    }
}

void SysExplosions::Quit()
{
}

void SysExplosions::InstantiateSmaller(const Vec2 &pos, Size size)
{
    Size smaller = size.OneSmaller();

    if (smaller == Size::None)
        return;

    Instantiate(pos, smaller);
}

void SysExplosions::Instantiate(const Vec2 &pos, Size size)
{
    auto &reg = Game::GetRegistry();

    entt::entity id;

    if (!TryPoolling(id))
        id = reg.create();

    Sprite *sprite;
    Vec2 spriteSize;

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

    reg.get_or_emplace<GameObject>(id, true);
    reg.get_or_emplace<Transform>(id, pos, Vec2::One(), 0.f);
    reg.get_or_emplace<Explosion>(id, true, 0.1f, size);
    reg.get_or_emplace<SpriteRenderer>(id, true, sprite, Vec2::Zero(), 0.f, spriteSize, Vec2::One() * 0.5f, 1,
                                       BLEND_ALPHA);
}

bool TryPoolling(entt::entity &id)
{
    auto &reg = Game::GetRegistry();
    auto explosions = reg.view<GameObject, Transform, Explosion>();

    // Pooling
    for (auto [entity, go, tf, ex] : explosions.each())
        if (!go.isActive && ex.enable)
        {
            id = entity;
            return true;
        }

    return false;
}
