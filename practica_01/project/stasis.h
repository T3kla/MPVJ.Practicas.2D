#pragma once

#include <windows.h>

class Stasis
{
    friend class Engine;

  private:                           // SINGLETONE STUFF
    Stasis();                        //
    static Stasis instance;          //
  public:                            //
    Stasis(const Stasis &) = delete; //
    static Stasis &Get();            //

  private:
    void Update();
    void RefreshFreq();

    LARGE_INTEGER buffer = LARGE_INTEGER();
    double freq = 0.;
    long long old = 0ll;

    double deltaUnscaled = 0.;
    double timeUnscaled = 0.;
    double deltaScaled = 0.;
    double timeScaled = 0.;
    double scale = 1.;

  public:
    static double GetDeltaUnscaled();
    static double GetTimeUnscaled();
    static double GetDeltaScaled();
    static double GetTimeScaled();
    static double GetScale();
    static void SetScale(const double &_scale);
};
