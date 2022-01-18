#include "sys_physics.h"

#include "collider.h"
#include "engine.h"
#include "gameobject.h"
#include "rigidbody.h"
#include "stasis.h"
#include "transform.h"
#include "vec.h"

#include <entt/entt.hpp>

SysPhysics::SysPhysics() {}
SysPhysics::~SysPhysics() {}

void SysPhysics::Awake() {}

void SysPhysics::Start() {}

void SysPhysics::Update() {}

void SysPhysics::Fixed() {
  // Movement
  auto movers = Engine::GetRegistry().view<Transform, GameObject, Rigidbody>();

  for (auto [entity, tf, go, rb] : movers.each()) {
    if (!go.isActive)
      continue;
    tf.position += rb.velocity * (float)STP * 0.001f;
    rb.velocity = rb.velocity * (1.f - rb.linearDamp);
  }

  // Collision
  auto collisioners =
      Engine::GetRegistry().view<Transform, GameObject, Rigidbody, Collider>();

  for (auto [entity, tf0, go0, rb0, cl0] : collisioners.each()) {

    if (!go0.isActive)
      continue;

    auto xTop0 = tf0.position.x + cl0.size.x / 2.f;
    auto xBot0 = tf0.position.x - cl0.size.x / 2.f;
    auto yTop0 = tf0.position.y + cl0.size.y / 2.f;
    auto yBot0 = tf0.position.y - cl0.size.y / 2.f;

    auto Inside = [](const float &t, const float &b, const float &v) {
      return v > t ? false : v < b ? false : true;
    };

    for (auto [entity, tf1, go1, rb1, cl1] : collisioners.each()) {

      if (!go0.isActive)
        continue;

      auto sqr = Collider::Type::Square;
      auto crl = Collider::Type::Square;

      // Collision Square vs Square
      if (cl0.type == sqr && cl1.type == sqr) {

        auto xTop1 = tf1.position.x + cl1.size.x / 2.f;
        auto xBot1 = tf1.position.x - cl1.size.x / 2.f;
        auto yTop1 = tf1.position.y + cl1.size.y / 2.f;
        auto yBot1 = tf1.position.y - cl1.size.y / 2.f;

        if ((Inside(xTop0, xBot0, xTop1) || Inside(xTop0, xBot0, xBot1)) &&
            (Inside(yTop0, yBot0, yTop1) || Inside(yTop0, yBot0, yBot1))) {
          // TODO: collision
        }
      }

      // Collision Circle vs Circle
      if (cl0.type == crl && cl1.type == crl) {

        if ((tf0.position - tf1.position).MagnitudeSq() <=
            powf(cl0.radius + cl1.radius, 2)) {
          // TODO: collision
        }
      }
    }
  }
}

void SysPhysics::Quit() {}
