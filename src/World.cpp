#include "World.hpp"

Ecs::World::World() : _stopped(true), _sleepDuration(std::chrono::milliseconds(10)) {}

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
    it->update(*this);
  _time = std::chrono::steady_clock::now() - start;
  std::this_thread::sleep_for(_sleepDuration - _time);
}

void Ecs::World::stop() {
  _stopped = true;
}

void Ecs::World::lock() {
  _mutex.lock();
}

void Ecs::World::unlock() {
  _mutex.unlock();
}

std::vector<Ecs::Entity *>& Ecs::World::getEntities() {
  return _entities;
}

Ecs::Entity *Ecs::World::get(unsigned int const i) {
  return _entities.at(i);
}

unsigned int Ecs::World::add(Ecs::Entity *e) {
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

void Ecs::World::remove(std::vector<Ecs::Entity*>::iterator it) {
  delete *it;
  *it = NULL;
  _garbage.push(std::distance(_entities.begin(), it));
}

void Ecs::World::remove(unsigned int const i) {
  delete _entities[i];
  _entities[i] = new Ecs::Entity;
  _garbage.push(i);
}

void Ecs::World::setSleepDuration(std::chrono::nanoseconds const& sleepDuration) {
  _sleepDuration = sleepDuration;
}

std::chrono::nanoseconds Ecs::World::getSleepDuration() const {
  return _sleepDuration;
}
