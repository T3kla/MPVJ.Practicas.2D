#pragma once

#include "entity.h"

class EngineRender {
  friend class Engine;

private:                                       // SINGLETON
  EngineRender();                              //
  static EngineRender instance;                //
public:                                        //
  EngineRender(const EngineRender &) = delete; //
  static EngineRender &Get();                  //

private:
  static void Awake();
  static void Start();
  static void Update();
  static void Fixed();
  static void Quit();
};
