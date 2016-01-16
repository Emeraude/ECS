#pragma once

namespace Ecs {
  class World;

  namespace System {
    class Base {
    public:
      virtual ~Base() {}
      virtual void update(Ecs::World &world) = 0;
    };
    extern int _idCount;

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
