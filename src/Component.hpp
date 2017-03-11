#pragma once

namespace Ecs {
  class Component {
  protected:
    static unsigned int _idCount;
  };

  template<typename T>
  class TemplateComponent : public Component {
  public:
    static unsigned int getId() {
      static unsigned int id = Ecs::Component::_idCount++;
      return id;
    }
  };
}
