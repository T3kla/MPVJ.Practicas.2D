#pragma once

#include "vec.h"

class Engine
{
  private:                           // SINGLETONE STUFF
    Engine();                        //     Singletone constructor
    static Engine instance;          //     Singletone single instance
  public:                            //
    Engine(const Engine &) = delete; //     Singletone copy constructor deletion
    static Engine &Get();            //     Singletone getter

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
