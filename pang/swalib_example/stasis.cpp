#include "stasis.h"
#include <windows.h>

Stasis Stasis::Instance;

Stasis::Stasis(const double &scale)
{
    this->scale = scale;
    RefreshFreq();
    QueryPerformanceCounter(&buffer);
    old = buffer.QuadPart;
}

Stasis &Stasis::Get()
{
    return Instance;
}

void Stasis::RefreshFreq()
{
    if (!QueryPerformanceFrequency(&Instance.buffer))
        throw "Counter error";

    Instance.freq = double(Instance.buffer.QuadPart) / 1000.;
}

void Stasis::RefreshTime()
{
    QueryPerformanceCounter(&Instance.buffer);

    Instance.delta = double(Instance.buffer.QuadPart - Instance.old) / Instance.freq;
    Instance.deltaScaled = Instance.delta * Instance.scale;

    Instance.old = Instance.buffer.QuadPart;

    Instance.time += Instance.delta;
    Instance.timeScaled += Instance.delta * Instance.scale;

    RefreshFreq();
}

const double &Stasis::GetTime()
{
    return Instance.time;
}
const double &Stasis::GetDelta()
{
    return Instance.delta;
}

const double &Stasis::GetTimeScaled()
{
    return Instance.timeScaled;
}
const double &Stasis::GetDeltaScaled()
{
    return Instance.deltaScaled;
}

void Stasis::SetScale(const double &scale)
{
    Instance.scale = scale;
}
const double &Stasis::GetScale()
{
    return Instance.scale;
}
