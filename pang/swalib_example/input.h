#pragma once

#include "keycode.h"
#include "vec.h"

class Input
{
    friend class Game;
    static Input Instance;

  private:
    Input(){};

    Vec2 MouseOldPos = {0.f, 0.f};
    Vec2 MousePos = {0.f, 0.f};
    Vec2 MouseDelta = {0.f, 0.f};

    static void Awake();
    static void Start();
    static void Update();
    static void Fixed();
    static void Quit();

  public:
    Input(const Input &) = delete;

    static Vec2 GetMousePos();
    static Vec2 GetMouseDelta();

    static unsigned char GetKey(KeyCode key);
};
