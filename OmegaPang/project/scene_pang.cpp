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
    // Instantiate balls
    SysBalls::Instantiate({300.f, 200.f}, true, Size::L);
    SysBalls::Instantiate({600.f, 200.f}, true, Size::B);
    SysBalls::Instantiate({800.f, 200.f}, true, Size::M);
    SysBalls::Instantiate({1000.f, 200.f}, true, Size::S);

    // BG
    auto &reg = Game::GetRegistry();
    auto id = reg.create();

    int w, h;
    Render::GetWindowSize(w, h);

    auto &go = reg.emplace<GameObject>(id);
    go.isActive = true;

    auto &tf = reg.emplace<Transform>(id);
    tf.position = {w / 2.f, h / 2.f};
    tf.scale = Vec2::One();
    tf.rotation = 0.f;

    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.enable = true;
    sr.sprite = &SpriteLoader::sprBg;
    sr.offsetPosition = Vec2::Zero();
    sr.offsetRotation = 0.f;
    sr.size = {(float)w, (float)h};
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
