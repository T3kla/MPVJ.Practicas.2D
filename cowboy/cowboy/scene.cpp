#include "scene.h"

#include "engine.h"
#include "engine_game.h"
#include "engine_input.h"
#include "engine_render.h"
#include "sprite_loader.h"
#include "stasis.h"

#include "bullet.h"
#include "camera.h"
#include "enemy.h"
#include "gameobject.h"
#include "oval_renderer.h"
#include "player.h"
#include "rect_renderer.h"
#include "rigidbody.h"
#include "sprite_renderer.h"
#include "transform.h"

#include "sys_bullet.h"
#include "sys_enemy.h"
#include "sys_physics.h"
#include "sys_player.h"

#include <chrono>
#include <random>

#include "vec.h"

#include <entt/entt.hpp>

using RandRangeInt = std::uniform_int_distribution<int>;
using RandEngine = std::default_random_engine;

constexpr float FLOORSIZE = 500.f;

Scene::Scene() {}
Scene::~Scene() {}

void Scene::Awake() {
  EngineRender::SetTitle(title);

  InstantiateFloor();
  SysPlayer::InstantiatePlayer();

  new SysPlayer();
  new SysPhysics();
  new SysBullet();
  new SysEnemy();
}

void Scene::Start() {}

void Scene::Update() {}

void Scene::Fixed() {}

void Scene::Quit() {}

void Scene::InstantiateFloor() {
  auto &reg = Engine::GetRegistry();

  auto now = std::chrono::system_clock::now();
  RandEngine rand((unsigned int)now.time_since_epoch().count());
  RandRangeInt randTx(0, 4);

  for (int x = -1; x <= 1; x++)
    for (int y = -1; y <= 1; y++) {

      const auto id = reg.create();

      Vec2 size = Vec2(FLOORSIZE, FLOORSIZE);
      Vec2 pos = Vec2(FLOORSIZE * x * 1.01f, FLOORSIZE * y * 1.01f);

      Sprite *tx;
      int random = randTx(rand);

      if (random == 0)
        tx = &SpriteLoader::sprFloor01;
      else if (random == 1)
        tx = &SpriteLoader::sprFloor02;
      else if (random == 2)
        tx = &SpriteLoader::sprFloor03;
      else if (random == 3)
        tx = &SpriteLoader::sprFloor04;

      reg.emplace<Transform>(id, true, pos, Vec2::One(), 0.f);
      reg.emplace<GameObject>(id, true, true);
      reg.emplace<SpriteRenderer>(id, true, tx, Vec2::Zero(), 0.f, size,
                                  Vec2(0.5f, 0.5f), 0, BLEND_SOLID);
    }
}
