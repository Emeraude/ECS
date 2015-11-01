#pragma once

#include <bitset>

namespace Ecs {

#ifndef __MAX_COMPONENTS
  static const int MAX_COMPONENTS = 256;
#else
  static const int MAX_COMPONENTS = __MAX_COMPONENTS;
#endif

  class BaseComponent {
  private:
    int _id;

  public:
    BaseComponent();
    int getId() const;
  };

  using ComponentMask = std::bitset<Ecs::MAX_COMPONENTS>;
}
