#pragma once

#include "../engine/engine.h"
#include "../time/time.h"
#include <vector>

namespace tkl
{

constexpr auto TIME_FIXED_FREQ = (1. / 60.) * 1000.;
constexpr auto TIME_AVG_SAMPLES = 64u;

class game
{
  private:
    engine *m_engine;
    time m_time;
    double m_fx_count = 0.;

    std::vector<double> m_avg_up;
    std::vector<double> m_avg_fx;
    double m_avg_buffer_up;
    double m_avg_buffer_fx;
    unsigned int m_avg_up_it = 0u;
    unsigned int m_avg_fx_it = 0u;

  public:
    game(engine *eng);

    void init();
    void loop();
    void exit();

    void update(double dt = 0.);
    void fixed(double dt = 0.);

    void print_fps();
};

} // namespace tkl
