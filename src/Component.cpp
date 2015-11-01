#include "Component.hpp"

Ecs::BaseComponent::BaseComponent() {
  static int _idCount = 0;
  _id = _idCount++;
}

int Ecs::BaseComponent::getId() const {
  return _id;
}
