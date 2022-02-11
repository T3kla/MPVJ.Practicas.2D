#include "sys_physics.h"

#include "game.h"
#include "gameobject.h"
#include "rigidbody.h" S
#include "transform.h"

auto GetView = []() { return Game::GetRegistry().view<GameObject, Transform, RigidBody>(); };

void SysPhysics::Fixed()
{
    for (auto [entity, go, tf, rb] : GetView().each())
    {
        if (!go.isActive)
            continue;

        tf.position += rb.velocity * (float)STP * 0.001f;
        rb.velocity = rb.velocity * (1.f - rb.linearDrag);
    }
}
