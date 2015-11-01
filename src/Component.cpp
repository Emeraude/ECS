#include "Component.hpp"
#include "Exceptions.hpp"

Ecs::BaseComponent::BaseComponent() {
  static int _idCount = 0;
  _id = _idCount++;
  if (_idCount >= Ecs::MAX_COMPONENTS)
    __throw(Ecs::Exception::Component, "Too many components");
}

int Ecs::BaseComponent::getId() const {
  return _id;
}
