#include "sys_enemy.h"

#include "bullet.h"
#include "enemy.h"
#include "engine.h"
#include "engine_game.h"
#include "engine_input.h"
#include "entity.h"
#include "gameobject.h"
#include "rigidbody.h"
#include "sprite_loader.h"
#include "sprite_renderer.h"
#include "stasis.h"
#include "sys_player.h"
#include "transform.h"
#include "vec.h"

#include <chrono>
#include <random>

using RandRangeFloat = std::uniform_real_distribution<float>;
using RandEngine = std::default_random_engine;

static float spawnCD = 1.f;
static double spawnCDcurrent = 1.f;
static float spawnDistance = 500.f;
static int enemyHealth = 5;

SysEnemy::SysEnemy() {}
SysEnemy::~SysEnemy() {}

void SysEnemy::Awake() {}

void SysEnemy::Start() {}

void SysEnemy::Update() { spawnCDcurrent -= Stasis::GetDeltaScaled() * 0.001f; }

void SysEnemy::Fixed() {
  auto &reg = Engine::GetRegistry();

  auto playerID = SysPlayer::GetPlayer();
  auto &playerTF = reg.get<Transform>(playerID);
  auto enemies =
      Engine::GetRegistry().view<Transform, GameObject, Rigidbody, Enemy>();
  auto bullets = Engine::GetRegistry().view<Transform, GameObject, Bullet>();

  for (auto [entity, tf, go, rb, en] : enemies.each()) {
    // Move towards player
    Vec2 vel = rb.velocity;
    Vec2 add = {0.f, 0.f};

    auto dir = playerTF.position - tf.position;

    vel += (dir.Normalized() * en.maxSpeed);
    vel = vel.Magnitude() < en.maxSpeed ? vel : vel.Normalized() * en.maxSpeed;
    rb.velocity = vel;

    // Die
    for (auto [entity, tf0, go0, bl0] : bullets.each()) {
      auto dis = Vec2::Distance(tf.position, tf0.position);
      if (dis < 30.f) {
        go0.isActive = false;
        go.isActive = false;
      }
    }
  }

  // Spawn enemy
  if (spawnCDcurrent < 0.f) {

    auto now = std::chrono::system_clock::now();
    RandEngine rand((unsigned int)now.time_since_epoch().count());
    RandRangeFloat randPos(-1.f, 1.f);

    auto p = Vec2(randPos(rand), randPos(rand)).Normalized() * spawnDistance +
             playerTF.position;
    auto id = InstantiateEnemy();

    reg.get<Transform>(id).position = p;
    reg.get<Enemy>(id).health = enemyHealth;

    spawnCDcurrent = spawnCD;
  }
}

void SysEnemy::Quit() {}

entt::entity SysEnemy::InstantiateEnemy() {
  auto &reg = Engine::GetRegistry();

  auto enemies = Engine::GetRegistry().view<Transform, GameObject, Enemy>();

  for (auto [entity, tf, go, bl] : enemies.each())
    if (!go.isActive) {
      go.isActive = true;
      return entity;
    }

  const auto id = reg.create();

  reg.emplace<Transform>(id, true, Vec2::Zero(), Vec2::One(), 0.f);
  reg.emplace<GameObject>(id, true, true);
  reg.emplace<Rigidbody>(id, true, Vec2::Zero(), 0.1f);
  reg.emplace<Enemy>(id, true, 5, 10, 200.f);
  reg.emplace<SpriteRenderer>(id, true, &SpriteLoader::sprEnemy, Vec2::Zero(),
                              -90.f, Vec2::One() * 100.f, Vec2::One() * 0.5f, 1,
                              BLEND_ALPHA);

  return id;
}
