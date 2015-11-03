#include "System.hpp"

void Ecs::System::Base::setMs(int ms) {
  _ms = ms;
}

int Ecs::System::Base::getMs(void) const {
  return _ms;
}
