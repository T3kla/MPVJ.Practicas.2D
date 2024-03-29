#include "scene_pang.h"

#include "game.h"
#include "render.h"
#include "sprite_loader.h"

#include "gameobject.h"
#include "sprite_renderer.h"
#include "transform.h"

#include "sys_balls.h"
#include "sys_explosions.h"
#include "sys_hook.h"
#include "sys_physics.h"
#include "sys_player.h"
#include "vec.h"

void ScenePang::LoadScene()
{
    Render::SetOrigin({0.f, 0.f});

    // Instantiate balls
    SysBalls::Instantiate({300.f, 200.f}, true, Size::L);
    SysBalls::Instantiate({600.f, 200.f}, true, Size::B);
    SysBalls::Instantiate({800.f, 200.f}, true, Size::M);
    SysBalls::Instantiate({1000.f, 200.f}, true, Size::S);

    // BG
    auto &reg = Game::GetRegistry();
    auto id = reg.create();
    auto wSize = Render::GetWindowSize();
    reg.emplace<GameObject>(id, true);
    reg.emplace<Transform>(id, Vec2(static_cast<float>(wSize.x) / 2.f, static_cast<float>(wSize.y) / 2.f), Vec2::One(),
                           0.f);
    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.enable = true;
    sr.sprite = &SpriteLoader::sprBg;
    sr.offsetPosition = Vec2::Zero();
    sr.offsetRotation = 0.f;
    sr.size = {static_cast<float>(wSize.x), static_cast<float>(wSize.y)};
    sr.pivot = Vec2::One() * 0.5f;
    sr.layer = 0;
    sr.blend = BLEND_SOLID;

    // Systems
    sysPlayer = new SysPlayer();
    sysPhysics = new SysPhysics();
    sysHook = new SysHook();
    sysBalls = new SysBalls();
    sysExplosions = new SysExplosions();
}

void ScenePang::UnloadScene()
{
    delete sysPlayer;
    delete sysPhysics;
    delete sysHook;
    delete sysBalls;
    delete sysExplosions;
}
