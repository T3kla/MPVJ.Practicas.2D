#pragma once

class System
{
  public:
    System();
    virtual ~System();

    virtual void Update() = 0;
    virtual void Fixed() = 0;
    virtual void Quit() = 0;
};
