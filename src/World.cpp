#include "World.hpp"

Ecs::World::World() : _stopped(true) {}

Ecs::World::~World() {
  for (auto *it: _systems)
    delete it;
  for (auto *it: _entities)
    delete it;
}

void Ecs::World::run() {
  _stopped = false;
  while (_stopped == false)
    this->update();
}

void Ecs::World::update() {
  static int i = 0;
  std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

  for (auto *it: _systems)
    if (it)
      it->update(*this);
  _time = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - start).count();
  ++i;
  std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(10000 - _time * 1000)));
}

void Ecs::World::stop() {
  _stopped = true;
}

std::list<Ecs::Entity *>& Ecs::World::getEntities() {
  return _entities;
}

std::vector<Ecs::System::Base *>& Ecs::World::getSystems() {
  return _systems;
}

void Ecs::World::addEntity(Ecs::Entity *e) {
  _entities.push_back(e);
}
