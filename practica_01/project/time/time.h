#pragma once
#include <windows.h>

namespace tkl
{

class time
{
  private:
    void update_freq();

    LARGE_INTEGER buffer = LARGE_INTEGER();
    double frequency = 0.;
    long long old = 0ll;

    double delta_unscaled = 0.;
    double count_unscaled = 0.;
    double delta_scaled = 0.;
    double count_scaled = 0.;
    double scale = 1.;

  public:
    time(double _scale = 0.);
    ~time();

    void update();

    double get_delta_unscaled()
    {
        return delta_unscaled;
    }

    double get_count_unscaled()
    {
        return count_unscaled;
    }

    double get_delta_scaled()
    {
        return delta_scaled;
    }

    double get_count_scaled()
    {
        return count_scaled;
    }

    double get_scale()
    {
        return scale;
    }

    void set_scale(double _scale)
    {
        scale = _scale;
    }
};

}; // namespace tkl
