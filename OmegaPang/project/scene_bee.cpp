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
#include <vector>

static entt::entity bee;
static entt::entity camera;
static std::vector<entt::entity> clouds;
static std::vector<entt::entity> levels;

static Vec2 beePos = {0.f, 0.f};
static Vec2 beePosOld = {0.f, 0.f};

entt::entity CreateCamera(entt::registry &);
void CreateLevels(entt::registry &);
void CreateTree1s(entt::registry &);
void CreateTree2s(entt::registry &);
void CreateClouds(entt::registry &);

void UpdateLevels(Vec2, Vec2);
void UpdateClouds(Vec2, Vec2);

void SceneBee::LoadScene()
{
    auto &reg = Game::GetRegistry();

    Render::SetBgColor({0.55f, 0.7f, 0.9f, 0.5f});

    // Buffer size
    clouds.reserve(10);

    // Stuff
    auto pos = Vec2(200.f, 200.f);
    bee = SysBee::Instantiate(pos);
    beePos = pos;
    beePosOld = pos;

    camera = CreateCamera(reg);
    CreateLevels(reg);
    CreateClouds(reg);

    // Systems
    sysBee = new SysBee();
}

void SceneBee::UnloadScene()
{
    delete sysBee;
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
    UpdateClouds(beePos, beeDelta);

    beePos = beePos;
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

void CreateLevels(entt::registry &reg)
{
    const auto Spawn = [&]() {
        auto id = reg.create();
        auto wSize = Render::GetWindowSize();
        auto &go = reg.emplace<GameObject>(id, true);
        auto &tf = reg.emplace<Transform>(id, wSize / 2.f, Vec2::One(), 0.f);
        auto &sr = reg.emplace<SpriteRenderer>(id);
        sr.sprite = &SpriteLoader::sprLevel;
        sr.size = {(float)sr.sprite->texture->width, (float)sr.sprite->texture->height};
        sr.layer = 5;
        return id;
    };
}

void CreateClouds(entt::registry &reg)
{
    auto id = reg.create();

    auto wSize = Render::GetWindowSize();

    auto &go = reg.emplace<GameObject>(id, true);
    auto &tf = reg.emplace<Transform>(id, wSize / 2.f, Vec2::One(), 0.f);
    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.sprite = &SpriteLoader::sprCloud;
    sr.size = Vec2((float)sr.sprite->texture->width, (float)sr.sprite->texture->height) * 3.f;
    sr.layer = 4;

    return id;
}

void UpdateLevels(Vec2 beePos, Vec2 beeDelta)
{
    auto &reg = Game::GetRegistry();
    auto view = reg.view<GameObject, Transform>();
}

void UpdateClouds(Vec2 beePos, Vec2 beeDelta)
{
    auto &reg = Game::GetRegistry();
    auto view = reg.view<GameObject, Transform>();

    for (auto &&cloud : clouds)
    {
        reg.get<Transform>(cloud).position.x = beeDelta.x * -0.6f;

        // if(cloud too far)
        //      move to cloud.size * cloud.sprite.width * signo de beeDelta
    }
}
