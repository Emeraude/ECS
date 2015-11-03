#include "World.hpp"

Ecs::World::~World() {
  for (auto& it: _systems)
    delete it;
}
