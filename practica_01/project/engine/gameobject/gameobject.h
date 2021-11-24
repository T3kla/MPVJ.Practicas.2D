#pragma once

#include "../engine.h"

class gameobject
{

  public:
    gameobject()
    {
        tkl::engine::get().m_gameobj
    }
    ~gameobject()
    {
    }
    virtual void start() = 0;
    virtual void update() = 0;
    virtual void fixed() = 0;
};
