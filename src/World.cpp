#include "World.hpp"

Ecs::World::World() : _stopped(true) {}

Ecs::World::~World() {
  for (auto& it: _systems)
    delete it.first;
  for (auto& it: _entities)
    delete it;
}

void Ecs::World::run() {
  _stopped = false;
  std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
  while (_stopped == false) {
    auto diff = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - startTime).count();
    for (auto& it: _systems) {
      if (it.first && it.second < diff) {
	  it.second += it.first->getMs() / 1000.0;
	  it.first->update(*this);
	}
    }
    std::this_thread::sleep_for(std::chrono::microseconds(100));
  }
}

void Ecs::World::stop() {
  _stopped = true;
}

std::list<Ecs::Entity *>& Ecs::World::getEntities() {
  return _entities;
}

void Ecs::World::addEntity(Ecs::Entity const& e) {
  _entities.push_back(new Ecs::Entity(e));
}

void Ecs::World::addEntity(Ecs::Entity *e) {
  _entities.push_back(e);
}
