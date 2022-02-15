#include "scene_01.h"

#include "sys_balls.h"
#include "sys_explosions.h"
#include "sys_hook.h"
#include "sys_physics.h"
#include "sys_player.h"
#include "vec.h"

void Scene01::LoadScene()
{
    SysBalls::Instantiate({300.f, 200.f}, true, Size::L);
    SysBalls::Instantiate({600.f, 200.f}, true, Size::B);
    SysBalls::Instantiate({800.f, 200.f}, true, Size::M);
    SysBalls::Instantiate({1000.f, 200.f}, true, Size::S);

    // Systems
    sysPlayer = new SysPlayer();
    sysPhysics = new SysPhysics();
    sysHook = new SysHook();
    sysBalls = new SysBalls();
    sysExplosions = new SysExplosions();
}

void Scene01::UnloadScene()
{
    delete sysPlayer;
    delete sysPhysics;
    delete sysHook;
    delete sysBalls;
    delete sysExplosions;
}
