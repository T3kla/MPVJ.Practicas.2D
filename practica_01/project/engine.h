#pragma once

#include "vec.h"

constexpr double STEP = 1000. / 144.;

class Engine {
private:                           // SINGLETONE STUFF
  Engine();                        //
  static Engine instance;          //
public:                            //
  Engine(const Engine &) = delete; //
  static Engine &Get();            //

private:
  double mouseX = 0.;
  double mouseY = 0.;
  double mouseDeltaX = 0.;
  double mouseDeltaY = 0.;

public:
  static void Run();

  static Vec2 GetMousePos();
  static void SetMousePos(const Vec2 &pos);
  static Vec2 GetMouseDelta();
  static void SetMouseDelta(const Vec2 &dt);
};
