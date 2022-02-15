#include "scene_mm.h"

#include "color.h"
#include "font_loader.h"
#include "sys_ui.h"
#include "vec.h"

void SceneMM::LoadScene()
{
    SysUI::Instantiate({100.f, 300.f}, "A feisty red fox", FontLoader::GetFontSlap(), 11.f, {0.7f, 0.f, 0.f, 1.f});
    SysUI::Instantiate({100.f, 400.f}, "ate slime, and fog", FontLoader::GetFontSlap(), 11.f, {0.7f, 0.f, 0.7f, 1.f});
    SysUI::Instantiate({100.f, 500.f}, "and... turned blue!", FontLoader::GetFontSlap(), 11.f, {0.f, 0.f, 0.7f, 1.f});

    SysUI::Instantiate({800.f, 300.f}, "A feisty red fox", FontLoader::GetFontOrange(), 11.f, {0.7f, 0.f, 0.f, 1.f});
    SysUI::Instantiate({800.f, 400.f}, "ate slime, and fog", FontLoader::GetFontOrange(), 11.f, {0.7f, 0.f, 0.7f, 1.f});
    SysUI::Instantiate({800.f, 500.f}, "and... turned blue!", FontLoader::GetFontOrange(), 11.f, {0.f, 0.f, 0.7f, 1.f});
}

void SceneMM::UnloadScene()
{
}
