#pragma once

struct Player {
  int health = 3;
  float speed = 100.f;
  char *state = nullptr;
  bool reversed = false;
};
