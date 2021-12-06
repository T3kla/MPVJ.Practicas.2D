#pragma once

#include "gameobject.h"
#include <vector>

constexpr auto TIME_FIXED_FREQ = (1. / 60.) * 1000.;
constexpr auto TIME_AVG_SAMPLES = 16u;

class Game
{
  private:                       // SINGLETON
    Game();                      //
    static Game instance;        //
  public:                        //
    Game(const Game &) = delete; //
    static Game &Get();          //

  private:
    double countToFX = 0.;

    std::vector<double> avgUP = std::vector<double>(TIME_AVG_SAMPLES, 0);
    std::vector<double> avgFX = std::vector<double>(TIME_AVG_SAMPLES, 0);
    double avgBufferUP = 0.;
    double avgBufferFX = 0.;
    unsigned int avgIterUP = 0u;
    unsigned int avgIterFX = 0u;

    std::vector<GameObject *> each = std::vector<GameObject *>();

  public:
    static void Subscribe(GameObject *gameObject);
    static void UnSubscribe(const GameObject *gameObject);
    static const std::vector<GameObject *> *GetGameObjects();

    void Init();
    void Loop();
    void Exit();

    void Start();
    void Update(double dt = 0.);
    void Fixed(double dt = 0.);
    void End();

    void PrintFps();
};
