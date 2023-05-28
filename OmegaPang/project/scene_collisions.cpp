#include "scene_collisions.h"

#include "glfw3.h"

#include "game.h"
#include "input.h"
#include "render.h"

#include "circle_collider.h"
#include "gameobject.h"
#include "pixel_collider.h"
#include "rigidbody.h"
#include "sprite_renderer.h"
#include "square_collider.h"
#include "transform.h"

#include "sys_physics.h"

#include "sprite_loader.h"

entt::entity CreateSqrMouse(entt::registry &);
entt::entity CreateCrlMouse(entt::registry &);
entt::entity CreateBeeMouse(entt::registry &);

entt::entity CreateSqrProp(entt::registry &);
entt::entity CreateBallProp(entt::registry &);
entt::entity CreateBeeProp(entt::registry &);

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
    Render::SetOrigin({0.0f, 0.0f});

    auto &reg = Game::GetRegistry();

    // Props
    staticSquare = CreateSqrProp(reg);
    staticBall = CreateBallProp(reg);
    staticBee = CreateBeeProp(reg);

    // Mouse follower
    mouseFigure = CreateSqrMouse(reg);

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

    t += static_cast<float>(STP) * 0.001f;

    // Move square to mouse
    if (Input::GetKey(GLFW_MOUSE_BUTTON_LEFT))
    {
        reg.destroy(mouseFigure);
        mouseFigure = CreateCrlMouse(reg);
    }
    else if (Input::GetKey(GLFW_MOUSE_BUTTON_RIGHT))
    {
        reg.destroy(mouseFigure);
        mouseFigure = CreateSqrMouse(reg);
    }
    else if (Input::GetKey(GLFW_MOUSE_BUTTON_MIDDLE))
    {
        reg.destroy(mouseFigure);
        mouseFigure = CreateBeeMouse(reg);
    }

    reg.get<Transform>(mouseFigure).position = Input::GetMousePos();

    // Scale stuff
    reg.get<Transform>(staticSquare).scale = Vec2::One() * (sinf(t) / 2.f + 1.f);
    reg.get<Transform>(staticBall).scale = Vec2::One() * (cosf(t) / 2.f + 1.f);
    reg.get<Transform>(staticBee).scale = Vec2::One() * (sinf(t) / 2.f + 1.f);
}

entt::entity CreateSqrMouse(entt::registry &reg)
{
    auto id = reg.create();

    reg.emplace<GameObject>(id, true);
    reg.emplace<Transform>(id, Vec2(25.f, 25.f), Vec2::One(), 0.f);

    auto &rb = reg.get_or_emplace<RigidBody>(id);
    rb.velocity = Vec2::Zero();

    auto &sc = reg.emplace<SquareCollider>(id);
    sc.center = {0.f, 0.f};
    sc.size = {25.f, 25.f};

    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.sprite = &SpriteLoader::sprSqr;
    sr.size = {25.f, 25.f};
    sr.layer = 1;

    return id;
}

entt::entity CreateCrlMouse(entt::registry &reg)
{
    auto id = reg.create();

    reg.emplace<GameObject>(id, true);
    reg.emplace<Transform>(id, Vec2(25.f, 25.f), Vec2::One(), 0.f);

	auto &rb = reg.get_or_emplace<RigidBody>(id);
    rb.velocity = Vec2::Zero();

    auto &sc = reg.emplace<CircleCollider>(id);
    sc.center = {0.f, 0.f};
    sc.radius = 25.f;

    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.sprite = &SpriteLoader::sprCrl;
    sr.size = {25.f, 25.f};
    sr.layer = 1;

    return id;
}

entt::entity CreateBeeMouse(entt::registry &reg)
{
    auto id = reg.create();

    reg.emplace<GameObject>(id, true);
    reg.emplace<Transform>(id, Vec2(800.f, 300.f), Vec2::One(), 0.f);

	auto &rb = reg.get_or_emplace<RigidBody>(id);
    rb.velocity = Vec2::Zero();

    auto &pc = reg.emplace<PixelCollider>(id);
    pc.OnTriggerEnter = OnTriggerEnter;
    pc.OnTriggerStay = OnTriggerStay;
    pc.OnTriggerExit = OnTriggerExit;

    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.sprite = &SpriteLoader::sprBee;
    sr.size = {200.f, 200.f};
    sr.layer = 0;

    return id;
}

entt::entity CreateSqrProp(entt::registry &reg)
{
    auto id = reg.create();

    reg.emplace<GameObject>(id, true);
    reg.emplace<Transform>(id, Vec2(200.f, 300.f), Vec2::One(), 0.f);

    auto &sc = reg.emplace<SquareCollider>(id);
    sc.center = {0.f, 0.f};
    sc.size = {100.f, 100.f};
    sc.isTrigger = true;
    sc.OnTriggerEnter = OnTriggerEnter;
    sc.OnTriggerStay = OnTriggerStay;
    sc.OnTriggerExit = OnTriggerExit;

    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.sprite = &SpriteLoader::sprBox;
    sr.size = {100.f, 100.f};
    sr.layer = 0;

    return id;
}

entt::entity CreateBallProp(entt::registry &reg)
{
    auto id = reg.create();

    reg.emplace<GameObject>(id, true);
    reg.emplace<Transform>(id, Vec2(500.f, 300.f), Vec2::One(), 0.f);

    auto &cc = reg.emplace<CircleCollider>(id);
    cc.center = {0.f, 0.f};
    cc.radius = 100.f;
    cc.isTrigger = true;
    cc.OnTriggerEnter = OnTriggerEnter;
    cc.OnTriggerStay = OnTriggerStay;
    cc.OnTriggerExit = OnTriggerExit;

    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.sprite = &SpriteLoader::sprBall;
    sr.size = {100.f, 100.f};
    sr.layer = 0;

    return id;
}

entt::entity CreateBeeProp(entt::registry &reg)
{
    auto id = reg.create();

    reg.emplace<GameObject>(id, true);
    reg.emplace<Transform>(id, Vec2(800.f, 300.f), Vec2::One(), 0.f);

    auto &pc = reg.emplace<PixelCollider>(id);
    pc.isTrigger = true;
    pc.OnTriggerEnter = OnTriggerEnter;
    pc.OnTriggerStay = OnTriggerStay;
    pc.OnTriggerExit = OnTriggerExit;

    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.sprite = &SpriteLoader::sprBee;
    sr.size = {200.f, 200.f};
    sr.layer = 0;

    return id;
}

void OnTriggerEnter(Collision *col)
{
    auto &reg = Game::GetRegistry();

    if (auto *sr = reg.try_get<SpriteRenderer>(col->a.id))
        sr->color = {1.f, 0.f, 0.f, 1.f};
}

void OnTriggerStay(Collision *col)
{
    auto &reg = Game::GetRegistry();

    if (auto *sr = reg.try_get<SpriteRenderer>(col->a.id))
        sr->color = {0.f, 1.f, 0.f, 1.f};
}

void OnTriggerExit(Collision *col)
{
    auto &reg = Game::GetRegistry();

    if (auto *sr = reg.try_get<SpriteRenderer>(col->a.id))
        sr->color = {1.f, 1.f, 1.f, 1.f};
}
