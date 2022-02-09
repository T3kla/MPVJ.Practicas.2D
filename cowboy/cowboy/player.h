#pragma once

struct Player {
  bool enable = true;

  int health = 0;

  // Movement
  float maxSpeed = 0.f;
  float acceleration = 0.f;

  // Shooting
  float shootCD = 0.f;
};
