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
        alSourcei(as.id, AL_SOURCE_RELATIVE, 0);
        alSourcei(as.id, AL_LOOPING, 0);
        alSourcei(as.id, AL_BUFFER, 0);
        alSource3f(as.id, AL_POSITION, tf.position.x, tf.position.y, 0.f);
        alSource3f(as.id, AL_DIRECTION, 0.f, 0.f, 0.f);
        alSource3f(as.id, AL_VELOCITY, rb.velocity.x, rb.velocity.y, 0.f);
    }

    auto alView = reg.view<GameObject, Transform, RigidBody, AudioListener>();
    for (auto [entity, go, tf, rb, al] : asView.each())
    {
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

void Audio::SourcePlay(AudioSource source)
{
    alSourcePlay(source.id);
}

void Audio::SourceStop(AudioSource source)
{
    alSourceStop(source.id);
}

void Audio::SourcePause(AudioSource source)
{
    alSourcePause(source.id);
}

// Int

void Audio::SetSourceRelative(AudioSource source, int value)
{
    alSourcei(source.id, AL_SOURCE_RELATIVE, value);
}

void Audio::SetSourceLooping(AudioSource source, int value)
{
    alSourcei(source.id, AL_LOOPING, value);
}

void Audio::SetSourceBuffer(AudioSource source, int value)
{
    alSourcei(source.id, AL_BUFFER, value);
}

int Audio::GetSourceRelative(AudioSource source)
{
    int value;
    alGetSourcei(source.id, AL_SOURCE_RELATIVE, &value);
    return value;
}

int Audio::GetSourceBuffer(AudioSource source)
{
    int value;
    alGetSourcei(source.id, AL_BUFFER, &value);
    return value;
}

int Audio::GetSourceState(AudioSource source)
{
    int value;
    alGetSourcei(source.id, AL_SOURCE_STATE, &value);
    return value;
}

// Float

void Audio::SetSourcePitch(AudioSource source, float value)
{
    alSourcei(source.id, AL_PITCH, value);
}

void Audio::SetSourceGain(AudioSource source, float value)
{
    alSourcei(source.id, AL_GAIN, value);
}

void Audio::SetSourceMinGain(AudioSource source, float value)
{
    alSourcei(source.id, AL_MIN_GAIN, value);
}

void Audio::SetSourceMaxGain(AudioSource source, float value)
{
    alSourcei(source.id, AL_MAX_GAIN, value);
}

void Audio::SetSourceMaxDistance(AudioSource source, float value)
{
    alSourcei(source.id, AL_MAX_DISTANCE, value);
}

void Audio::SetSourceRefDistance(AudioSource source, float value)
{
    alSourcei(source.id, AL_REFERENCE_DISTANCE, value);
}

void Audio::SetSourceRolloff(AudioSource source, float value)
{
    alSourcei(source.id, AL_ROLLOFF_FACTOR, value);
}

void Audio::SetSourceConeOuterGain(AudioSource source, float value)
{
    alSourcei(source.id, AL_CONE_OUTER_GAIN, value);
}

void Audio::SetSourceConeInnerAngle(AudioSource source, float value)
{
    alSourcei(source.id, AL_CONE_INNER_ANGLE, value);
}

void Audio::SetSourceConeOuterAngle(AudioSource source, float value)
{
    alSourcei(source.id, AL_CONE_OUTER_ANGLE, value);
}

// Vec3

void Audio::SetSourcePosition(AudioSource source, Vec2 value)
{
    alSource3f(source.id, AL_POSITION, value.x, value.y, 0.f);
}

void Audio::SetSourceDirection(AudioSource source, Vec2 value)
{
    alSource3f(source.id, AL_DIRECTION, value.x, value.y, 0.f);
}

void Audio::SetSourceVelocity(AudioSource source, Vec2 value)
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
