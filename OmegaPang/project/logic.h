#pragma once

#include <vector>

class System;

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

    std::vector<System *> each = std::vector<System *>();

  public:
    Logic(const Logic &) = delete;

    static void Subscribe(System *gameObject);
    static void UnSubscribe(const System *gameObject);
    static const std::vector<System *> *GetSystems();
};
