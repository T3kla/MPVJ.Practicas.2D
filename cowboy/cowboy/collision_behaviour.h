#pragma once

class Collider;

class CollisionBehaviour {
  //virtual void OnCollisionEnter(Entity *entity){};
  //virtual void OnCollisionStay(Entity *entity){};
  //virtual void OnCollisionExit(Entity *entity){};

  virtual void OnTriggerEnter(Collider *collider) = 0;
  virtual void OnTriggerStay(Collider *collider) = 0;
  virtual void OnTriggerExit(Collider *collider) = 0;
};
