#pragma once

#include <functional>

struct Collision;

static void Null(Collision *){};

struct Collider
{
    bool enable = true;
    bool isTrigger = false;

    std::function<void(Collision *)> OnTriggerEnter = Null;
    std::function<void(Collision *)> OnTriggerStay = Null;
    std::function<void(Collision *)> OnTriggerExit = Null;
};
