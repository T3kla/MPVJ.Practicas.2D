#include "sys_player.h"

#include "bullet.h"
#include "camera.h"
#include "engine.h"
#include "engine_game.h"
#include "engine_input.h"
#include "entity.h"
#include "gameobject.h"
#include "player.h"
#include "rigidbody.h"
#include "sprite_loader.h"
#include "sprite_renderer.h"
#include "stasis.h"
#include "sys_bullet.h"
#include "transform.h"
#include "vec.h"

#include "scene.h"

static entt::entity playerID = {};
static Transform *tf = nullptr;
static Rigidbody *rb = nullptr;
static Player *pl = nullptr;
static double shootCoolDown = 0.f;

bool SearchForPlayer() {
  auto &reg = Engine::GetRegistry();

  playerID = reg.view<Player>().front();

  tf = &reg.get<Transform>(playerID);
  rb = &reg.get<Rigidbody>(playerID);
  pl = &reg.get<Player>(playerID);

  return pl != 0 ? true : false;
}

SysPlayer::SysPlayer() {}
SysPlayer::~SysPlayer() {}

void SysPlayer::Awake() {}

void SysPlayer::Start() {}

void SysPlayer::Update() {
  if (!SearchForPlayer())
    return;

  // Look towards mouse
  auto ang = (EngineInput::GetMousePosInWorld() - tf->position).AngleDeg();
  tf->rotation = ang;

  // Shooting
  shootCoolDown -= Stasis::GetDeltaScaled() * 0.001f;
  if (shootCoolDown < 0.f && EngineInput::GetKey(EngineInput::KeyCode::Left)) {
    for (int i = -3; i <= 3; i++) {
      auto id = SysBullet::InstantiateBullet();

      auto &reg = Engine::GetRegistry();

      auto speed = reg.get<Bullet>(id).speed;
      reg.get<Transform>(id).position = tf->position;
      reg.get<Rigidbody>(id).velocity =
          Vec2::AngleToVector(tf->rotation + 90 + 4 * i) * speed;

      shootCoolDown = pl->shootCD;
    }
  }
}

void SysPlayer::Fixed() {
  if (!SearchForPlayer())
    return;

  // Movement
  Vec2 vel = rb->velocity;
  Vec2 add = {0.f, 0.f};
  float max = pl->maxSpeed;
  float acc = pl->acceleration;

  if (EngineInput::GetKey(EngineInput::KeyCode::W))
    add.y--;
  if (EngineInput::GetKey(EngineInput::KeyCode::S))
    add.y++;
  if (EngineInput::GetKey(EngineInput::KeyCode::A))
    add.x--;
  if (EngineInput::GetKey(EngineInput::KeyCode::D))
    add.x++;

  vel += (add.Normalized() * max) * acc;
  vel = vel.Magnitude() < max ? vel : vel.Normalized() * max;
  rb->velocity = vel;
}

void SysPlayer::Quit() {}

entt::entity SysPlayer::GetPlayer() {
  SearchForPlayer();
  return playerID;
}

entt::entity SysPlayer::InstantiatePlayer() {
  auto &reg = Engine::GetRegistry();

  const auto id = reg.create();

  reg.emplace<Transform>(id, true, Vec2::Zero(), Vec2::One(), 0.f);
  reg.emplace<GameObject>(id, true, true);
  reg.emplace<Rigidbody>(id, true, Vec2::Zero(), 0.1f);
  reg.emplace<Player>(id, true, 20, 400.f, 0.1f, 0.25f);
  reg.emplace<SpriteRenderer>(id, true, &SpriteLoader::sprPlayer,
                              Vec2(0.f, 0.f), -90.f, Vec2(100.f, 100.f),
                              Vec2(0.5f, 0.5f), 1, BLEND_ALPHA);
  reg.emplace<Camera>(id, true, true, 1.f);

  return id;
}
