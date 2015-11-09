#pragma once

#include <utility>
#include <vector>
#include "Component.hpp"
#include "Exceptions.hpp"

namespace Ecs {
  class Entity {
  private:
    std::vector<Ecs::Component::Base*> _components;

  public:
    Entity();
    Entity(Entity const& o);
    ~Entity();
    template<typename T> T* getComponent();
    template<typename T> bool hasComponent() const;
    template<typename T> void removeComponent();
    template<typename T, typename ... U> void addComponent(U && ... args);
  };
}

template<typename T>
T* Ecs::Entity::getComponent() {
  if (hasComponent<T>() == false)
    __throw(Ecs::Exception::Entity, "Component not found");
  return static_cast<T *>(_components[Ecs::Component::Template<T>::getId()]);
}

template<typename T>
bool Ecs::Entity::hasComponent() const {
  unsigned int id = Ecs::Component::Template<T>::getId();
  return id < _components.capacity() && _components[id];
}

template<typename T>
void Ecs::Entity::removeComponent() {
  if (hasComponent<T>() == false)
    __throw(Ecs::Exception::Entity, "Component not found");
  delete _components[Ecs::Component::Template<T>::getId()];
  _components[Ecs::Component::Template<T>::getId()] = 0;
}

template<typename T, typename ... U>
void Ecs::Entity::addComponent(U && ... args) {
  if (hasComponent<T>() == true)
    __throw(Ecs::Exception::Entity, "Component already exists");

  unsigned int id = Ecs::Component::Template<T>::getId();
  if (id >= _components.capacity())
    _components.resize(id + 1);
  _components[Ecs::Component::Template<T>::getId()] = new T(std::forward<U>(args) ...);
}
