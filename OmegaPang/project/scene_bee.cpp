#include "scene_bee.h"

#include "render.h"
#include "sys_bee.h"
#include "vec.h"

void SceneBee::LoadScene()
{
    Render::SetBgColor({0.f, 0.f, 0.f, 0.f});
    SysBee::Instantiate({200.f, 200.f});

    // Systems
    sysBee = new SysBee();
}

void SceneBee::UnloadScene()
{
    delete sysBee;
}
