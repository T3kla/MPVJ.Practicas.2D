#include "stasis.h"

#include <Windows.h>

LARGE_INTEGER buffer = LARGE_INTEGER();

Stasis Stasis::Instance;

Stasis::Stasis(const double &scale)
{
    this->scale = scale;
    RefreshFreq();
    QueryPerformanceCounter(&buffer);
    old = buffer.QuadPart;
}

void Stasis::RefreshFreq()
{
    if (!QueryPerformanceFrequency(&buffer))
        throw "Counter error";

    Instance.freq = double(buffer.QuadPart) / 1000.;
}

void Stasis::RefreshTime()
{
    QueryPerformanceCounter(&buffer);

    Instance.delta = double(buffer.QuadPart - Instance.old) / Instance.freq;
    Instance.deltaScaled = Instance.delta * Instance.scale;

    Instance.old = buffer.QuadPart;

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
