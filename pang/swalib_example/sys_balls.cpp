#include "sys_balls.h"

#include "ball.h"
#include "circle_collider.h"
#include "entity.h"
#include "game.h"
#include "gameobject.h"
#include "inputs.h"
#include "logic.h"
#include "render.h"
#include "rigidbody.h"
#include "scene_01.h"
#include "sprite_animation.h"
#include "sprite_loader.h"
#include "sprite_renderer.h"
#include "stasis.h"
#include "sys_hook.h"
#include "transform.h"

#include "sizes.h"

Entity *Instantiate(const Vec2 &pos, bool right, char size);
Entity *GetBall();
float ReboundPerSize(char size);

SysBalls::SysBalls()
{
    Logic::Subscribe(this);
}

SysBalls::~SysBalls()
{
    Logic::UnSubscribe(this);
}

void SysBalls::Awake()
{
}

void SysBalls::Start()
{
}

void SysBalls::Update()
{
}

void SysBalls::Fixed()
{
    auto &reg = Scene_01::GetRegistry();

    for (auto &i : reg)
    {
        auto *tf = i->GetComponent<Transform>();
        auto *go = i->GetComponent<GameObject>();
        auto *rb = i->GetComponent<RigidBody>();
        auto *bl = i->GetComponent<Ball>();
        auto *cl = i->GetComponent<CircleCollider>();

        if (!tf || !go || !rb || !bl || !cl || !go->isActive)
            continue;

        // Gravity
        rb->velocity += Vec2::Down() * 600.f * (float)STP * 0.001f;

        // Rebound
        int width, height;
        Render::GetWindowSize(width, height);
        if (tf->position.x > width - cl->radius / 2.f)
        {
            tf->position.x = width - cl->radius / 2.f - 1.f;
            rb->velocity.x *= -1.f;
        }
        if (tf->position.x < cl->radius / 2.f)
        {
            tf->position.x = cl->radius / 2.f + 1.f;
            rb->velocity.x *= -1.f;
        }
        if (tf->position.y < cl->radius / 2.f)
        {
            tf->position.y = cl->radius / 2.f + 1.f;
            rb->velocity.y = ReboundPerSize(bl->size) * 1.2f;
        }
    }
}

void SysBalls::Quit()
{
}

void SysBalls::InstantiateSmaller(const Vec2 &pos, bool right, Size size)
{
    auto next = size.OneSmaller();
    if (next == 'X')
        return;
    Instantiate(pos, right, next);
}

Entity *Instantiate(const Vec2 &pos, bool right, Size size)
{
    auto *ball = GetBall();

    auto *tf = ball->GetComponent<Transform>();
    auto *go = ball->GetComponent<GameObject>();
    auto *rb = ball->GetComponent<RigidBody>();
    auto *bl = ball->GetComponent<Ball>();
    auto *cl = ball->GetComponent<CircleCollider>();
    auto *sr = ball->GetComponent<SpriteRenderer>();

    tf->position = pos;

    go->isActive = true;

    rb->linearDrag = 0.0f;
    rb->velocity = {175.f * (right ? 1.f : -1.f), 200.f};

    bl->size = size;

    sr->offsetPosition = {0.f, 0.f};
    sr->offsetRotation = 0.f;
    sr->pivot = {0.5f, 0.5f};
    sr->layer = 1;

    if (size == Size::L)
    {
        sr->sprite = &SpriteLoader::sprBalls[0];
        sr->size = {260.f, 260.f};
        cl->radius = 160.f;
    }
    else if (size == Size::B)
    {
        sr->sprite = &SpriteLoader::sprBalls[1];
        sr->size = {160.f, 160.f};
        cl->radius = 115.f;
    }
    else if (size == Size::M)
    {
        sr->sprite = &SpriteLoader::sprBalls[2];
        sr->size = {140.f, 140.f};
        cl->radius = 65.f;
    }
    else if (size == Size::S)
    {
        sr->sprite = &SpriteLoader::sprBalls[3];
        sr->size = {110.f, 110.f};
        cl->radius = 20.f;
    }

    return ball;
}

Entity *GetBall()
{
    auto &reg = Scene_01::GetRegistry();

    // Pooling
    for (auto &i : reg)
    {
        auto *gaob = i->GetComponent<GameObject>();
        auto *ball = i->GetComponent<Ball>();

        if (gaob && ball && !gaob->isActive)
            return i;
    }

    // Instantiation
    auto ball = new Entity();

    auto tf = Transform();
    auto go = GameObject();
    auto rb = RigidBody();
    auto bl = Ball();
    auto sr = SpriteRenderer();
    auto cl = CircleCollider();

    ball->AddComponent<Transform>(&tf);
    ball->AddComponent<GameObject>(&go);
    ball->AddComponent<RigidBody>(&rb);
    ball->AddComponent<Ball>(&bl);
    ball->AddComponent<SpriteRenderer>(&sr);
    ball->AddComponent<CircleCollider>(&cl);

    reg.push_back(ball);
    return ball;
}

float ReboundPerSize(char size)
{
    switch (size)
    {
    case 'L':
        return 650.f;
    case 'B':
        return 550.f;
    case 'M':
        return 450.f;
    case 'S':
        return 350.f;
    default:
        return 100.f;
    }
}
