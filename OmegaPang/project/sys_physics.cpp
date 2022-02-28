#include "sys_physics.h"

#include "game.h"
#include "gameobject.h"
#include "rigidbody.h"
#include "transform.h"

auto GetRBs = []() { return Game::GetRegistry().view<GameObject, Transform, RigidBody>(); };

void SysPhysics::Fixed()
{
    for (auto [entity, go, tf, rb] : GetRBs().each())
    {
        if (!go.isActive)
            continue;

        tf.position += rb.velocity * (float)STP * 0.001f;
        rb.velocity = rb.velocity * (1.f - rb.linearDrag);
    }
}
