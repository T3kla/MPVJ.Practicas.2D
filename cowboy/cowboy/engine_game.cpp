#include "engine_game.h"
#include "stasis.h"
#include <iostream>

EngineGame EngineGame::instance;

EngineGame::EngineGame() {}

EngineGame &EngineGame::Get() { return instance; }

void EngineGame::Subscribe(Behaviour *gameObject) {
  // Duplication guard
  auto it = std::find(instance.each.begin(), instance.each.end(), gameObject);
  if (it != instance.each.end())
    return;

  instance.each.emplace_back(gameObject);
}

void EngineGame::UnSubscribe(const Behaviour *gameObject) {
  // Not found guard
  auto it = std::find(instance.each.begin(), instance.each.end(), gameObject);
  if (it == instance.each.end())
    return;

  instance.each.erase(it);
}

const std::vector<Behaviour *> *EngineGame::GetGameObjects() {
  return &Get().each;
}

void EngineGame::Awake() {
  for (auto &&go : *instance.GetGameObjects())
    go->Awake();
}

void EngineGame::Start() {
  for (auto &&go : *instance.GetGameObjects())
    go->Start();
}

void EngineGame::Update() {
  for (auto &&go : *instance.GetGameObjects())
    go->Update();
}

void EngineGame::Fixed() {
  for (auto &&go : *instance.GetGameObjects())
    go->Fixed();
}

void EngineGame::Quit() {
  for (auto &&go : *instance.GetGameObjects())
    go->Quit();
}
