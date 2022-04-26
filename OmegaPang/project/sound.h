#pragma once

#include "openal/AL/alc.h"

class Sound
{
    friend class Game;
    static Sound Instance;

  private:
    Sound() = default;
    Sound(const Sound &) = delete;

    ALCdevice *device;
    ALCcontext *context;

    static void Init();
    static void Quit();
};
