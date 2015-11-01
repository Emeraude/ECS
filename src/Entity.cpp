#include "Entity.hpp"

Ecs::Entity::Entity() : _components(Ecs::MAX_COMPONENTS, 0) {}

Ecs::Entity::~Entity() {
  for (int i = 0; i < Ecs::MAX_COMPONENTS; ++i)
    if (_components[i])
      delete _components[i];
}
