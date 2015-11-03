#include "System.hpp"

void Ecs::System::Base::setMs(float ms) {
  _ms = ms;
}

float Ecs::System::Base::getMs() const {
  return _ms;
}
