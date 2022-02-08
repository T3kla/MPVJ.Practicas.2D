#pragma once

#include "vec.h"

class EngineInput {
  friend class Engine;

private:                                     // SINGLETON
  EngineInput();                             //
  static EngineInput instance;               //
public:                                      //
  EngineInput(const EngineInput &) = delete; //
  static EngineInput &Get();                 //

private:
  Vec2 mousePos = {0.f, 0.f};
  Vec2 mouseDelta = {0.f, 0.f};

  static void Awake();
  static void Start();
  static void Update();
  static void Fixed();
  static void Quit();

public:
  static Vec2 GetMousePos();
  static Vec2 GetMouseDelta();
};
