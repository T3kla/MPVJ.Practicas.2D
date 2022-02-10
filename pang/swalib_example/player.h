#pragma once

struct Player
{
    bool enable = true;

    int health = 3;
    float speed = 100.f;
    char *state = nullptr;
    bool reversed = false;
};
