#pragma once

#include "logic.h"

class Behaviour
{
  public:
    Behaviour()
    {
        Logic::Subscribe(this);
    }

    virtual ~Behaviour()
    {
        Logic::UnSubscribe(this);
    }

    virtual void Awake() = 0;
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Fixed() = 0;
    virtual void Quit() = 0;
};
