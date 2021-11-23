#include "time.h"
#include <iostream>
#include <windows.h>

namespace tkl
{

time::time(double _scale)
{
    scale = _scale;
    update_freq();
    QueryPerformanceCounter(&buffer);
    old = buffer.QuadPart;
}

time::~time()
{
}

void time::update_freq()
{
    if (!QueryPerformanceFrequency(&buffer))
        throw "Counter error";

    frequency = double(buffer.QuadPart) / 1000.;
}

void time::update()
{
    QueryPerformanceCounter(&buffer);
    delta_unscaled = double(buffer.QuadPart - old) / frequency;
    old = buffer.QuadPart;
    count_unscaled += delta_unscaled;
    delta_scaled = delta_unscaled * scale;
    count_scaled += delta_scaled;
    update_freq();
}

}; // namespace tkl
