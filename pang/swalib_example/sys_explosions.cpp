#include "sys_explosions.h"

#include "ball.h"
#include "circle_collider.h"
#include "entity.h"
#include "explosion.h"
#include "game.h"
#include "gameobject.h"
#include "inputs.h"
#include "logic.h"
#include "rigidbody.h"
#include "scene_01.h"
#include "sprite_animation.h"
#include "sprite_loader.h"
#include "sprite_renderer.h"
#include "stasis.h"
#include "sys_hook.h"
#include "transform.h"

Entity *SetExplosion(const Vec2 &pos, char size);
Entity *GetExplosion();
float ReboundPerSize(char size);

SysExplosions::SysExplosions()
{
}

SysExplosions::~SysExplosions()
{
}

void SysExplosions::Awake()
{
}

void SysExplosions::Start()
{
}

void SysExplosions::Update()
{
}

void SysExplosions::Fixed()
{
    auto &reg = Scene_01::GetRegistry();

    for (auto &i : reg)
    {
        auto *go = i->GetComponent<GameObject>();
        auto *ex = i->GetComponent<Explosion>();

        if (!go || !ex || !go->isActive)
            continue;

        if (ex->lifespan > 0.f)
            ex->lifespan -= (float)STP * 0.001f;
        else
            go->isActive = false;
    }
}

void SysExplosions::Quit()
{
}

void SysExplosions::InstantiateSmaller(const Vec2 &pos, char size)
{
    SetExplosion(pos, size);
}

Entity *SetExplosion(const Vec2 &pos, char size)
{
    auto *expl = GetExplosion();

    auto *tf = expl->GetComponent<Transform>();
    auto *go = expl->GetComponent<GameObject>();
    auto *ex = expl->GetComponent<Explosion>();
    auto *sr = expl->GetComponent<SpriteRenderer>();

    tf->position = pos;

    go->isActive = true;

    ex->lifespan = 0.1f;
    ex->size = size;

    sr->offsetPosition = {0.f, 0.f};
    sr->offsetRotation = 0.f;
    sr->pivot = {0.5f, 0.5f};
    sr->layer = 1;

    if (size == 'L')
    {
        sr->sprite = &SpriteLoader::sprExpls[0];
        sr->size = {260.f, 260.f};
    }
    else if (size == 'B')
    {
        sr->sprite = &SpriteLoader::sprExpls[1];
        sr->size = {160.f, 160.f};
    }
    else if (size == 'M')
    {
        sr->sprite = &SpriteLoader::sprExpls[2];
        sr->size = {140.f, 140.f};
    }
    else if (size == 'S')
    {
        sr->sprite = &SpriteLoader::sprExpls[3];
        sr->size = {110.f, 110.f};
    }

    return expl;
}

Entity *GetExplosion()
{
    auto &reg = Scene_01::GetRegistry();

    // Pooling
    for (auto &i : reg)
    {
        auto *gaob = i->GetComponent<GameObject>();
        auto *ball = i->GetComponent<Explosion>();

        if (gaob && ball && !gaob->isActive)
            return i;
    }

    // Instantiation
    auto expl = new Entity();

    auto tf = Transform();
    auto go = GameObject();
    auto bl = Explosion();
    auto sr = SpriteRenderer();

    expl->AddComponent<Transform>(&tf);
    expl->AddComponent<GameObject>(&go);
    expl->AddComponent<Explosion>(&bl);
    expl->AddComponent<SpriteRenderer>(&sr);

    reg.push_back(expl);
    return expl;
}

static float ReboundPerSize(Size size)
{
    switch (size)
    {
    case Size::L:
        return 650.f;
    case Size::B:
        return 550.f;
    case Size::M:
        return 450.f;
    case Size::S:
        return 350.f;
    default:
        return 100.f;
    }
}
