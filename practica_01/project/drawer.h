#pragma once

#include "drawable.h"
#include "rect.h"
#include <vector>

class Drawer {
private:                           // SINGLETON
  Drawer();                        //
  static Drawer instance;          //
public:                            //
  Drawer(const Drawer &) = delete; //
  static Drawer &Get();            //

private:
  std::vector<Drawable *> each = std::vector<Drawable *>();

public:
  static void Subscribe(Drawable *drawable);
  static void UnSubscribe(const Drawable *drawable);
  static const std::vector<Drawable *> *GetDrawables();
};
