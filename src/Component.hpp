#pragma once

#include <bitset>

namespace Ecs {

#ifdef __MAX_COMPONENTS
  static const int MAX_COMPONENTS = __MAX_COMPONENTS;
#else
  static const int MAX_COMPONENTS = 256;
#endif

  class BaseComponent {
  private:
    int _id;

  public:
    BaseComponent();
    int getId() const;
  };

  typedef std::bitset<Ecs::MAX_COMPONENTS> ComponentMask;
}
