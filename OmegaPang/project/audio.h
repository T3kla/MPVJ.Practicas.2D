#pragma once

#include "al.h"
#include "alc.h"

class Audio
{
    friend class Game;
    static Audio Instance;

  private:
    Audio() = default;
    Audio(const Audio &) = delete;

    ALCdevice *device;
    ALCcontext *context;

    ALuint *buffers;

    static void Init();
    static void Quit();
};
