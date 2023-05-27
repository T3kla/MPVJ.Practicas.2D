#include "scene_bee.h"

#include "vec.h"

#include "game.h"
#include "render.h"

#include "sprite_loader.h"
#include "sys_bee.h"

#include "camera.h"
#include "gameobject.h"
#include "sprite_renderer.h"
#include "transform.h"

#include <entt/entt.hpp>

static entt::entity bee;
static entt::entity camera;
static entt::entity cloud;
static entt::entity level;
static entt::entity tree1;
static entt::entity tree2;

static Vec2 beePos = {0.f, 0.f};
static Vec2 beePosOld = {0.f, 0.f};

entt::entity CreateCamera(entt::registry &);
void CreateLevel(entt::registry &);
void CreateCloud(entt::registry &);
void CreateTree1(entt::registry &);
void CreateTree2(entt::registry &);

void UpdateLevel(const Vec2 &, const Vec2 &);
void UpdateCloud(const Vec2 &, const Vec2 &);
void UpdateTree1(const Vec2 &, const Vec2 &);
void UpdateTree2(const Vec2 &, const Vec2 &);

void SceneBee::LoadScene()
{
    auto &reg = Game::GetRegistry();

    Render::SetBgColor({0.55f, 0.7f, 0.9f, 0.5f});

    // Stuff
    auto pos = Vec2(200.f, 200.f);
    bee = SysBee::Instantiate(pos);
    beePos = pos;
    beePosOld = pos;

    camera = CreateCamera(reg);
    CreateCloud(reg);
    CreateLevel(reg);
    CreateTree1(reg);
    CreateTree2(reg);

    // Systems
    sysBee = new SysBee();
}

void SceneBee::UnloadScene()
{
    delete sysBee;
    delete this;
}

void SceneBee::Fixed()
{
    auto &reg = Game::GetRegistry();

    auto &beeTF = reg.get<Transform>(bee);
    beePos = beeTF.position;

    // Move Camera
    auto &camTF = reg.get<Transform>(camera);
    camTF.position.x = beeTF.position.x;

    auto beeDelta = beePos - beePosOld;
    UpdateCloud(beePos, beeDelta);
    UpdateLevel(beePos, beeDelta);
    UpdateTree1(beePos, beeDelta);
    UpdateTree2(beePos, beeDelta);

    beePosOld = beePos;
}

entt::entity CreateCamera(entt::registry &reg)
{
    auto id = reg.create();

    auto wSize = Render::GetWindowSize();

    reg.emplace<GameObject>(id, true);
    reg.emplace<Transform>(id, wSize / 2.f, Vec2::One(), 0.f);
    reg.emplace<Camera>(id, true, true, 1.f);

    return id;
}

void CreateLevel(entt::registry &reg)
{
    auto wSize = Render::GetWindowSize();

    auto id = reg.create();
    reg.emplace<GameObject>(id, true);
    reg.emplace<Transform>(id, wSize / 2.f, Vec2::One(), 0.f);
    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.sprite = &SpriteLoader::sprLevel;
    sr.size = Vec2(static_cast<float>(sr.sprite->texture->width), static_cast<float>(sr.sprite->texture->height));
    sr.layer = 4;

    level = id;
}

void CreateCloud(entt::registry &reg)
{
    auto wSize = Render::GetWindowSize();
    auto repeatRate = 3.f;

    auto id = reg.create();
    reg.emplace<GameObject>(id, true);
    reg.emplace<Transform>(id, wSize / 2.f, Vec2::One(), 0.f);
    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.sprite = &SpriteLoader::sprCloud;
    sr.size = Vec2(static_cast<float>(sr.sprite->texture->width) * repeatRate,
                   static_cast<float>(sr.sprite->texture->height)) *
              3.f;
    sr.sprite->uv1.x = repeatRate;
    sr.layer = 1;

    cloud = id;
}

void CreateTree1(entt::registry &reg)
{
    auto wSize = Render::GetWindowSize();
    auto repeatRate = 5.f;

    auto id = reg.create();
    reg.emplace<GameObject>(id, true);
    reg.emplace<Transform>(id, wSize / 2.f, Vec2::One(), 0.f);
    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.sprite = &SpriteLoader::sprTrees1;
    sr.size = Vec2(static_cast<float>(sr.sprite->texture->width) * repeatRate,
                   static_cast<float>(sr.sprite->texture->height)) *
              1.5f;
    sr.sprite->uv1.x = repeatRate;
    sr.layer = 3;

    tree1 = id;
}

void CreateTree2(entt::registry &reg)
{
    auto wSize = Render::GetWindowSize();
    auto repeatRate = 5.f;

    auto id = reg.create();
    reg.emplace<GameObject>(id, true);
    reg.emplace<Transform>(id, wSize / 2.f, Vec2::One(), 0.f);
    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.sprite = &SpriteLoader::sprTrees2;
    sr.size = Vec2(static_cast<float>(sr.sprite->texture->width) * repeatRate,
                   static_cast<float>(sr.sprite->texture->height)) ;
    sr.sprite->uv1.x = repeatRate;
    sr.layer = 2;

    tree2 = id;
}

void UpdateLevel(const Vec2 &pos, const Vec2 &beeDelta)
{
    auto &reg = Game::GetRegistry();

    auto &tf = reg.get<Transform>(level);
    auto &sr = reg.get<SpriteRenderer>(level);

    tf.position.x = pos.x;

    sr.sprite->uv0.x += beeDelta.x * static_cast<float>(STP) * 0.01f * 0.02f;
    sr.sprite->uv1.x += beeDelta.x * static_cast<float>(STP) * 0.01f * 0.02f;
}

void UpdateCloud(const Vec2 &pos, const Vec2 &beeDelta)
{
    auto &reg = Game::GetRegistry();
    
    auto &tf = reg.get<Transform>(cloud);
    auto &sr = reg.get<SpriteRenderer>(cloud);
    
    tf.position.x = pos.x;
    
    sr.sprite->uv0.x += beeDelta.x * static_cast<float>(STP) * 0.01f * 0.01f;
    sr.sprite->uv1.x += beeDelta.x * static_cast<float>(STP) * 0.01f * 0.01f;
}

void UpdateTree1(const Vec2 &pos, const Vec2 &beeDelta)
{
    auto &reg = Game::GetRegistry();

    auto &tf = reg.get<Transform>(tree1);
    auto &sr = reg.get<SpriteRenderer>(tree1);

    tf.position.x = pos.x;
    tf.position.y = 230.f;

    sr.sprite->uv0.x += beeDelta.x * static_cast<float>(STP) * 0.01f * 0.1f;
    sr.sprite->uv1.x += beeDelta.x * static_cast<float>(STP) * 0.01f * 0.1f;
}

void UpdateTree2(const Vec2 &pos, const Vec2 &beeDelta)
{
    auto &reg = Game::GetRegistry();

    auto &tf = reg.get<Transform>(tree2);
    auto &sr = reg.get<SpriteRenderer>(tree2);

    tf.position.x = pos.x;
    tf.position.y = 260.f;

    sr.sprite->uv0.x += beeDelta.x * static_cast<float>(STP) * 0.01f * 0.11f;
    sr.sprite->uv1.x += beeDelta.x * static_cast<float>(STP) * 0.01f * 0.11f;
}
