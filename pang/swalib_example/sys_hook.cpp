#include "sys_hook.h"

#include "sys.h"

#include "ball.h"
#include "circle_collider.h"
#include "engine.h"
#include "engine_game.h"
#include "entity.h"
#include "gameobject.h"
#include "hook.h"
#include "inputs.h"
#include "player.h"
#include "rigidbody.h"
#include "scene_01.h"
#include "sprite_animation.h"
#include "sprite_loader.h"
#include "sprite_renderer.h"
#include "square_collider.h"
#include "sys_balls.h"
#include "sys_explosions.h"
#include "transform.h"

Entity *GetHook();
bool IsColliding(Vec2 circlePos, float circleRad, Vec2 sqrPos, Vec2 sqrSize);
float Clamp(float value, float min, float max);

SysHook::SysHook() { EngineGame::Subscribe(this); }

SysHook::~SysHook() { EngineGame::UnSubscribe(this); }

void SysHook::Awake() {}

void SysHook::Start() {}

void SysHook::Update() {}

void SysHook::Fixed() {
  auto &reg = Scene_01::GetRegistry();

  // Travel
  for (auto &hook : reg) {
    auto *tf = hook->GetComponent<Transform>();
    auto *go = hook->GetComponent<GameObject>();
    auto *hk = hook->GetComponent<Hook>();
    auto *sc = hook->GetComponent<SquareCollider>();

    if (!tf || !hk || !go->isActive)
      continue;

    tf->position += Vec2::Up() * hk->speed * (float)STP * 0.001f;
    if (tf->position.y > SCR_HEIGHT - 50)
      go->isActive = false;

    // Collisions
    for (auto &ball : reg) {
      auto *btf = ball->GetComponent<Transform>();
      auto *bgo = ball->GetComponent<GameObject>();
      auto *brb = ball->GetComponent<RigidBody>();
      auto *bbl = ball->GetComponent<Ball>();
      auto *bcl = ball->GetComponent<CircleCollider>();

      if (!btf || !bgo || !brb || !bbl || !bcl || !bgo->isActive)
        continue;

      if (IsColliding(btf->position, bcl->radius, tf->position + sc->center,
                      sc->size)) {
        go->isActive = false;
        bgo->isActive = false;
        auto size = bbl->size;
        SysBalls::InstantiateSmaller(btf->position, true, size);
        SysBalls::InstantiateSmaller(btf->position, false, size);
        SysExplosions::InstantiateSmaller(btf->position, size);
        return;
      }
    }
  }
}

void SysHook::Quit() {}

void SysHook::InstantiateHook(const Vec2 &pos) {
  auto *hook = GetHook();

  if (!hook)
    return;

  auto *tf = hook->GetComponent<Transform>();
  auto *go = hook->GetComponent<GameObject>();
  auto *hk = hook->GetComponent<Hook>();
  auto *sc = hook->GetComponent<SquareCollider>();
  auto *sr = hook->GetComponent<SpriteRenderer>();
  auto *sa = hook->GetComponent<SpriteAnimation>();

  tf->position = pos;

  go->isActive = true;

  hk->speed = -1000.f;

  sc->center = {0.f, -420.f};
  sc->size = {35.f, 950.f};

  sr->sprite = &SpriteLoader::sprHook[0];
  sr->offsetPosition = {0.f, -420.f};
  sr->offsetRotation = 0.f;
  sr->size = {100.f, 1000.f};
  sr->pivot = {0.5f, 0.5f};
  sr->layer = 5;

  sa->animation = &SpriteLoader::sprHook;
  sa->duration = 0.2f;
  sa->count = 0.f;
  sa->frame = 0;
  sa->enable = true;
}

Entity *GetHook() {
  auto &reg = Scene_01::GetRegistry();

  // Pooling
  for (auto &i : reg) {
    auto *gaob = i->GetComponent<GameObject>();
    auto *hook = i->GetComponent<Hook>();

    if (gaob && hook && !gaob->isActive)
      return i;
  }

  // Instantiation
  auto hook = new Entity();

  auto tf = Transform();
  auto go = GameObject();
  auto hk = Hook();
  auto sc = SquareCollider();
  auto sr = SpriteRenderer();
  auto sa = SpriteAnimation();

  hook->AddComponent<Transform>(&tf);
  hook->AddComponent<GameObject>(&go);
  hook->AddComponent<Hook>(&hk);
  hook->AddComponent<SquareCollider>(&sc);
  hook->AddComponent<SpriteRenderer>(&sr);
  hook->AddComponent<SpriteAnimation>(&sa);

  reg.push_back(hook);
  return hook;
}

bool IsColliding(Vec2 circlePos, float circleRad, Vec2 sqrPos, Vec2 sqrSize) {
  Vec2 point = {0.f, 0.f};

  auto maxX = sqrPos.x + sqrSize.x / 2.f;
  auto minX = sqrPos.x - sqrSize.x / 2.f;

  auto maxY = sqrPos.y + sqrSize.y / 2.f;
  auto minY = sqrPos.y - sqrSize.y / 2.f;

  point.x = Clamp(circlePos.x - sqrPos.x + sqrPos.x, minX, maxX);
  point.y = Clamp(circlePos.y - sqrPos.y + sqrPos.y, minY, maxY);

  auto distance = (point - circlePos).Magnitude();

  return distance < circleRad / 2.f;
}

float Clamp(float value, float min, float max) {
  return std::max(min, std::min(max, value));
}
