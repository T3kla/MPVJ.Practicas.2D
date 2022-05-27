#pragma once

#include "openal/efx.h"

LPALGENEFFECTS alGenEffects = (LPALGENEFFECTS)alGetProcAddress("alGenEffects");

LPALDELETEEFFECTS alDeleteEffects = (LPALDELETEEFFECTS)alGetProcAddress("alDeleteEffects");

struct AudioEffect
{
    ALuint id;

    AudioEffect(ALuint id = 0) : id(id)
    {
        alGenEffects(1, &id);
    };

    ~AudioEffect()
    {
        alDeleteEffects(1, &id);
    };
};
