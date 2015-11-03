#pragma once

#include <chrono>
#include <thread>
#include <utility>
#include <vector>
#include "Entity.hpp"
#include "System.hpp"

namespace Ecs {
  class World {
  private:
    std::vector<Ecs::Entity> _entities;
    std::vector<std::pair<Ecs::System::Base *, double>> _systems;
    bool _stopped;

  public:
    World();
    ~World();
    template<typename T, typename ... U> void addSystem(float ms, U && ... args);
    template<typename T> bool hasSystem();
    template<typename T> void removeSystem();

    void run();
  };
}

template<typename T, typename ... U>
void Ecs::World::addSystem(float ms, U && ... args) {
  if (hasSystem<T>() == true)
    __throw(Ecs::Exception::World, "System already exists");

  unsigned int id = Ecs::System::Template<T>::getId();
  if (id >= _systems.capacity())
    _systems.resize(id + 1);
  _systems[id] = std::pair<Ecs::System::Base *, double>(new T(std::forward<U>(args) ...), 0.0);
  _systems[id].first->setMs(ms);
}

template<typename T>
bool Ecs::World::hasSystem() {
  unsigned int id = Ecs::System::Template<T>::getId();
  return id < _systems.capacity() && _systems[id].first;
}

template<typename T>
void Ecs::World::removeSystem() {
  if (hasSystem<T>() == false)
    __throw(Ecs::Exception::World, "System not found");
  delete _systems[Ecs::System::Template<T>::getId()].first;
  _systems[Ecs::System::Template<T>::getId()].first = 0;
}
