#include "game.h"

#include "glfw3.h"

#include "asset_loader.h"
#include "font_loader.h"
#include "scene_loader.h"
#include "sprite_loader.h"
#include "thread_pool.h"

#include "input.h"
#include "logic.h"
#include "render.h"
#include "stasis.h"

#include "scene_bee.h"
#include "scene_collisions.h"
#include "scene_fonts.h"
#include "scene_map.h"
#include "scene_pang.h"

#include <algorithm>

static double fxCount = 0.;

static double dt = 0.;
static double nowFx = 0.;
static double oldFx = 0.;
static double freqFx = 0.;

auto FreqRefresh = [](double &now, double &old, double &freq) {
    now = Stasis::GetTime();
    freq = now - old;
    old = now;
};

Game Game::Instance;
entt::registry Game::Registry;

void Travel()
{
    if (Input::GetKey(GLFW_KEY_1))
        SceneLoader::LoadScene<SceneFonts>();
    else if (Input::GetKey(GLFW_KEY_2))
        SceneLoader::LoadScene<ScenePang>();
    else if (Input::GetKey(GLFW_KEY_3))
        SceneLoader::LoadScene<SceneBee>();
    else if (Input::GetKey(GLFW_KEY_4))
        SceneLoader::LoadScene<SceneCollisions>();
    else if (Input::GetKey(GLFW_KEY_5))
        SceneLoader::LoadScene<SceneMap>();
}

void Game::Run()
{
    Stasis::RefreshTime();
    ThreadPool::Init();
    Render::Awake();
    AssetLoader::LoadAssets();

    SceneLoader::LoadScene<SceneMap>(); // TODO: main scene

    while (!glfwWindowShouldClose(Render::GetWindow()))
    {
        Stasis::RefreshTime();

        Travel();

        Input::Update();
        Logic::Update();

        dt = Stasis::GetDelta();
        fxCount += dt;
        fxCount = fmin(fxCount, STP * 2.);
        while (fxCount >= STP)
        {
            FreqRefresh(nowFx, oldFx, freqFx);
            Render::Fixed(); // FIXME: debug mode
            Logic::Fixed();
            glfwSwapBuffers(Render::GetWindow()); // FIXME: debug mode
            fxCount -= STP;
        }
    }

    Logic::Quit();
    ThreadPool::Quit();
}

float Game::GetUpdateFPS()
{
    return (float)(1000. / dt);
}

float Game::GetFixedFPS()
{
    return (float)(1000. / freqFx);
}

entt::registry &Game::GetRegistry()
{
    return Registry;
}
