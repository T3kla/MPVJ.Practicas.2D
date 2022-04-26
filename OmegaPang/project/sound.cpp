#include "sound.h"

Sound Sound::Instance;

void Sound::Init()
{
    Instance.device = alcOpenDevice(nullptr);
    Instance.context = alcCreateContext(Instance.device, nullptr);
    alcMakeContextCurrent(Instance.context);
}

void Sound::Quit()
{
    alcDestroyContext(Instance.context);
    alcCloseDevice(Instance.device);
}
