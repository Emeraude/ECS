#pragma once

#include <vector>
#include "Component.hpp"
#include "Exceptions.hpp"

namespace Ecs {
  class Entity {
    std::vector<Ecs::BaseComponent> _components[Ecs::MAX_COMPONENTS];
    Ecs::ComponentMask _componentMask;

    template<typename T> T& getComponent() const;
    template<typename T> bool hasComponent() const;
    template<typename T> void removeComponent();
  };
}

template<typename T>
T& Ecs::Entity::getComponent() const {
  if (hasComponent<T>() == false)
    __throw(Ecs::Exception::Entity, "Component not found");
  return _components[T::getId()];
}

template<typename T>
bool Ecs::Entity::hasComponent() const {
  return _componentMask[T::getId()];
}

template<typename T>
void Ecs::Entity::removeComponent() {
  if (hasComponent<T>() == false)
    __throw(Ecs::Exception::Entity, "Component not found");
  _componentMask[T::getId()] = false;
  return _componentMask[T::getId()];
}
