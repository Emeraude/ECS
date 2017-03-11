#pragma once

#include <chrono>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include "Entity.hpp"
#include "System.hpp"

namespace Ecs {
  class World {
  private:
    std::vector<Ecs::Entity *> _entities;
    std::vector<Ecs::System *> _systems;
    std::queue<int> _garbage;
    std::mutex _mutex;
    bool _stopped;
    std::chrono::nanoseconds _time;
    std::chrono::nanoseconds _sleepDuration;

  public:
    World();
    ~World();
    template<typename T> T* get();
    template<typename T, typename ... U> void add(U && ... args);
    template<typename T> bool has() const;
    template<typename T> void remove();

    void run();
    void update();
    void stop();
    void lock();
    void unlock();

    unsigned int add(Ecs::Entity *e);
    Ecs::Entity *get(unsigned int const id);
    void remove(std::vector<Ecs::Entity*>::iterator it);
    void remove(unsigned int const i);
    std::vector<Ecs::Entity *>& getEntities();

    void setSleepDuration(std::chrono::nanoseconds const& sleepDuration);
    std::chrono::nanoseconds getSleepDuration() const;
  };
}

template<typename T>
T* Ecs::World::get() {
  if (has<T>() == false)
    __throw(Ecs::Exception::World, "System not found");
  return static_cast<T *>(_systems[Ecs::TemplateSystem<T>::getId()]);
}

template<typename T, typename ... U>
void Ecs::World::add(U && ... args) {
  if (has<T>() == true)
    __throw(Ecs::Exception::World, "System already exists");

  unsigned int id = Ecs::TemplateSystem<T>::getId();
  if (id >= _systems.size())
    _systems.resize(id + 1);
  _systems[id] = new T(std::forward<U>(args) ...);
}

template<typename T>
bool Ecs::World::has() const {
  unsigned int id = Ecs::TemplateSystem<T>::getId();
  return id < _systems.size() && _systems[id];
}

template<typename T>
void Ecs::World::remove() {
  if (has<T>() == false)
    __throw(Ecs::Exception::World, "System not found");
  delete _systems[Ecs::TemplateSystem<T>::getId()];
  _systems[Ecs::TemplateSystem<T>::getId()] = 0;
}
