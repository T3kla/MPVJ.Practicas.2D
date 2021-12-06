#include "stasis.h"
#include <windows.h>

Stasis Stasis::instance;

Stasis::Stasis()
{
    RefreshFreq();
    QueryPerformanceCounter(&buffer);
    old = buffer.QuadPart;
}

Stasis &Stasis::Get()
{
    return instance;
}

void Stasis::RefreshFreq()
{
    if (!QueryPerformanceFrequency(&buffer))
        throw "Counter error";

    freq = double(buffer.QuadPart) / 1000.;
}

void Stasis::Update()
{
    QueryPerformanceCounter(&buffer);
    deltaUnscaled = double(buffer.QuadPart - old) / freq;
    old = buffer.QuadPart;
    timeUnscaled += deltaUnscaled;
    deltaScaled = deltaUnscaled * scale;
    timeScaled += deltaScaled;
    RefreshFreq();
}

double Stasis::GetDeltaUnscaled()
{
    return Get().deltaUnscaled;
}

double Stasis::GetTimeUnscaled()
{
    return Get().timeUnscaled;
}

double Stasis::GetDeltaScaled()
{
    return Get().deltaScaled;
}

double Stasis::GetTimeScaled()
{
    return Get().timeScaled;
}

double Stasis::GetScale()
{
    return Get().scale;
}

void Stasis::SetScale(const double &_scale)
{
    Get().scale = _scale;
}
