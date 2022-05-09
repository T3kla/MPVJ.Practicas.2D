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

  public:
    // ------------------------------------------------------------------ Source

    // Void
    static void SourcePlay(const AudioSource &source);
    static void SourceStop(const AudioSource &source);
    static void SourcePause(const AudioSource &source);

    // Int
    static void SetSourceRelative(const AudioSource &source, int value);
    static void SetSourceLooping(const AudioSource &source, int value);
    static void SetSourceBuffer(const AudioSource &source, int value);

    static int GetSourceRelative(const AudioSource &source);
    static int GetSourceBuffer(const AudioSource &source);
    static int GetSourceState(const AudioSource &source);

    // Float
    static void SetSourcePitch(const AudioSource &source, float value);
    static void SetSourceGain(const AudioSource &source, float value);
    static void SetSourceMinGain(const AudioSource &source, float value);
    static void SetSourceMaxGain(const AudioSource &source, float value);
    static void SetSourceMaxDistance(const AudioSource &source, float value);
    static void SetSourceRefDistance(const AudioSource &source, float value);
    static void SetSourceRolloff(const AudioSource &source, float value);
    static void SetSourceConeOuterGain(const AudioSource &source, float value);
    static void SetSourceConeInnerAngle(const AudioSource &source, float value);
    static void SetSourceConeOuterAngle(const AudioSource &source, float value);

    // Vec3
    static void SetSourcePosition(const AudioSource &source, Vec2 value);
    static void SetSourceDirection(const AudioSource &source, Vec2 value);
    static void SetSourceVelocity(const AudioSource &source, Vec2 value);

    // ------------------------------------------------------------------ Listener

    // Float
    static void SetListenerPosition(Vec2 value);
    static void SetListenerOrientation(Vec2 value);
    static void SetListenerVelocity(Vec2 value);
};
