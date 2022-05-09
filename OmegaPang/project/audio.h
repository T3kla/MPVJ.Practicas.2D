#pragma once

#include "openal/al.h"
#include "openal/alc.h"

struct AudioSource;
struct Vec2;

class Audio
{
    friend class Game;
    static Audio Instance;

  private:
    Audio() = default;
    Audio(const Audio &) = delete;

    ALCdevice *device;
    ALCcontext *context;

    static void Init();
    static void Fixed();
    static void Quit();

    // ------------------------------------------------------------------ Source

    // Void
    static void SourcePlay(AudioSource source);
    static void SourceStop(AudioSource source);
    static void SourcePause(AudioSource source);

    // Int
    static void SetSourceRelative(AudioSource source, int value);
    static void SetSourceLooping(AudioSource source, int value);
    static void SetSourceBuffer(AudioSource source, int value);

    static int GetSourceRelative(AudioSource source);
    static int GetSourceBuffer(AudioSource source);
    static int GetSourceState(AudioSource source);

    // Float
    static void SetSourcePitch(AudioSource source, float value);
    static void SetSourceGain(AudioSource source, float value);
    static void SetSourceMinGain(AudioSource source, float value);
    static void SetSourceMaxGain(AudioSource source, float value);
    static void SetSourceMaxDistance(AudioSource source, float value);
    static void SetSourceRefDistance(AudioSource source, float value);
    static void SetSourceRolloff(AudioSource source, float value);
    static void SetSourceConeOuterGain(AudioSource source, float value);
    static void SetSourceConeInnerAngle(AudioSource source, float value);
    static void SetSourceConeOuterAngle(AudioSource source, float value);

    // Vec3
    static void SetSourcePosition(AudioSource source, Vec2 value);
    static void SetSourceDirection(AudioSource source, Vec2 value);
    static void SetSourceVelocity(AudioSource source, Vec2 value);

    // ------------------------------------------------------------------ Listener

    // Float
    static void SetListenerPosition(Vec2 value);
    static void SetListenerOrientation(Vec2 value);
    static void SetListenerVelocity(Vec2 value);
};
