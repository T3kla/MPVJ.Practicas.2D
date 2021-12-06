#include "engine.h"
#include "game.h"
#include "logic.h"
#include "render.h"
#include "stasis.h"

Engine Engine::instance;

Engine::Engine()
{
}

Engine &Engine::Get()
{
    return instance;
}

void Engine::Run()
{
    auto &logic = Logic::Get();
    auto &game = Game::Get();
    auto &rend = Render::Get();
    auto &time = Stasis::Get();

    logic.Init();
    game.Init();
    rend.Init();

    while (!glfwWindowShouldClose(Render::GetWindow()))
    {
        time.Update();
        logic.Loop();
        game.Loop();
        rend.Loop();
    }

    logic.Exit();
    game.Exit();
    rend.Exit();
}

void Engine::GetMousePos(double &x, double &y)
{
    x = Get().mouseX;
    y = Get().mouseY;
}

void Engine::SetMousePos(const double &x, const double &y)
{
    Get().mouseX = x;
    Get().mouseY = y;
}

void Engine::GetMouseDelta(double &x, double &y)
{
    x = Get().mouseDeltaX;
    y = Get().mouseDeltaY;
}

void Engine::SetMouseDelta(const double &x, const double &y)
{
    Get().mouseDeltaX = x;
    Get().mouseDeltaY = y;
}
