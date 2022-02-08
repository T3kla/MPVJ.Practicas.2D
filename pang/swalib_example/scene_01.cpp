#include "scene_01.h"

#include "engine_game.h"
#include "sys_balls.h"
#include "sys_explosions.h"
#include "sys_hook.h"
#include "sys_physics.h"
#include "sys_player.h"

#include "vec.h"

#include "entity.h"

std::vector<Entity *> Scene_01::reg;

Scene_01 Scene_01::instance;
Scene_01::Scene_01() {}

void Scene_01::Load() { EngineGame::Subscribe(&instance); }

std::vector<Entity *> &Scene_01::GetRegistry() { return reg; }

void Scene_01::Awake() {}

void Scene_01::Start() {

  SysBalls::InstantiateL({300.f, 500.f}, true);
  SysBalls::InstantiateB({600.f, 500.f}, true);
  SysBalls::InstantiateM({800.f, 500.f}, true);
  SysBalls::InstantiateS({1000.f, 500.f}, true);

  // Systems
  new SysPlayer();
  new SysPhysics();
  new SysHook();
  new SysBalls();
  new SysExplosions();
}

void Scene_01::Update() {}

void Scene_01::Fixed() {}

void Scene_01::Quit() {
  for (auto &entity : reg)
    entity->RemoveAllComponents();

  reg.clear();

  EngineGame::UnSubscribe(this);
}
