#include "engine.h"
#include "stasis.h"
#include <iostream>

Engine Engine::instance;

Engine::Engine()
{
}

Engine &Engine::Get()
{
    return instance;
}

static double count = 0.;

void Engine::Run()
{
    auto &input = Input::Get();
    auto &game = Game::Get();
    auto &rend = Render::Get();
    auto &time = Stasis::Get();

    time.RefreshTime();

    input.Init();
    rend.Init();
    game.Init();

    while (!glfwWindowShouldClose(Render::GetWindow()))
    {
        time.RefreshTime();

        input.Loop();
        game.Update();

        count += time.GetDelta();
        count = min(count, GAME_FREQ * 2);
        while (count >= GAME_FREQ)
        {
            game.Fixed();
            count -= GAME_FREQ;
        }

        rend.Loop();
    }

    input.Exit();
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
