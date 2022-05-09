#pragma once

#include "sound.h"

struct AudioSource
{
    bool enable = true;

    ALCuint id = 0;
    Sound *sound = nullptr;

    AudioSource(Sound *sound = nullptr) : sound(sound)
    {
        alGenSources(1, &id);
        alSourcei(id, AL_BUFFER, sound->id);
    };

    ~AudioSource()
    {
        alDeleteSources(1, &id);
    };
};
