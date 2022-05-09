#pragma once

#include "audio.h"
#include "sound.h"

struct AudioSource
{
    bool enable = true;

    ALCuint id = 0;
    Sound *sound = nullptr;

    AudioSource(Sound *sound = nullptr) : sound(sound)
    {
        alGenSources(1, &id);

        if (sound)
            Audio::SetSourceBuffer(*this, sound->id);
    };

    ~AudioSource()
    {
        alDeleteSources(1, &id);
    };
};
