#include "System.hpp"

namespace Ecs {
  namespace System {
    int _idCount = 0;
  }
}

void Ecs::System::Base::setMs(float ms) {
  _ms = ms;
}

float Ecs::System::Base::getMs() const {
  return _ms;
}
