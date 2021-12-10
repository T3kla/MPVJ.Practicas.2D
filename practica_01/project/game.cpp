#include "game.h"
#include "stasis.h"
#include <iostream>

Game Game::instance;

Game::Game() {}

Game &Game::Get() { return instance; }

void Game::Subscribe(GameObject *gameObject) {
  // Duplication guard
  auto it = std::find(instance.each.begin(), instance.each.end(), gameObject);
  if (it != instance.each.end())
    return;

  instance.each.emplace_back(gameObject);
}

void Game::UnSubscribe(const GameObject *gameObject) {
  // Not found guard
  auto it = std::find(instance.each.begin(), instance.each.end(), gameObject);
  if (it == instance.each.end())
    return;

  instance.each.erase(it);
}

const std::vector<GameObject *> *Game::GetGameObjects() { return &Get().each; }

void Game::Init() { Start(); }

void Game::Exit() { End(); }

void Game::Start() {
  for (auto &&go : *Game::Get().GetGameObjects())
    go->Start();
}

void Game::Update() {
  for (auto &&go : *Game::Get().GetGameObjects())
    go->Update();
}

void Game::Fixed() {
  for (auto &&go : *Game::Get().GetGameObjects())
    go->Fixed();
}

void Game::End() {
  for (auto &&go : *Game::Get().GetGameObjects())
    go->End();
}
