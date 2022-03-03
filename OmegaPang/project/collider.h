#pragma once

struct Collision;

static void Null(Collision *){};

struct Collider
{
    bool enable = true;
    bool IsTrigger = false;

    void (*OnTriggerEnter)(Collision *) = Null;
    void (*OnTriggerStay)(Collision *) = Null;
    void (*OnTriggerExit)(Collision *) = Null;
};
