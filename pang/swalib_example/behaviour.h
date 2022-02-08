#pragma once

struct Behaviour {
  virtual void Awake() = 0;
  virtual void Start() = 0;
  virtual void Update() = 0;
  virtual void Fixed() = 0;
  virtual void Quit() = 0;
};
