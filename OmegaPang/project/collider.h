#pragma once

struct Collision;

struct Collider
{
    bool enable = true;
    bool IsTrigger = false;

    void (*OnCollision)(Collision *) = nullptr;
    void (*OnTrigger)(Collision *) = nullptr;
};
