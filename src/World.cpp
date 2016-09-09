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
  std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

  for (auto *it: _systems)
    if (it)
      it->update(*this);
  _time = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - start).count();
  std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(10000 - _time * 1000)));
}

void Ecs::World::stop() {
  _stopped = true;
}

std::vector<Ecs::Entity *>& Ecs::World::getEntities() {
  return _entities;
}

Ecs::Entity *Ecs::World::getEntity(unsigned int const i) {
  return _entities.at(i);
}

unsigned int Ecs::World::addEntity(Ecs::Entity *e) {
  if (_garbage.empty()) {
    _entities.push_back(e);
    return _entities.size() - 1;
  }
  else {
    unsigned int const id = _garbage.front();
    delete _entities[id];
    _entities[id] = e;
    _garbage.pop();
    return id;
  }
}

void Ecs::World::removeEntity(int i) {
  delete _entities[i];
  _entities[i] = new Ecs::Entity;
  _garbage.push(i);
}
