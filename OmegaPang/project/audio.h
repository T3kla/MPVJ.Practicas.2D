#pragma once

#include "openal/AL/al.h"
#include "openal/AL/alc.h"

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

    static void InitBuffers(int n);
};
