#pragma once

class GameObject {
public:
  virtual void Start() = 0;
  virtual void Update() = 0;
  virtual void Fixed() = 0;
  virtual void End() = 0;
};
