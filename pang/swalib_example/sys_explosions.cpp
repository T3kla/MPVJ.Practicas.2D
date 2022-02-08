#include "sys_explosions.h"

#include "sys.h"

#include "engine.h"
#include "engine_game.h"
#include "inputs.h"
#include "scene_01.h"
#include "sprite_loader.h"
#include "stasis.h"
#include "sys_hook.h"

#include "entity.h"

#include "ball.h"
#include "circle_collider.h"
#include "explosion.h"
#include "gameobject.h"
#include "rigidbody.h"
#include "sprite_animation.h"
#include "sprite_renderer.h"
#include "transform.h"

Entity *SetExplosion(const Vec2 &pos, char size);
Entity *GetExplosion();
float ReboundPerSize(char size);
char Smaller(char size);

SysExplosions::SysExplosions() { EngineGame::Subscribe(this); }

SysExplosions::~SysExplosions() { EngineGame::UnSubscribe(this); }

void SysExplosions::Awake() {}

void SysExplosions::Start() {}

void SysExplosions::Update() {}

void SysExplosions::Fixed() {
  auto &reg = Scene_01::GetRegistry();

  for (auto &i : reg) {
    auto *go = i->GetComponent<GameObject>();
    auto *ex = i->GetComponent<Explosion>();

    if (!go || !ex || !go->isActive)
      continue;

    if (ex->lifespan > 0.f)
      ex->lifespan -= (float)STP * 0.001f;
    else
      go->isActive = false;
  }
}

void SysExplosions::Quit() {}

void SysExplosions::InstantiateSmaller(const Vec2 &pos, char size) {
  SetExplosion(pos, size);
}
void SysExplosions::InstantiateL(const Vec2 &pos) { SetExplosion(pos, 'L'); }
void SysExplosions::InstantiateB(const Vec2 &pos) { SetExplosion(pos, 'B'); }
void SysExplosions::InstantiateM(const Vec2 &pos) { SetExplosion(pos, 'M'); }
void SysExplosions::InstantiateS(const Vec2 &pos) { SetExplosion(pos, 'S'); }

Entity *SetExplosion(const Vec2 &pos, char size) {
  auto *expl = GetExplosion();

  auto *tf = expl->GetComponent<Transform>();
  auto *go = expl->GetComponent<GameObject>();
  auto *ex = expl->GetComponent<Explosion>();
  auto *sr = expl->GetComponent<SpriteRenderer>();

  tf->position = pos;

  go->isActive = true;

  ex->lifespan = 0.1f;
  ex->size = size;

  sr->offsetPosition = {0.f, 0.f};
  sr->offsetRotation = 0.f;
  sr->pivot = {0.5f, 0.5f};
  sr->layer = 1;

  if (size == 'L') {
    sr->sprite = &SpriteLoader::sprExpls[0];
    sr->size = {260.f, 260.f};
  } else if (size == 'B') {
    sr->sprite = &SpriteLoader::sprExpls[1];
    sr->size = {160.f, 160.f};
  } else if (size == 'M') {
    sr->sprite = &SpriteLoader::sprExpls[2];
    sr->size = {140.f, 140.f};
  } else if (size == 'S') {
    sr->sprite = &SpriteLoader::sprExpls[3];
    sr->size = {110.f, 110.f};
  }

  return expl;
}

Entity *GetExplosion() {
  auto &reg = Scene_01::GetRegistry();

  // Pooling
  for (auto &i : reg) {
    auto *gaob = i->GetComponent<GameObject>();
    auto *ball = i->GetComponent<Explosion>();

    if (gaob && ball && !gaob->isActive)
      return i;
  }

  // Instantiation
  auto expl = new Entity();

  auto tf = Transform();
  auto go = GameObject();
  auto bl = Explosion();
  auto sr = SpriteRenderer();

  expl->AddComponent<Transform>(&tf);
  expl->AddComponent<GameObject>(&go);
  expl->AddComponent<Explosion>(&bl);
  expl->AddComponent<SpriteRenderer>(&sr);

  reg.push_back(expl);
  return expl;
}

static float ReboundPerSize(char size) {
  switch (size) {
  case 'L':
    return 650.f;
  case 'B':
    return 550.f;
  case 'M':
    return 450.f;
  case 'S':
    return 350.f;
  default:
    return 100.f;
  }
}
