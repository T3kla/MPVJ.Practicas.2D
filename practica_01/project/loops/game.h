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
  private:                       // SINGLETON
    game();                      //
    static game instance;        //
  public:                        //
    game(const game &) = delete; //
    static game &get();          //

  private:
    time m_time = time(1.);
    double m_fx_count = 0.;

    std::vector<double> m_avg_up = std::vector<double>(TIME_AVG_SAMPLES, 0);
    std::vector<double> m_avg_fx = std::vector<double>(TIME_AVG_SAMPLES, 0);
    double m_avg_buffer_up = 0.;
    double m_avg_buffer_fx = 0.;
    unsigned int m_avg_up_it = 0u;
    unsigned int m_avg_fx_it = 0u;

  public:
    void init();
    void loop();
    void exit();

    void update(double dt = 0.);
    void fixed(double dt = 0.);

    void print_fps();
};

} // namespace tkl
