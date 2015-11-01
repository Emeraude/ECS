#pragma once

#include <utility>
#include <vector>
#include "Component.hpp"
#include "Exceptions.hpp"

namespace Ecs {
  class Entity {
  private:
    std::vector<Ecs::BaseComponent> _components[Ecs::MAX_COMPONENTS];
    Ecs::ComponentMask _componentMask;

  public:
    template<typename T> T& getComponent() const;
    template<typename T> bool hasComponent() const;
    template<typename T> void removeComponent();
    template<typename T, typename ... U> void addComponent(U && ... args);
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
}

template<typename T, typename ... U>
void Ecs::Entity::addComponent(U && ... args) {
  T component(std::forward<U>(args) ...);
  _componentMask[component.getId()] = true;
  _components[component.getId()] = component;
}
