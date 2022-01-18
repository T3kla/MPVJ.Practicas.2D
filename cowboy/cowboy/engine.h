#pragma once

#include <entt/entt.hpp>

constexpr double FPS = 144.;
constexpr double STP = 1000. / FPS;

class Engine {
private:                           // SINGLETON
  Engine();                        //
  static Engine instance;          //
public:                            //
  Engine(const Engine &) = delete; //
  static Engine &Get();            //

private:
  static entt::registry reg;

public:
  static void Run();

  static float GetUpdateFPS();
  static float GetFixedFPS();

  static entt::registry &GetRegistry();
};
