#pragma once

#include "vec.h"

class Input
{
    friend class Game;
    static Input Instance;

  private:
    Input() = default;
    Input(const Input &) = delete;

    Vec2 MouseOldPos = {0.f, 0.f};
    Vec2 MousePos = {0.f, 0.f};
    Vec2 MouseDelta = {0.f, 0.f};

    static void Update();

  public:
    static Vec2 GetMousePos();
    static Vec2 GetMouseDelta();

    static unsigned char GetKey(int key);
};
