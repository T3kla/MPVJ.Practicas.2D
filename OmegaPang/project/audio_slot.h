#pragma once

#include "openal/efx.h"

LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots =
    (LPALGENAUXILIARYEFFECTSLOTS)alGetProcAddress("alGenAuxiliaryEffectSlots");

LPALDELETEAUXILIARYEFFECTSLOTS alDeleteAuxiliaryEffectSlots =
    (LPALDELETEAUXILIARYEFFECTSLOTS)alGetProcAddress("alDeleteAuxiliaryEffectSlots");

struct AudioSlot
{
    ALuint id;

    AudioSlot(ALuint id = 0) : id(id)
    {
        alGenAuxiliaryEffectSlots(1, &id);
    };

    ~AudioSlot()
    {
        alDeleteAuxiliaryEffectSlots(1, &id);
    };
};
