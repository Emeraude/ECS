#pragma once

namespace Ecs {
  class World;

  namespace System {
    class Base {
    private:
      float _ms;

    public:
      virtual ~Base() {}
      virtual void update(Ecs::World &world) = 0;

      void setMs(float);
      float getMs() const;
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
