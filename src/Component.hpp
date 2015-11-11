#pragma once

namespace Ecs {
  namespace Component {
    class Base {};
    static int _idCount = 0;

    template<typename T>
    class Template : public Base {
    public:
      static int getId() {
	static int id = Ecs::Component::_idCount++;
	return id;
      }
    };
  }
}
