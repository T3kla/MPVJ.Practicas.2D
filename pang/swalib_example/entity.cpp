#include "entity.h"

Entity::Entity() {}

Entity::~Entity() { RemoveAllComponents(); }

void Entity::RemoveAllComponents() {
  for (auto &cmp : components)
    delete cmp.second;
  components.clear();
}
