#pragma once

namespace Ecs {
  class Component {
  protected:
    static int _idCount;
  };

  template<typename T>
  class TemplateComponent : public Component {
  public:
    static int getId() {
      static int id = Ecs::Component::_idCount++;
      return id;
    }
  };
}
