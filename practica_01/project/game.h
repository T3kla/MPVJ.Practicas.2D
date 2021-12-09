#pragma once

#include "gameobject.h"
#include <vector>

class Game {
  friend class Engine;

private:                       // SINGLETON
  Game();                      //
  static Game instance;        //
public:                        //
  Game(const Game &) = delete; //
  static Game &Get();          //

private:
  std::vector<GameObject *> each = std::vector<GameObject *>();

  void Init();
  void Exit();

  void Start();  // GameObject calls
  void Update(); //
  void Fixed();  //
  void End();    //

public:
  static void Subscribe(GameObject *gameObject);
  static void UnSubscribe(const GameObject *gameObject);
  static const std::vector<GameObject *> *GetGameObjects();
};
