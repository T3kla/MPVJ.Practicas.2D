#include "sys_ui.h"

#include "game.h"
#include "gameobject.h"
#include "textbox.h"
#include "transform.h"

static auto GetView = []() { return Game::GetRegistry().view<GameObject, RectTransform, TextBox>(); };
static bool TryPoolling(entt::entity &id);

void SysUI::Fixed()
{
    // do stuff?
}

void SysUI::Instantiate(const Vec2 &pos, const char *text, Font *font, float weight, const Color &color)
{
    auto &reg = Game::GetRegistry();

    entt::entity id;

    if (!TryPoolling(id))
        id = reg.create();

    auto &go = reg.get_or_emplace<GameObject>(id);
    go.isActive = true;

    auto &tf = reg.get_or_emplace<RectTransform>(id);
    tf.position = pos;
    tf.size = {100.f, 100.f};
    tf.anchor0 = {0.5f, 0.5f};
    tf.anchor1 = {0.5f, 0.5f};
    tf.pivot = {0.5f, 0.5f};
    tf.scale = Vec2::One();
    tf.rotation = 0.f;

    auto &tb = reg.get_or_emplace<TextBox>(id);
    tb.enable = true;
    tb.text = text;
    tb.font = font;
    tb.weight = weight;
    tb.color = color;
    tb.layer = 0;
    tb.blend = BLEND_ALPHA;
}

bool TryPoolling(entt::entity &id)
{
    for (auto [entity, go, tf, tb] : GetView().each())
        if (!go.isActive && tb.enable)
        {
            id = entity;
            return true;
        }

    return false;
}
