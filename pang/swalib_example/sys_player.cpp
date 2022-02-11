#include "sys_player.h"

#include "ball.h"
#include "circle_collider.h"
#include "entity.h"
#include "game.h"
#include "gameobject.h"
#include "inputs.h"
#include "logic.h"
#include "player.h"
#include "render.h"
#include "rigidbody.h"
#include "scene_01.h"
#include "sprite_animation.h"
#include "sprite_loader.h"
#include "sprite_renderer.h"
#include "stasis.h"
#include "sys_hook.h"
#include "transform.h"

#include <entt/entt.hpp>

constexpr char *stateIdle = "idle";
constexpr char *stateMoving = "moving";
constexpr char *stateShooting = "shooting";
constexpr char *stateHurt = "hurt";

Entity player;

float moveBlockCounter = 0.f;
float shootBlockCounter = 0.f;
float hurtBlockCounter = 0.f;
float blinkCounter = 0.f;

float blinkRate = 0.2f;

void UpdateAnimation();

void BlockMove(float time)
{
    moveBlockCounter = time;
}

void BlockShoot(float time)
{
    shootBlockCounter = time;
}

void BlockHurt(float time)
{
    hurtBlockCounter = time;
    blinkCounter = 3.f;
}

bool CanMove()
{
    return moveBlockCounter < 0.f;
}

bool CanShoot()
{
    return shootBlockCounter < 0.f;
}

bool IsColliding(Vec2 posA, float radA, Vec2 posB, float radB)
{
    return (posA - posB).Magnitude() < radA + radB;
}

void SysPlayer::Awake()
{
    auto &reg = Game::GetRegistry();

    entt::entity id = reg.create();

    player = Entity(id, &reg);

    int width, height;
    Render::GetWindowSize(width, height);

    reg.get_or_emplace<GameObject>(id, true);
    reg.get_or_emplace<Transform>(id, Vec2(width / 2.f, 50.f), Vec2::One(), 0.f);
    reg.get_or_emplace<RigidBody>(id, true, Vec2::Zero(), 0.2f);
    reg.get_or_emplace<Player>(id, true, 3, 5000.f, stateIdle, false);
    reg.get_or_emplace<CircleCollider>(id, true, 50.f);
    reg.get_or_emplace<SpriteRenderer>(id, true, &SpriteLoader::sprPlayerMoveL[0], Vec2::Zero(), 0.f,
                                       Vec2(100.f, 100.f), Vec2::One() * 0.5f, 10, BLEND_ALPHA);
    reg.get_or_emplace<SpriteAnimation>(id, true, &SpriteLoader::sprHook, 0, 0.f, 0.2f, 0.f, 1);
}

void SysPlayer::Update()
{
    auto time = (float)Stasis::GetDeltaScaled() * 0.001f;
    moveBlockCounter -= time;
    shootBlockCounter -= time;
    hurtBlockCounter -= time;
    blinkCounter -= time;

    auto &reg = Game::GetRegistry();

    auto &tf = reg.get<Transform>(player.GetID());
    auto &go = player.GetComponent<GameObject>();
    auto &rb = player.GetComponent<RigidBody>();
    auto &pl = player.GetComponent<Player>();
    auto &sa = player.GetComponent<SpriteAnimation>();

    if (!go || !go->isActive)
        return;

    // Collision with balls
    for (auto &ball : reg)
    {
        auto *btf = ball->GetComponent<Transform>();
        auto *bgo = ball->GetComponent<GameObject>();
        auto *brb = ball->GetComponent<RigidBody>();
        auto *bbl = ball->GetComponent<Ball>();
        auto *bcl = ball->GetComponent<CircleCollider>();

        if (!btf || !bgo || !brb || !bbl || !bcl || !bgo->isActive)
            continue;

        if (pl->health > 0 && blinkCounter < 0.f && IsColliding(tf->position, fakeCC, btf->position, bcl->radius / 2.f))
        {

            pl->health += pl->health > 0 ? -1 : 0;
            BlockHurt(0.3f);
            BlockShoot(0.3f);
            BlockMove(0.3f);

            if (pl->health <= 0)
            {
                BlockHurt(9999.9f);
                BlockShoot(9999.9f);
                BlockMove(9999.9f);
            }
        }
    }

    // Input Move
    Vec2 add = Vec2::Zero();

    if (CanMove() && SYS_KeyPressed(KEY_A))
        add -= pl->speed * (float)Stasis::GetDeltaScaled() * 0.001f;
    if (CanMove() && SYS_KeyPressed(KEY_D))
        add += pl->speed * (float)Stasis::GetDeltaScaled() * 0.001f;

    rb->velocity += add;

    auto velMag = rb->velocity.Magnitude();

    if (velMag > pl->speed)
        rb->velocity = rb->velocity.Normalized() * pl->speed;

    pl->reversed = rb->velocity.x < 0.f ? true : false;

    // Bounds
    if (tf->position.x > SCR_WIDTH - fakeCC / 2.f)
    {
        tf->position.x = SCR_WIDTH - fakeCC / 2.f - 1.f;
        rb->velocity.x = 0;
    }
    if (tf->position.x < fakeCC / 2.f)
    {
        tf->position.x = fakeCC / 2.f + 1.f;
        rb->velocity.x = 0;
    }

    // Input Shoot
    if (CanShoot() && SYS_KeyPressed(KEY_W))
    {
        BlockShoot(0.3f);
        BlockMove(0.1f);
        SysHook::Instantiate(tf->position);
    }

    // State Machine
    if (hurtBlockCounter > 0.f)
        pl->state = stateHurt;
    else if (!CanShoot())
        pl->state = stateShooting;
    else if (CanMove())
        pl->state = velMag < 200.f ? stateIdle : stateMoving;

    UpdateAnimation();
}

void SysPlayer::Fixed()
{
}

void SysPlayer::Quit()
{
}

Entity *SysPlayer::GetPlayer()
{
    return &player;
}

int SysPlayer::GetPlayerHealth()
{
    auto *pl = player.GetComponent<Player>();
    return pl ? pl->health : 0;
}

void UpdateAnimation()
{
    auto *pl = player.GetComponent<Player>();
    auto *sr = player.GetComponent<SpriteRenderer>();
    auto *sa = player.GetComponent<SpriteAnimation>();

    if (sa)
        if (pl->state == stateHurt)
        {

            sa->enable = false;
            sr->sprite = pl->reversed ? &SpriteLoader::sprPlayerHitL : &SpriteLoader::sprPlayerHitR;
        }
        else if (pl->state == stateMoving)
        {

            sa->enable = true;
            sa->duration = 0.25f;
            sa->animation = pl->reversed ? &SpriteLoader::sprPlayerMoveL : &SpriteLoader::sprPlayerMoveR;
        }
        else if (pl->state == stateShooting)
        {

            sa->enable = true;
            sa->duration = 0.4f;
            sa->animation = pl->reversed ? &SpriteLoader::sprPlayerShootL : &SpriteLoader::sprPlayerShootR;
        }
        else if (pl->state == stateIdle)
        {

            sa->enable = false;
            sr->sprite = pl->reversed ? &SpriteLoader::sprPlayerShootL[0] : &SpriteLoader::sprPlayerShootR[0];
        }

    // Blink if invulnerable
    if (blinkCounter > 0.f)
    {
        auto frameFreq = blinkRate / 2.f;
        auto frame = floorf(blinkCounter / frameFreq) + (pl->health > 0 ? 1 : 0);
        auto mod = fmodf(frame, 2.f);
        sr->enable = mod;
    }
    else
    {
        sr->enable;
    }
}
