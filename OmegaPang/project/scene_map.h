#pragma once

#include "pugixml.hpp"
#include "scene.h"
#include "system.h"
#include "vec.h"
#include <entt/entt.hpp>

class SceneMap : public Scene, public System
{
  public:
    virtual void LoadScene() override;
    virtual void UnloadScene() override;

    virtual void Update() override{};
    virtual void Fixed() override;
    virtual void Quit() override{};

    void CreateTile(entt::registry &, int, Vec2i);

    int firstGID = 0;
    int lastGID = 0;
    int count = 0;

    const pugi::char_t *source = nullptr;

    Vec2i mapSize = {0, 0};
    Vec2i tileSize = {0, 0};

  private:
    class SysPhysics *sysPhysics;
    class SysMapPlayer *sysPlayer;
};
