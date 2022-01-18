#pragma once

struct Behaviour {
  Behaviour();
  virtual ~Behaviour();

  virtual void Awake(){};
  virtual void Start(){};
  virtual void Update(){};
  virtual void Fixed(){};
  virtual void Quit(){};
};
