#include "audio.h"

#include "vec.h"

#include "audio_source.h"

#include "game.h"

#include "audio_listener.h"
#include "audio_source.h"
#include "gameobject.h"
#include "rigidbody.h"
#include "transform.h"

Audio Audio::Instance;

void Audio::Init()
{
    Instance.device = alcOpenDevice(nullptr);
    Instance.context = alcCreateContext(Instance.device, nullptr);
    alcMakeContextCurrent(Instance.context);
}

void Audio::Fixed()
{
    auto &reg = Game::GetRegistry();

    auto asView = reg.view<GameObject, Transform, RigidBody, AudioSource>();
    for (auto [entity, go, tf, rb, as] : asView.each())
    {
        Audio::SetSourcePosition(as, tf.position);
        Audio::SetSourceDirection(as, {0.f, 0.f});
        Audio::SetSourceVelocity(as, rb.velocity);
    }

    auto alView = reg.view<GameObject, Transform, RigidBody, AudioListener>();
    for (auto [entity, go, tf, rb, al] : alView.each())
        if (al.main)
        {
            Audio::SetListenerPosition(tf.position);
            Audio::SetListenerOrientation({0.f, 0.f});
            Audio::SetListenerVelocity(rb.velocity);
        }
}

void Audio::Quit()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(Instance.context);
    alcCloseDevice(Instance.device);
}

// ------------------------------------------------------------------ Source

// Void

void Audio::SourcePlay(const AudioSource &source)
{
    alSourcePlay(source.id);
}

void Audio::SourceStop(const AudioSource &source)
{
    alSourceStop(source.id);
}

void Audio::SourcePause(const AudioSource &source)
{
    alSourcePause(source.id);
}

// Int

void Audio::SetSourceRelative(const AudioSource &source, int value)
{
    alSourcei(source.id, AL_SOURCE_RELATIVE, value);
}

void Audio::SetSourceLooping(const AudioSource &source, int value)
{
    alSourcei(source.id, AL_LOOPING, value);
}

void Audio::SetSourceBuffer(const AudioSource &source, int value)
{
    alSourcei(source.id, AL_BUFFER, value);
}

int Audio::GetSourceRelative(const AudioSource &source)
{
    int value;
    alGetSourcei(source.id, AL_SOURCE_RELATIVE, &value);
    return value;
}

int Audio::GetSourceBuffer(const AudioSource &source)
{
    int value;
    alGetSourcei(source.id, AL_BUFFER, &value);
    return value;
}

int Audio::GetSourceState(const AudioSource &source)
{
    int value;
    alGetSourcei(source.id, AL_SOURCE_STATE, &value);
    return value;
}

// Float

void Audio::SetSourcePitch(const AudioSource &source, float value)
{
    alSourcei(source.id, AL_PITCH, value);
}

void Audio::SetSourceGain(const AudioSource &source, float value)
{
    alSourcei(source.id, AL_GAIN, value);
}

void Audio::SetSourceMinGain(const AudioSource &source, float value)
{
    alSourcei(source.id, AL_MIN_GAIN, value);
}

void Audio::SetSourceMaxGain(const AudioSource &source, float value)
{
    alSourcei(source.id, AL_MAX_GAIN, value);
}

void Audio::SetSourceMaxDistance(const AudioSource &source, float value)
{
    alSourcei(source.id, AL_MAX_DISTANCE, value);
}

void Audio::SetSourceRefDistance(const AudioSource &source, float value)
{
    alSourcei(source.id, AL_REFERENCE_DISTANCE, value);
}

void Audio::SetSourceRolloff(const AudioSource &source, float value)
{
    alSourcei(source.id, AL_ROLLOFF_FACTOR, value);
}

void Audio::SetSourceConeOuterGain(const AudioSource &source, float value)
{
    alSourcei(source.id, AL_CONE_OUTER_GAIN, value);
}

void Audio::SetSourceConeInnerAngle(const AudioSource &source, float value)
{
    alSourcei(source.id, AL_CONE_INNER_ANGLE, value);
}

void Audio::SetSourceConeOuterAngle(const AudioSource &source, float value)
{
    alSourcei(source.id, AL_CONE_OUTER_ANGLE, value);
}

// Vec3

void Audio::SetSourcePosition(const AudioSource &source, Vec2 value)
{
    alSource3f(source.id, AL_POSITION, value.x, value.y, 0.f);
}

void Audio::SetSourceDirection(const AudioSource &source, Vec2 value)
{
    alSource3f(source.id, AL_DIRECTION, value.x, value.y, 0.f);
}

void Audio::SetSourceVelocity(const AudioSource &source, Vec2 value)
{
    alSource3f(source.id, AL_VELOCITY, value.x, value.y, 0.f);
}

// ------------------------------------------------------------------ Listener

// Float

void Audio::SetListenerPosition(Vec2 position)
{
    alListener3f(AL_POSITION, position.x, position.y, 0.f);
}

void Audio::SetListenerOrientation(Vec2 orientation)
{
    alListener3f(AL_ORIENTATION, orientation.x, orientation.y, 0.f);
}

void Audio::SetListenerVelocity(Vec2 velocity)
{
    alListener3f(AL_VELOCITY, velocity.x, velocity.y, 0.f);
}
