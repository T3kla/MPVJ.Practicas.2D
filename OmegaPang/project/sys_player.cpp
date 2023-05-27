#include "sys_player.h"

#include "ball.h"
#include "circle_collider.h"
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
#include "stasis.h"
#include "sys_hook.h"
#include "sys_ui.h"
#include "textbox.h"
#include "transform.h"

#include <entt/entt.hpp>

constexpr char *stateIdle = "idle";
constexpr char *stateMoving = "moving";
constexpr char *stateShooting = "shooting";
constexpr char *stateHurt = "hurt";
constexpr float blinkRate = 0.2f;

Entity player;
Entity textPlain;
Entity textShadw;

static float moveBlockCounter = 0.f;
static float shootBlockCounter = 0.f;
static float hurtBlockCounter = 0.f;
static float blinkCounter = 0.f;

void UpdateAnimation();

auto BlockMove = [](float time) { moveBlockCounter = time; };
auto BlockShoot = [](float time) { shootBlockCounter = time; };
auto BlockHurt = [](float time) {
    hurtBlockCounter = time;
    blinkCounter = 3.f;
};

auto CanMove = []() { return moveBlockCounter < 0.f; };
auto CanShoot = []() { return shootBlockCounter < 0.f; };
auto IsColliding = [](Vec2 posA, float radA, Vec2 posB, float radB) {
    auto dir = (posA - posB);
    return dir.Magnitude() < radA + radB;
};

auto GetBallsView = []() { return Game::GetRegistry().view<GameObject, Transform, RigidBody, Ball, CircleCollider>(); };

void InstantiatePlayer()
{
    auto &reg = Game::GetRegistry();

    // Reset statics
    moveBlockCounter = 0.f;
    shootBlockCounter = 0.f;
    hurtBlockCounter = 0.f;
    blinkCounter = 0.f;

    // Instantiation
    entt::entity id = reg.create();

    player = Entity(id, &reg);

    auto wSize = Render::GetWindowSize();

    auto &go = reg.get_or_emplace<GameObject>(id);
    go.isActive = true;

    auto &tf = reg.get_or_emplace<Transform>(id);
    tf.position = {static_cast<float>(wSize.x) / 2.f, static_cast<float>(wSize.y) - 50.f};
    tf.scale = Vec2::One();
    tf.rotation = 0.f;

    auto &rb = reg.get_or_emplace<RigidBody>(id);
    rb.enable = true;
    rb.velocity = Vec2::Zero();
    rb.linearDrag = 0.2f;

    auto &pl = reg.get_or_emplace<Player>(id);
    pl.enable = true;
    pl.health = 3;
    pl.speed = 10.f;
    pl.state = stateIdle;
    pl.reversed = false;

    auto &cc = reg.get_or_emplace<CircleCollider>(id);
    cc.enable = true;
    cc.radius = 50.f;

    auto &sr = reg.get_or_emplace<SpriteRenderer>(id);
    sr.enable = true;
    sr.sprite = &SpriteLoader::sprPlayerMoveL[0];
    sr.offsetPosition = Vec2::Zero();
    sr.offsetRotation = 0.f;
    sr.size = {100.f, 100.f};
    sr.pivot = Vec2::One() * 0.5f;
    sr.layer = 10;
    sr.blend = BLEND_ALPHA;

    auto &sa = reg.get_or_emplace<SpriteAnimation>(id);
    sa.enable = true;
    sa.animation = &SpriteLoader::sprPlayerShootR;
    sa.frame = 0;
    sa.speed = 0.f;
    sa.duration = 1.f;
    sa.count = 0.f;
}

void InstantiatePlayerText()
{
    auto &reg = Game::GetRegistry();
    auto *font = FontLoader::GetFont("fontOrange.ttf");

    auto plain = SysUI::Instantiate({80.f, 100.f}, "Health: 3", font, 11.f, {1.f, 1.f, 1.f, 1.f});
    auto shadow = SysUI::Instantiate({82.f, 102.f}, "Health: 3", font, 11.f, {0.f, 0.f, 0.f, 1.f});

    textPlain = Entity(plain, &reg);
    textShadw = Entity(shadow, &reg);
}

SysPlayer::SysPlayer()
{
    InstantiatePlayer();
    InstantiatePlayerText();
}

