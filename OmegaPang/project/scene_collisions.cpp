#include "scene_collisions.h"

#include "glfw3.h"

#include "game.h"
#include "input.h"
#include "render.h"

#include "circle_collider.h"
#include "gameobject.h"
#include "pixel_collider.h"
#include "sprite_renderer.h"
#include "square_collider.h"
#include "transform.h"

#include "sys_physics.h"

#include "sprite_loader.h"

entt::entity CreateSqr(entt::registry &);
entt::entity CreateCrl(entt::registry &);
entt::entity CreateBox(entt::registry &);
entt::entity CreateBall(entt::registry &);
entt::entity CreateBee(entt::registry &);

void OnTriggerEnter(Collision *);
void OnTriggerStay(Collision *);
void OnTriggerExit(Collision *);

static entt::entity staticSquare;
static entt::entity staticBall;
static entt::entity staticBee;
static entt::entity mouseFigure;

static float t = 0.f;

void SceneCollisions::LoadScene()
{
    Render::SetBgColor({0.5f, 0.44f, 0.37f, 0.5f});

    auto &reg = Game::GetRegistry();

    // Props
    staticSquare = CreateBox(reg);
    staticBall = CreateBall(reg);
    staticBee = CreateBee(reg);

    // Mouse follower
    mouseFigure = CreateSqr(reg);

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

    t += (float)STP * 0.001f;

    // Move square to mouse
    if (Input::GetKey(GLFW_MOUSE_BUTTON_LEFT))
    {
        reg.destroy(mouseFigure);
        mouseFigure = CreateCrl(reg);
    }
    else if (Input::GetKey(GLFW_MOUSE_BUTTON_RIGHT))
    {
        reg.destroy(mouseFigure);
        mouseFigure = CreateSqr(reg);
    }
    else if (Input::GetKey(GLFW_MOUSE_BUTTON_MIDDLE))
    {
        reg.destroy(mouseFigure);
        mouseFigure = CreateBee(reg);
    }

    reg.get<Transform>(mouseFigure).position = Input::GetMousePos();

    // Scale stuff
    // reg.get<Transform>(staticSquare).scale = Vec2::One() * (sinf(t) / 2.f + 1.f);
    // reg.get<Transform>(staticBall).scale = Vec2::One() * (cosf(t) / 2.f + 1.f);
    // reg.get<Transform>(staticBee).scale = Vec2::One() * (sinf(t) / 2.f + 1.f);
}

entt::entity CreateSqr(entt::registry &reg)
{
    auto id = reg.create();

    auto &go = reg.emplace<GameObject>(id, true);
    auto &tf = reg.emplace<Transform>(id, Vec2(25.f, 25.f), Vec2::One(), 0.f);
    auto &sc = reg.emplace<SquareCollider>(id);
    sc.center = {0.f, 0.f};
    sc.size = {25.f, 25.f};
    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.sprite = &SpriteLoader::sprSqr;
    sr.size = {25.f, 25.f};
    sr.layer = 1;

    return id;
}

entt::entity CreateCrl(entt::registry &reg)
{
    auto id = reg.create();

    auto &go = reg.emplace<GameObject>(id, true);
    auto &tf = reg.emplace<Transform>(id, Vec2(25.f, 25.f), Vec2::One(), 0.f);
    auto &sc = reg.emplace<CircleCollider>(id);
    sc.center = {0.f, 0.f};
    sc.radius = 25.f;
    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.sprite = &SpriteLoader::sprCrl;
    sr.size = {25.f, 25.f};
    sr.layer = 1;

    return id;
}

entt::entity CreateBox(entt::registry &reg)
{
    auto id = reg.create();

    auto &go = reg.emplace<GameObject>(id, true);
    auto &tf = reg.emplace<Transform>(id, Vec2(100.f, 200.f), Vec2::One(), 0.f);
    auto &sc = reg.emplace<SquareCollider>(id);
    sc.center = {0.f, 0.f};
    sc.size = {100.f, 100.f};
    sc.OnTriggerEnter = &OnTriggerEnter;
    sc.OnTriggerStay = &OnTriggerStay;
    sc.OnTriggerExit = &OnTriggerExit;
    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.sprite = &SpriteLoader::sprBox;
    sr.size = {100.f, 100.f};
    sr.layer = 0;

    return id;
}

entt::entity CreateBall(entt::registry &reg)
{
    auto id = reg.create();

    auto &go = reg.emplace<GameObject>(id, true);
    auto &tf = reg.emplace<Transform>(id, Vec2(400.f, 200.f), Vec2::One(), 0.f);
    auto &sc = reg.emplace<CircleCollider>(id);
    sc.center = {0.f, 0.f};
    sc.radius = 100.f;
    sc.OnTriggerEnter = &OnTriggerEnter;
    sc.OnTriggerStay = &OnTriggerStay;
    sc.OnTriggerExit = &OnTriggerExit;
    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.sprite = &SpriteLoader::sprBall;
    sr.size = {100.f, 100.f};
    sr.layer = 0;

    return id;
}

entt::entity CreateBee(entt::registry &reg)
{
    auto id = reg.create();

    auto &go = reg.emplace<GameObject>(id, true);
    auto &tf = reg.emplace<Transform>(id, Vec2(700.f, 200.f), Vec2::One(), 0.f);
    auto &sc = reg.emplace<PixelCollider>(id);
    sc.OnTriggerEnter = &OnTriggerEnter;
    sc.OnTriggerStay = &OnTriggerStay;
    sc.OnTriggerExit = &OnTriggerExit;
    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.sprite = &SpriteLoader::sprBee;
    sr.size = {100.f, 100.f};
    sr.layer = 0;

    return id;
}

void OnTriggerEnter(Collision *col)
{
    auto &reg = Game::GetRegistry();
    auto *sr = reg.try_get<SpriteRenderer>(col->a.id);
    if (sr)
        sr->color = {1.f, 0.f, 0.f, 1.f};
}

void OnTriggerStay(Collision *col)
{
    auto &reg = Game::GetRegistry();
    auto *sr = reg.try_get<SpriteRenderer>(col->a.id);
    if (sr)
        sr->color = {0.f, 1.f, 0.f, 1.f};
}

void OnTriggerExit(Collision *col)
{
    auto &reg = Game::GetRegistry();
    auto *sr = reg.try_get<SpriteRenderer>(col->a.id);
    if (sr)
        sr->color = {1.f, 1.f, 1.f, 1.f};
}
