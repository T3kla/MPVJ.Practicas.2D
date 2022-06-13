#include "scene_audio_1.h"

#include "game.h"
#include "render.h"

#include "audio_loader.h"
#include "glfw3.h"
#include "input.h"
#include "sprite_loader.h"

#include "audio_listener.h"
#include "audio_source.h"
#include "camera.h"
#include "circle_collider.h"
#include "gameobject.h"
#include "rigidbody.h"
#include "sprite_renderer.h"
#include "transform.h"

#include "sys_physics.h"

entt::entity listener;
entt::entity source1;
entt::entity source2;
entt::entity source3;

static float pitch = 1.f;

entt::entity CreateSource1(entt::registry &reg)
{
    auto id = reg.create();
    auto &go = reg.emplace<GameObject>(id, true);
    auto &tf = reg.emplace<Transform>(id, Vec2(0.f, 0.f), Vec2::One(), 0.f);
    auto &rb = reg.emplace<RigidBody>(id);
    auto &cm = reg.emplace<Camera>(id, true, true, 1.f);

    auto &as = reg.emplace<AudioSource>(id, true, AudioLoader::GetSound("music.wav"));
    Audio::SetSourceRolloff(as, 0.2f);
    Audio::SourcePlay(as);

    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.sprite = &SpriteLoader::sprSqr;
    sr.size = {25.f, 25.f};
    sr.layer = 1;
    return id;
}

entt::entity CreateSource2(entt::registry &reg)
{
    auto id = reg.create();
    auto &go = reg.emplace<GameObject>(id, true);
    auto &tf = reg.emplace<Transform>(id, Vec2(300.f, 0.f), Vec2::One(), 0.f);
    auto &rb = reg.emplace<RigidBody>(id);

    auto &as = reg.emplace<AudioSource>(id, true, AudioLoader::GetSound("engine.wav"));
    Audio::SetSourceLooping(as, 1);
    Audio::SetSourceRolloff(as, 0.2f);
    Audio::SourcePlay(as);

    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.sprite = &SpriteLoader::sprSqr;
    sr.size = {25.f, 25.f};
    sr.layer = 1;
    return id;
}

entt::entity CreateSource3(entt::registry &reg)
{
    auto id = reg.create();
    auto &go = reg.emplace<GameObject>(id, true);
    auto &tf = reg.emplace<Transform>(id, Vec2(-300.f, 0.f), Vec2::One(), 0.f);
    auto &rb = reg.emplace<RigidBody>(id);

    auto &as = reg.emplace<AudioSource>(id, true, AudioLoader::GetSound("file1.wav"));
    Audio::SetSourceLooping(as, 1);
    Audio::SetSourceRolloff(as, 0.2f);
    Audio::SourcePlay(as);

    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.sprite = &SpriteLoader::sprSqr;
    sr.size = {25.f, 25.f};
    sr.layer = 1;
    return id;
}

entt::entity CreateListener(entt::registry &reg)
{
    auto id = reg.create();

    auto &go = reg.emplace<GameObject>(id, true);
    auto &tf = reg.emplace<Transform>(id, Vec2(0.f, 0.f), Vec2::One(), 0.f);
    auto &rb = reg.emplace<RigidBody>(id);
    auto &al = reg.emplace<AudioListener>(id, true, true);
    auto &sr = reg.emplace<SpriteRenderer>(id);
    sr.sprite = &SpriteLoader::sprCrl;
    sr.size = {35.f, 35.f};
    sr.layer = 1;

    return id;
}

void SceneAudio1::LoadScene()
{
    Render::SetBgColor({0.1f, 0.1f, 0.1f, 1.f});

    auto &reg = Game::GetRegistry();

    source1 = CreateSource1(reg);
    source2 = CreateSource2(reg);
    source3 = CreateSource3(reg);
    listener = CreateListener(reg);

    // Systems
    sysPhysics = new SysPhysics();
}

void SceneAudio1::UnloadScene()
{
    delete sysPhysics;
    delete this;
}

void SceneAudio1::Fixed()
{
    auto &reg = Game::GetRegistry();

    auto step = (float)STP * 0.001f;

    // Move listener
    auto &lisTF = reg.get<Transform>(listener);
    auto &lisRB = reg.get<RigidBody>(listener);
    auto dir = Input::GetMousePosWorld() - lisTF.position;
    lisRB.AddForce(dir, step);

    // Change pitch
    if (Input::GetKey(GLFW_KEY_W) || Input::GetKey(GLFW_KEY_UP))
        pitch += step * 10.f;
    if (Input::GetKey(GLFW_KEY_S) || Input::GetKey(GLFW_KEY_DOWN))
        pitch -= step * 10.f;

    auto *src1 = reg.try_get<AudioSource>(source1);
    auto *src2 = reg.try_get<AudioSource>(source2);
    auto *src3 = reg.try_get<AudioSource>(source3);

    if (src1)
        Audio::SetSourcePitch(*src1, pitch);
    if (src2)
        Audio::SetSourcePitch(*src2, pitch);
    if (src3)
        Audio::SetSourcePitch(*src3, pitch);
}
