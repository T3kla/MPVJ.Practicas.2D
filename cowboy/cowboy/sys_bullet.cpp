#include "sys_bullet.h"

#include "bullet.h"
#include "engine.h"
#include "gameobject.h"
#include "player.h"
#include "rigidbody.h"
#include "sprite_loader.h"
#include "sprite_renderer.h"
#include "stasis.h"
#include "transform.h"
#include "vec.h"

#include <entt/entt.hpp>

SysBullet::SysBullet() {}
SysBullet::~SysBullet() {}

void SysBullet::Awake() {}

void SysBullet::Start() {}

void SysBullet::Update() {}

void SysBullet::Fixed() {
  auto &reg = Engine::GetRegistry();

  auto player = reg.view<Player>();
  auto &playerPos = reg.get<Transform>(player.front()).position;

  auto bullets = Engine::GetRegistry().view<Transform, GameObject, Bullet>();

  for (auto [entity, tf, go, bl] : bullets.each())
    if (Vec2::Distance(playerPos, tf.position) > 1500.f)
      go.isActive = false;
}

void SysBullet::Quit() {}

entt::entity SysBullet::InstantiateBullet() {
  auto &reg = Engine::GetRegistry();

  auto bullets = Engine::GetRegistry().view<Transform, GameObject, Bullet>();

  for (auto [entity, tf, go, bl] : bullets.each())
    if (!go.isActive) {
      go.isActive = true;
      return entity;
    }

  const auto id = reg.create();

  reg.emplace<Transform>(id, true, Vec2::Zero(), Vec2::One(), 0.f);
  reg.emplace<GameObject>(id, true, true);
  reg.emplace<Rigidbody>(id, true, Vec2::Zero(), 0.000001f);
  reg.emplace<Bullet>(id, true, 1000.f, 5);
  reg.emplace<SpriteRenderer>(id, true, &SpriteLoader::sprBullet, Vec2::Zero(),
                              -90.f, Vec2::One() * 100.f, Vec2::One() * 0.5f, 1,
                              BLEND_ALPHA);

  return id;
}
