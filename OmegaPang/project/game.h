#pragma once

#include <entt/entt.hpp>

constexpr double FPS = 60.;
constexpr double STP = 1000. / FPS;

class Game
{
    static Game Instance;
    static entt::registry Registry;

  private:
    Game() = default;
    Game(const Game &) = delete;

  public:
    static void Run();

    static float GetUpdateFPS();
    static float GetFixedFPS();

    static entt::registry &GetRegistry();
};
