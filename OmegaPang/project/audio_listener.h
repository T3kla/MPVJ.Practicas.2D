#pragma once

#pragma once

#include "sound.h"
#include "vec.h"

struct AudioListener
{
    bool enable = true;

    ALCuint id = 0;

    AudioListener()
    {
        alSourcei(id, AL_BUFFER, sound->id);
    };
};
