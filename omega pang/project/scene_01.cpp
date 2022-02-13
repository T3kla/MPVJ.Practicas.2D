#include "scene_01.h"

#include "sys_balls.h"
#include "sys_explosions.h"
#include "sys_hook.h"
#include "sys_physics.h"
#include "sys_player.h"
#include "vec.h"

Scene01::Scene01()
{
    SysBalls::Instantiate({300.f, 200.f}, true, Size::L);
    SysBalls::Instantiate({600.f, 200.f}, true, Size::B);
    SysBalls::Instantiate({800.f, 200.f}, true, Size::M);
    SysBalls::Instantiate({1000.f, 200.f}, true, Size::S);

    // Systems
    new SysPlayer();
    new SysPhysics();
    new SysHook();
    new SysBalls();
    new SysExplosions();
}
