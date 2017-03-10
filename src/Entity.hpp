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
    ~Entity();
    template<typename T> T* get();
    template<typename T> bool has() const;
    template<typename T> void remove();
    template<typename T, typename ... U> void add(U && ... args);
  };
}

template<typename T>
T* Ecs::Entity::get() {
  if (has<T>() == false)
    __throw(Ecs::Exception::Entity, "Component not found");
  return static_cast<T *>(_components[Ecs::Component::Template<T>::getId()]);
}

template<typename T>
bool Ecs::Entity::has() const {
  unsigned int id = Ecs::Component::Template<T>::getId();
  return id < _components.size() && _components[id];
}

template<typename T>
void Ecs::Entity::remove() {
  if (has<T>() == false)
    __throw(Ecs::Exception::Entity, "Component not found");
  delete _components[Ecs::Component::Template<T>::getId()];
  _components[Ecs::Component::Template<T>::getId()] = 0;
}

template<typename T, typename ... U>
void Ecs::Entity::add(U && ... args) {
  if (has<T>() == true)
    __throw(Ecs::Exception::Entity, "Component already exists");

  unsigned int id = Ecs::Component::Template<T>::getId();
  if (id >= _components.size())
    _components.resize(id + 1);
  _components[id] = new T(std::forward<U>(args) ...);
}
