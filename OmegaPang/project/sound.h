#pragma once

#include "openal/AL/alc.h"

struct Sound
{
    const char *name = nullptr;
    ALCuint id;

    Sound(const char *name = nullptr, ALCuint id = 0) : name(name), id(id){};
};
