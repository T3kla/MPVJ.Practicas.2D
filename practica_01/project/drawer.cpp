#include "drawer.h"

Drawer Drawer::instance;

Drawer::Drawer() {}

Drawer &Drawer::Get() { return instance; }

void Drawer::Subscribe(Drawable *drawable) {
  auto &instance = Drawer::Get();

  // Duplication guard
  auto it = std::find(instance.each.begin(), instance.each.end(), drawable);
  if (it != instance.each.end())
    return;

  instance.each.emplace_back(drawable);
}

void Drawer::UnSubscribe(const Drawable *drawable) {
  auto &instance = Drawer::Get();

  // Not found guard
  auto it = std::find(instance.each.begin(), instance.each.end(), drawable);
  if (it == instance.each.end())
    return;

  instance.each.erase(it);
}

const std::vector<Drawable *> *Drawer::GetDrawables() { return &Get().each; }
