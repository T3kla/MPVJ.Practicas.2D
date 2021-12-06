#include "game.h"
#include "stasis.h"
#include <iostream>

Game Game::instance;

Game::Game()
{
}

Game &Game::Get()
{
    return instance;
}

void Game::Subscribe(GameObject *gameObject)
{
    auto &instance = Game::Get();

    // Duplication guard
    auto it = std::find(instance.each.begin(), instance.each.end(), gameObject);
    if (it != instance.each.end())
        return;

    instance.each.push_back(gameObject);
}

void Game::UnSubscribe(const GameObject *gameObject)
{
    auto &instance = Game::Get();

    // Not found guard
    auto it = std::find(instance.each.begin(), instance.each.end(), gameObject);
    if (it == instance.each.end())
        return;

    instance.each.erase(it);
}

const std::vector<GameObject *> *Game::GetGameObjects()
{
    return &Get().each;
}

void Game::Init()
{
    Start();
}

auto timeUp = 0.;
auto timeFx = 0.;

void Game::Loop()
{
    auto next = [](auto &it) { it += 1u - TIME_AVG_SAMPLES * (it == TIME_AVG_SAMPLES - 1u); };
    auto delta = Stasis::GetDeltaUnscaled();

    avgUP[avgIterUP] = delta;
    next(avgIterUP);

    timeUp += delta;

    countToFX += delta;
    Update(delta);

    if (countToFX >= TIME_FIXED_FREQ)
    {
        avgFX[avgIterFX] = countToFX;
        next(avgIterFX);

        timeFx += countToFX;

        Fixed(countToFX * Stasis::GetScale());
        countToFX = 0;
    }
}

void Game::Exit()
{
    End();
}

void Game::Start()
{
    for (auto &&go : *Game::Get().GetGameObjects())
        go->Start();
}

void Game::Update(double dt)
{
    for (auto &&go : *Game::Get().GetGameObjects())
        go->Update(dt);
}

void Game::Fixed(double dt)
{
    for (auto &&go : *Game::Get().GetGameObjects())
        go->Fixed(dt);
    PrintFps();
}

void Game::End()
{
    for (auto &&go : *Game::Get().GetGameObjects())
        go->End();
}

void Game::PrintFps()
{
    avgBufferUP = 0.;
    avgBufferFX = 0.;

    for (auto &&i : avgUP)
        avgBufferUP += i;
    for (auto &&i : avgFX)
        avgBufferFX += i;

    avgBufferUP /= (double)TIME_AVG_SAMPLES;
    avgBufferFX /= (double)TIME_AVG_SAMPLES;

    avgBufferUP = 1. / (avgBufferUP / 1000.);
    avgBufferFX = 1. / (avgBufferFX / 1000.);

    // Only works disabling VSync
    std::cout << "  fixed: " << avgBufferFX << std::endl;
    std::cout << " update: " << avgBufferUP << std::endl;
    std::cout << "time fx: " << timeUp << std::endl;
    std::cout << "time up: " << timeFx << std::endl;
}
