#include "scene_mm.h"

#include "color.h"
#include "font_loader.h"
#include "sys_ui.h"
#include "vec.h"

void SceneMM::LoadScene()
{
    auto *slap = FontLoader::GetFont("fontSlap.ttf");
    auto *org = FontLoader::GetFont("fontOrange.ttf");

    SysUI::Instantiate({100.f, 300.f}, "A feisty red fox", slap, 11.f, {0.7f, 0.f, 0.f, 1.f});
    SysUI::Instantiate({100.f, 400.f}, "ate slime, and fog", slap, 11.f, {0.7f, 0.f, 0.7f, 1.f});
    SysUI::Instantiate({100.f, 500.f}, "and... turned blue!", slap, 11.f, {0.f, 0.f, 0.7f, 1.f});

    SysUI::Instantiate({800.f, 300.f}, "A feisty red fox", org, 11.f, {0.7f, 0.f, 0.f, 1.f});
    SysUI::Instantiate({800.f, 400.f}, "ate slime, and fog", org, 11.f, {0.7f, 0.f, 0.7f, 1.f});
    SysUI::Instantiate({800.f, 500.f}, "and... turned blue!", org, 11.f, {0.f, 0.f, 0.7f, 1.f});
}

void SceneMM::UnloadScene()
{
}
