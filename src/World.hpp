#pragma once

#include <chrono>
#include <list>
#include <thread>
#include <utility>
#include <vector>
#include "Entity.hpp"
#include "System.hpp"

namespace Ecs {
  class World {
  private:
    std::list<Ecs::Entity *> _entities;
    std::vector<Ecs::System::Base *> _systems;
    bool _stopped;
    double _time;

  public:
    World();
    ~World();
    template<typename T, typename ... U> void addSystem(U && ... args);
    template<typename T> bool hasSystem();
    template<typename T> void removeSystem();

    void run();
    void update();
    void stop();
    void addEntity(Ecs::Entity *e);
    std::list<Ecs::Entity *>& getEntities();
    std::vector<Ecs::System::Base *>& getSystems();
  };
}

template<typename T, typename ... U>
void Ecs::World::addSystem(U && ... args) {
  if (hasSystem<T>() == true)
    __throw(Ecs::Exception::World, "System already exists");

  unsigned int id = Ecs::System::Template<T>::getId();
  if (id >= _systems.size())
    _systems.resize(id + 1);
  _systems[id] = new T(std::forward<U>(args) ...);
}

template<typename T>
bool Ecs::World::hasSystem() {
  unsigned int id = Ecs::System::Template<T>::getId();
  return id < _systems.size() && _systems[id];
}

template<typename T>
void Ecs::World::removeSystem() {
  if (hasSystem<T>() == false)
    __throw(Ecs::Exception::World, "System not found");
  delete _systems[Ecs::System::Template<T>::getId()];
  _systems[Ecs::System::Template<T>::getId()] = 0;
}
