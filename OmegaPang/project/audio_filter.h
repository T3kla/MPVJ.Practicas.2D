#pragma once

#include "openal/efx.h"

LPALGENFILTERS alGenFilters = (LPALGENFILTERS)alGetProcAddress("alGenFilters");

LPALDELETEFILTERS alDeleteFilters = (LPALDELETEFILTERS)alGetProcAddress("alDeleteFilters");

LPALFILTERI alFilteri = (LPALFILTERI)alGetProcAddress("alFilteri");

struct AudioFilter
{
    ALuint id;

    AudioFilter(ALuint id = 0) : id(id)
    {
        alGenFilters(1, &id);
    };

    ~AudioFilter()
    {
        alDeleteFilters(1, &id);
    };
};
