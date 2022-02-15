#include "sys_bee.h"

#include "bee.h"
#include "game.h"
#include "gameobject.h"
#include "input.h"
#include "sprite_animation.h"
#include "sprite_loader.h"
#include "sprite_renderer.h"
#include "transform.h"

static auto GetView = []() {
    return Game::GetRegistry().view<GameObject, Transform, Bee, SpriteRenderer, SpriteAnimation>();
};
static bool TryPoolling(entt::entity &id);

void SysBee::Fixed()
{
    for (auto [entity, go, tf, be, sr, sa] : GetView().each())
    {
        if (!go.isActive || !be.enable)
            continue;

        auto mousePos = Input::GetMousePos();

        // Follow Mouse
        auto dir = mousePos - tf.position;
        tf.position += dir.Normalized() * 128.f * STP * 0.001f;

        // Reverse sprite
        if (mousePos.x < tf.position.x)
            sr.reverse = true;
        else
            sr.reverse = false;
    }
}

void SysBee::Instantiate(const Vec2 &pos)
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

    auto &be = reg.get_or_emplace<Bee>(id);
    be.enable = true;

    auto &sr = reg.get_or_emplace<SpriteRenderer>(id);
    sr.enable = true;
    sr.sprite = &SpriteLoader::sprBee[0];
    sr.offsetPosition = Vec2::Zero();
    sr.offsetRotation = 0.f;
    sr.size = {100.f, 100.f};
    sr.pivot = Vec2::One() * 0.5f;
    sr.layer = 1;
    sr.blend = BLEND_ALPHA;

    auto &sa = reg.get_or_emplace<SpriteAnimation>(id);
    sa.enable = true;
    sa.animation = &SpriteLoader::sprBee;
    sa.frame = 0;
    sa.speed = 0.f;
    sa.duration = 1.f;
    sa.count = 0.f;
}

bool TryPoolling(entt::entity &id)
{
    for (auto [entity, go, tf, be, sr, sa] : GetView().each())
        if (!go.isActive && be.enable)
        {
            id = entity;
            return true;
        }

    return false;
}
