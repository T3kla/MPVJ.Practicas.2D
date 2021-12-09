#pragma once

#include "color.h"

class Drawable {
public:
  Color color{1.f, 1.f, 1.f, 1.f};
  virtual void Draw() const = 0;
};
