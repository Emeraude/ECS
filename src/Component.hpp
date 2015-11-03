#pragma once

#include <bitset>
#include "Exceptions.hpp"

namespace Ecs {

#ifdef __MAX_COMPONENTS
  static const int MAX_COMPONENTS = __MAX_COMPONENTS;
#else
  static const int MAX_COMPONENTS = 256;
#endif

  namespace Component {
    class Base {};
    static int _idCount = 0;

    template<typename T>
    class Template : public Base {
    public:
      static int getId() {
	static int id = Ecs::Component::_idCount++;
	if (_idCount >= Ecs::MAX_COMPONENTS)
	  __throw(Ecs::Exception::Component, "Too many components");
	return id;
      }
    };
  }
}
