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
static bool TryPolling(entt::entity &id);

void SysBee::Fixed()
{
    for (auto [entity, go, tf, be, sr, sa] : GetView().each())
    {
        if (!go.isActive || !be.enable)
            continue;

        auto mousePos = Input::GetMousePosWorld();
        auto dir = mousePos - tf.position;

        // Directional behaviour
        auto fSTP = static_cast<float>(STP);
        if (dir.Magnitude() < 50.f)
        {
            tf.rotation += (0.f - tf.rotation > 0.f ? 1.f : -1.f) * 32.f * fSTP * 0.001f;
            return;
        }
        else if (mousePos.x < tf.position.x)
        {
            // Left
            sr.reverse = true;
            tf.rotation += (15.f - tf.rotation > 0.f ? 1.f : -1.f) * 32.f * fSTP * 0.001f;
        }
        else
        {
            // Right
            sr.reverse = false;
            tf.rotation += (-15.f - tf.rotation > 0.f ? 1.f : -1.f) * 32.f * fSTP * 0.001f;
        }

        // Movement
        tf.position += dir.Normalized() * 128.f * fSTP * 0.001f;
    }
}

entt::entity SysBee::Instantiate(const Vec2 &pos)
{
    auto &reg = Game::GetRegistry();

    entt::entity id;

    if (!TryPolling(id))
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
    sr.sprite = &SpriteLoader::sprSheetBee[0];
    sr.offsetPosition = Vec2::Zero();
    sr.offsetRotation = 0.f;
    sr.size = {100.f, 100.f};
    sr.pivot = Vec2::One() * 0.5f;
    sr.layer = 10;
    sr.blend = BLEND_ALPHA;

    auto &sa = reg.get_or_emplace<SpriteAnimation>(id);
    sa.enable = true;
    sa.animation = &SpriteLoader::sprSheetBee;
    sa.frame = 0;
    sa.speed = 0.f;
    sa.duration = 1.f;
    sa.count = 0.f;

    return id;
}

bool TryPolling(entt::entity &id)
{
    for (auto [entity, go, tf, be, sr, sa] : GetView().each())
        if (!go.isActive && be.enable)
        {
            id = entity;
            return true;
        }

    return false;
}
