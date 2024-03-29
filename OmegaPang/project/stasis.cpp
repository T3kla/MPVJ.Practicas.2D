#include "stasis.h"

#include <Windows.h>

static LARGE_INTEGER buffer = LARGE_INTEGER();

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

    Instance.freq = static_cast<double>(buffer.QuadPart) / 1000.0;
}

void Stasis::RefreshTime()
{
    QueryPerformanceCounter(&buffer);

    Instance.delta = static_cast<double>(buffer.QuadPart - Instance.old) / Instance.freq;
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
