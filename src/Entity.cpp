#include "Entity.hpp"

Ecs::Entity::~Entity() {
  for (auto *it: _components)
    delete it;
}
