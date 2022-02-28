//#include "sys_image.h"
//
//#include "entt/entt.hpp"
//
// static auto GetView = []() {
//    return Game::GetRegistry().view<GameObject, Transform, RigidBody, Ball, CircleCollider>();
//};
// static bool TryPoolling(entt::entity &id);
//
// void SysBalls::Instantiate(const Vec2 &pos, bool right, Size size)
//{
//    if (size == Size::None)
//        return;
//
//    auto &reg = Game::GetRegistry();
//
//    entt::entity id;
//
//    if (!TryPoolling(id))
//        id = reg.create();
//
//    Sprite *sprite = nullptr;
//    Vec2 spriteSize = {};
//    float colRadius = 0.f;
//
//    if (size == Size::L)
//    {
//        sprite = &SpriteLoader::sprBalls[0];
//        spriteSize = {260.f, 260.f};
//        colRadius = 160.f;
//    }
//    else if (size == Size::B)
//    {
//        sprite = &SpriteLoader::sprBalls[1];
//        spriteSize = {160.f, 160.f};
//        colRadius = 115.f;
//    }
//    else if (size == Size::M)
//    {
//        sprite = &SpriteLoader::sprBalls[2];
//        spriteSize = {140.f, 140.f};
//        colRadius = 65.f;
//    }
//    else if (size == Size::S)
//    {
//        sprite = &SpriteLoader::sprBalls[3];
//        spriteSize = {110.f, 110.f};
//        colRadius = 20.f;
//    }
//
//    auto &go = reg.get_or_emplace<GameObject>(id);
//    go.isActive = true;
//
//    auto &tf = reg.get_or_emplace<Transform>(id);
//    tf.position = pos;
//    tf.scale = Vec2::One();
//    tf.rotation = 0.f;
//
//    auto &rb = reg.get_or_emplace<RigidBody>(id);
//    rb.enable = true;
//    rb.velocity = {175.f * (right ? 1.f : -1.f), -200.f};
//    rb.linearDrag = 0.0f;
//
//    auto &bl = reg.get_or_emplace<Ball>(id);
//    bl.enable = true;
//    bl.rebound = 0.f;
//    bl.size = size;
//
//    auto &cc = reg.get_or_emplace<CircleCollider>(id);
//    cc.enable = true;
//    cc.radius = colRadius;
//
//    auto &sr = reg.get_or_emplace<SpriteRenderer>(id);
//    sr.enable = true;
//    sr.sprite = sprite;
//    sr.offsetPosition = Vec2::Zero();
//    sr.offsetRotation = 0.f;
//    sr.size = spriteSize;
//    sr.pivot = Vec2::One() * 0.5f;
//    sr.layer = 1;
//    sr.blend = BLEND_ALPHA;
//}
//
// bool TryPoolling(entt::entity &id)
//{
//    for (auto [entity, go, tf, rb, bl, cc] : GetView().each())
//        if (!go.isActive && bl.enable)
//        {
//            id = entity;
//            return true;
//        }
//
//    return false;
//}
