#include "time.h"
#include <iostream>
#include <windows.h>

namespace tkl
{

time time::instance;

time::time()
{
    update_freq();
    QueryPerformanceCounter(&buffer);
    old = buffer.QuadPart;
}

time &time::get()
{
    return instance;
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

double time::delta_unscl()
{
    return get().delta_unscaled;
}

double time::time_unscl()
{
    return get().count_unscaled;
}

double time::delta_scl()
{
    return get().delta_scaled;
}

double time::time_scl()
{
    return get().count_scaled;
}

double time::get_scale()
{
    return get().scale;
}

void time::set_scale(const double &_scale)
{
    get().scale = _scale;
}

}; // namespace tkl
