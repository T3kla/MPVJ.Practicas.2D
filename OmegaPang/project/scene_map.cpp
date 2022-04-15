#include "scene_map.h"

#include "glfw3.h"

#include "game.h"
#include "input.h"
#include "render.h"

#include "circle_collider.h"
#include "gameobject.h"
#include "pixel_collider.h"
#include "sprite_renderer.h"
#include "square_collider.h"
#include "transform.h"

#include "sys_physics.h"

#include "sprite_loader.h"

void SceneMap::LoadScene()
{
    Render::SetBgColor({ 0.5f, 0.44f, 0.37f, 0.5f });

    auto& reg = Game::GetRegistry();

    // Systems
    sysPhysics = new SysPhysics();
}

void SceneMap::UnloadScene()
{
    delete sysPhysics;
    delete this;
}

void SceneMap::Fixed()
{
    auto& reg = Game::GetRegistry();
}
