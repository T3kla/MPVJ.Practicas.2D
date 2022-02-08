#include "stasis.h"
#include <windows.h>

Stasis Stasis::instance;

Stasis::Stasis(const double &scale) {
  this->scale = scale;
  RefreshFreq();
  QueryPerformanceCounter(&buffer);
  old = buffer.QuadPart;
}

Stasis &Stasis::Get() { return instance; }

void Stasis::RefreshFreq() {
  if (!QueryPerformanceFrequency(&instance.buffer))
    throw "Counter error";

  instance.freq = double(instance.buffer.QuadPart) / 1000.;
}

void Stasis::RefreshTime() {
  QueryPerformanceCounter(&instance.buffer);

  instance.delta =
      double(instance.buffer.QuadPart - instance.old) / instance.freq;
  instance.deltaScaled = instance.delta * instance.scale;

  instance.old = instance.buffer.QuadPart;

  instance.time += instance.delta;
  instance.timeScaled += instance.delta * instance.scale;

  RefreshFreq();
}

const double &Stasis::GetTime() { return instance.time; }
const double &Stasis::GetDelta() { return instance.delta; }

const double &Stasis::GetTimeScaled() { return instance.timeScaled; }
const double &Stasis::GetDeltaScaled() { return instance.deltaScaled; }

void Stasis::SetScale(const double &scale) { instance.scale = scale; }
const double &Stasis::GetScale() { return instance.scale; }
