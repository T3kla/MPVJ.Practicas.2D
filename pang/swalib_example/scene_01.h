#pragma once

#include "behaviour.h"
#include "entity.h"
#include <memory>
#include <vector>

constexpr int BALLS_NUM = 100;
constexpr float MAX_SPEED = 100.f;
constexpr float MAX_RADIUS = 20.f;
constexpr float MIN_RADIUS = 10.f;

class Scene_01 : public Behaviour {
private:                               // SINGLETON
  Scene_01();                          //
  static Scene_01 instance;            //
public:                                //
  Scene_01(const Scene_01 &) = delete; //

public:
  static std::vector<Entity *> reg;

  static void Load();
  static std::vector<Entity *> &GetRegistry();

private:
  virtual void Awake() override;
  virtual void Start() override;
  virtual void Update() override;
  virtual void Fixed() override;
  virtual void Quit() override;
};
