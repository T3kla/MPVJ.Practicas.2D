#pragma once

#include "engine.h"

class GameObject
{
  public:
    virtual void Update(const double &dt) = 0;
    virtual void Fixed(const double &dt) = 0;
};
