#include "audio.h"

#include "vec.h"

#include "game.h"

#include "audio_listener.h"
#include "audio_source.h"
#include "gameobject.h"
#include "rigidbody.h"
#include "transform.h"

#include "audio_effect.h"
#include "audio_filter.h"
#include "audio_slot.h"

#include "openal/efx.h"

LPALEFFECTI alEffecti = (LPALEFFECTI)alGetProcAddress("alEffecti");

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

    auto asView = reg.view<GameObject, Transform, AudioSource>();
    for (auto [entity, go, tf, as] : asView.each())
    {
        auto *rb = reg.try_get<RigidBody>(entity);
        Audio::SetSourcePosition(as, tf.position);
        Audio::SetSourceVelocity(as, rb ? rb->velocity : Vec2(0.f, 0.f));
    }

    auto alView = reg.view<GameObject, Transform, AudioListener>();
    for (auto [entity, go, tf, al] : alView.each())
        if (al.main)
        {
            auto *rb = reg.try_get<RigidBody>(entity);
            Audio::SetListenerPosition(tf.position);
            Audio::SetListenerVelocity(rb ? rb->velocity : Vec2(0.f, 0.f));
            break;
        }
}

void Audio::Quit()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(Instance.context);
    alcCloseDevice(Instance.device);
}

// ------------------------------------------------------------------ Listener

// Vec3

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

void Audio::SetSourceSlot(const AudioSource &source, int value)
{
    alSource3i(source.id, AL_AUXILIARY_SEND_FILTER, value, 0, 0);
}

void Audio::SetSourceFilter(const AudioSource &source, int value)
{
    alSourcei(source.id, AL_DIRECT_FILTER, value);
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
    alSourcef(source.id, AL_PITCH, value);
}

void Audio::SetSourceGain(const AudioSource &source, float value)
{
    alSourcef(source.id, AL_GAIN, value);
}

void Audio::SetSourceMinGain(const AudioSource &source, float value)
{
    alSourcef(source.id, AL_MIN_GAIN, value);
}

void Audio::SetSourceMaxGain(const AudioSource &source, float value)
{
    alSourcef(source.id, AL_MAX_GAIN, value);
}

void Audio::SetSourceMaxDistance(const AudioSource &source, float value)
{
    alSourcef(source.id, AL_MAX_DISTANCE, value);
}

void Audio::SetSourceRefDistance(const AudioSource &source, float value)
{
    alSourcef(source.id, AL_REFERENCE_DISTANCE, value);
}

void Audio::SetSourceRolloff(const AudioSource &source, float value)
{
    alSourcef(source.id, AL_ROLLOFF_FACTOR, value);
}

void Audio::SetSourceConeOuterGain(const AudioSource &source, float value)
{
    alSourcef(source.id, AL_CONE_OUTER_GAIN, value);
}

void Audio::SetSourceConeInnerAngle(const AudioSource &source, float value)
{
    alSourcef(source.id, AL_CONE_INNER_ANGLE, value);
}

void Audio::SetSourceConeOuterAngle(const AudioSource &source, float value)
{
    alSourcef(source.id, AL_CONE_OUTER_ANGLE, value);
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

// ------------------------------------------------------------------ Slot

AudioSlot *Audio::CreateSlot()
{
    return new AudioSlot();
}

// ------------------------------------------------------------------ Effects

AudioEffect *Audio::CreateEffect()
{
    return new AudioEffect();
}

void Audio::SetEffectReverb(const AudioEffect &effect, int value)
{
    alEffecti(effect.id, AL_EFFECT_REVERB, value);
}

void Audio::SetEffectChorus(const AudioEffect &effect, int value)
{
    alEffecti(effect.id, AL_EFFECT_CHORUS, value);
}

void Audio::SetEffectDistortion(const AudioEffect &effect, int value)
{
    alEffecti(effect.id, AL_EFFECT_DISTORTION, value);
}

void Audio::SetEffectEcho(const AudioEffect &effect, int value)
{
    alEffecti(effect.id, AL_EFFECT_ECHO, value);
};

void Audio::SetEffectFlanger(const AudioEffect &effect, int value)
{
    alEffecti(effect.id, AL_EFFECT_FLANGER, value);
}

// ------------------------------------------------------------------ Filters

AudioFilter *Audio::CreateFilter()
{
    return new AudioFilter();
}

void Audio::SetFilterNull(const AudioFilter &filter, int value)
{
    alFilteri(filter.id, AL_FILTER_TYPE, AL_FILTER_NULL);
}

void Audio::SetFilterLowPass(const AudioFilter &filter, int value)
{
    alFilteri(filter.id, AL_FILTER_TYPE, AL_FILTER_LOWPASS);
}

void Audio::SetFilterHighPass(const AudioFilter &filter, int value)
{
    alFilteri(filter.id, AL_FILTER_TYPE, AL_FILTER_HIGHPASS);
}

void Audio::SetFilterBandPass(const AudioFilter &filter, int value)
{
    alFilteri(filter.id, AL_FILTER_TYPE, AL_FILTER_BANDPASS);
}
