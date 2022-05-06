#include "audio.h"

Audio Audio::Instance;

void Audio::Init()
{
    Instance.device = alcOpenDevice(nullptr);
    Instance.context = alcCreateContext(Instance.device, nullptr);
    alcMakeContextCurrent(Instance.context);
}

void Audio::Quit()
{
    alcDestroyContext(Instance.context);
    alcCloseDevice(Instance.device);
}
