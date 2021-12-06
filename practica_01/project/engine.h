#pragma once

#include <vector>

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

    static void GetMousePos(double &pos_x, double &pos_y);
    static void SetMousePos(const double &pos_x, const double &pos_y);
    static void GetMouseDelta(double &delta_x, double &delta_y);
    static void SetMouseDelta(const double &delta_x, const double &delta_y);
};
