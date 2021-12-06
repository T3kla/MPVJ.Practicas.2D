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
    rend.Init();
    game.Init();

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

Vec2 Engine::GetMousePos()
{
    return Vec2((float)Get().mouseX, (float)Get().mouseY);
}

void Engine::SetMousePos(const Vec2 &pos)
{
    Get().mouseX = pos.x;
    Get().mouseY = pos.y;
}

Vec2 Engine::GetMouseDelta()
{
    return Vec2((float)Get().mouseDeltaX, (float)Get().mouseDeltaY);
}

void Engine::SetMouseDelta(const Vec2 &pos)
{
    Get().mouseDeltaX = pos.x;
    Get().mouseDeltaY = pos.y;
}
