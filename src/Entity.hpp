#pragma once

#include <utility>
#include <vector>
#include "Component.hpp"
#include "Exceptions.hpp"

namespace Ecs {
  class Entity {
  private:
    std::vector<Ecs::Component::Base> _components;
    Ecs::ComponentMask _componentMask;

  public:
    Entity();
    template<typename T> T& getComponent();
    template<typename T> bool hasComponent() const;
    template<typename T> void removeComponent();
    template<typename T, typename ... U> void addComponent(U && ... args);
  };
}

template<typename T>
T& Ecs::Entity::getComponent() {
  if (hasComponent<T>() == false)
    __throw(Ecs::Exception::Entity, "Component not found");
  return _components[Ecs::Component::Template<T>::getId()];
}

template<typename T>
bool Ecs::Entity::hasComponent() const {
  return _componentMask[Ecs::Component::Template<T>::getId()];
}

template<typename T>
void Ecs::Entity::removeComponent() {
  if (hasComponent<T>() == false)
    __throw(Ecs::Exception::Entity, "Component not found");
  _componentMask[Ecs::Component::Template<T>::getId()] = false;
}

template<typename T, typename ... U>
void Ecs::Entity::addComponent(U && ... args) {
  int id = Ecs::Component::Template<T>::getId();
  T comp(std::forward<U>(args) ...);
  _componentMask[id] = true;
  _components[id] = comp;
}
