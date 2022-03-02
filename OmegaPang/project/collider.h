#pragma once

struct Collision;

static void Null(Collision *){};

struct Collider
{
    bool enable = true;
    bool IsTrigger = false;

    void (*OnCollision)(Collision *) = Null;
    void (*OnTrigger)(Collision *) = Null;
};
