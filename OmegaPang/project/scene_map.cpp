#include "scene_map.h"

#include "game.h"
#include "input.h"
#include "render.h"

#include "gameobject.h"
#include "sprite_renderer.h"
#include "square_collider.h"
#include "transform.h"

#include "sys_mapPlayer.h"
#include "sys_physics.h"

#include "sprite_loader.h"

void SceneMap::LoadScene()
{
    Render::SetBgColor({0.5f, 0.44f, 0.37f, 0.5f});

    auto &reg = Game::GetRegistry();

    auto doc = pugi::xml_document();
    auto result = doc.load_file("../resources/map.tmx");

    if (!result)
        throw;

    // Nodes
    auto mapNode = doc.child("map");
    auto setNode = doc.child("map").child("tileset");
    auto imgNode = doc.child("map").child("tileset").child("image");
    auto tleNode = doc.child("map").child("layer").child("data").child("tile");

    // Node map data
    mapSize.x = mapNode.attribute("width").as_int();  // map width in tiles
    mapSize.y = mapNode.attribute("height").as_int(); // map height in tiles

    // Node tile set data
    firstGID = setNode.attribute("firstgid").as_int();     // first id number
    tileSize.x = setNode.attribute("tilewidth").as_int();  // tile width
    tileSize.y = setNode.attribute("tileheight").as_int(); // tile height
    count = setNode.attribute("tilecount").as_int();       // total ids
    lastGID = firstGID + count - 1;                        // last id number

    // Iterate every node
    Vec2i pos = {0, 0};
    auto all = doc.child("map").child("layer").child("data").children();

    for (auto &it : all)
    {
        if (pos.x >= mapSize.x)
        {
            pos.x = 0;
            pos.y++;
        }

        auto gid = it.attribute("gid").as_int();
        auto worldPos = Vec2i::Hadamard(pos, tileSize);

        pos.x++;

        CreateTile(reg, gid, worldPos);
    }

    // Systems
    sysPhysics = new SysPhysics();
    sysPlayer = new SysMapPlayer();
}

void SceneMap::UnloadScene()
{
    delete sysPhysics;
    delete sysPlayer;
    delete this;
}

void SceneMap::CreateTile(entt::registry &reg, int gid, Vec2i pos)
{
    if (gid == 0)
        return;

    auto id = reg.create();

    auto &go = reg.emplace<GameObject>(id, true);
    auto &tf = reg.emplace<Transform>(id, Vec2(pos), Vec2::One(), 0.f);
    auto &sc = reg.emplace<SquareCollider>(id);
    sc.center = {0.f, 0.f};
    sc.size = Vec2(tileSize);
    // sc.OnTriggerEnter = &OnTriggerEnter;
    // sc.OnTriggerStay = &OnTriggerStay;
    // sc.OnTriggerExit = &OnTriggerExit;
    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.size = Vec2(tileSize);
    sr.blend = BLEND_ALPHA;
    sr.layer = 0;

    switch (gid)
    {
    case 6:
        sr.sprite = &SpriteLoader::sprMapGUI_06;
        break;
    case 8:
        sr.sprite = &SpriteLoader::sprMapGUI_08;
        break;
    case 9:
        sr.sprite = &SpriteLoader::sprMapGUI_09;
        break;
    case 11:
        sr.sprite = &SpriteLoader::sprMapGUI_11;
        break;
    case 16:
        sr.sprite = &SpriteLoader::sprMapGUI_16;
        break;
    case 17:
        sr.sprite = &SpriteLoader::sprMapGUI_17;
        break;
    case 18:
        sr.sprite = &SpriteLoader::sprMapGUI_18;
        break;
    case 19:
        sr.sprite = &SpriteLoader::sprMapGUI_19;
        break;
    case 29:
        sr.sprite = &SpriteLoader::sprMapGUI_29;
        break;
    default:
        throw;
    }
}
