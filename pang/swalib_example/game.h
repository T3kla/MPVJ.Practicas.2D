#pragma once

#include <entt/entt.hpp>

constexpr double FPS = 60.;
constexpr double STP = 1000. / FPS;

class Game
{
    static Game Instance;

  private:
    Game(){};

    static entt::registry Registry;

  public:
    Game(const Game &) = delete;

    static void Run();

    static float GetUpdateFPS();
    static float GetFixedFPS();

    static entt::registry &GetRegistry();
};
