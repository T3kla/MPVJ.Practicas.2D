#include "game.h"

#include "input.h"
#include "logic.h"
#include "render.h"
#include "stasis.h"

static double fxCount = 0.;

double dt = 0.;
static double nowFx = 0.;
static double oldFx = 0.;
static double freqFx = 0.;

auto FreqRefresh = [](double &now, double &old, double &freq) {
    now = Stasis::GetTime();
    freq = now - old;
    old = now;
};

Game Game::Instance;

void Game::Run()
{
    Stasis::RefreshTime();

    Input::Awake();
    Logic::Awake();
    Render::Awake();

    Input::Start();
    Logic::Start();
    Render::Start();

    while (!glfwWindowShouldClose(Render::GetWindow()))
    {
        Stasis::RefreshTime();

        Input::Update();
        Logic::Update();

        dt = Stasis::GetDelta();
        fxCount += dt;
        fxCount = min(fxCount, STP * 2.);
        while (fxCount >= STP)
        {
            FreqRefresh(nowFx, oldFx, freqFx);
            Input::Fixed();
            Logic::Fixed();
            Render::Fixed();
            fxCount -= STP;
        }

        Render::Update();
    }

    Input::Quit();
    Logic::Quit();
    Render::Quit();
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
