#pragma once

#include <string>

class Scene
{
  public:
    Scene(const char *name = "") : name(name){};

    virtual void LoadScene() = 0;
    virtual void UnloadScene() = 0;

  protected:
    virtual ~Scene(){};

  private:
    std::string name;
};
