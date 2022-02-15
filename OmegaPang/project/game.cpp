#include "game.h"

#include "glfw3.h"
#include "input.h"
#include "logic.h"
#include "render.h"
#include "scene_loader.h"
#include "stasis.h"

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

void Game::Run()
{
    Stasis::RefreshTime();

    Render::Awake();

    SceneLoader::LoadScene("Scene01");
    // SceneLoader::LoadScene("SceneMM");

    Logic::Awake();
    Logic::Start();

    while (!glfwWindowShouldClose(Render::GetWindow()))
    {
        Stasis::RefreshTime();

        Input::Update();
        Logic::Update();

        dt = Stasis::GetDelta();
        fxCount += dt;
        fxCount = fmin(fxCount, STP * 2.);
        while (fxCount >= STP)
        {
            FreqRefresh(nowFx, oldFx, freqFx);
            Logic::Fixed();
            Render::Fixed();
            fxCount -= STP;
        }
    }

    Logic::Quit();
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
