#pragma once
#include <windows.h>

namespace tkl
{

class time
{
  private:                       // SINGLETONE STUFF
    time();                      //     Singletone constructor
    static time instance;        //     Singletone single instance
  public:                        //
    time(const time &) = delete; //     Singletone copy constructor deletion
    static time &get();          //     Singletone getter

  private:
    void update();
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
    static double delta_unscl();
    static double time_unscl();
    static double delta_scl();
    static double time_scl();
    static double get_scale();
    static void set_scale(const double &_scale);
};

}; // namespace tkl
