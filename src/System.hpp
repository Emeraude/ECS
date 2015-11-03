#pragma once

namespace Ecs {
  namespace System {
    class Base {
    public:
      virtual ~Base() {}
      virtual void update() = 0;
    };
    static int _idCount = 0;

    template<typename T>
    class Template : public Base {
    public:
      static int getId() {
	static int id = Ecs::System::_idCount++;
	return id;
      }
    };
  }
}
