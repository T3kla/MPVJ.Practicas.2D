#pragma once

#include "behaviour.h"

constexpr int BALLS_NUM = 100;
constexpr float MAX_SPEED = 100.f;
constexpr float MAX_RADIUS = 20.f;
constexpr float MIN_RADIUS = 10.f;

class Scene_01 : public Behaviour
{
    static Scene_01 Instance;

  private:
    Scene_01(){};

  public:
    Scene_01(const Scene_01 &) = delete;

    virtual void Awake() override{};
    virtual void Start() override;
    virtual void Update() override{};
    virtual void Fixed() override{};
    virtual void Quit() override;

    static void Load();
};
