#pragma once

namespace Ecs {
  class World;

  class System {
  public:
    virtual ~System() {}
    virtual void update(Ecs::World &world) = 0;

  protected:
    static int _idCount;
  };

  template<typename T>
  class TemplateSystem : public System {
  public:
    static int getId() {
      static int id = Ecs::System::_idCount++;
      return id;
    }
  };
}
