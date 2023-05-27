#pragma once

#include "pugixml.hpp"
#include "scene.h"
#include "vec.h"
#include <entt/entt.hpp>

class SysPhysics;
class SysMapPlayer;

class SceneMap : public Scene
{
  public:
    void LoadScene() override;
    void UnloadScene() override;

    void CreateTile(entt::registry &, int, Vec2i);

    int firstGID = 0;
    int lastGID = 0;
    int count = 0;

    const pugi::char_t *source = nullptr;

    Vec2i mapSize = {0, 0};
    Vec2i tileSize = {0, 0};

  private:
    SysPhysics *sysPhysics = nullptr;
    SysMapPlayer *sysPlayer = nullptr;
};
