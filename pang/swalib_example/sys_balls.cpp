#include "sys_balls.h"

#include "ball.h"
#include "circle_collider.h"
#include "entity.h"
#include "game.h"
#include "gameobject.h"
#include "inputs.h"
#include "logic.h"
#include "render.h"
#include "rigidbody.h"
#include "scene_01.h"
#include "sizes.h"
#include "sprite_animation.h"
#include "sprite_loader.h"
#include "sprite_renderer.h"
#include "stasis.h"
#include "sys_hook.h"
#include "transform.h"

#include <entt/entt.hpp>

Entity *TryPoolling();
float ReboundPerSize(char size);

SysBalls::SysBalls()
{
    Logic::Subscribe(this);
}

SysBalls::~SysBalls()
{
    Logic::UnSubscribe(this);
}

void SysBalls::Awake()
{
}

void SysBalls::Start()
{
}

void SysBalls::Update()
{
}

void SysBalls::Fixed()
{
    auto &reg = Scene_01::GetRegistry();

    for (auto &i : reg)
    {
        auto *tf = i->GetComponent<Transform>();
        auto *go = i->GetComponent<GameObject>();
        auto *rb = i->GetComponent<RigidBody>();
        auto *bl = i->GetComponent<Ball>();
        auto *cl = i->GetComponent<CircleCollider>();

        if (!tf || !go || !rb || !bl || !cl || !go->isActive)
            continue;

        // Gravity
        rb->velocity += Vec2::Down() * 600.f * (float)STP * 0.001f;

        // Rebound
        int width, height;
        Render::GetWindowSize(width, height);
        if (tf->position.x > width - cl->radius / 2.f)
        {
            tf->position.x = width - cl->radius / 2.f - 1.f;
            rb->velocity.x *= -1.f;
        }
        if (tf->position.x < cl->radius / 2.f)
        {
            tf->position.x = cl->radius / 2.f + 1.f;
            rb->velocity.x *= -1.f;
        }
        if (tf->position.y < cl->radius / 2.f)
        {
            tf->position.y = cl->radius / 2.f + 1.f;
            rb->velocity.y = ReboundPerSize(bl->size) * 1.2f;
        }
    }
}

void SysBalls::Quit()
{
}

void SysBalls::InstantiateSmaller(const Vec2 &pos, bool right, Size size)
{
    auto next = size.OneSmaller();
    if (next == 'X')
        return;
    Instantiate(pos, right, next);
}

void Instantiate(const Vec2 &pos, bool right, Size size)
{
    auto &reg = Game::GetRegistry();

    entt::entity id;

    if (!TryPoolling(id))
        id = reg.create();

    reg.get_or_emplace<GameObject>(id, true);
    reg.get_or_emplace<Transform>(id, pos, Vec2::One(), 0.f);
    reg.get_or_emplace<RigidBody>(id, true, Vec2(175.f * (right ? 1.f : -1.f), 200.f), 0.0f);
    reg.get_or_emplace<Ball>(id, true, Vec2::Zero(), size);
    reg.get_or_emplace<CircleCollider>(id, true, 100.f);
    reg.get_or_emplace<SpriteRenderer>(id, true, &SpriteLoader::sprBalls[0], Vec2::Zero(), 0.f, Vec2::One() * 100.f,
                                       Vec2::One() * 0.5f, 1, BLEND_ALPHA);

    if (size == Size::L)
    {
        sr->sprite = &SpriteLoader::sprBalls[0];
        sr->size = {260.f, 260.f};
        cl->radius = 160.f;
    }
    else if (size == Size::B)
    {
        sr->sprite = &SpriteLoader::sprBalls[1];
        sr->size = {160.f, 160.f};
        cl->radius = 115.f;
    }
    else if (size == Size::M)
    {
        sr->sprite = &SpriteLoader::sprBalls[2];
        sr->size = {140.f, 140.f};
        cl->radius = 65.f;
    }
    else if (size == Size::S)
    {
        sr->sprite = &SpriteLoader::sprBalls[3];
        sr->size = {110.f, 110.f};
        cl->radius = 20.f;
    }

    return ball;
}

bool TryPoolling(entt::entity &id)
{
    auto &reg = Game::GetRegistry();
    auto balls = reg.view<GameObject, Transform, Ball>();

    // Pooling
    for (auto [entity, go, tf, bl] : balls.each())
        if (!go.isActive && bl.enable)
        {
            id = entity;
            return true;
        }

    return false;
}

float ReboundPerSize(char size)
{
    switch (size)
    {
    case 'L':
        return 650.f;
    case 'B':
        return 550.f;
    case 'M':
        return 450.f;
    case 'S':
        return 350.f;
    default:
        return 100.f;
    }
}
