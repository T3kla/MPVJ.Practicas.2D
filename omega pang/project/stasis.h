#pragma once

class Stasis
{
    static Stasis Instance;

  private:
    Stasis(const double &scale = 1.);

    long long old = 0ll;

    double freq = 0.;
    double scale = 1.;

    double time = 0.;
    double delta = 0.;

    double timeScaled = 0.;
    double deltaScaled = 0.;

    static void RefreshFreq();

  public:
    Stasis(const Stasis &) = delete;

    static void RefreshTime();

    static const double &GetTime();
    static const double &GetDelta();

    static const double &GetTimeScaled();
    static const double &GetDeltaScaled();

    static void SetScale(const double &scale);
    static const double &GetScale();
};
