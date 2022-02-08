#include "sys_physics.h"

#include "engine.h"
#include "engine_game.h"
#include "scene_01.h"

#include "gameobject.h"
#include "rigidbody.h"
#include "transform.h"

void SysPhysics::Awake() {}

void SysPhysics::Start() {}

void SysPhysics::Update() {}

void SysPhysics::Fixed() {

  for (auto &entity : Scene_01::GetRegistry()) {
    auto tf = entity->GetComponent<Transform>();
    auto go = entity->GetComponent<GameObject>();
    auto rb = entity->GetComponent<RigidBody>();

    if (!tf || !go || !rb || !go->isActive)
      continue;
    tf->position += rb->velocity * (float)STP * 0.001f;
    rb->velocity = rb->velocity * (1.f - rb->linearDrag);
  }
}

void SysPhysics::Quit() {}

SysPhysics::SysPhysics() { EngineGame::Subscribe(this); }

SysPhysics::~SysPhysics() { EngineGame::UnSubscribe(this); }
