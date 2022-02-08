#pragma once

#include "behaviour.h"

struct Vec2;

class SysBalls : public Behaviour {
  virtual void Awake() override;
  virtual void Start() override;
  virtual void Update() override;
  virtual void Fixed() override;
  virtual void Quit() override;

public:
  SysBalls();
  ~SysBalls();

  static void SysBalls::InstantiateSmaller(const Vec2 &pos, bool right,
                                           char size);
  static void SysBalls::InstantiateL(const Vec2 &pos, bool right);
  static void SysBalls::InstantiateB(const Vec2 &pos, bool right);
  static void SysBalls::InstantiateM(const Vec2 &pos, bool right);
  static void SysBalls::InstantiateS(const Vec2 &pos, bool right);
};
