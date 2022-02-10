#pragma once

#include "behaviour.h"
#include <vector>

class Logic
{
    friend class Game;
    static Logic Instance;

  private:
    Logic() = default;

    static void Awake();
    static void Start();
    static void Update();
    static void Fixed();
    static void Quit();

    std::vector<Behaviour *> each = std::vector<Behaviour *>();

  public:
    Logic(const Logic &) = delete;

    static void Subscribe(Behaviour *gameObject);
    static void UnSubscribe(const Behaviour *gameObject);
    static const std::vector<Behaviour *> *GetGameObjects();
};
