#include "scene_collisions.h"

#include "game.h"
#include "input.h"
#include "render.h"

#include "circle_collider.h"
#include "gameobject.h"
#include "pixel_collider.h"
#include "sprite_renderer.h"
#include "square_collider.h"
#include "transform.h"

#include "collision.h"

#include "sys_physics.h"

#include "sprite_loader.h"

entt::entity CreateSqr(entt::registry &reg);
void Lol(Collision *a);

static entt::entity staticSquare;
static entt::entity mouseSquare;

void SceneCollisions::LoadScene()
{
    Render::SetBgColor({0.5f, 0.44f, 0.37f, 0.5f});

    auto &reg = Game::GetRegistry();

    // Props
    staticSquare = CreateSqr(reg);
    mouseSquare = CreateSqr(reg);

    // Systems
    sysPhysics = new SysPhysics();
}

void SceneCollisions::UnloadScene()
{
    delete sysPhysics;
    delete this;
}

void SceneCollisions::Fixed()
{
    auto &reg = Game::GetRegistry();

    reg.get<Transform>(mouseSquare).position = Input::GetMousePos();
}

entt::entity CreateSqr(entt::registry &reg)
{
    auto id = reg.create();

    auto &go = reg.emplace<GameObject>(id, true);
    auto &tf = reg.emplace<Transform>(id, Vec2(100.f, 100.f), Vec2::One(), 0.f);
    auto &sc = reg.emplace<SquareCollider>(id);
    sc.center = {0.f, 0.f};
    sc.size = {100.f, 100.f};
    sc.OnCollision = Lol;
    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.sprite = &SpriteLoader::sprBox;
    sr.size = {100.f, 100.f};
    sr.layer = 0;

    return id;
}

void Lol(Collision *a)
{
    auto &reg = Game::GetRegistry();
    auto *sr = reg.try_get<SpriteRenderer>(a->colliderSelf);
    if (sr)
        sr->color = {1.f, 0.f, 0.f, 1.f};
}
