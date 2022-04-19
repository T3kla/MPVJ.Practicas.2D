#include "sys_mapPlayer.h"

#include "ball.h"
#include "camera.h"
#include "entity.h"
#include "font_loader.h"
#include "game.h"
#include "gameobject.h"
#include "glfw3.h"
#include "input.h"
#include "player.h"
#include "render.h"
#include "rigidbody.h"
#include "sprite_animation.h"
#include "sprite_loader.h"
#include "sprite_renderer.h"
#include "square_collider.h"
#include "stasis.h"
#include "sys_hook.h"
#include "sys_ui.h"
#include "textbox.h"
#include "transform.h"

#include <entt/entt.hpp>

static constexpr char *stateIdle = "idle";
static constexpr char *stateMoving = "moving";

static Entity player;

static bool actionJump = false;
static bool actionJumpOld = false;

static void InstantiatePlayer()
{
    auto &reg = Game::GetRegistry();

    // Instantiation
    entt::entity id = reg.create();

    player = Entity(id, &reg);

    auto wSize = Render::GetWindowSize();

    auto &go = reg.get_or_emplace<GameObject>(id);
    go.isActive = true;

    auto &tf = reg.get_or_emplace<Transform>(id);
    tf.position = {500.f, 300.f};
    tf.scale = Vec2::One();
    tf.rotation = 0.f;

    auto &rb = reg.get_or_emplace<RigidBody>(id);
    rb.enable = true;
    rb.velocity = Vec2::Zero();
    rb.linearDrag = 0.2f;
    rb.gravity = true;
    rb.gravityScale = 10.f;

    auto &sc = reg.get_or_emplace<SquareCollider>(id);
    sc.enable = true;
    sc.center = {0.f, 0.f};
    sc.size = {32.f, 64.f};

    auto &sr = reg.get_or_emplace<SpriteRenderer>(id);
    sr.enable = true;
    sr.sprite = &SpriteLoader::sprPlayerMoveL[0];
    sr.offsetPosition = Vec2::Zero();
    sr.offsetRotation = 0.f;
    sr.size = {64.f, 64.f};
    sr.pivot = Vec2::One() * 0.5f;
    sr.layer = 10;
    sr.blend = BLEND_ALPHA;

    auto &sa = reg.get_or_emplace<SpriteAnimation>(id);
    sa.enable = true;
    sa.animation = &SpriteLoader::sprMapPlayerRun;
    sa.frame = 0;
    sa.speed = 0.f;
    sa.duration = 1.f;
    sa.count = 0.f;

    auto &pl = reg.get_or_emplace<Player>(id);
    pl.enable = true;
    pl.health = 3;
    pl.speed = 5.f;
    pl.state = stateIdle;
    pl.reversed = false;

    auto &cm = reg.get_or_emplace<Camera>(id);
    cm.enable = true;
    cm.main = true;
    cm.height = 1.f;
}

static void UpdateAnimation()
{
    auto id = player.GetID();
    auto &pl = player.GetReg().get<Player>(id);
    auto &sr = player.GetReg().get<SpriteRenderer>(id);
    auto &sa = player.GetReg().get<SpriteAnimation>(id);

    if (pl.state == stateMoving)
    {
        sa.enable = true;
        sa.duration = 0.8f;
        sa.animation = &SpriteLoader::sprMapPlayerRun;
    }
    else if (pl.state == stateIdle)
    {
        sa.enable = false;
        sr.sprite = &SpriteLoader::sprMapPlayerIdle;
    }
}

SysMapPlayer::SysMapPlayer()
{
    InstantiatePlayer();
}

void SysMapPlayer::Fixed()
{
    auto time = (float)Stasis::GetDeltaScaled() * 0.001f;

    auto &reg = Game::GetRegistry();
    auto playerID = player.GetID();

    auto &tf = reg.get<Transform>(playerID);
    auto &go = reg.get<GameObject>(playerID);
    auto &rb = reg.get<RigidBody>(playerID);
    auto &pl = reg.get<Player>(playerID);
    auto &sc = reg.get<SquareCollider>(playerID);
    auto &sr = reg.get<SpriteRenderer>(playerID);
    auto &sa = reg.get<SpriteAnimation>(playerID);

    if (!go.isActive)
        return;

    // Input Move
    float add = 0.f;

    if (Input::GetKey(GLFW_KEY_A))
        add -= pl.speed;
    if (Input::GetKey(GLFW_KEY_D))
        add += pl.speed;

    actionJump = Input::GetKey(GLFW_KEY_SPACE);
    if (actionJump && !actionJumpOld)
        rb.velocity.y = -6.f;
    actionJumpOld = actionJump;

    // Debug
    Vec2 tl = tf.position + Vec2(sc.center.x - sc.size.x / 2.f, sc.center.y - sc.size.y / 2.f);
    Vec2 br = tf.position + Vec2(sc.center.x + sc.size.x / 2.f, sc.center.y + sc.size.y / 2.f);
    Render::DrawDebugSquare(tl, br, {1.f, 0.f, 0.f, 1.f}, {1.f, 1.f, 1.f, 1.f});

    // Velocity
    rb.velocity.x = add;

    sr.reverse = rb.velocity.x < 0.f ? true : false;

    // State Machine
    pl.state = fabsf(rb.velocity.x) < 1.f ? stateIdle : stateMoving;

    UpdateAnimation();
}

Entity *SysMapPlayer::GetPlayer()
{
    return &player;
}
