#pragma once

#include "behaviour.h"
#include <vector>

class EngineGame {
  friend class Engine;

private:                                   // SINGLETON
  EngineGame();                            //
  static EngineGame instance;              //
public:                                    //
  EngineGame(const EngineGame &) = delete; //
  static EngineGame &Get();                //

private:
  static void Awake();
  static void Start();
  static void Update();
  static void Fixed();
  static void Quit();

  std::vector<Behaviour *> each = std::vector<Behaviour *>();

public:
  static void Subscribe(Behaviour *gameObject);
  static void UnSubscribe(const Behaviour *gameObject);
  static const std::vector<Behaviour *> *GetGameObjects();
};