void SysPlayer::Update()
{
    auto time = static_cast<float>(Stasis::GetDeltaScaled()) * 0.001f;
    moveBlockCounter -= time;
    shootBlockCounter -= time;
    hurtBlockCounter -= time;
    blinkCounter -= time;

    auto &reg = Game::GetRegistry();
    auto playerID = player.GetID();

    auto &tf = reg.get<Transform>(playerID);
    auto &go = reg.get<GameObject>(playerID);
    auto &rb = reg.get<RigidBody>(playerID);
    auto &pl = reg.get<Player>(playerID);
    auto &cc = reg.get<CircleCollider>(playerID);
    auto &sa = reg.get<SpriteAnimation>(playerID);

    if (!go.isActive)
        return;

    // Collision with balls
    for (auto &[entity, ball_go, ball_tf, ball_rb, ball_bl, ball_cc] : GetBallsView().each())
    {
        if (!ball_go.isActive || pl.health <= 0 || blinkCounter > 0.f)
            continue;

        if (IsColliding(tf.position, cc.radius, ball_tf.position, ball_cc.radius / 2.f))
        {
            pl.health += pl.health > 0 ? -1 : 0;
            BlockHurt(0.3f);
            BlockShoot(0.3f);
            BlockMove(0.3f);

            if (pl.health <= 0)
            {
                BlockHurt(9999.9f);
                BlockShoot(9999.9f);
                BlockMove(9999.9f);
            }

            // Update health text
            char buffer[10];
            sprintf_s(buffer, "Health: %d", pl.health);
            reg.get<TextBox>(textPlain.GetID()).text = buffer;
            reg.get<TextBox>(textShadw.GetID()).text = buffer;

            // Change health text color
            if (pl.health == 1)
                reg.get<TextBox>(textPlain.GetID()).color = {1.f, 0.3f, 0.3f, 1.f};
        }
    }

    // Input Move
    auto wSize = Render::GetWindowSize();

    Vec2 add = Vec2::Zero();

    if (CanMove() && Input::GetKey(GLFW_KEY_A))
        add -= pl.speed * static_cast<float>(Stasis::GetDelta());
    if (CanMove() && Input::GetKey(GLFW_KEY_D))
        add += pl.speed * static_cast<float>(Stasis::GetDelta());

    rb.velocity += add;

    auto velMag = rb.velocity.Magnitude();

    if (velMag > pl.speed)
        rb.velocity = rb.velocity.Normalized() * pl.speed;

    pl.reversed = rb.velocity.x < 0.f ? true : false;

    // Bounds
    if (tf.position.x > static_cast<float>(wSize.x) - cc.radius / 2.f)
    {
        tf.position.x = static_cast<float>(wSize.x) - cc.radius / 2.f - 1.f;
        rb.velocity.x = 0;
    }
    if (tf.position.x < cc.radius / 2.f)
    {
        tf.position.x = cc.radius / 2.f + 1.f;
        rb.velocity.x = 0;
    }

    // Input Shoot
    if (CanShoot() && Input::GetKey(GLFW_KEY_W))
    {
        BlockShoot(0.3f);
        BlockMove(0.1f);
        SysHook::Instantiate(tf.position);
    }

    // State Machine
    if (hurtBlockCounter > 0.f)
        pl.state = stateHurt;
    else if (!CanShoot())
        pl.state = stateShooting;
    else if (CanMove())
        pl.state = velMag > pl.speed / 2.f ? stateMoving : stateIdle;

    UpdateAnimation();
}

Entity *SysPlayer::GetPlayer()
{
    return &player;
}

int SysPlayer::GetPlayerHealth()
{
    auto health = player.GetReg().get<Player>(player.GetID()).health;
    return health ? health : 0;
}

void UpdateAnimation()
{
    auto id = player.GetID();
    auto &pl = player.GetReg().get<Player>(id);
    auto &sr = player.GetReg().get<SpriteRenderer>(id);
    auto &sa = player.GetReg().get<SpriteAnimation>(id);

    if (pl.state == stateHurt)
    {
        sa.enable = false;
        sr.sprite = pl.reversed ? &SpriteLoader::sprPlayerHitL : &SpriteLoader::sprPlayerHitR;
    }
    else if (pl.state == stateMoving)
    {
        sa.enable = true;
        sa.duration = 0.25f;
        sa.animation = pl.reversed ? &SpriteLoader::sprPlayerMoveL : &SpriteLoader::sprPlayerMoveR;
    }
    else if (pl.state == stateShooting)
    {
        sa.enable = true;
        sa.duration = 0.4f;
        sa.animation = pl.reversed ? &SpriteLoader::sprPlayerShootL : &SpriteLoader::sprPlayerShootR;
    }
    else if (pl.state == stateIdle)
    {
        sa.enable = false;
        sr.sprite = pl.reversed ? &SpriteLoader::sprPlayerShootL[0] : &SpriteLoader::sprPlayerShootR[0];
    }

    // Blink if invulnerable
    if (blinkCounter > 0.f)
    {
        auto frameFreq = blinkRate / 2.f;
        auto frame = floorf(blinkCounter / frameFreq) + (pl.health > 0 ? 1 : 0);
        auto mod = fmodf(frame, 2.f);
        sr.enable = mod;
    }
    else
    {
        sr.enable;
    }
}
