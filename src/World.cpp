#include "World.hpp"

Ecs::World::World() : _stopped(false) {}

Ecs::World::~World() {
  for (auto& it: _systems)
    delete it.first;
}

void Ecs::World::run() {
  std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
  while (_stopped == false) {
    auto diff = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - startTime).count();
    for (auto& it: _systems) {
      if (it.first && it.second < diff) {
	  it.second += it.first->getMs() / 1000.0;
	  it.first->update();
	}
    }
    std::this_thread::sleep_for(std::chrono::microseconds(100));
  }
}
