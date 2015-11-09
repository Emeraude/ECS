#include "Entity.hpp"

Ecs::Entity::Entity() {}

Ecs::Entity::Entity(Entity const& o) {
  _components.resize(o._components.size());
  for (unsigned int i = 0; i < o._components.size(); ++i)
    _components[i] = new Ecs::Component::Base(*o._components[i]);
}

Ecs::Entity::~Entity() {
  for (auto& it: _components)
    delete it;
}
