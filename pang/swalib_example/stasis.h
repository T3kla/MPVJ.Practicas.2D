#pragma once

#include <windows.h>

class Stasis {
private:                            // SINGLETONE STUFF
  Stasis(const double &scale = 1.); //
  static Stasis instance;           //
public:                             //
  Stasis(const Stasis &) = delete;  //
  static Stasis &Get();             //

private:
  LARGE_INTEGER buffer = LARGE_INTEGER();
  long long old = 0ll;

  double freq = 0.;
  double scale = 1.;

  double time = 0.;
  double delta = 0.;

  double timeScaled = 0.;
  double deltaScaled = 0.;

  static void RefreshFreq();

public:
  static void RefreshTime();

  static const double &GetTime();
  static const double &GetDelta();

  static const double &GetTimeScaled();
  static const double &GetDeltaScaled();

  static void SetScale(const double &scale);
  static const double &GetScale();
};
